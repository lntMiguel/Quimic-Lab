#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdbool.h>
#include "Struct.h"

#ifndef Funcoes_H
#define Funcoes_H
bool mouseHover(int mouseX, int mouseY, int x, int y, int largura, int altura) {
	return mouseX > x && mouseX < x + largura 
		&& mouseY > y && mouseY < y + altura;
}

void desenhaRegentes(Prog* progresso) {
	if(progresso->cenario->acido->naEstante)
		al_draw_bitmap(progresso->cenario->acido->imagemEstante, progresso->cenario->acido->x, progresso->cenario->acido->y, 0);
	
	if (progresso->cenario->acucar->naEstante)
		al_draw_bitmap(progresso->cenario->acucar->imagemEstante, progresso->cenario->acucar->x, progresso->cenario->acucar->y, 0);
	
	if (progresso->cenario->agua->naEstante)
		al_draw_bitmap(progresso->cenario->agua->imagemEstante, progresso->cenario->agua->x, progresso->cenario->agua->y, 0);
	
	if (progresso->cenario->aluminio->naEstante)
		al_draw_bitmap(progresso->cenario->aluminio->imagemEstante, progresso->cenario->aluminio->x, progresso->cenario->aluminio->y, 0);
	
	if (progresso->cenario->bicarbonato->naEstante)
		al_draw_bitmap(progresso->cenario->bicarbonato->imagemEstante, progresso->cenario->bicarbonato->x, progresso->cenario->bicarbonato->y, 0);
	
	if (progresso->cenario->cDeCobre->naEstante)
		al_draw_bitmap(progresso->cenario->cDeCobre->imagemEstante, progresso->cenario->cDeCobre->x, progresso->cenario->cDeCobre->y, 0);
	
	if (progresso->cenario->comprimido->naEstante)
		al_draw_bitmap(progresso->cenario->comprimido->imagemEstante, progresso->cenario->comprimido->x, progresso->cenario->comprimido->y, 0);
	
	if (progresso->cenario->coranteG->naEstante)
		al_draw_bitmap(progresso->cenario->coranteG->imagemEstante, progresso->cenario->coranteG->x, progresso->cenario->coranteG->y, 0);
	
	if (progresso->cenario->coranteR->naEstante)
		al_draw_bitmap(progresso->cenario->coranteR->imagemEstante, progresso->cenario->coranteR->x, progresso->cenario->coranteR->y, 0);
	
	if (progresso->cenario->hidrogenio->naEstante)
		al_draw_bitmap(progresso->cenario->hidrogenio->imagemEstante, progresso->cenario->hidrogenio->x, progresso->cenario->hidrogenio->y, 0);
	
	if (progresso->cenario->luminol->naEstante)
		al_draw_bitmap(progresso->cenario->luminol->imagemEstante, progresso->cenario->luminol->x, progresso->cenario->luminol->y, 0);
	
	if (progresso->cenario->macarico->naEstante)
		al_draw_bitmap(progresso->cenario->macarico->imagemEstante, progresso->cenario->macarico->x, progresso->cenario->macarico->y, 0);
	
	if (progresso->cenario->oleo->naEstante)
		al_draw_bitmap(progresso->cenario->oleo->imagemEstante, progresso->cenario->oleo->x, progresso->cenario->oleo->y, 0);
	
	if (progresso->cenario->potassio->naEstante)
		al_draw_bitmap(progresso->cenario->potassio->imagemEstante, progresso->cenario->potassio->x, progresso->cenario->potassio->y, 0);
	
	//if (progresso->cenario->recipiente->naEstante)
		//al_draw_bitmap(progresso->cenario->recipiente->imagemEstante, progresso->cenario->recipiente->x, progresso->cenario->recipiente->y, 0);
	
	if (progresso->cenario->soda->naEstante)
		al_draw_bitmap(progresso->cenario->soda->imagemEstante, progresso->cenario->soda->x, progresso->cenario->soda->y, 0);
	
	if (progresso->cenario->vinagre->naEstante)
		al_draw_bitmap(progresso->cenario->vinagre->imagemEstante, progresso->cenario->vinagre->x, progresso->cenario->vinagre->y, 0);
}

