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
int comoJogar(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {

	//fonte
	ALLEGRO_FONT* font;

	ALLEGRO_BITMAP* btVoltarH = al_load_bitmap("imagens/btVoltarH.png");
	ALLEGRO_BITMAP* btVoltarN = al_load_bitmap("imagens/btVoltarN.png");

	Objeto* btVoltar;

	btVoltar = (Objeto*)malloc(sizeof(Objeto));
	btVoltar->altura = 98;
	btVoltar->largura = 310;
	btVoltar->imagem = btVoltarN;
	btVoltar->wx = 0;
	btVoltar->wy = 0;
	btVoltar->x = 30;
	btVoltar->y = 700;

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

			if (mouseHover(mouseX, mouseY, btVoltar->x, btVoltar->y, btVoltar->largura, btVoltar->altura)) {
				progresso->proximaReacao = 0;
				sair = true;

			}

		}
			if (mouseHover(mouseX, mouseY, btVoltar->x, btVoltar->y, btVoltar->largura, btVoltar->altura)) {
				btVoltar->imagem = btVoltarH;
			}

			else {
				btVoltar->imagem = btVoltarN;
			}
			
			al_draw_bitmap(progresso->cenario->cjFundo, 0, 0, 0);
			al_draw_bitmap(btVoltar->imagem, btVoltar->x, btVoltar->y, 0);
			
			al_flip_display();


		}
	
	al_destroy_bitmap(btVoltarH);
	al_destroy_bitmap(btVoltarN);
	free(btVoltar);
	
	return 0;
	
}

