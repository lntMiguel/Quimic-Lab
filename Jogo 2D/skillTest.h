#ifndef skillTest_H
#define skillTest_H

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
#include <allegro5/allegro_primitives.h>
#include <math.h>

int mouseX, mouseY;

bool acerteVerde(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {

	Objeto* seta;
	seta = (Objeto*)malloc(sizeof(Objeto));
	seta->altura = 32;
	seta->largura = 24;
	seta->imagem = al_load_bitmap("imagens/seta.png");
	seta->wx = 4;
	seta->wy = 0;
	seta->x = 503;
	seta->y = 345;

	Objeto* teste;
	teste = (Objeto*)malloc(sizeof(Objeto));
	teste->altura = 75;
	teste->largura = 500;
	teste->imagem = al_load_bitmap("imagens/barra.png");
	teste->wx = 0;
	teste->wy = 0;
	teste->x = 500;
	teste->y = 340;

	ALLEGRO_BITMAP* botaoAdd = al_load_bitmap("imagens/btAdd.png");
	ALLEGRO_BITMAP* botaoAddH = al_load_bitmap("imagens/adss.png");
	
	Objeto* botao;
	botao = (Objeto*)malloc(sizeof(Objeto));
	botao->altura = 98;
	botao->largura = 308;
	botao->imagem = botaoAdd;
	botao->wx = 0;
	botao->wy = 0;
	botao->x = 609;
	botao->y = 500;

	bool sair = false;
	bool acertou = false;
	int velocidade = 2;
	
	
	ALLEGRO_FONT* font;
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	
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

		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

			if (mouseHover(mouseX, mouseY, botao->x, botao->y, botao->largura, botao->altura)) {
				
				if (seta->x >= 689 && seta->x <= 777) {
					acertou = true;
				}

				sair = true;
			}

		}
		
		if (mouseHover(mouseX, mouseY, botao->x, botao->y, botao->largura, botao->altura)) {
			botao->imagem = botaoAddH;
		}
		else
			botao->imagem = botaoAdd;
			
		//al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0); 
		//desenhaRegentes(progresso);
		al_draw_bitmap(teste->imagem, teste->x, teste->y, 0);
		al_draw_bitmap(seta->imagem, seta->x, seta->y, 0);
		al_draw_bitmap(botao->imagem, botao->x, botao->y, 0);
		
		seta->x = seta->x + velocidade;

		if (seta->x <= 503) {
			velocidade = 2;
		}
		if (seta->x >= 960) {
			velocidade = -2;
		}

		
		al_flip_display();
	}

	al_destroy_bitmap(seta->imagem);
	al_destroy_bitmap(teste->imagem);
	al_destroy_bitmap(botao->imagem);
	free(seta);
	free(teste);
	free(botao);
	
	return acertou;
}

bool equilibrio(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {

	Objeto* colher;
	colher = (Objeto*)malloc(sizeof(Objeto));
	colher->altura = 300;
	colher->largura = 150;
	colher->imagem = al_load_bitmap("imagens/colher.png");
	colher->wx = 0;
	colher->wy = 0;
	colher->x = 928;
	colher->y = 592;

	ALLEGRO_BITMAP* fundo = al_load_bitmap("imagens/fundoEquilibrio.png");
	bool sair = false;
	bool acertou = false;
	float velocidade = 0.5;
	float angulo = 318;
	int timer = 0;

	ALLEGRO_FONT* font;
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);

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

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

			if (velocidade == 0.5) {
				velocidade = -0.5;

			}
			else if (velocidade == -0.5)
				velocidade = 0.5;

		}

		angulo += velocidade;
		
		if (angulo > 360) 
			angulo = 0;
		
		else if (angulo < 0) 
			angulo = 360;
		

		
		if (angulo == 7 || angulo == 317) {
			acertou = false;
			sair = true;
		}
		
		else if (timer >= 600) {
			acertou = true;
			sair = true;
		}
		
		timer++;
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_bitmap(fundo, 0, 0, 0);
		al_draw_rotated_bitmap(colher->imagem, 300 / 2, 150 / 2, 928, 592, angulo * 3.14159 / 180, 0);
		
		al_flip_display();
	}

	al_destroy_bitmap(colher->imagem);
	al_destroy_bitmap(fundo);
	al_destroy_font(font);
	free(colher);
	

	return acertou;
}