void  desenharTextos(Prog* progresso, ALLEGRO_FONT* font, int mouseX, int mouseY) {
	if (mouseHover(mouseX, mouseY, progresso->cenario->acido->x, progresso->cenario->acido->y, 
		progresso->cenario->acido->largura, progresso->cenario->acido->altura) && progresso->cenario->acido->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1070, 115, 0, "Acido Cloridrico");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->acucar->x, progresso->cenario->acucar->y, 
		progresso->cenario->acucar->largura, progresso->cenario->acucar->altura ) && progresso->cenario->acucar->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1360, 220, 0, "Acucar");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->agua->x, progresso->cenario->agua->y, 
		progresso->cenario->agua->largura, progresso->cenario->agua->altura) && progresso->cenario->agua->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1375, 125, 0, "Agua");
	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->aluminio->x, progresso->cenario->aluminio->y, 
		progresso->cenario->aluminio->largura, progresso->cenario->aluminio->altura) && progresso->cenario->aluminio->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1103, 330, 0, "Aluminio");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->bicarbonato->x, progresso->cenario->bicarbonato->y, 
		progresso->cenario->bicarbonato->largura, progresso->cenario->bicarbonato->altura) && progresso->cenario->bicarbonato->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 960, 115, 0, "Bicarbonato");
	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->cDeCobre->x, progresso->cenario->cDeCobre->y, 
		progresso->cenario->cDeCobre->largura, progresso->cenario->cDeCobre->altura) && progresso->cenario->cDeCobre->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1190, 110, 0, "Cloreto de Cobre");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->comprimido->x, progresso->cenario->comprimido->y, 
		progresso->cenario->comprimido->largura, progresso->cenario->comprimido->altura) && progresso->cenario->comprimido->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 860, 215, 0, "Comprimido Efervescente");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->coranteG->x, progresso->cenario->coranteG->y, 
		progresso->cenario->coranteG->largura, progresso->cenario->coranteG->altura) && progresso->cenario->coranteG->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1115, 230, 0, "Corante Verde");
	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->coranteR->x, progresso->cenario->coranteR->y, 
		progresso->cenario->coranteR->largura, progresso->cenario->coranteR->altura) && progresso->cenario->coranteR->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1235, 335, 0, "Corante Vermelho");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->hidrogenio->x, progresso->cenario->hidrogenio->y, 
		progresso->cenario->hidrogenio->largura, progresso->cenario->hidrogenio->altura) && progresso->cenario->hidrogenio->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1020, 10, 0, "Peroxido de Hidrogenio");
	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->luminol->x, progresso->cenario->luminol->y, 
		progresso->cenario->luminol->largura, progresso->cenario->luminol->altura) && progresso->cenario->luminol->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1000, 20, 0, "Luminol");
	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->macarico->x, progresso->cenario->macarico->y, 
		progresso->cenario->macarico->largura, progresso->cenario->macarico->altura) && progresso->cenario->macarico->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1350, 15, 0, "Macarico");
	
	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->oleo->x, progresso->cenario->oleo->y, 
		progresso->cenario->oleo->largura, progresso->cenario->oleo->altura) && progresso->cenario->oleo->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1260, 230, 0, "Oleo");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->potassio->x, progresso->cenario->potassio->y, 
		progresso->cenario->potassio->largura, progresso->cenario->potassio->altura) && progresso->cenario->potassio->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1120, 36, 0, "Permanganato de Potassio");

	}

	//if (mouseHover(mouseX, mouseY, progresso->cenario->recipiente->x, progresso->cenario->recipiente->y, progresso->cenario->recipiente->largura, progresso->cenario->recipiente->altura)) {}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->soda->x, progresso->cenario->soda->y, 
		progresso->cenario->soda->largura, progresso->cenario->soda->altura) && progresso->cenario->soda->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 1305, 320, 0, "Soda Caustica");

	}

	else if (mouseHover(mouseX, mouseY, progresso->cenario->vinagre->x, progresso->cenario->vinagre->y, 
		progresso->cenario->vinagre->largura, progresso->cenario->vinagre->altura) && progresso->cenario->vinagre->naEstante) {
		al_draw_text(font, al_map_rgb(0, 0, 0), 992, 330, 0, "Vinagre");
	}
}

void destruirBitmaps(Prog* progresso) {
	al_destroy_bitmap(progresso->cenario->acido->imagemEstante);
	al_destroy_bitmap(progresso->cenario->acucar->imagemEstante);
	al_destroy_bitmap(progresso->cenario->agua->imagemEstante);
	al_destroy_bitmap(progresso->cenario->aluminio->imagemEstante);
	al_destroy_bitmap(progresso->cenario->bicarbonato->imagemEstante);
	al_destroy_bitmap(progresso->cenario->cDeCobre->imagemEstante);
	al_destroy_bitmap(progresso->cenario->comprimido->imagemEstante);
	al_destroy_bitmap(progresso->cenario->coranteG->imagemEstante);
	al_destroy_bitmap(progresso->cenario->coranteR->imagemEstante);
	al_destroy_bitmap(progresso->cenario->hidrogenio->imagemEstante);
	al_destroy_bitmap(progresso->cenario->luminol->imagemEstante);
	al_destroy_bitmap(progresso->cenario->macarico->imagemEstante);
	al_destroy_bitmap(progresso->cenario->oleo->imagemEstante);
	al_destroy_bitmap(progresso->cenario->potassio->imagemEstante);
	al_destroy_bitmap(progresso->cenario->soda->imagemEstante);
	al_destroy_bitmap(progresso->cenario->vinagre->imagemEstante);
	
}

