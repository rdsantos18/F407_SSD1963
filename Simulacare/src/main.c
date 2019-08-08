/*
 * main.c
 *
 *  Created on: 30 de jul de 2019
 *      Author: Rinaldo Dos Santos
 */

#include "Simulacare/src/main.h"
#include "lvgl/lvgl.h"
#include "stdio.h"
#include "string.h"

uint32_t btn5 = 0, btn4 = 0;
uint32_t btn_home = 0, btn_inicio = 0, btn_pausa = 0;

static void btn_event_btn5(lv_obj_t * btn, lv_event_t event);
static void btn_event_btn4(lv_obj_t * btn, lv_event_t event);
static void btn_event_home(lv_obj_t * btn, lv_event_t event);
static void btn_event_inicio(lv_obj_t * btn, lv_event_t event);
static void btn_event_pausa(lv_obj_t * btn, lv_event_t event);
static void event_handler_bpm(lv_obj_t * slider, lv_event_t event);
static void event_handler_duracao(lv_obj_t * slider, lv_event_t event);

static lv_obj_t * Tela_RCP;
static lv_style_t style_fundo;
//static lv_obj_t * img_fundo_1;
//static lv_obj_t * img_fundo_2;
static lv_obj_t * img_pulmao;
static lv_obj_t * img_coracao;
static lv_obj_t * img_frequencia;
static lv_obj_t * img_duracao;
static lv_obj_t * txt_on_off;
static lv_obj_t * txt_freq;
static lv_obj_t * txt_dur;
static lv_obj_t * txt_tempo;
static lv_obj_t * txt_bpm;

static lv_style_t style_txt1;
static lv_style_t style_bg;
static lv_style_t style_indic;
static lv_style_t style_knob;
static lv_style_t style_cont;

static lv_obj_t * imgbtn1;
static lv_obj_t * imgbtn2;
static lv_obj_t * imgbtn3;
static lv_obj_t * imgbtn4;
static lv_obj_t * imgbtn5;

static lv_obj_t * cont1;
static lv_obj_t * cont2;

lv_obj_t * bpm;
lv_obj_t * duracao;

LV_IMG_DECLARE(Pulmao);
LV_IMG_DECLARE(Btn_Home);
LV_IMG_DECLARE(Btn_Inicio);
LV_IMG_DECLARE(Btn_Pausa);
LV_IMG_DECLARE(Distorcia_ON);
LV_IMG_DECLARE(Distorcia_OFF);
LV_IMG_DECLARE(Pulmao);
LV_IMG_DECLARE(Coracao);
LV_IMG_DECLARE(ON);
LV_IMG_DECLARE(OFF);
LV_IMG_DECLARE(Barra);
LV_IMG_DECLARE(Home_OFF);
LV_IMG_DECLARE(Inicio_OFF);
LV_IMG_DECLARE(Pausa_OFF);

char buf[100] = {0};

