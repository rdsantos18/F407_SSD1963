/**
 * @file SSD1963.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "SSD1963.h"
#include "main.h"
#if USE_SSD1963

#include <stdbool.h>
#include LV_DRV_DISP_INCLUDE
#include LV_DRV_DELAY_INCLUDE

/*********************
 *      DEFINES
 *********************/
#define SSD1963_CMD_MODE     0
#define SSD1963_DATA_MODE    1

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static inline void ssd1963_cmd_mode(void);
static inline void ssd1963_data_mode(void);
static inline void ssd1963_cmd(uint8_t cmd);
static inline void ssd1963_data(uint8_t data);
//static void ssd1963_io_init(void);
static void ssd1963_reset(void);
//static void ssd1963_set_clk(void);
//static void ssd1963_set_tft_spec(void);
//static void ssd1963_init_bl(void);

/**********************
 *  STATIC VARIABLES
 **********************/
static bool cmd_mode = true;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void ssd1963_init(void)
{

    LV_DRV_DISP_CMD_DATA(SSD1963_CMD_MODE);
    cmd_mode = true;

    ssd1963_reset();
    LV_DRV_DELAY_MS(250);


    ssd1963_cmd(0x00E2);    //PLL multiplier, set PLL clock to 120M
    ssd1963_data(0x0023);   //N=0x36 for 6.5M, 0x23 for 10M crystal
    ssd1963_data(0x0002);
    ssd1963_data(0x0004);
    ssd1963_cmd(0x00E0);    // PLL enable
    ssd1963_data(0x0001);
    LV_DRV_DELAY_MS(1);
    ssd1963_cmd(0x00E0);
    ssd1963_data(0x0003);   // now, use PLL output as system clock
    LV_DRV_DELAY_MS(1);
    ssd1963_cmd(0x0001);    // software reset
    LV_DRV_DELAY_MS(1);
    ssd1963_cmd(0x00E6);    //PLL setting for PCLK, depends on resolution

    ssd1963_data(0x0001);  //HX8257C
    ssd1963_data(0x0047);  //HX8257C
    ssd1963_data(0x00B1);  //HX8257C


    ssd1963_cmd(0x00B0);    //LCD SPECIFICATION
    ssd1963_data(0x0020);
    ssd1963_data(0x0000);
    ssd1963_data(((SSD1963_HOR_RES - 1) >> 8) & 0X00FF); //Set HDP
    ssd1963_data((SSD1963_HOR_RES - 1) & 0X00FF);
    ssd1963_data(((SSD1963_VER_RES - 1) >> 8) & 0X00FF); //Set VDP
    ssd1963_data((SSD1963_VER_RES - 1) & 0X00FF);
    ssd1963_data(0x0000);
    LV_DRV_DELAY_MS(1);//Delay10us(5);
    ssd1963_cmd(0x00B4);            //HSYNC
    ssd1963_data((SSD1963_HT >> 8) & 0X00FF); //Set HT
    ssd1963_data(SSD1963_HT & 0X00FF);
    ssd1963_data((SSD1963_HPS >> 8) & 0X00FF); //Set HPS
    ssd1963_data(SSD1963_HPS & 0X00FF);
    ssd1963_data(SSD1963_HPW);              //Set HPW
    ssd1963_data((SSD1963_LPS >> 8) & 0X00FF); //SetLPS
    ssd1963_data(SSD1963_LPS & 0X00FF);
    ssd1963_data(0x0000);

    ssd1963_cmd(0x00B6);            //VSYNC
    ssd1963_data((SSD1963_VT >> 8) & 0X00FF); //Set VT
    ssd1963_data(SSD1963_VT & 0X00FF);
    ssd1963_data((SSD1963_VPS >> 8) & 0X00FF); //Set VPS
    ssd1963_data(SSD1963_VPS & 0X00FF);
    ssd1963_data(SSD1963_VPW);              //Set VPW
    ssd1963_data((SSD1963_FPS >> 8) & 0X00FF); //Set FPS
    ssd1963_data(SSD1963_FPS & 0X00FF);

    ssd1963_cmd(0x00B8);
    ssd1963_data(0x0007);    //GPIO is controlled by host GPIO[3:0]=output   GPIO[0]=1  LCD ON  GPIO[0]=1  LCD OFF
    ssd1963_data(0x0001);    //GPIO0 normal

    ssd1963_cmd(0x00BA);
    ssd1963_data(0x000F);    //GPIO[0] out 1 --- LCD display on/off control PIN

    ssd1963_cmd(0x0036);    //rotation
    ssd1963_data(0x0010);   //RGB=BGR

    ssd1963_cmd(0x003A);    //Set the current pixel format for RGB image data
    ssd1963_data(0x0050);   //16-bit/pixel

    ssd1963_cmd(0x00F0);    //Pixel Data Interface Format
    ssd1963_data(0x0000);   //16-bit(565 format) data

    ssd1963_cmd(0x00BC);
    ssd1963_data(0x0040);   //contrast value
    ssd1963_data(0x0080);   //brightness value
    ssd1963_data(0x0040);   //saturation value
    ssd1963_data(0x0001);   //Post Processor Enable

    LV_DRV_DELAY_MS(1);

    ssd1963_cmd(0x2a);			//SET page address
    ssd1963_data(0x00);			//SET start page address
    ssd1963_data(0x00);
    ssd1963_data((SSD1963_HOR_RES - 1) >> 8);		//SET end page address
    ssd1963_data((SSD1963_HOR_RES - 1) & 0xFF);

    ssd1963_cmd(0x2b);			//SET column address
    ssd1963_data(0x00);				//SET start column address
    ssd1963_data(0x00);
    ssd1963_data((SSD1963_VER_RES - 1) >> 8);		//SET end column address
    ssd1963_data((SSD1963_VER_RES - 1) & 0xFF);

    ssd1963_cmd(0x2c);
    for (uint16_t x=0; x < SSD1963_HOR_RES; x++)
    {
      for (uint16_t y= 0; y < SSD1963_VER_RES; y++)
      {
    	  ssd1963_data((0x000000)>>16); 		// color is red
    	  ssd1963_data((0x000000)>>8);  		// color is green
    	  ssd1963_data(0x000000);  		 		// color is blue
      }
    }

    ssd1963_cmd(0x29); //display on

    ssd1963_cmd(0xBE); //set PWM for B/L
    ssd1963_data(0x06);
    ssd1963_data(0xF0);
    ssd1963_data(0x01);
    ssd1963_data(0xf0);
    ssd1963_data(0x00);
    ssd1963_data(0x00);

    ssd1963_cmd(0x00d0);
    ssd1963_data(0x000d);

//    DisplayBacklightOn();
    ssd1963_cmd(0x2c);

    LV_DRV_DELAY_MS(30);
}

