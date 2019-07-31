/*
 * main.c
 *
 *  Created on: 30 de jul de 2019
 *      Author: rinaldo
 */

#include "Simulacare/src/main.h"
#include "lvgl/lvgl.h"
#include "stdio.h"
#include "string.h"

uint32_t btn5 = 0, btn4 = 0;

static void btn_event_btn5(lv_obj_t * btn, lv_event_t event);
static void btn_event_btn4(lv_obj_t * btn, lv_event_t event);

static lv_obj_t * Tela_RCP;
static lv_style_t style_fundo;
static lv_obj_t * img_fundo;
static lv_obj_t * img_fundo_1;
static lv_obj_t * img_fundo_2;
static lv_obj_t * img_pulmao;
static lv_obj_t * img_coracao;
static lv_obj_t * img_frequencia;
static lv_obj_t * img_duracao;

static lv_obj_t * imgbtn1;
static lv_obj_t * imgbtn2;
static lv_obj_t * imgbtn3;
static lv_obj_t * imgbtn4;
static lv_obj_t * imgbtn5;

LV_IMG_DECLARE(Pulmao);
//LV_IMG_DECLARE(Background);
LV_IMG_DECLARE(Fundo_1);
LV_IMG_DECLARE(Fundo_2);
LV_IMG_DECLARE(Btn_Home);
LV_IMG_DECLARE(Btn_Inicio);
LV_IMG_DECLARE(Btn_Pausa);
LV_IMG_DECLARE(Btn_Distorcia);
LV_IMG_DECLARE(Btn_Distorcia_OFF);
LV_IMG_DECLARE(Pulmao);
LV_IMG_DECLARE(Coracao);
LV_IMG_DECLARE(Frequencia);
LV_IMG_DECLARE(Duracao);
LV_IMG_DECLARE(Btn_ON);
LV_IMG_DECLARE(Btn_OFF);

void simulacare(void)
{
	// Create a Screen
	Tela_RCP = lv_obj_create(NULL, NULL);

	lv_style_copy(&style_fundo, &lv_style_plain_color);
	style_fundo.body.main_color = LV_COLOR_WHITE;
	style_fundo.body.grad_color = LV_COLOR_WHITE;
	lv_obj_set_style(Tela_RCP, &style_fundo); 					// Configura o estilo criado

	// Imagem de Fundo
//	img_fundo = lv_img_create(Tela_RCP, NULL);
//    lv_img_set_src(img_fundo, &Background);
//	lv_obj_set_protect(img_fundo, LV_PROTECT_POS);
	//lv_obj_set_event_cb(img_fundo, main_screen_event);
	//lv_obj_set_click(img_fundo, 1);
//	img_fundo_1 = lv_img_create(Tela_RCP, NULL);
 //   lv_img_set_src(img_fundo_1, &Fundo_1);
//    lv_img_set_auto_size(img_fundo_1, true);
//    lv_obj_set_pos(img_fundo_1, 30, 10);

 //   img_fundo_2 = lv_img_create(Tela_RCP, NULL);
//   lv_img_set_src(img_fundo_2, &Fundo_2);
 //   lv_img_set_auto_size(img_fundo_2, true);
 //   lv_obj_set_pos(img_fundo_2, 350, 315);
	//
    img_pulmao = lv_img_create(Tela_RCP, NULL);
    lv_img_set_src(img_pulmao, &Pulmao);
    lv_img_set_auto_size(img_pulmao, true);
    lv_obj_set_pos(img_pulmao, 60, 250);
    //
//    img_coracao = lv_img_create(Tela_RCP, NULL);
 //   lv_img_set_src(img_coracao, &Coracao);
 //   lv_img_set_auto_size(img_coracao, true);
 //   lv_obj_set_pos(img_coracao, 60, 50);
    //
    img_frequencia = lv_img_create(Tela_RCP, NULL);
    lv_img_set_src(img_frequencia, &Frequencia);
    lv_img_set_auto_size(img_frequencia, true);
    lv_obj_set_pos(img_frequencia, 350, 140);

    img_duracao = lv_img_create(Tela_RCP, NULL);
    lv_img_set_src(img_duracao, &Duracao);
    lv_img_set_auto_size(img_duracao, true);
    lv_obj_set_pos(img_duracao, 350, 50);

    // Create Button Frequency
	imgbtn1 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_REL, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_TGL_REL, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_TGL_PR, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_PR, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_REL, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_INA, &Btn_Home);
	//lv_obj_set_event_cb(imgbtn1, btn_event_btn1);
	lv_obj_set_pos(imgbtn1, 380, 325);
	//
	imgbtn2 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_REL, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_TGL_REL, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_TGL_PR, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_PR, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_REL, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_INA, &Btn_Inicio);
	//lv_obj_set_event_cb(imgbtn1, btn_event_btn1);
	lv_obj_set_pos(imgbtn2, 490, 325);
	//
	imgbtn3 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_REL, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_TGL_REL, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_TGL_PR, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_PR, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_REL, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_INA, &Btn_Pausa);
	//lv_obj_set_event_cb(imgbtn1, btn_event_btn1);
	lv_obj_set_pos(imgbtn3, 600, 325);
	// Distorcia
	imgbtn4 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_REL, &Btn_Distorcia);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_TGL_REL, &Btn_Distorcia);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_TGL_PR, &Btn_Distorcia_OFF);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_PR, &Btn_Distorcia);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_REL, &Btn_Distorcia);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_INA, &Btn_Distorcia);
	lv_obj_set_event_cb(imgbtn4, btn_event_btn4);
	lv_btn_set_state(imgbtn4, LV_BTN_STATE_TGL_PR);
	lv_obj_set_pos(imgbtn4, 350, 230);
	// ON-OFF
	imgbtn5 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_REL, &Btn_ON);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_TGL_REL, &Btn_ON);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_TGL_PR, &Btn_OFF);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_PR, &Btn_OFF);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_REL, &Btn_ON);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_INA, &Btn_ON);
	lv_imgbtn_set_toggle(imgbtn5, true);
	lv_obj_set_event_cb(imgbtn5, btn_event_btn5);
	lv_btn_set_state(imgbtn5, LV_BTN_STATE_TGL_PR);
	lv_obj_set_pos(imgbtn5, 660, 1);



	lv_scr_load(Tela_RCP);
}

static void btn_event_btn5(lv_obj_t * btn, lv_event_t event)
{
	if(event == LV_EVENT_RELEASED) {
		printf("debug: %d\n", lv_btn_get_state(btn));
		if(btn5) {
			btn5 = 0;
			lv_btn_set_state(imgbtn5, LV_BTN_STATE_TGL_PR);
		}
		else {
			btn5 = 1;
			lv_btn_set_state(imgbtn5, LV_BTN_STATE_TGL_REL);
		}
	}
}

static void btn_event_btn4(lv_obj_t * btn, lv_event_t event)
{
	if(event == LV_EVENT_RELEASED) {
		printf("debug: %d\n", lv_btn_get_state(btn));
		if(btn4) {
			btn4 = 0;
			lv_btn_set_state(imgbtn4, LV_BTN_STATE_TGL_PR);
		}
		else {
			btn4 = 1;
			lv_btn_set_state(imgbtn4, LV_BTN_STATE_TGL_REL);
		}
	}
}
