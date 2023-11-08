#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Funcoes.h"
#include "Struct.h"
#include "AcidoCarbonico.h"
#include "teste.h"

#ifndef mudarReacao_H
#define mudarReacao_H

void selecionaReacao(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
	switch (progresso->proximaReacao) {
	
	case 0:
		jogarAcidoCarbonico(display, filaDeEventos, progresso);
		return;

	case 1:
		jogarAcInverso(display, filaDeEventos, progresso);
		return;
	
	default:
		break;
	}
}
;
#endif