void bloquearCliques(Prog* progresso) {
	progresso->cenario->acido->podeClicar = false;
	progresso->cenario->acucar->podeClicar = false;
	progresso->cenario->agua->podeClicar = false;
	progresso->cenario->aluminio->podeClicar = false;
	progresso->cenario->bicarbonato->podeClicar = false;
	progresso->cenario->cDeCobre->podeClicar = false;
	progresso->cenario->comprimido->podeClicar = false;
	progresso->cenario->coranteG->podeClicar = false;
	progresso->cenario->coranteR->podeClicar = false;
	progresso->cenario->hidrogenio->podeClicar = false;
	progresso->cenario->luminol->podeClicar = false;
	progresso->cenario->macarico->podeClicar = false;
	progresso->cenario->oleo->podeClicar = false;
	progresso->cenario->potassio->podeClicar = false;
	progresso->cenario->soda->podeClicar = false;
	progresso->cenario->vinagre->podeClicar = false;
}

void liberearCliques(Prog* progresso) {
	progresso->cenario->acido->podeClicar = true;
	progresso->cenario->acucar->podeClicar = true;
	progresso->cenario->agua->podeClicar = true;
	progresso->cenario->aluminio->podeClicar = true;
	progresso->cenario->bicarbonato->podeClicar = true;
	progresso->cenario->cDeCobre->podeClicar = true;
	progresso->cenario->comprimido->podeClicar = true;
	progresso->cenario->coranteG->podeClicar = true;
	progresso->cenario->coranteR->podeClicar = true;
	progresso->cenario->hidrogenio->podeClicar = true;
	progresso->cenario->luminol->podeClicar = true;
	progresso->cenario->macarico->podeClicar = true;
	progresso->cenario->oleo->podeClicar = true;
	progresso->cenario->potassio->podeClicar = true;
	progresso->cenario->soda->podeClicar = true;
	progresso->cenario->vinagre->podeClicar = true;
}

void carregarImg(Prog* progresso) {
	progresso->cenario->cientista->imagem = al_load_bitmap("imagens/cientista.png");
	progresso->cenario->bicarbonato->imagemEstante = al_load_bitmap("imagens/bicarbonatoEstante.png");
	progresso->cenario->vinagre->imagemEstante = al_load_bitmap("imagens/vinagreEstante.png");
	progresso->cenario->bicarbonatoColher->imagemEstante = al_load_bitmap("imagens/bicarbonatoEstante.png");
	progresso->cenario->acido->imagemEstante = al_load_bitmap("imagens/acidoEstante.png");
	progresso->cenario->cDeCobre->imagemEstante = al_load_bitmap("imagens/cDeCobreEstante.png");
	progresso->cenario->acucar->imagemEstante = al_load_bitmap("imagens/acucarEstante.png");
	progresso->cenario->agua->imagemEstante = al_load_bitmap("imagens/aguaEstante.png");
	progresso->cenario->aluminio->imagemEstante = al_load_bitmap("imagens/aluminioEstante.png");
	progresso->cenario->comprimido->imagemEstante = al_load_bitmap("imagens/comprimidoEstante.png");
	progresso->cenario->coranteG->imagemEstante = al_load_bitmap("imagens/coranteGEstante.png");
	progresso->cenario->coranteR->imagemEstante = al_load_bitmap("imagens/coranteREstante.png");
	progresso->cenario->hidrogenio->imagemEstante = al_load_bitmap("imagens/hidrogenioEstante.png");
	progresso->cenario->luminol->imagemEstante = al_load_bitmap("imagens/luminolEstante.png");
	progresso->cenario->macarico->imagemEstante = al_load_bitmap("imagens/macaricoEstante.png");
	progresso->cenario->oleo->imagemEstante = al_load_bitmap("imagens/oleoEstante.png");
	progresso->cenario->potassio->imagemEstante = al_load_bitmap("imagens/potassioEstante.png");
	progresso->cenario->soda->imagemEstante = al_load_bitmap("imagens/sodaEstante.png");
	progresso->cenario->fundo = al_load_bitmap("imagens/fundo.png");
}
#endif