int acerteBecker(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso){
	bool sair = false;
	int arrastando = 0;
	int angulo = 0;//Usado para calculos
	int anguloArco = 45;//Usado para desenho
	int velocidade = 0;
	int contador = 0;//Usado para "animar" o tiro
	bool acertou = false;
	int tentativas = 3;


	while (!sair) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(filaDeEventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			progresso->fimDeJogo = true;

		}
		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouseX = evento.mouse.x;
			mouseY = evento.mouse.y;
		}
		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

			//Marcador de Velocidade
			if (mouseHover(mouseX, mouseY, progresso->cenario->marcaV->x, progresso->cenario->marcaV->y, 30, 10))
			{
				arrastando = 1;
				progresso->cenario->marcaH->cliqueX = MapearDistancia(evento.mouse.x, progresso->cenario->marcaH->x);
				progresso->cenario->marcaH->cliqueY = MapearDistancia(evento.mouse.y, progresso->cenario->marcaH->y);
			}
			//Marcador de Angulo
			else if (mouseHover(mouseX, mouseY, progresso->cenario->marcaH->x, progresso->cenario->marcaH->y, 10, 30))
			{
				arrastando = 2;
				progresso->cenario->marcaV->cliqueX = MapearDistancia(evento.mouse.x, progresso->cenario->marcaV->x);
				progresso->cenario->marcaV->cliqueY = MapearDistancia(evento.mouse.y, progresso->cenario->marcaV->y);
			}

			else if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->barraH->x, progresso->cenario->barraH->y, progresso->cenario->barraH->largura, progresso->cenario->barraH->altura))//Deixa o user clicar na barra pra mover a marca
			{
				progresso->cenario->marcaV->y = evento.mouse.y - progresso->cenario->marcaV->altura / 2;//Desenha o marcador sob o mouse

				//Ajusta o marcador na barra
				if (evento.mouse.y - progresso->cenario->marcaV->altura / 2 < progresso->cenario->barraV->y)
					progresso->cenario->marcaV->y = progresso->cenario->barraV->y;
				else if (evento.mouse.y - progresso->cenario->marcaV->altura / 2 > progresso->cenario->barraV->y + progresso->cenario->barraV->altura - progresso->cenario->marcaV->altura)
					progresso->cenario->marcaV->y = progresso->cenario->barraV->y + progresso->cenario->barraV->altura - progresso->cenario->marcaV->altura;

				//Permite o marcador ser arrastado caso o btn do mouse continue precionado
				arrastando = 2;
				progresso->cenario->marcaV->cliqueX = MapearDistancia(evento.mouse.x, progresso->cenario->marcaV->x);
				progresso->cenario->marcaV->cliqueY = MapearDistancia(evento.mouse.y, progresso->cenario->marcaV->y);
			}
			else if (mouseHover(evento.mouse.x, evento.mouse.y, progresso->cenario->barraH->x, progresso->cenario->barraH->y, progresso->cenario->barraH->largura, progresso->cenario->barraH->altura))//Deixa o user clicar na barra pra mover a marca
			{
				progresso->cenario->marcaH->x = evento.mouse.x - progresso->cenario->marcaH->largura / 2;//Desenha o marcador sob o mouse

				//Ajusta o marcador na barra
				if (evento.mouse.x - progresso->cenario->marcaH->largura / 2 < progresso->cenario->barraH->x)
					progresso->cenario->marcaH->x = progresso->cenario->barraH->x;
				else if (evento.mouse.x - progresso->cenario->marcaH->largura / 2 > progresso->cenario->barraH->x + progresso->cenario->barraH->largura - progresso->cenario->marcaH->largura)
					progresso->cenario->marcaH->x = progresso->cenario->barraH->x + progresso->cenario->barraH->largura - progresso->cenario->marcaH->largura;

				//Permite o marcador ser arrastado caso o btn do mouse continue precionado
				arrastando = 1;
				progresso->cenario->marcaH->cliqueX = MapearDistancia(evento.mouse.x, progresso->cenario->marcaH->x);
				progresso->cenario->marcaH->cliqueY = MapearDistancia(evento.mouse.y, progresso->cenario->marcaH->y);
			}
			//Zera o arrastar do mouse
			else {
				arrastando = 0;
			}


		}
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			//Muda o valor do angulo do desenho
			anguloArco = 90 + (progresso->cenario->barraV->y - progresso->cenario->marcaV->y);

			int i = 0;
			//Caso o mouse estivesse movendo o marcador de angulo, muda o angulo do cálculo a velocidade e o contador da animação
			if (arrastando == 1) {
				if (tentativas > 0) {
					tentativas--;
					angulo = 90 + (progresso->cenario->barraV->y - progresso->cenario->marcaV->y);
					velocidade = 30 + (progresso->cenario->barraH->x - progresso->cenario->marcaH->x) / 3;
					contador = 1;
				}
			}

			//Volta o marcador de velocidade para o início
			progresso->cenario->marcaH->x = progresso->cenario->barraH->x + progresso->cenario->barraH->largura - 10;

			//Zera o arrastar
			arrastando = 0;
		}

		ALLEGRO_MOUSE_STATE state;

		al_get_mouse_state(&state);
		if (state.buttons & 1 && arrastando)
		{
			switch (arrastando)
			{
			case 1:
				//Muda o valor do marcador de velocidade ao ser arrastado
				if (evento.mouse.x - progresso->cenario->marcaH->cliqueX <= progresso->cenario->barraH->x) {
					//Passou pra esquerda
					progresso->cenario->marcaH->x = progresso->cenario->barraH->x;
				}
				else if (evento.mouse.x - progresso->cenario->marcaH->cliqueX + progresso->cenario->marcaH->largura >= progresso->cenario->barraH->x + progresso->cenario->barraH->largura)
				{
					//Passou pra direita
					progresso->cenario->marcaH->x = progresso->cenario->barraH->x + progresso->cenario->barraH->largura - progresso->cenario->marcaH->largura;
				}
				else {
					progresso->cenario->marcaH->x = evento.mouse.x - progresso->cenario->marcaH->cliqueX;
				}
				break;
			case 2:
				//Muda o valor do marcador de angulo ao ser arrastado
				if (evento.mouse.y - progresso->cenario->marcaV->cliqueY <= progresso->cenario->barraV->y) {
					//Passou pra esquerda
					progresso->cenario->marcaV->y = progresso->cenario->barraV->y;
				}
				else if (evento.mouse.y - progresso->cenario->marcaV->cliqueY + progresso->cenario->marcaV->altura >= progresso->cenario->barraV->y + progresso->cenario->barraV->altura)
				{
					//Passou pra direita
					progresso->cenario->marcaV->y = progresso->cenario->barraV->y + progresso->cenario->barraV->altura - progresso->cenario->marcaV->altura;
				}
				else {
					progresso->cenario->marcaV->y = evento.mouse.y - progresso->cenario->marcaV->cliqueY;
				}
				break;
			default:
				break;
			}
		}




		contador = CalcularTiro(progresso, angulo, velocidade, contador, acertou);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_bitmap(progresso->cenario->barraH->bitmap, progresso->cenario->barraH->x, progresso->cenario->barraH->y, 0);
		al_draw_bitmap(progresso->cenario->barraV->bitmap, progresso->cenario->barraV->x, progresso->cenario->barraV->y, 0);
		al_draw_bitmap(progresso->cenario->marcaH->bitmap, progresso->cenario->marcaH->x, progresso->cenario->marcaH->y, 0);
		al_draw_bitmap(progresso->cenario->marcaV->bitmap, progresso->cenario->marcaV->x, progresso->cenario->marcaV->y, 0);

		al_draw_rotated_bitmap(progresso->cenario->mao->bitmap, progresso->cenario->mao->largura / 2, progresso->cenario->mao->altura / 2, progresso->cenario->mao->x + progresso->cenario->mao->largura / 2, progresso->cenario->mao->y + progresso->cenario->mao->altura / 2, 44.7 - anguloArco * 3.14159 / 180, 0);
		al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);

		al_flip_display();
	}


	return 0;
}

