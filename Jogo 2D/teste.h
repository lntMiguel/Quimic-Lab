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
int jogarAcInverso(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
	
	bool sair = false;

	while (!sair) {

		ALLEGRO_EVENT evento;
		al_wait_for_event(filaDeEventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			progresso->fimDeJogo = true;
		}

		//Desenhos
		al_clear_to_color(al_map_rgb(255, 0, 255));
		al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0);
		
		al_flip_display();
	}

	al_destroy_bitmap(progresso->cenario->fundo);
	
	;
	return 0;
}

