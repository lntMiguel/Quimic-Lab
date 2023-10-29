#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_ttf.h>
#include "Jogo 2D/botoes.h"

//variaveis globais
int width = 900, height = 600;
int mouseX, mouseY;

int main() {
	//inicialização
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	
	//Display
	ALLEGRO_DISPLAY* display = al_create_display(1213, 681);
	al_set_window_title(display, "Prova de conceito - PI");

	//Bitmaps
	ALLEGRO_BITMAP* buffer, * background, * vinagreImg, * bicarbonatoImg, * recipiente, * cientista, *balao;
	background = al_load_bitmap("imagens/fundo.png");
	cientista = al_load_bitmap("imagens/cientista.png");
	vinagreImg = al_load_bitmap("imagens/vinagre.png");
	bicarbonatoImg = al_load_bitmap("imagens/bicarbonato.png");
	recipiente = al_load_bitmap("imagens/recipiente.png");
	balao = al_load_bitmap("imagens/balao.png");

	//Fila de eventos
	ALLEGRO_EVENT_QUEUE* filaDeEventos = filaDeEventos = al_create_event_queue();
	al_register_event_source(filaDeEventos, al_get_display_event_source(display));

	//Load da fonte
	ALLEGRO_FONT* font, *fonteBalao;
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	fonteBalao = al_load_ttf_font("fontes/fonteBalao.ttf", 20, 0);

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

	buffer = al_create_bitmap(width, height);

	//Botões
	Botoes* vinagre = criarBotao(101, 74, 800, 300, 82, 152, vinagreImg);
	Botoes* bicarbonato = criarBotao(46, 50, 450, 350, 108, 100, bicarbonatoImg);

	//registrando eventos
	al_register_event_source(filaDeEventos, al_get_timer_event_source(timer));
	al_register_event_source(filaDeEventos, al_get_mouse_event_source());

	//start timer
	al_start_timer(timer);

	// variaveis booleanas
	bool jogando = true, clicouVinagre = false, errou = false, concluido = false;
	
	while (jogando) {
		
		//registrando eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(filaDeEventos, &evento);

		//fechar janela
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

			jogando = false;
		}

		//registrando posição do mouse
		else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {

			mouseX = evento.mouse.x;
			mouseY = evento.mouse.y;
		}
		
		//desenhos
		al_clear_to_color(al_map_rgb(255, 0, 255));
		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(cientista, 150, 300, 0);
		al_draw_bitmap(recipiente, 590, 250, 0);
		desenharBotao(vinagre);
		desenharBotao(bicarbonato);

		//logica de jogo
		if (inputBotao(vinagre, mouseX, mouseY)) {
			
			al_draw_text(font, al_map_rgb(0, 0, 0), 730, 250, 0, "Vinagre (CH3COOH)");
				
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {
				
				clicouVinagre = true;
				recipiente = al_load_bitmap("imagens/recipienteVinagre.png");
			}	
		}
			
		else if (inputBotao(bicarbonato, mouseX, mouseY)) {
				
			al_draw_text(font, al_map_rgb(0, 0, 0), 380, 300, 0, "Bicarbonato (NaHCO3)");
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {
				
				if (clicouVinagre == true) {

					recipiente = al_load_bitmap("imagens/recipienteVB.png");
					concluido = true;
				}
				else
					errou = true;
			}	 
		}
			if (errou) {

				al_draw_bitmap(balao, 320, 150, 0);
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 420, 220, 0, "Ops... A ordem dos");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 430, 240, 0, "reagentes e muito");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 400, 260, 0, "importante para que a");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 360, 280, 0, "reacao ocorra corretamente.");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 430, 320, 0, "Tente novamente.");
			}

			if (concluido) {

				recipiente = al_load_bitmap("imagens/recipienteFeito.png");
				al_draw_bitmap(balao, 290, 130, 0);
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 360, 200, 0, "Voce conseguiu produzir");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 400, 220, 0, "a reacao esperada.");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 350, 250, 0, "Ate que enfim contrataram");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 350, 270, 0, "um estagiario que saiba");
				al_draw_text(fonteBalao, al_map_rgb(0, 0, 0), 420, 290, 0, "fazer algo.");
			}

		al_flip_display();
	}

	al_destroy_display(display);
	al_destroy_event_queue(filaDeEventos);
	al_destroy_bitmap(cientista);
	al_destroy_bitmap(background);
	al_destroy_bitmap(recipiente);
	al_destroy_bitmap(balao);
	destruirBotao(vinagre);
	destruirBotao(bicarbonato);

	return 0;
}