int CalcularTiro(Prog* progresso,int angulo, int velocidade, int cont, bool acertou) {
	

	//Executa somente se a velocidade for maior que 0
	if (velocidade != 0)
	{
		float VelVertical = sin(angulo * 3.14159 / 180) * velocidade;//Calcula a Velociade vertical pelo seno do angulo em Radianos
		VelVertical *= -1;//Inverte o sentido da velocidade

		float VelHorizontal = cos(angulo * 3.14159 / 180) * velocidade;//Calcula a Velociade horizontal pelo cosseno do angulo em Radianos

		int t;//Var que simula o tempo

		//Posição da bolinha desenhada
		int posX = progresso->cenario->mao->x + progresso->cenario->mao->largura / 2 - 10;
		int posY = progresso->cenario->mao->y + progresso->cenario->mao->altura / 2 - 10;

		//O tempo corre até o contador que cresce a cada execução da função
		//Para dar o efeito de movimento
		for (t = 0; t <= cont; t++)
		{
			//Incrementa a posição da bolinha
			posX += VelHorizontal;
			posY += VelVertical;

			VelVertical += 0.5;//Aplica uma gravidade na velocidade vertical

			//Verifica se algo foi acertado

			if (posX >= 80 && posX <= (80 + 150) && posY >= 430 && posY <= (430 + 203))
				acertou = true;
			al_draw_bitmap(progresso->cenario->bala->bitmap, posX, posY, 0);
		}
	}

	//Aumenta o contador para a próxima execução
	return cont += 1;
}
#endif