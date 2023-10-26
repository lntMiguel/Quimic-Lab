#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

int main() {

	al_init();
	al_init_image_addon();

	ALLEGRO_DISPLAY* display = NULL;
	display = al_create_display(1213, 681);
	al_set_window_title(display, "Prova de conceito - PI");

	ALLEGRO_EVENT_QUEUE* filaDeEventos = NULL;
	filaDeEventos = al_create_event_queue();
	al_register_event_source(filaDeEventos, al_get_display_event_source(display));

	ALLEGRO_BITMAP* background;
	background = al_load_bitmap("imagens/fundo.png");

	ALLEGRO_BITMAP* cientista;
	cientista = al_load_bitmap("imagens/cientista.png");
	al_convert_mask_to_alpha(cientista, al_map_rgb(255, 255, 255));

	ALLEGRO_BITMAP* vinagre;
	vinagre = al_load_bitmap("imagens/vinagre.png");
	al_convert_mask_to_alpha(vinagre, al_map_rgb(255, 255, 255));

	ALLEGRO_BITMAP* bicarbonato;
	bicarbonato = al_load_bitmap("imagens/bicarbonato.png");
	al_convert_mask_to_alpha(bicarbonato, al_map_rgb(0, 0, 0));

	ALLEGRO_BITMAP* recipiente;
	recipiente = al_load_bitmap("imagens/recipiente.png");
	al_convert_mask_to_alpha(recipiente, al_map_rgb(57, 16, 123));

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

	al_register_event_source(filaDeEventos, al_get_timer_event_source(timer));

	al_start_timer(timer);

	bool jogando = true;

	while (jogando) {

		ALLEGRO_EVENT evento;
		al_wait_for_event(filaDeEventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			jogando = false;
		}

		else if (evento.type == ALLEGRO_EVENT_TIMER) {

		}

		al_clear_to_color(al_map_rgb(255, 0, 255));

		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(cientista, 150, 300, 0);
		al_draw_bitmap(vinagre, 750, 300, 0);
		al_draw_bitmap(bicarbonato, 400, 370, 0);
		al_draw_bitmap(recipiente, 590, 250, 0);

		al_flip_display();
	}

	al_destroy_display(display);
	al_destroy_event_queue(filaDeEventos);
	al_destroy_bitmap(cientista);
	al_destroy_bitmap(background);
	al_destroy_bitmap(vinagre);
	al_destroy_bitmap(bicarbonato);
	al_destroy_bitmap(recipiente);

	return 0;
}