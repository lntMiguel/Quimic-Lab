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
ALLEGRO_BITMAP *buffer, *background, *vinagreImg, *bicarbonatoImg, *recipiente;

int main() {
	//inicialização
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	
	//criando variaveis globais e populando 
	ALLEGRO_DISPLAY* display = al_create_display(1213, 681);
	al_set_window_title(display, "Prova de conceito - PI");
	ALLEGRO_EVENT_QUEUE* filaDeEventos = filaDeEventos = al_create_event_queue();
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	ALLEGRO_BITMAP* cientista;
	buffer = al_create_bitmap(width, height);
	al_register_event_source(filaDeEventos, al_get_display_event_source(display));
	background = al_load_bitmap("imagens/fundo.png");	
	cientista = al_load_bitmap("imagens/cientista.png");
	vinagreImg = al_load_bitmap("imagens/vinagre.png");
	bicarbonatoImg = al_load_bitmap("imagens/bicarbonato.png");
	Botoes* vinagre = criarBotao(101, 74, 800, 300, 82, 152, vinagreImg);
	Botoes* bicarbonato = criarBotao(46, 50, 450, 350, 108, 100, bicarbonatoImg);
	recipiente = al_load_bitmap("imagens/recipiente.png");

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
		desenharBotao(vinagre);
		desenharBotao(bicarbonato);
		al_draw_bitmap(recipiente, 590, 250, 0);

		//logica de jogo
		if (inputBotao(vinagre, mouseX, mouseY)) {
			
			al_draw_text(font, al_map_rgb(0, 0, 0), 800, 250, 0, "vinagre");
				
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {
				
				clicouVinagre = true;
				recipiente = al_load_bitmap("imagens/recipienteVinagre.png");
				
			}
			
		}
			
		else if (inputBotao(bicarbonato, mouseX, mouseY)) {
				
			al_draw_text(font, al_map_rgb(0, 0, 0), 450, 250, 0, "Bicarbonato");
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {
				
				if (clicouVinagre == true) {
					recipiente = al_load_bitmap("imagens/recipienteVB.png");
					concluido = true;
				}
				else
					errou = true;
			}
			 
		}
			if(errou)
				al_draw_text(font, al_map_rgb(0, 0, 0), 800, 250, 0, "Fez Errado");

			if (concluido) {
				recipiente = al_load_bitmap("imagens/recipienteFeito.png");
				al_draw_text(font, al_map_rgb(0, 0, 0), 800, 250, 0, "Reacao concluida");
				
			}

		al_flip_display();
		
	}

	al_destroy_display(display);
	al_destroy_event_queue(filaDeEventos);
	al_destroy_bitmap(cientista);
	al_destroy_bitmap(background);
	destruirBotao(vinagre);
	destruirBotao(bicarbonato);
	al_destroy_bitmap(recipiente);
	
	
	return 0;
}
