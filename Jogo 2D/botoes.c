#include "botoes.h"

//construtor
Botoes* criarBotao(int _wx, int _wy, int _x, int _y, int _w, int _h, ALLEGRO_BITMAP* _imagem) {
	Botoes* b = (Botoes*)malloc(sizeof(Botoes));
	b->x = _x;
	b->y = _y;
	b->wx = _wx;
	b->wy = _wy;
	b->w = _w;
	b->h = _h;
	b->imagem = _imagem;

	return b;
}

//métodos
void desenharBotao(Botoes* b) {
	al_draw_bitmap_region(b->imagem, b->wx, b->wy, b->w, b->h, b->x, b->y, 0);
}

bool inputBotao(Botoes* b, int mouseX, int mouseY) {
	return mouseX > b->x && mouseX < b->x + b->w
		&& mouseY > b->y && mouseY < b->y + b->h;
}

void destruirBotao(Botoes* b) {
	free(b);
};