void ssd1963_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*Return if the area is out the screen*/
    if(area->x2 < 0) return;
    if(area->y2 < 0) return;
    if(area->x1 > SSD1963_HOR_RES - 1) return;
    if(area->y1 > SSD1963_VER_RES - 1) return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > SSD1963_HOR_RES - 1 ? SSD1963_HOR_RES - 1 : area->x2;
    int32_t act_y2 = area->y2 > SSD1963_VER_RES - 1 ? SSD1963_VER_RES - 1 : area->y2;

    //Set the rectangular area
    ssd1963_cmd(0x002A);
    ssd1963_data(act_x1 >> 8);
    ssd1963_data(0x00FF & act_x1);
    ssd1963_data(act_x2 >> 8);
    ssd1963_data(0x00FF & act_x2);

    ssd1963_cmd(0x002B);
    ssd1963_data((act_y1 + OFFSET_Y) >> 8);
    ssd1963_data(0x00FF & (act_y1 + OFFSET_Y));
    ssd1963_data((act_y2 + OFFSET_Y) >> 8);
    ssd1963_data(0x00FF & (act_y2 + OFFSET_Y));

    ssd1963_cmd(0x2c);
//    int16_t i;
//    uint16_t full_w = area->x2 - area->x1 + 1;

    ssd1963_data_mode();
    LV_DRV_DISP_PAR_CS(0);

#if LV_COLOR_DEPTH == 16
    uint16_t act_w = act_x2 - act_x1 + 1;
    for(i = act_y1; i <= act_y2; i++) {
        LV_DRV_DISP_PAR_WR_ARRAY((uint16_t *)color_p, act_w);
        color_p += full_w;
    }
    LV_DRV_DISP_PAR_CS(1);
#else
    uint32_t size = (act_x2 - act_x1 + 1) * (act_y2 - act_y1 + 1);
    for(uint32_t i = 0; i <= size-1; i++) {
    	ssd1963_data(color_p->ch.red); 			// color red
    	ssd1963_data(color_p->ch.green); 		// color green
    	ssd1963_data(color_p->ch.blue); 		// color blue
    	color_p++;
    }
#endif

    lv_disp_flush_ready(disp_drv);                  /* Tell you are ready with the flushing*/
}

void ssd1963_fill(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*Return if the area is out the screen*/
    if(area->x2 < 0) return;
    if(area->y2 < 0) return;
    if(area->x1 > SSD1963_HOR_RES - 1) return;
    if(area->y1 > SSD1963_VER_RES - 1) return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > SSD1963_HOR_RES - 1 ? SSD1963_HOR_RES - 1 : area->x2;
    int32_t act_y2 = area->y2 > SSD1963_VER_RES - 1 ? SSD1963_VER_RES - 1 : area->y2;

    //Set the rectangular area
    ssd1963_cmd(0x002A);
    ssd1963_data(act_x1 >> 8);
    ssd1963_data(0x00FF & act_x1);
    ssd1963_data(act_x2 >> 8);
    ssd1963_data(0x00FF & act_x2);

    ssd1963_cmd(0x002B);
    ssd1963_data((act_y1 + OFFSET_Y) >> 8);
    ssd1963_data(0x00FF & (act_y1 + OFFSET_Y));
    ssd1963_data((act_y2 + OFFSET_Y) >> 8);
    ssd1963_data(0x00FF & (act_y2 + OFFSET_Y));

    ssd1963_cmd(0x2c);

    LV_DRV_DISP_PAR_CS(0);
    ssd1963_data_mode();

    //uint16_t color16 = lv_color_to16(color);
    uint32_t size = (act_x2 - act_x1 + 1) * (act_y2 - act_y1 + 1);
    uint32_t i;
    for(i = 0; i < size-1; i++) {
    	ssd1963_data(color_p->ch.red); 			// color red
    	ssd1963_data(color_p->ch.green); 		// color green
    	ssd1963_data(color_p->ch.blue); 		// color blue
    }
    LV_DRV_DISP_PAR_CS(1);
}

