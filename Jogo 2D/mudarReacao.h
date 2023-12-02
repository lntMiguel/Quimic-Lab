#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Funcoes.h"
#include "Struct.h"
#include "AcidoCarbonico.h"
#include "hajaLuz.h"
#include "menu.h"
#include "comoJogar.h"
#include "camaleao.h"
#include "lampada.h"
#include "aurora.h"
#include "serpente.h"
#ifndef mudarReacao_H
#define mudarReacao_H

void selecionaReacao(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
	
	switch (progresso->proximaReacao) {
	
	case 0:
		jogarMenu(display, filaDeEventos, progresso);
		return ;

	case 1:
		comoJogar(display, filaDeEventos, progresso);
		return ;

	case 2:
		jogarAcidoCarbonico(display, filaDeEventos, progresso);
		return ;

	case 3:
		jogarHajaLuz(display, filaDeEventos, progresso);
		return ;
	
	case 4:
		jogarCamaleao(display, filaDeEventos, progresso);
		return;

	case 5:
		jogarLampada(display, filaDeEventos, progresso);
		return;
	
	case 6:
		jogarAurora(display, filaDeEventos, progresso);
		return;
	case 7:
		jogarSerpente(display, filaDeEventos, progresso);
		return;
	default:
		break;
	}
}

#endif
