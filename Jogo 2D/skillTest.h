#ifndef skillTest_H
#define skillTest_H

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
#include <allegro5/allegro_primitives.h>

int mouseX, mouseY;

bool acerteVerde(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {

	Objeto* seta;
	seta = (Objeto*)malloc(sizeof(Objeto));
	seta->altura = 32;
	seta->largura = 24;
	seta->imagem = al_load_bitmap("imagens/seta.png");
	seta->wx = 4;
	seta->wy = 0;
	seta->x = 503;
	seta->y = 345;

	Objeto* teste;
	teste = (Objeto*)malloc(sizeof(Objeto));
	teste->altura = 75;
	teste->largura = 500;
	teste->imagem = al_load_bitmap("imagens/barra.png");
	teste->wx = 0;
	teste->wy = 0;
	teste->x = 500;
	teste->y = 340;

	ALLEGRO_BITMAP* botaoAdd = al_load_bitmap("imagens/btAdd.png");
	ALLEGRO_BITMAP* botaoAddH = al_load_bitmap("imagens/adss.png");
	
	Objeto* botao;
	botao = (Objeto*)malloc(sizeof(Objeto));
	botao->altura = 98;
	botao->largura = 308;
	botao->imagem = botaoAdd;
	botao->wx = 0;
	botao->wy = 0;
	botao->x = 609;
	botao->y = 500;

	bool sair = false;
	bool acertou = false;
	int velocidade = 2;
	al_init_primitives_addon();
	
	ALLEGRO_FONT* font;
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	
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

		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

			if (mouseHover(mouseX, mouseY, botao->x, botao->y, botao->largura, botao->altura)) {
				
				if (seta->x >= 689 && seta->x <= 777) {
					acertou = true;
				}

				sair = true;
			}

		}
		
		if (mouseHover(mouseX, mouseY, botao->x, botao->y, botao->largura, botao->altura)) {
			botao->imagem = botaoAddH;
		}
		else
			botao->imagem = botaoAdd;
			
		//al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0); 
		//desenhaRegentes(progresso);
		al_draw_bitmap(teste->imagem, teste->x, teste->y, 0);
		al_draw_bitmap(seta->imagem, seta->x, seta->y, 0);
		al_draw_bitmap(botao->imagem, botao->x, botao->y, 0);
		
		seta->x = seta->x + velocidade;

		if (seta->x <= 503) {
			velocidade = 2;
		}
		if (seta->x >= 960) {
			velocidade = -2;
		}

		
		al_flip_display();
	}

	al_destroy_bitmap(seta->imagem);
	al_destroy_bitmap(teste->imagem);
	al_destroy_bitmap(botao->imagem);
	free(seta);
	free(teste);
	free(botao);
	
	return acertou;
}
#endif