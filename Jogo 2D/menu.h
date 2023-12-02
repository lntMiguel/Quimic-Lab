#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "Funcoes.h"
#include "Struct.h"
#include <stdbool.h>


int mouseX;
int mouseY;

//Função central da fase
int jogarMenu(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {

	//fonte
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* logo = al_load_bitmap("imagens/logo.png");
	
	ALLEGRO_BITMAP* btJogarH = al_load_bitmap("imagens/btJogarH.png");
	ALLEGRO_BITMAP* btJogarN = al_load_bitmap("imagens/btJogar.png");
	
	ALLEGRO_BITMAP* btCJN = al_load_bitmap("imagens/btCJ.png");
	ALLEGRO_BITMAP* btCJH = al_load_bitmap("imagens/btCJH.png");
	
	ALLEGRO_BITMAP* btSairH = al_load_bitmap("imagens/btSairH.png");
	ALLEGRO_BITMAP* btSairN = al_load_bitmap("imagens/btSair.png");

	Objeto* btJogar, * btCJ, * btSair;

	progresso->cenario->fundo = al_load_bitmap("imagens/escritorio1.png");

	btJogar = (Objeto*)malloc(sizeof(Objeto));
	btJogar->altura = 98;
	btJogar->largura = 310;
	btJogar->imagem = btJogarN;
	btJogar->wx = 0;
	btJogar->wy = 0;
	btJogar->x = 605;
	btJogar->y = 300;

	btCJ = (Objeto*)malloc(sizeof(Objeto));
	btCJ->altura = 99;
	btCJ->largura = 310;
	btCJ->imagem = btCJN;
	btCJ->wx = 0;
	btCJ->wy = 0;
	btCJ->x = 605;
	btCJ->y = 450;

	btSair = (Objeto*)malloc(sizeof(Objeto));
	btSair->altura = 98;
	btSair->largura = 310;
	btSair->imagem = btSairN;
	btSair->wx = 0;
	btSair->wy = 0;
	btSair->x = 605;
	btSair->y = 600;

	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);

	bool sair = false;

	while (!sair) {

		//criando eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(filaDeEventos, &evento);

		//fechar janela
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

			sair = true;
			progresso->fimDeJogo = true;
		}

		//registrando posição do mouse
		else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {

			mouseX = evento.mouse.x;
			mouseY = evento.mouse.y;
		}

		//registrando clique do mouse
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

			if (mouseHover(mouseX, mouseY, btJogar->x, btJogar->y, btJogar->largura, btJogar->altura)) {
				progresso->proximaReacao = 2;
				sair = true;

			}

			 if (mouseHover(mouseX, mouseY, btCJ->x, btCJ->y, btCJ->largura, btCJ->altura)) {
				progresso->proximaReacao = 1;
				sair = true;

			}

			else if (mouseHover(mouseX, mouseY, btSair->x, btSair->y, btSair->largura, btSair->altura)) {
				sair = true;
				progresso->fimDeJogo = true;

			}
		}

		
		if (mouseHover(mouseX, mouseY, btJogar->x, btJogar->y, btJogar->largura, btJogar->altura)){
			btJogar->imagem = btJogarH;
		}
		
		else {
			btJogar->imagem = btJogarN;
		}
		
		if (mouseHover(mouseX, mouseY, btCJ->x, btCJ->y, btCJ->largura, btCJ->altura)) {
			btCJ->imagem = btCJH;
		}
		
		else {
			btCJ->imagem = btCJN;
		}
		
		if (mouseHover(mouseX, mouseY, btSair->x, btSair->y, btSair->largura, btSair->altura)) {
			btSair->imagem = btSairH;
		}
		else {
			btSair->imagem = btSairN;
		}
		
			
		al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0);
		al_draw_bitmap(logo, 350, 100, 0);
		al_draw_bitmap(btJogar->imagem, btJogar->x, btJogar->y, 0);
		al_draw_bitmap(btCJ->imagem, btCJ->x, btCJ->y, 0);
		al_draw_bitmap(btSair->imagem, btSair->x, btSair->y, 0);
		
		al_flip_display();
	}
	
	al_destroy_bitmap(logo);
	al_destroy_bitmap(progresso->cenario->fundo);
	al_destroy_bitmap(btJogarH);
	al_destroy_bitmap(btCJH);
	al_destroy_bitmap(btSairH);
	al_destroy_bitmap(btJogarN);
	al_destroy_bitmap(btSairN);
	al_destroy_bitmap(btCJN);
	
	free(btJogar);
	free(btCJ);
	free(btSair);
	return 0;
}