void simulacare(void)
{
	// Create a Styles
	lv_style_copy(&style_txt1, &lv_style_plain);
	style_txt1.text.font = &lv_font_roboto_22;
	style_txt1.text.letter_space = 0;
	style_txt1.text.line_space = 0;
	style_txt1.text.color = LV_COLOR_GRAY;
    lv_style_copy(&style_bg, &lv_style_pretty);
    style_bg.body.main_color =  LV_COLOR_BLACK;
    style_bg.body.grad_color =  LV_COLOR_GRAY;
    style_bg.body.radius = LV_RADIUS_CIRCLE;
    style_bg.body.border.color = LV_COLOR_WHITE;

    lv_style_copy(&style_indic, &lv_style_pretty_color);
    style_indic.body.radius = LV_RADIUS_CIRCLE;
    style_indic.body.shadow.width = 10;
    style_indic.body.shadow.color = style_indic.body.main_color;
    style_indic.body.padding.left = 5;
    style_indic.body.padding.right = 5;
    style_indic.body.padding.top = 5;
    style_indic.body.padding.bottom = 5;

    lv_style_copy(&style_knob, &lv_style_pretty);
    style_knob.body.radius = LV_RADIUS_CIRCLE;
    style_knob.body.opa = 255;
    style_knob.body.padding.top = 10;
    style_knob.body.padding.bottom = 10;

	lv_style_copy(&style_cont, &lv_style_plain);
	style_cont.body.radius = 15;
   	style_cont.body.main_color = LV_COLOR_WHITE;
	style_cont.body.grad_color = LV_COLOR_WHITE;
	style_cont.body.shadow.width = 10;
	style_cont.body.shadow.color = LV_COLOR_GRAY;

	Tela_RCP = lv_obj_create(NULL, NULL);

	lv_style_copy(&style_fundo, &lv_style_plain_color);
	style_fundo.body.main_color = LV_COLOR_MAKE(220, 220, 220);
	style_fundo.body.grad_color = LV_COLOR_MAKE(220, 220, 220);
	lv_obj_set_style(Tela_RCP, &style_fundo); 					// Configura o estilo criado

	// Cont
	cont1 = lv_cont_create(Tela_RCP, NULL);
	lv_obj_set_style(cont1, &style_cont);
	lv_obj_set_size(cont1, 220, 430);
	lv_obj_align(cont1, NULL, LV_ALIGN_IN_TOP_LEFT, 40, 30);
	lv_cont_set_layout(cont1, LV_LAYOUT_COL_M);

	cont2 = lv_cont_create(Tela_RCP, NULL);
	lv_obj_set_style(cont2, &style_cont);
	lv_obj_set_size(cont2, 420, 130);
	lv_obj_align(cont2, NULL, LV_ALIGN_IN_TOP_RIGHT, -35, 330);
	lv_cont_set_layout(cont2, LV_LAYOUT_COL_M);
	//
    img_pulmao = lv_img_create(Tela_RCP, NULL);
    lv_img_set_src(img_pulmao, &Pulmao);
    lv_img_set_auto_size(img_pulmao, true);
    lv_obj_set_pos(img_pulmao, 60, 250);
    //
    img_coracao = lv_img_create(Tela_RCP, NULL);
    lv_img_set_src(img_coracao, &Coracao);
    lv_img_set_auto_size(img_coracao, true);
    lv_obj_set_pos(img_coracao, 70, 50);
    //
    img_frequencia = lv_img_create(Tela_RCP, NULL);
    lv_img_set_src(img_frequencia, &Barra);
    lv_img_set_auto_size(img_frequencia, true);
    lv_obj_set_pos(img_frequencia, 340, 140);
    //
    // Label Frequencia
	txt_freq = lv_label_create(Tela_RCP, NULL);
    lv_obj_set_style(txt_freq, &style_txt1);
    lv_label_set_long_mode(txt_freq, LV_LABEL_LONG_EXPAND); 		// Quebra as linhas longas
    lv_label_set_recolor(txt_freq, true); 						// Ativa recolorizar por comandos no texto
    lv_label_set_align(txt_freq, LV_ALIGN_IN_TOP_MID); 			// Centraliza linhas alinhadas
    lv_label_set_text(txt_freq, "Frequencia");
    lv_obj_set_width(txt_freq, 500); 								// Configuura o comprimento
    lv_obj_align(txt_freq, NULL, LV_ALIGN_IN_TOP_MID, 20, 148); 	// Alinha ao centro
    // Create a slider BPM
    bpm = lv_slider_create(Tela_RCP, NULL);
    lv_slider_set_range(bpm, 60, 200);
    lv_obj_set_width(bpm, 320);
    lv_obj_set_height(bpm, 25);
    lv_slider_set_style(bpm, LV_SLIDER_STYLE_BG, &style_bg);
    lv_slider_set_style(bpm, LV_SLIDER_STYLE_INDIC,&style_indic);
    lv_slider_set_style(bpm, LV_SLIDER_STYLE_KNOB, &style_knob);
    lv_obj_align(bpm, NULL, LV_ALIGN_CENTER, 120, -39);
    lv_obj_set_event_cb(bpm, event_handler_bpm);
    // Label BPM
	txt_bpm = lv_label_create(Tela_RCP, NULL);
    lv_obj_set_style(txt_bpm, &style_txt1);
    lv_label_set_long_mode(txt_bpm, LV_LABEL_LONG_EXPAND); 		// Quebra as linhas longas
    lv_label_set_recolor(txt_bpm, true); 						// Ativa recolorizar por comandos no texto
    lv_label_set_align(txt_bpm, LV_ALIGN_IN_TOP_MID); 			// Centraliza linhas alinhadas
    sprintf(buf, "%u bpm", lv_slider_get_value(bpm));
    lv_label_set_text(txt_bpm, buf);
    lv_label_set_text(txt_bpm, buf);
    lv_obj_set_width(txt_bpm, 500); 								// Configuura o comprimento
    lv_obj_align(txt_bpm, NULL, LV_ALIGN_IN_TOP_MID, 340, 188); 	// Alinha ao centro

    img_duracao = lv_img_create(Tela_RCP, NULL);
    lv_img_set_src(img_duracao, &Barra);
    lv_img_set_auto_size(img_duracao, true);
    lv_obj_set_pos(img_duracao, 340, 50);
    //
    // Label Duracao
	txt_dur = lv_label_create(Tela_RCP, NULL);
    lv_obj_set_style(txt_dur, &style_txt1);
    lv_label_set_long_mode(txt_dur, LV_LABEL_LONG_EXPAND); 		// Quebra as linhas longas
    lv_label_set_recolor(txt_dur, true); 						// Ativa recolorizar por comandos no texto
    lv_label_set_align(txt_dur, LV_ALIGN_IN_TOP_MID); 			// Centraliza linhas alinhadas
    lv_label_set_text(txt_dur, "Duracao");
    lv_obj_set_width(txt_dur, 500); 							// Configuura o comprimento
    lv_obj_align(txt_dur, NULL, LV_ALIGN_IN_TOP_MID, 5, 60); 	// Alinha ao centro
    //
    // Create a slider Tempo
    duracao = lv_slider_create(Tela_RCP, NULL);
    lv_slider_set_range(duracao, 1, 30);
    lv_obj_set_width(duracao, 320);
    lv_obj_set_height(duracao, 25);
    lv_slider_set_style(duracao, LV_SLIDER_STYLE_BG, &style_bg);
    lv_slider_set_style(duracao, LV_SLIDER_STYLE_INDIC,&style_indic);
    lv_slider_set_style(duracao, LV_SLIDER_STYLE_KNOB, &style_knob);
    lv_obj_align(duracao, NULL, LV_ALIGN_CENTER, 120, -128);
    lv_obj_set_event_cb(duracao, event_handler_duracao);

    // Label Duracao - Tempo
	txt_tempo = lv_label_create(Tela_RCP, NULL);
    lv_obj_set_style(txt_tempo, &style_txt1);
    lv_label_set_long_mode(txt_tempo, LV_LABEL_LONG_EXPAND); 		// Quebra as linhas longas
    lv_label_set_recolor(txt_tempo, true); 						// Ativa recolorizar por comandos no texto
    lv_label_set_align(txt_tempo, LV_ALIGN_IN_TOP_MID); 			// Centraliza linhas alinhadas
    sprintf(buf, "%u Min.", lv_slider_get_value(duracao));
    lv_label_set_text(txt_tempo, buf);
    lv_obj_set_width(txt_tempo, 500); 								// Configuura o comprimento
    lv_obj_align(txt_tempo, NULL, LV_ALIGN_IN_TOP_MID, 340, 98); 	// Alinha ao centro
    //
    // Create Button Home
	imgbtn1 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_REL, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_TGL_REL, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_TGL_PR, &Home_OFF);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_PR, &Home_OFF);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_REL, &Btn_Home);
	lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_INA, &Btn_Home);
	lv_obj_set_event_cb(imgbtn1, btn_event_home);
	lv_obj_set_pos(imgbtn1, 360, 335);
	// Create Button Inicio
	imgbtn2 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_REL, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_TGL_REL, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_TGL_PR, &Inicio_OFF);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_PR, &Inicio_OFF);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_REL, &Btn_Inicio);
	lv_imgbtn_set_src(imgbtn2, LV_BTN_STATE_INA, &Btn_Inicio);
	lv_obj_set_event_cb(imgbtn2, btn_event_inicio);
	lv_obj_set_pos(imgbtn2, 500, 335);
	// Create Button Pausa
	imgbtn3 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_REL, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_TGL_REL, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_TGL_PR, &Pausa_OFF);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_PR, &Pausa_OFF);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_REL, &Btn_Pausa);
	lv_imgbtn_set_src(imgbtn3, LV_BTN_STATE_INA, &Btn_Pausa);
	lv_obj_set_event_cb(imgbtn3, btn_event_pausa);
	lv_obj_set_pos(imgbtn3, 640, 335);
	// Distorcia
	imgbtn4 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_REL, &Distorcia_ON);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_TGL_REL, &Distorcia_ON);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_TGL_PR, &Distorcia_OFF);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_PR, &Distorcia_ON);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_REL, &Distorcia_ON);
	lv_imgbtn_set_src(imgbtn4, LV_BTN_STATE_INA, &Distorcia_ON);
	lv_obj_set_event_cb(imgbtn4, btn_event_btn4);
	lv_btn_set_state(imgbtn4, LV_BTN_STATE_TGL_PR);
	lv_obj_set_pos(imgbtn4, 345, 225);
    // Label Distorcia
	txt_on_off = lv_label_create(Tela_RCP, NULL);
    lv_obj_set_style(txt_on_off, &style_txt1);
    lv_label_set_long_mode(txt_on_off, LV_LABEL_LONG_EXPAND); 		// Quebra as linhas longas
    lv_label_set_recolor(txt_on_off, true); 						// Ativa recolorizar por comandos no texto
    lv_label_set_align(txt_on_off, LV_ALIGN_IN_TOP_MID); 			// Centraliza linhas alinhadas
    lv_label_set_text(txt_on_off, "Distocia");
    lv_obj_set_width(txt_on_off, 500); 								// Configuura o comprimento
    lv_obj_align(txt_on_off, NULL, LV_ALIGN_IN_TOP_MID, 5, 235); 	// Alinha ao centro

	// ON-OFF
	imgbtn5 = lv_imgbtn_create(Tela_RCP, NULL);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_REL, &ON);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_TGL_REL, &ON);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_TGL_PR, &OFF);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_PR, &OFF);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_REL, &ON);
	lv_imgbtn_set_src(imgbtn5, LV_BTN_STATE_INA, &ON);
	lv_imgbtn_set_toggle(imgbtn5, true);
	lv_obj_set_event_cb(imgbtn5, btn_event_btn5);
	lv_btn_set_state(imgbtn5, LV_BTN_STATE_TGL_PR);
	lv_obj_set_pos(imgbtn5, 690, 6);
	// Label Button ON-OFF
    txt_on_off = lv_label_create(Tela_RCP, NULL);
    lv_obj_set_style(txt_on_off, &style_txt1);
    lv_label_set_long_mode(txt_on_off, LV_LABEL_LONG_EXPAND); 		// Quebra as linhas longas
    lv_label_set_recolor(txt_on_off, true); 						// Ativa recolorizar por comandos no texto
    lv_label_set_align(txt_on_off, LV_ALIGN_IN_TOP_MID); 			// Centraliza linhas alinhadas
    lv_label_set_text(txt_on_off, "OFF");
    lv_obj_set_width(txt_on_off, 300); 								// Configuura o comprimento
    lv_obj_align(txt_on_off, NULL, LV_ALIGN_IN_TOP_MID, 340, 52); 	// Alinha ao centro

    // Seta Estado OFF dos Buttons
    lv_btn_set_state(imgbtn1, LV_BTN_STATE_TGL_PR);
    lv_btn_set_state(imgbtn2, LV_BTN_STATE_TGL_PR);
	lv_btn_set_state(imgbtn3, LV_BTN_STATE_TGL_PR);
	lv_btn_set_state(imgbtn4, LV_BTN_STATE_TGL_PR);
	lv_btn_set_state(imgbtn5, LV_BTN_STATE_TGL_PR);

	lv_scr_load(Tela_RCP);
}

