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
#include "skillTest.h"
//Função central da fase
int jogarAcidoCarbonico(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso){
	
	//struct do recipiente
	Objeto* recipiente;
	recipiente = (Objeto*)malloc(sizeof(Objeto));
	recipiente->altura = 122;
	recipiente->largura = 109;
	recipiente->imagem = al_load_bitmap("imagens/recipiente.png");
	recipiente->wx = 0;
	recipiente->wy = 0;
	recipiente->x = 590;
	recipiente->y = 250;

	Objeto* seta;
	seta = (Objeto*)malloc(sizeof(Objeto));
	seta->altura = 32;
	seta->largura = 24;
	seta->imagem = al_load_bitmap("imagens/seta.png");
	seta->wx = 4;
	seta->wy = 0;
	seta->x = 0;
	seta->y = 0;

	Objeto* teste;
	teste = (Objeto*)malloc(sizeof(Objeto));
	teste->altura = 32;
	teste->largura = 24;
	teste->imagem = al_load_bitmap("imagens/acerteVerde.png");
	teste->wx = 0;
	teste->wy = 0;
	teste->x = 0;
	teste->y = 0;

	Objeto* botao;
	botao = (Objeto*)malloc(sizeof(Objeto));
	botao->altura = 32;
	botao->largura = 24;
	botao->imagem = al_load_bitmap("imagens/botaoAdicionar.png");
	botao->wx = 0;
	botao->wy = 0;
	botao->x = 0;
	botao->y = 0;

	//fonte
	ALLEGRO_FONT* font;

	//estados do recipiente 
	ALLEGRO_BITMAP* recipienteVinagre = al_load_bitmap("imagens/recipienteVinagre.png");
	ALLEGRO_BITMAP* recipienteBicarbonato = al_load_bitmap("imagens/recipienteVB.png");
	ALLEGRO_BITMAP* recipienteFeito = al_load_bitmap("imagens/recipienteFeito.png");
	
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	
	bool sair = false;
	
	int mouseX;
	int mouseY;
	
	//estados da fase
	enum Estados {
		inicio,
		clicouVinagre,
		clicouBicarbonato,
		errou,
		acertou,
		st
	};
	
	bool podeClicar = true;
	enum Estados estado = inicio;
	
	//looping principal
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
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1 && podeClicar) {
			
			//clique no vinagre
			if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->vinagre)) {
				estado = clicouVinagre;
				acerteVerde(display, filaDeEventos, progresso);
				recipiente->imagem = recipienteVinagre;

			}
		
			//clique no bicarbonato
			else if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->bicarbonato)) {
				
				if (!estado == clicouVinagre) {
					estado = errou;
				}
				
				else {
					estado = clicouBicarbonato;
					recipiente->imagem = recipienteBicarbonato;
				}
			}
		}

		//desenhos
		al_clear_to_color(al_map_rgb(255, 0, 255));
		al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0);
		al_draw_bitmap(progresso->cenario->bicarbonato->imagem, progresso->cenario->bicarbonato->x, progresso->cenario->bicarbonato->y, 0);
		al_draw_bitmap(progresso->cenario->vinagre->imagem, progresso->cenario->vinagre->x, progresso->cenario->vinagre->y, 0);
		al_draw_bitmap(recipiente->imagem, recipiente->x, recipiente->y, 0);

		//texto quando o mouse passar em cima dos elementos 
		if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->vinagre) && podeClicar) {

			al_draw_text(font, al_map_rgb(0, 0, 0), 730, 250, 0, "Vinagre (CH3COOH)");
		}
		
		else if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->bicarbonato) && podeClicar) {

			al_draw_text(font, al_map_rgb(0, 0, 0), 380, 300, 0, "Bicarbonato (NaHCO3)");
		}
		
		//texto se acertou
		if (estado == acertou) {
			
			al_draw_text(font, al_map_rgb(0, 0, 0), 360, 200, 0, "Voce conseguiu produzir");
			al_draw_text(font, al_map_rgb(0, 0, 0), 400, 220, 0, "a reacao esperada.");
			al_draw_text(font, al_map_rgb(0, 0, 0), 350, 250, 0, "Ate que enfim contrataram");
			al_draw_text(font, al_map_rgb(0, 0, 0), 350, 270, 0, "um estagiario que saiba");
			al_draw_text(font, al_map_rgb(0, 0, 0), 420, 290, 0, "fazer algo.");
		
		}
		
		//texto se errou
		if (estado == errou) {
			al_draw_text(font, al_map_rgb(0, 0, 0), 420, 220, 0, "Ops... A ordem dos");
			al_draw_text(font, al_map_rgb(0, 0, 0), 430, 240, 0, "reagentes e muito");
			al_draw_text(font, al_map_rgb(0, 0, 0), 400, 260, 0, "importante para que a");
			al_draw_text(font, al_map_rgb(0, 0, 0), 360, 280, 0, "reacao ocorra corretamente.");
			al_draw_text(font, al_map_rgb(0, 0, 0), 430, 320, 0, "Tente novamente.");
		}
		/*if (sequenciaCerta[1] == true) {
				progresso->proximaReacao = 1;
				sair = true;
			}*/
		
		al_flip_display();
	
	}

	
	al_destroy_bitmap(recipiente->imagem);
	al_destroy_bitmap(progresso->cenario->fundo);
	al_destroy_bitmap(progresso->cenario->bicarbonato->imagem);
	al_destroy_bitmap(progresso->cenario->vinagre->imagem);
	free(recipiente);
	
	return 0;
}

