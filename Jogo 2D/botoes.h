#ifndef BOTOES_H_INCLUED
#define BOTOES_H_INCLUED

#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//"classe botoes"
typedef struct botoes {
	int wx, wy, x, y, w, h;
	ALLEGRO_BITMAP* imagem;

}Botoes;

//construtor
Botoes* criarBotao(int _wx, int _wy, int _x, int _y, int _w, int _h, ALLEGRO_BITMAP* imagem);

//metodos
bool inputBotao(Botoes* b, int mouseX, int mouseY);
void desenharBotao(Botoes* b);
void destruirBotao(Botoes* b);

#endif
#pragma once
