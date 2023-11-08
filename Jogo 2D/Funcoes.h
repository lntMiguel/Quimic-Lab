#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdbool.h>
#include "Struct.h"

#ifndef Funcoes_H
#define Funcoes_H
bool mouseHover(int mouseX, int mouseY, Objeto* objeto) {
	return mouseX > objeto->x && mouseX < objeto->x + objeto->largura 
		&& mouseY > objeto->y && mouseY < objeto->y + objeto->altura;
}
	

;
#endif