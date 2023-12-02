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

//eixos do mouse
int mouseX;
int mouseY;

//temporizador para a animação


//Função central da fase
int jogarCamaleao(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
	int timer = 0;
	//al_load nas imagnes
	carregarImg(progresso);

	//liberando cliques nas imagens
	liberearCliques(progresso);

	//mudando o fundo
	progresso->cenario->fundo = al_load_bitmap("imagens/fundo.png");

	//fonte
	ALLEGRO_FONT* font;

	//load em bitmaps especificos desta fase 
	ALLEGRO_BITMAP* aguaMesa = al_load_bitmap("imagens/aguaMesa.png");
	ALLEGRO_BITMAP* sodaMesa = al_load_bitmap("imagens/sodaMesa.png");
	ALLEGRO_BITMAP* potassioMesa = al_load_bitmap("imagens/potassioMesa.png");
	ALLEGRO_BITMAP* acucarMesa = al_load_bitmap("imagens/acucarMesa.png");
	ALLEGRO_BITMAP* recipiente = al_load_bitmap("imagens/recipiente.png");
	ALLEGRO_BITMAP* becker = al_load_bitmap("imagens/beckerMesa.png");
	ALLEGRO_BITMAP* beckerAguaSoda = al_load_bitmap("imagens/beckerAguaSoda.png");
	ALLEGRO_BITMAP* beckerAguaPotassio = al_load_bitmap("imagens/beckerAguaPotassio.png");
	ALLEGRO_BITMAP* beckerAguaSodaAcucar = al_load_bitmap("imagens/beckerAguaSodaAcucar.png");
	ALLEGRO_BITMAP* recipienteMisturado = al_load_bitmap("imagens/recipienteMisturado.png");
	ALLEGRO_BITMAP* recipienteRoxo = al_load_bitmap("imagens/recipienteRoxo.png");
	ALLEGRO_BITMAP* recipienteVerde = al_load_bitmap("imagens/recipienteVerde.png");
	ALLEGRO_BITMAP* recipienteLaranja = al_load_bitmap("imagens/recipienteLaranja.png");
	ALLEGRO_BITMAP* btProxN = al_load_bitmap("imagens/btProx.png");
	ALLEGRO_BITMAP* btProxH = al_load_bitmap("imagens/btProxH.png");
	ALLEGRO_BITMAP* btResetN = al_load_bitmap("imagens/btReset.png");
	ALLEGRO_BITMAP* btResetH = al_load_bitmap("imagens/btResetH.png");
	ALLEGRO_BITMAP* btMenuN = al_load_bitmap("imagens/btMenu.png");
	ALLEGRO_BITMAP* btMenuH = al_load_bitmap("imagens/btMenuH.png");
	ALLEGRO_BITMAP* escritorio = al_load_bitmap("imagens/escritorio2.png");
	ALLEGRO_BITMAP* fala1 = al_load_bitmap("imagens/fase3H1.png");
	ALLEGRO_BITMAP* fala2 = al_load_bitmap("imagens/fase3H2.png");
	ALLEGRO_BITMAP* fala3 = al_load_bitmap("imagens/fase3H3.png");
	ALLEGRO_BITMAP* fala4 = al_load_bitmap("imagens/fase3H4.png");
	ALLEGRO_BITMAP* dialogo = fala1;

	//botoes se errou e acertou
	Objeto* btProx, * btReset, * btMenu;

	btProx = (Objeto*)malloc(sizeof(Objeto));
	btProx->altura = 98;
	btProx->largura = 310;
	btProx->imagem = btProxN;
	btProx->wx = 0;
	btProx->wy = 0;
	btProx->x = 1010;
	btProx->y = 480;

	btReset = (Objeto*)malloc(sizeof(Objeto));
	btReset->altura = 98;
	btReset->largura = 310;
	btReset->imagem = btResetN;
	btReset->wx = 0;
	btReset->wy = 0;
	btReset->x = 1010;
	btReset->y = 600;

	btMenu = (Objeto*)malloc(sizeof(Objeto));
	btMenu->altura = 98;
	btMenu->largura = 310;
	btMenu->imagem = btMenuN;
	btMenu->wx = 0;
	btMenu->wy = 0;
	btMenu->x = 1010;
	btMenu->y = 720;

	//load na fonte
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);

	//variaveis de controle
	bool beckerVazio = true;
	bool sair = false;
	int hist = 1;

	//estados da fase
	enum Estados {
		historia,
		inicio,
		clicouAgua,
		clicouSoda,
		clicouAcucar,
		transferiu,
		clicouAgua2,
		clicouPotassio,
		transferiu2,
		errou,
		acertou

	};

	enum Estados estado = historia;

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
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {

			//passando a historia
			if (estado == historia) {
				hist++;
				if (hist > 4) {
					estado = inicio;
				}
			}

			//verifivações, se clicou no elemento errado == gameover, caso contrario, continua jogando

			else
				if (mouseHover(mouseX, mouseY, progresso->cenario->acido->x, progresso->cenario->acido->y, progresso->cenario->acido->largura, progresso->cenario->acido->altura) && progresso->cenario->acido->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->acucar->x, progresso->cenario->acucar->y, progresso->cenario->acucar->largura, progresso->cenario->acucar->altura) && progresso->cenario->acucar->podeClicar) {
					progresso->cenario->acucar->naEstante = false;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->agua->x, progresso->cenario->agua->y, progresso->cenario->agua->largura, progresso->cenario->agua->altura) && progresso->cenario->agua->podeClicar) {
					progresso->cenario->agua->naEstante = false;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->aluminio->x, progresso->cenario->aluminio->y, progresso->cenario->aluminio->largura, progresso->cenario->aluminio->altura) && progresso->cenario->aluminio->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->bicarbonato->x, progresso->cenario->bicarbonato->y, progresso->cenario->bicarbonato->largura, progresso->cenario->bicarbonato->altura) && progresso->cenario->bicarbonato->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->cDeCobre->x, progresso->cenario->cDeCobre->y, progresso->cenario->cDeCobre->largura, progresso->cenario->cDeCobre->altura) && progresso->cenario->cDeCobre->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->comprimido->x, progresso->cenario->comprimido->y, progresso->cenario->comprimido->largura, progresso->cenario->comprimido->altura) && progresso->cenario->comprimido->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->coranteG->x, progresso->cenario->coranteG->y, progresso->cenario->coranteG->largura, progresso->cenario->coranteG->altura) && progresso->cenario->coranteG->podeClicar) {
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->coranteR->x, progresso->cenario->coranteR->y, progresso->cenario->coranteR->largura, progresso->cenario->coranteR->altura) && progresso->cenario->coranteR->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->hidrogenio->x, progresso->cenario->hidrogenio->y, progresso->cenario->hidrogenio->largura, progresso->cenario->hidrogenio->altura) && progresso->cenario->hidrogenio->podeClicar) {
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->luminol->x, progresso->cenario->luminol->y, progresso->cenario->luminol->largura, progresso->cenario->luminol->altura) && progresso->cenario->luminol->podeClicar) {
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->macarico->x, progresso->cenario->macarico->y, progresso->cenario->macarico->largura, progresso->cenario->macarico->altura) && progresso->cenario->macarico->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->oleo->x, progresso->cenario->oleo->y, progresso->cenario->oleo->largura, progresso->cenario->oleo->altura) && progresso->cenario->oleo->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->potassio->x, progresso->cenario->potassio->y, progresso->cenario->potassio->largura, progresso->cenario->potassio->altura) && progresso->cenario->potassio->podeClicar) {
					progresso->cenario->potassio->naEstante = false;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->soda->x, progresso->cenario->soda->y, progresso->cenario->soda->largura, progresso->cenario->soda->altura) && progresso->cenario->soda->podeClicar) {
					progresso->cenario->soda->naEstante = false;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->vinagre->x, progresso->cenario->vinagre->y, progresso->cenario->vinagre->largura, progresso->cenario->vinagre->altura) && progresso->cenario->vinagre->podeClicar) {
					estado = errou;
				}

			if (progresso->cenario->agua->naEstante == false && progresso->cenario->agua->podeClicar == true) {

				if (mouseHover(mouseX, mouseY, 80, 430, 150, 203)) {
					//skill test da agua
					
					bool resultado = acerteVerde(display, filaDeEventos, progresso);

					if (resultado == true) {
						if (estado == transferiu) {
							estado = clicouAgua2;
						}
						else
							estado = clicouAgua;
						
						beckerVazio = false;
						progresso->cenario->agua->podeClicar = false;
					}

					else {
						estado = errou;
					}
				}


			}


			if (progresso->cenario->soda->naEstante == false && progresso->cenario->soda->podeClicar == true) {
				//clique no hidrogenio
				if (mouseHover(mouseX, mouseY, 280, 470, 150, 153)) {

					//skill test do hidrogenio

					if (estado == clicouAgua) {
						
						estado = clicouSoda;
						/*bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouHidrogenio;
							progresso->cenario->hidrogenio->podeClicar = false;
						}
						else
							estado = errou;*/
					}

					else
						estado = errou;
				}
			}

			if (progresso->cenario->acucar->naEstante == false && progresso->cenario->acucar->podeClicar == true) {
				//clique no hidrogenio
				if (mouseHover(mouseX, mouseY, 1100, 490, 150, 153)) {

					//skill test do hidrogenio

					if (estado == clicouSoda) {

						estado = clicouAcucar;
						/*bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouHidrogenio;
							progresso->cenario->hidrogenio->podeClicar = false;
						}
						else
							estado = errou;*/
					}

					else
						estado = errou;
				}
			}
			//RETEINDOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
			if (progresso->cenario->potassio->naEstante == false && progresso->cenario->potassio->podeClicar == true) {
				//clique no hidrogenio
				if (mouseHover(mouseX, mouseY, 880, 500, 150, 203)) {

					//skill test do hidrogenio

					if (estado == clicouAgua2) {

						estado = clicouPotassio;
						/*bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouHidrogenio;
							progresso->cenario->hidrogenio->podeClicar = false;
						}
						else
							estado = errou;*/
					}

					else
						estado = errou;
				}
			}
			
			if (beckerVazio == false) {
				//clique no hidrogenio
				if (mouseHover(mouseX, mouseY, 460, 430, 150, 203)) {

					//skill test do hidrogenio

					if (estado == clicouAcucar ) {

						estado = transferiu;
						beckerVazio = true;
						progresso->cenario->agua->podeClicar = true;
						/*bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouHidrogenio;
							progresso->cenario->hidrogenio->podeClicar = false;
						}
						else
							estado = errou;*/
					}
					else if (estado == clicouPotassio) {
						beckerVazio = true;
						estado = transferiu2;
					}
					
					else
						estado = errou;
				}
			}


			else if (estado == acertou) {
				//cliques nos botões em caso de acerto
				if (mouseHover(mouseX, mouseY, btProx->x, btProx->y, btProx->largura, btProx->altura)) {

					sair = true;
					progresso->proximaReacao = 6;
				}

				if (mouseHover(mouseX, mouseY, btReset->x, btReset->y, btReset->largura, btReset->altura)) {
					progresso->proximaReacao = 5;
					sair = true;

				}

				if (mouseHover(mouseX, mouseY, btMenu->x, btMenu->y, btMenu->largura, btMenu->altura)) {
					sair = true;
					progresso->proximaReacao = 0;


				}

			}

			else if (estado == errou) {
				//cliques nos botões em caso de erro
				if (mouseHover(mouseX, mouseY, btReset->x, btReset->y, btReset->largura, btReset->altura)) {
					sair = true;
					progresso->proximaReacao = 5;
				}

				if (mouseHover(mouseX, mouseY, btMenu->x, btMenu->y, btMenu->largura, btMenu->altura)) {
					sair = true;
					progresso->proximaReacao = 0;
				}
			}
		}

		//mudando imagem do botão quando o mouse passar em cima
		if (estado == acertou || estado == errou) {
			if (mouseHover(mouseX, mouseY, btProx->x, btProx->y, btProx->largura, btProx->altura)) {
				btProx->imagem = btProxH;
			}

			else
				btProx->imagem = btProxN;
			if (mouseHover(mouseX, mouseY, btReset->x, btReset->y, btReset->largura, btReset->altura)) {

				btReset->imagem = btResetH;

			}

			else

				btReset->imagem = btResetN;

			if (mouseHover(mouseX, mouseY, btMenu->x, btMenu->y, btMenu->largura, btMenu->altura)) {
				btMenu->imagem = btMenuH;
			}

			else
				btMenu->imagem = btMenuN;

		}
		//desenhos da historia
		if (estado == historia) {

			if (hist == 1) {
				dialogo = fala1;
			}

			else if (hist == 2) {
				dialogo = fala2;
			}

			else if (hist == 3) {
				dialogo = fala3;
			}

			else if (hist == 4) {
				dialogo = fala4;
			}

			al_draw_bitmap(escritorio, 0, 0, 0);
			al_draw_bitmap(dialogo, 0, 0, 0);

		}

		//desenhos da fase em geral
		else {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0);

			desenhaRegentes(progresso);

			desenharTextos(progresso, font, mouseX, mouseY);
			
			//reagentes na mesa
			if (progresso->cenario->agua->naEstante == false) {
				al_draw_bitmap(aguaMesa, 80, 430, 0);
			}

			if (progresso->cenario->soda->naEstante == false) {
				al_draw_bitmap(sodaMesa, 280, 470, 0);
			}

			if (progresso->cenario->potassio->naEstante == false) {
				al_draw_bitmap(potassioMesa, 880, 500, 0);
			}

			if (progresso->cenario->acucar->naEstante == false) {
				al_draw_bitmap(acucarMesa, 1100, 490, 0);
			}

			//switch case do estado para controlar os desenhos
			switch (estado) {

			case inicio:
				al_draw_bitmap(recipiente, 650, 360, 0);
				al_draw_bitmap(becker, 460, 430, 0);
				break;

			case clicouAgua:
				al_draw_bitmap(recipiente, 650, 360, 0);
				al_draw_bitmap(aguaMesa, 460, 430, 0);
				break;

			case clicouSoda:
				al_draw_bitmap(recipiente, 650, 360, 0);
				al_draw_bitmap(beckerAguaSoda, 460, 430, 0);
				break;

			case clicouAcucar:
				al_draw_bitmap(recipiente, 650, 360, 0);
				al_draw_bitmap(beckerAguaSodaAcucar, 460, 430, 0);

				break;

			case transferiu:
				al_draw_bitmap(recipienteMisturado, 650, 360, 0);
				al_draw_bitmap(becker, 460, 430, 0);
				break;

			case clicouAgua2:
				al_draw_bitmap(recipienteMisturado, 650, 360, 0);
				al_draw_bitmap(aguaMesa, 460, 430, 0);
				break;

			case clicouPotassio:
				al_draw_bitmap(recipienteMisturado, 650, 360, 0);
				al_draw_bitmap(beckerAguaPotassio, 460, 430, 0);

				break;

			case transferiu2:
				bloquearCliques(progresso);
				al_draw_bitmap(becker, 460, 430, 0);
				
				timer++;
				if (timer < 120) {
					al_draw_bitmap(recipienteRoxo, 650, 360, 0);
				}
				else if (timer >= 120 && timer <= 360) {
					al_draw_bitmap(recipienteLaranja, 650, 360, 0);
				}
				else if (timer >= 360 && timer <= 480) {
					al_draw_bitmap(recipienteVerde, 650, 360, 0);
					estado = acertou;
					timer = 0;
				}

				break;

			case acertou:
				bloquearCliques(progresso);
				al_draw_bitmap(btProx->imagem, btProx->x, btProx->y, 0);
				al_draw_bitmap(btReset->imagem, btReset->x, btReset->y, 0);
				al_draw_bitmap(btMenu->imagem, btMenu->x, btMenu->y, 0);
				bloquearCliques(progresso);
				al_draw_bitmap(becker, 460, 430, 0);

				timer++;
				if (timer >=  0 && timer < 120) {
					al_draw_bitmap(recipienteVerde, 650, 360, 0);
					
				}
				else if (timer >= 120 && timer <= 240) {
					al_draw_bitmap(recipienteLaranja, 650, 360, 0);
				}
				else if (timer >= 240 && timer <= 360) {
					
					al_draw_bitmap(recipienteRoxo, 650, 360, 0);
					
					if(timer == 360)
						timer = 0;
				}
				
				break;


			case errou:
				bloquearCliques(progresso);
				al_draw_bitmap(btReset->imagem, btReset->x, btReset->y, 0);
				al_draw_bitmap(btMenu->imagem, btMenu->x, btMenu->y, 0);
				break;
			}



			//texto se acertou
			//if (estado == acertou) {

			//	al_draw_text(font, al_map_rgb(0, 0, 0), 360, 200, 0, "Voce conseguiu produzir");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 400, 220, 0, "a reacao esperada.");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 350, 250, 0, "Ate que enfim contrataram");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 350, 270, 0, "um estagiario que saiba");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 420, 290, 0, "fazer algo.");

			//}

			//texto se errou
			//if (estado == errou) {
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 420, 220, 0, "Ops... A ordem dos");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 430, 240, 0, "reagentes e muito");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 400, 260, 0, "importante para que a");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 360, 280, 0, "reacao ocorra corretamente.");
			//	al_draw_text(font, al_map_rgb(0, 0, 0), 430, 320, 0, "Tente novamente.");
			//}

		//}


		}
		al_flip_display();
	}
	//trazendo elementos para a estante
	progresso->cenario->agua->naEstante = true;
	progresso->cenario->soda->naEstante = true;
	progresso->cenario->potassio->naEstante = true;
	progresso->cenario->acucar->naEstante = true;

	//destruindo imagens 
	al_destroy_bitmap(progresso->cenario->fundo);
	destruirBitmaps(progresso);
	//al_destroy_bitmap(vinagreMesa);
	//al_destroy_bitmap(bicarbonatoMesa);
	al_destroy_bitmap(recipiente);
	//al_destroy_bitmap(recipienteVinagre);

	//al_destroy_bitmap(recipienteFeito3);
	//al_destroy_bitmap(vapor);
	al_destroy_bitmap(btProxH);
	al_destroy_bitmap(btProxN);
	al_destroy_bitmap(btMenuH);
	al_destroy_bitmap(btMenuN);
	al_destroy_bitmap(btResetH);
	al_destroy_bitmap(btResetN);
	al_destroy_bitmap(fala1);
	al_destroy_bitmap(fala2);
	al_destroy_bitmap(fala3);

	al_destroy_font(font);

	free(btMenu);
	free(btProx);
	free(btReset);

	return 0;
}


