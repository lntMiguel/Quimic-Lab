#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include "Jogo 2D/Struct.h"
#include "Jogo 2D/mudarReacao.h"


//variaveis globais

int main() {
	//inicialização
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	
	//Display
	ALLEGRO_DISPLAY* display = al_create_display(1213, 681);
	al_set_window_title(display, "Teste - Nova Lógica");

	//Fila de eventos
	ALLEGRO_EVENT_QUEUE* filaDeEventos =  al_create_event_queue();
	al_register_event_source(filaDeEventos, al_get_display_event_source(display));

	//Load da fonte
	ALLEGRO_FONT* font, * fonteBalao;
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	fonteBalao = al_load_ttf_font("fontes/fonteBalao.ttf", 20, 0);

	if (!al_install_mouse()) {
		fprintf(stderr, "Falha ao iniciar o mouse\n");
		al_destroy_display(display);
		al_destroy_event_queue(filaDeEventos);

		return -1;
	}

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

	//registrando eventos
	al_register_event_source(filaDeEventos, al_get_timer_event_source(timer));
	al_register_event_source(filaDeEventos, al_get_mouse_event_source());

	//start timer
	al_start_timer(timer);

	Prog progresso;
	
	progresso.proximaReacao = 0;
	progresso.fimDeJogo = 0;
	;
	progresso.reacoes[0] = 0;
	progresso.reacoes[1] = 0;
	progresso.reacoes[2] = 0;
	progresso.reacoes[3] = 0;
	progresso.reacoes[4] = 0;
	progresso.reacoes[5] = 0;
	progresso.reacoes[6] = 0;

	progresso.cenario = (Cenario*)malloc(sizeof(Cenario));
	
	progresso.cenario->cientista = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->cientista->imagem = al_load_bitmap("imagens/cientista.png");
	progresso.cenario->cientista->altura = 200;
	progresso.cenario->cientista->largura = 124;
	progresso.cenario->cientista->wx = 0;
	progresso.cenario->cientista->wy = 0;
	progresso.cenario->cientista->x = 150;
	progresso.cenario->cientista->y = 300;

	progresso.cenario->bicarbonato = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->bicarbonato->imagem = al_load_bitmap("imagens/bicarbonato.png");
	progresso.cenario->bicarbonato->altura = 100;
	progresso.cenario->bicarbonato->largura = 108;
	progresso.cenario->bicarbonato->wx = 0;
	progresso.cenario->bicarbonato->wy = 0;
	progresso.cenario->bicarbonato->x = 450;
	progresso.cenario->bicarbonato->y = 350;
	                   
	progresso.cenario->vinagre = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->vinagre->imagem = al_load_bitmap("imagens/vinagre.png");
	progresso.cenario->vinagre->altura = 82;
	progresso.cenario->vinagre->largura = 152;
	progresso.cenario->vinagre->wx = 0;
	progresso.cenario->vinagre->wy = 0;
	progresso.cenario->vinagre->x = 800;
	progresso.cenario->vinagre->y = 300;

	progresso.cenario->fundo = al_load_bitmap("imagens/fundo.png");

	Prog* prog = &progresso;

	while (!prog->fimDeJogo) {
		selecionaReacao(display, filaDeEventos, prog);
		
	}
	
	al_destroy_event_queue(filaDeEventos);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_destroy_display(display);
	
	

	return 0;
}
