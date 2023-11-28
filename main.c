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
#include <allegro5/allegro_primitives.h>


//variaveis globais

int main() {
	//inicialização
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_init_primitives_addon();
	
	//Display
	ALLEGRO_DISPLAY* display = al_create_display(1500, 844);
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
	
	progresso.proximaReacao = 3;
	progresso.fimDeJogo = 0;
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

	progresso.cenario->bicarbonato = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->bicarbonato->imagemEstante = al_load_bitmap("imagens/bicarbonatoEstante.png");
	progresso.cenario->bicarbonato->altura = 100;
	progresso.cenario->bicarbonato->largura = 108;
	progresso.cenario->bicarbonato->wx = 0;
	progresso.cenario->bicarbonato->wy = 0;
	progresso.cenario->bicarbonato->x = 1010;
	progresso.cenario->bicarbonato->y = 130;
	progresso.cenario->bicarbonato->podeClicar = true;
	progresso.cenario->bicarbonato->naEstante = true;
	                   
	progresso.cenario->vinagre = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->vinagre->imagemEstante = al_load_bitmap("imagens/vinagreEstante.png");
	progresso.cenario->vinagre->altura = 95;
	progresso.cenario->vinagre->largura = 70;
	progresso.cenario->vinagre->wx = 0;
	progresso.cenario->vinagre->wy = 0;
	progresso.cenario->vinagre->x = 1010;
	progresso.cenario->vinagre->y = 325;
	progresso.cenario->vinagre->podeClicar = true;
	progresso.cenario->vinagre->naEstante = true;

	progresso.cenario->bicarbonatoColher = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->bicarbonatoColher->imagemEstante = al_load_bitmap("imagens/bicarbonatoEstante.png");
	progresso.cenario->bicarbonatoColher->altura = 100;
	progresso.cenario->bicarbonatoColher->largura = 108;
	progresso.cenario->bicarbonatoColher->wx = 0;
	progresso.cenario->bicarbonatoColher->wy = 0;
	progresso.cenario->bicarbonatoColher->x = 1010;
	progresso.cenario->bicarbonatoColher->y = 130;
	progresso.cenario->bicarbonatoColher->podeClicar = true;
	progresso.cenario->bicarbonatoColher->naEstante = true;

	progresso.cenario->acido = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->acido->imagemEstante = al_load_bitmap("imagens/acidoEstante.png");
	progresso.cenario->acido->altura = 95;
	progresso.cenario->acido->largura = 70;
	progresso.cenario->acido->wx = 0;
	progresso.cenario->acido->wy = 0;
	progresso.cenario->acido->x = 1130;
	progresso.cenario->acido->y = 115;
	progresso.cenario->acido->podeClicar = true;
	progresso.cenario->acido->naEstante = true;

	progresso.cenario->cDeCobre = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->cDeCobre->imagemEstante = al_load_bitmap("imagens/cDeCobreEstante.png");
	progresso.cenario->cDeCobre->altura = 75;
	progresso.cenario->cDeCobre->largura = 70;
	progresso.cenario->cDeCobre->wx = 0;
	progresso.cenario->cDeCobre->wy = 0;
	progresso.cenario->cDeCobre->x = 1250;
	progresso.cenario->cDeCobre->y = 130;
	progresso.cenario->cDeCobre->podeClicar = true;
	progresso.cenario->cDeCobre->naEstante = true;

	progresso.cenario->acucar = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->acucar->imagemEstante = al_load_bitmap("imagens/acucarEstante.png");
	progresso.cenario->acucar->altura = 66;
	progresso.cenario->acucar->largura = 70;
	progresso.cenario->acucar->wx = 0;
	progresso.cenario->acucar->wy = 0;
	progresso.cenario->acucar->x = 1370;
	progresso.cenario->acucar->y = 247;
	progresso.cenario->acucar->podeClicar = true;
	progresso.cenario->acucar->naEstante = true;

	progresso.cenario->agua = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->agua->imagemEstante = al_load_bitmap("imagens/aguaEstante.png");
	progresso.cenario->agua->altura = 95;
	progresso.cenario->agua->largura = 70;
	progresso.cenario->agua->wx = 0;
	progresso.cenario->agua->wy = 0;
	progresso.cenario->agua->x = 1370;
	progresso.cenario->agua->y = 115;
	progresso.cenario->agua->podeClicar = true;
	progresso.cenario->agua->naEstante = true;

	progresso.cenario->aluminio = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->aluminio->imagemEstante = al_load_bitmap("imagens/aluminioEstante.png");
	progresso.cenario->aluminio->altura = 27;
	progresso.cenario->aluminio->largura = 120;
	progresso.cenario->aluminio->wx = 0;
	progresso.cenario->aluminio->wy = 0;
	progresso.cenario->aluminio->x = 1100;
	progresso.cenario->aluminio->y = 375;
	progresso.cenario->aluminio->podeClicar = true;
	progresso.cenario->aluminio->naEstante = true;

	progresso.cenario->comprimido = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->comprimido->imagemEstante = al_load_bitmap("imagens/comprimidoEstante.png");
	progresso.cenario->comprimido->altura = 59;
	progresso.cenario->comprimido->largura = 70;
	progresso.cenario->comprimido->wx = 0;
	progresso.cenario->comprimido->wy = 0;
	progresso.cenario->comprimido->x = 1010;
	progresso.cenario->comprimido->y = 248;
	progresso.cenario->comprimido->podeClicar = true;
	progresso.cenario->comprimido->naEstante = true;

	progresso.cenario->coranteG = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->coranteG->imagemEstante = al_load_bitmap("imagens/coranteGEstante.png");
	progresso.cenario->coranteG->altura = 85;
	progresso.cenario->coranteG->largura = 40;
	progresso.cenario->coranteG->wx = 0;
	progresso.cenario->coranteG->wy = 0;
	progresso.cenario->coranteG->x = 1145;
	progresso.cenario->coranteG->y = 225	;
	progresso.cenario->coranteG->podeClicar = true;
	progresso.cenario->coranteG->naEstante = true;

	progresso.cenario->coranteR = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->coranteR->imagemEstante = al_load_bitmap("imagens/coranteREstante.png");
	progresso.cenario->coranteR->altura = 83;
	progresso.cenario->coranteR->largura = 40;
	progresso.cenario->coranteR->wx = 0;
	progresso.cenario->coranteR->wy = 0;
	progresso.cenario->coranteR->x = 1265;
	progresso.cenario->coranteR->y = 335;
	progresso.cenario->coranteR->podeClicar = true;
	progresso.cenario->coranteR->naEstante = true;

	progresso.cenario->hidrogenio = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->hidrogenio->imagemEstante = al_load_bitmap("imagens/hidrogenioEstante.png");
	progresso.cenario->hidrogenio->altura = 95;
	progresso.cenario->hidrogenio->largura = 70;
	progresso.cenario->hidrogenio->wx = 0;
	progresso.cenario->hidrogenio->wy = 0;
	progresso.cenario->hidrogenio->x = 1130;
	progresso.cenario->hidrogenio->y = 15;
	progresso.cenario->hidrogenio->podeClicar = true;
	progresso.cenario->hidrogenio->naEstante = true;

	progresso.cenario->luminol = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->luminol->imagemEstante = al_load_bitmap("imagens/luminolEstante.png");
	progresso.cenario->luminol->altura = 95;
	progresso.cenario->luminol->largura = 70;
	progresso.cenario->luminol->wx = 0;
	progresso.cenario->luminol->wy = 0;
	progresso.cenario->luminol->x = 1010;
	progresso.cenario->luminol->y = 15;
	progresso.cenario->luminol->podeClicar = true;
	progresso.cenario->luminol->naEstante = true;

	progresso.cenario->macarico = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->macarico->imagemEstante = al_load_bitmap("imagens/macaricoEstante.png");
	progresso.cenario->macarico->altura = 89;
	progresso.cenario->macarico->largura = 90;
	progresso.cenario->macarico->wx = 0;
	progresso.cenario->macarico->wy = 0;
	progresso.cenario->macarico->x = 1360;
	progresso.cenario->macarico->y = 15;
	progresso.cenario->macarico->podeClicar = true;
	progresso.cenario->macarico->naEstante = true;

	progresso.cenario->oleo = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->oleo->imagemEstante = al_load_bitmap("imagens/oleoEstante.png");
	progresso.cenario->oleo->altura = 95;
	progresso.cenario->oleo->largura = 70;
	progresso.cenario->oleo->wx = 0;
	progresso.cenario->oleo->wy = 0;
	progresso.cenario->oleo->x = 1250;
	progresso.cenario->oleo->y = 220;
	progresso.cenario->oleo->podeClicar = true;
	progresso.cenario->oleo->naEstante = true;

	progresso.cenario->potassio = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->potassio->imagemEstante = al_load_bitmap("imagens/potassioEstante.png");
	progresso.cenario->potassio->altura = 59;
	progresso.cenario->potassio->largura = 70;
	progresso.cenario->potassio->wx = 0;
	progresso.cenario->potassio->wy = 0;
	progresso.cenario->potassio->x = 1250;
	progresso.cenario->potassio->y = 36;
	progresso.cenario->potassio->podeClicar = true;
	progresso.cenario->potassio->naEstante = true;

	progresso.cenario->soda = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->soda->imagemEstante = al_load_bitmap("imagens/sodaEstante.png");
	progresso.cenario->soda->altura = 100;
	progresso.cenario->soda->largura = 108;
	progresso.cenario->soda->wx = 0;
	progresso.cenario->soda->wy = 0;
	progresso.cenario->soda->x = 1370;
	progresso.cenario->soda->y = 340;
	progresso.cenario->soda->podeClicar = true;
	progresso.cenario->soda->naEstante = true;

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
