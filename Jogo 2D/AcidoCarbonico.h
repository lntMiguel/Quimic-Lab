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

//Função central da fase
int jogarAcidoCarbonico(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso){
	
	ALLEGRO_FONT* font, * fonteBalao;
	ALLEGRO_BITMAP* recipienteVinagre = al_load_bitmap("imagens/recipienteVinagre.png");
	ALLEGRO_BITMAP* recipienteFeito = al_load_bitmap("imagens/recipienteFeito.png");
	ALLEGRO_BITMAP* recipiente = al_load_bitmap("imagens/recipiente.png");
	
	
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	;
	bool sair = false;
	int mouseX;
	int mouseY;
	
	bool sequenciaCerta[2];
	sequenciaCerta[0] = false;
	sequenciaCerta[1] = false;
	bool errou = false;
	
	while (!sair) {
		
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

		al_clear_to_color(al_map_rgb(255, 0, 255));
		al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0);
		al_draw_bitmap(progresso->cenario->bicarbonato->imagem, progresso->cenario->bicarbonato->x, progresso->cenario->bicarbonato->y, 0);
		al_draw_bitmap(progresso->cenario->vinagre->imagem, progresso->cenario->vinagre->x, progresso->cenario->vinagre->y, 0);
		
		if (sequenciaCerta[0] == false && sequenciaCerta[1] == false) {
			al_draw_bitmap(recipiente, 590, 250, 0);
		}
		else if (sequenciaCerta[0] == true && sequenciaCerta[1] == false) {
			al_draw_bitmap(recipienteVinagre, 590, 250, 0);
		}
		else if (sequenciaCerta[1] == true) {
			al_draw_bitmap(recipienteFeito, 590, 250, 0);
		}


		if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->vinagre)) {
		
			al_draw_text(font, al_map_rgb(0, 0, 0), 730, 250, 0, "Vinagre (CH3COOH)");

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

				sequenciaCerta[0] = true;
				
			}
		}

		else if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->bicarbonato)) {

			al_draw_text(font, al_map_rgb(0, 0, 0), 380, 300, 0, "Bicarbonato (NaHCO3)");
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

				if (sequenciaCerta[0] == true) {

					al_draw_bitmap(recipienteFeito, 590, 250, 0);
					sequenciaCerta[1] = true;
				}
				else {
					errou = true;
					
				}
					
			}
		}
		
		if (sequenciaCerta[1] == true) {
			
			al_draw_text(font, al_map_rgb(0, 0, 0), 360, 200, 0, "Voce conseguiu produzir");
			al_draw_text(font, al_map_rgb(0, 0, 0), 400, 220, 0, "a reacao esperada.");
			al_draw_text(font, al_map_rgb(0, 0, 0), 350, 250, 0, "Ate que enfim contrataram");
			al_draw_text(font, al_map_rgb(0, 0, 0), 350, 270, 0, "um estagiario que saiba");
			al_draw_text(font, al_map_rgb(0, 0, 0), 420, 290, 0, "fazer algo.");
		
		}
		
		if (errou) {
			al_draw_text(font, al_map_rgb(0, 0, 0), 420, 220, 0, "Ops... A ordem dos");
			al_draw_text(font, al_map_rgb(0, 0, 0), 430, 240, 0, "reagentes e muito");
			al_draw_text(font, al_map_rgb(0, 0, 0), 400, 260, 0, "importante para que a");
			al_draw_text(font, al_map_rgb(0, 0, 0), 360, 280, 0, "reacao ocorra corretamente.");
			al_draw_text(font, al_map_rgb(0, 0, 0), 430, 320, 0, "Tente novamente.");
		}
		if (sequenciaCerta[1] == true) {
				progresso->proximaReacao = 1;
				sair = true;
			}
	
		al_flip_display();
	
	}

	
	al_destroy_bitmap(recipienteVinagre);
	al_destroy_bitmap(recipienteFeito);
	al_destroy_bitmap(recipiente);
	al_destroy_bitmap(progresso->cenario->fundo);
	al_destroy_bitmap(progresso->cenario->bicarbonato->imagem);
	al_destroy_bitmap(progresso->cenario->vinagre->imagem);

	return 0;
}

