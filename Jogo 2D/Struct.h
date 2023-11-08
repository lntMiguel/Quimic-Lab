#ifndef Struct_H
#define Struct_H

#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>

//Aqui contem todas as structs

//"Objetos(cientista, elementos, etc)"
typedef struct obj { // <- obj recebe malloc
	int x, y, largura, altura, wx, wy;
	ALLEGRO_BITMAP* imagem; 

} Objeto;


;
typedef struct cenario {
	ALLEGRO_BITMAP* fundo; // <- cenario recebe malloc
	Objeto* cientista;// <- cada obj recebe malloc
	Objeto* bicarbonato;
	Objeto* vinagre;

} Cenario;

typedef struct progresso {
	int proximaReacao;
	int reacoes[7];
	int fimDeJogo;
	Cenario* cenario; // <- cenario recebe malloc
} Prog;

#endif