static void btn_event_home(lv_obj_t * btn, lv_event_t event)
{
	if(event == LV_EVENT_RELEASED) {
		printf("debug: Home: %d\n", lv_btn_get_state(btn));
		if(btn_home) {
			btn_home = 0;
			lv_btn_set_state(imgbtn1, LV_BTN_STATE_TGL_PR);
		}
		else {
			btn_home = 1;
			lv_btn_set_state(imgbtn1, LV_BTN_STATE_TGL_REL);
		}
	}
}

static void btn_event_inicio(lv_obj_t * btn, lv_event_t event)
{
	if(event == LV_EVENT_RELEASED) {
		printf("debug: Inicio: %d\n", lv_btn_get_state(btn));
		if(btn_inicio) {
			btn_inicio = 0;
			lv_btn_set_state(imgbtn2, LV_BTN_STATE_TGL_PR);
		}
		else {
			btn_inicio = 1;
			lv_btn_set_state(imgbtn2, LV_BTN_STATE_TGL_REL);
		}
	}
}

static void btn_event_pausa(lv_obj_t * btn, lv_event_t event)
{
	if(event == LV_EVENT_RELEASED) {
		printf("debug: Pausa: %d\n", lv_btn_get_state(btn));
		if(btn_pausa) {
			btn_pausa = 0;
			lv_btn_set_state(imgbtn3, LV_BTN_STATE_TGL_PR);
		}
		else {
			btn_pausa = 1;
			lv_btn_set_state(imgbtn3, LV_BTN_STATE_TGL_REL);
		}
	}
}

static void btn_event_btn5(lv_obj_t * btn, lv_event_t event)
{
	if(event == LV_EVENT_RELEASED) {
		printf("debug: ON-OFF: %d\n", lv_btn_get_state(btn));
		if(btn5) {
			btn5 = 0;
			lv_label_set_text(txt_on_off, "OFF");
			lv_btn_set_state(imgbtn5, LV_BTN_STATE_TGL_PR);
		}
		else {
			btn5 = 1;
			lv_label_set_text(txt_on_off, "ON");
			lv_btn_set_state(imgbtn5, LV_BTN_STATE_TGL_REL);
		}
	}
}

static void btn_event_btn4(lv_obj_t * btn, lv_event_t event)
{
	if(event == LV_EVENT_RELEASED) {
		printf("debug: Distorcia %d\n", lv_btn_get_state(btn));
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

static void event_handler_bpm(lv_obj_t * slider, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
    	sprintf(buf, "%u bpm", lv_slider_get_value(slider));
        lv_label_set_text(txt_bpm, buf);
    }
}

static void event_handler_duracao(lv_obj_t * slider, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
    	sprintf(buf, "%u Min.", lv_slider_get_value(slider));
        lv_label_set_text(txt_tempo, buf);
    }
}