void ssd1963_map(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{

    /*Return if the area is out the screen*/
    if(area->x2 < 0) return;
    if(area->y2 < 0) return;
    if(area->x1 > SSD1963_HOR_RES - 1) return;
    if(area->y1 > SSD1963_VER_RES - 1) return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > SSD1963_HOR_RES - 1 ? SSD1963_HOR_RES - 1 : area->x2;
    int32_t act_y2 = area->y2 > SSD1963_VER_RES - 1 ? SSD1963_VER_RES - 1 : area->y2;

    //Set the rectangular area
    ssd1963_cmd(0x002A);
    ssd1963_data(act_x1 >> 8);
    ssd1963_data(0x00FF & act_x1);
    ssd1963_data(act_x2 >> 8);
    ssd1963_data(0x00FF & act_x2);

    ssd1963_cmd(0x002B);
    ssd1963_data((act_y1 + OFFSET_Y) >> 8);
    ssd1963_data(0x00FF & (act_y1 + OFFSET_Y));
    ssd1963_data((act_y2 + OFFSET_Y) >> 8);
    ssd1963_data(0x00FF & (act_y2 + OFFSET_Y));

    ssd1963_cmd(0x2c);
    int16_t i;
    uint16_t full_w = area->x2 - area->x1 + 1;

    LV_DRV_DISP_PAR_CS(0);
    ssd1963_data_mode();

#if LV_COLOR_DEPTH == 16
    uint16_t act_w = act_x2 - act_x1 + 1;
    for(i = act_y1; i <= act_y2; i++) {
        LV_DRV_DISP_PAR_WR_ARRAY((uint16_t *)color_p, act_w);
        color_p += full_w;
    }
    LV_DRV_DISP_PAR_CS(1);
#else
    int16_t j;
    for(i = act_y1; i <= act_y2; i++) {
        for(j = 0; j <= act_x2 - act_x1 + 1; j++) {
            LV_DRV_DISP_PAR_WR_WORD(color_p[j]);
            color_p += full_w;
        }
    }
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

//static void ssd1963_io_init(void)
//{
//    LV_DRV_DISP_CMD_DATA(SSD1963_CMD_MODE);
//    cmd_mode = true;
//}

static void ssd1963_reset(void)
{
    /*Hardware reset*/
    LV_DRV_DISP_RST(1);
    LV_DRV_DELAY_MS(50);
    LV_DRV_DISP_RST(0);
    LV_DRV_DELAY_MS(50);
    LV_DRV_DISP_RST(1);
    LV_DRV_DELAY_MS(50);

    /*Software reset*/
    ssd1963_cmd(0x01);
    LV_DRV_DELAY_MS(20);

    ssd1963_cmd(0x01);
    LV_DRV_DELAY_MS(20);

    ssd1963_cmd(0x01);
    LV_DRV_DELAY_MS(20);

}

/**
 * Command mode
 */
static inline void ssd1963_cmd_mode(void)
{
    if(cmd_mode == false) {
        LV_DRV_DISP_CMD_DATA(SSD1963_CMD_MODE);
        cmd_mode = true;
    }
}

/**
 * Data mode
 */
static inline void ssd1963_data_mode(void)
{
    if(cmd_mode != false) {
        LV_DRV_DISP_CMD_DATA(SSD1963_DATA_MODE);
        cmd_mode = false;
    }
}

/**
 * Write command
 * @param cmd the command
 */
static inline void ssd1963_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET);
	// Escreve CMD no Port D
	GPIOD->ODR = (GPIOD->ODR & 0xFFFFFF00) | cmd;
	// Gera Pulso de Escrita
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);
}

/**
 * Write data
 * @param data the data
 */
static inline void ssd1963_data(uint8_t data)
{
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);
	// Escreve DATA no Port D
	 GPIOD->ODR = (GPIOD->ODR & 0xFFFFFF00) | data;
	// Gera Pulso de Escrita
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_SET);
}


void ssd1963_SetBacklight(uint8_t intensity)
{
	ssd1963_cmd(0xBE);			// Set PWM configuration for backlight control
	ssd1963_data(0x06);			// PWMF[7:0] = 2, PWM base freq = PLL/(256*(1+5))/256 =
								// 300Hz for a PLL freq = 120MHz
	ssd1963_data(intensity);	// Set duty cycle, from 0x00 (total pull-down) to 0xFF
								// (99% pull-up , 255/256)
	ssd1963_data(0x01);			// PWM enabled and controlled by host (mcu)
	ssd1963_data(0x00);
	ssd1963_data(0x00);
	ssd1963_data(0x00);
}


#endif
