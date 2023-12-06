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

//Função central da fase
int jogarCamaleao(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
	int timer = 0;
	
	//liberando cliques nas imagens
	liberearCliques(progresso);

	ALLEGRO_BITMAP* dialogo = NULL;

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
			if (progresso->cenario->potassio->naEstante == false && progresso->cenario->potassio->podeClicar == true) {
				//clique no hidrogenio
				if (mouseHover(mouseX, mouseY, 880, 500, 150, 203)) {

					//skill test do hidrogenio

					if (estado == clicouAgua2) {
						bool resultado = acerteBecker(display, filaDeEventos, progresso);
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
				if (mouseHover(mouseX, mouseY, progresso->cenario->btProx->x, progresso->cenario->btProx->y, progresso->cenario->btProx->largura, progresso->cenario->btProx->altura)) {

					sair = true;
					progresso->proximaReacao = 5;
				}

				if (mouseHover(mouseX, mouseY, progresso->cenario->btReset->x, progresso->cenario->btReset->y, progresso->cenario->btReset->largura, progresso->cenario->btReset->altura)) {
					progresso->proximaReacao = 4;
					sair = true;

				}

				if (mouseHover(mouseX, mouseY, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, progresso->cenario->btMenu->largura, progresso->cenario->btMenu->altura)) {
					sair = true;
					progresso->proximaReacao = 0;


				}

			}

			 if (estado == errou) {
				//cliques nos botões em caso de erro
				if (mouseHover(mouseX, mouseY, progresso->cenario->btReset->x, progresso->cenario->btReset->y, progresso->cenario->btReset->largura, progresso->cenario->btReset->altura)) {
					sair = true;
					progresso->proximaReacao = 4;
				}

				if (mouseHover(mouseX, mouseY, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, progresso->cenario->btMenu->largura, progresso->cenario->btMenu->altura)) {
					sair = true;
					progresso->proximaReacao = 0;
				}
			}
		}

		//desenhos da historia
		if (estado == historia) {

			if (hist == 1) {
				dialogo = progresso->cenario->fase3->fala1;
			}

			else if (hist == 2) {
				dialogo = progresso->cenario->fase3->fala2;
			}

			else if (hist == 3) {
				dialogo = progresso->cenario->fase3->fala3;
			}

			else if (hist == 4) {
				dialogo = progresso->cenario->fase3->fala4;
			}

			al_draw_bitmap(progresso->cenario->escritorio, 0, 0, 0);
			al_draw_bitmap(dialogo, 0, 0, 0);

		}

		//desenhos da fase em geral
		else {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(progresso->cenario->lab, 0, 0, 0);

			desenhaRegentes(progresso);

			desenharTextos(progresso, progresso->cenario->font, mouseX, mouseY);
			
			//reagentes na mesa
			if (progresso->cenario->agua->naEstante == false) {
				al_draw_bitmap(progresso->cenario->fase3->aguaMesa, 80, 430, 0);
			}

			if (progresso->cenario->soda->naEstante == false) {
				al_draw_bitmap(progresso->cenario->fase3->sodaMesa, 280, 470, 0);
			}

			if (progresso->cenario->potassio->naEstante == false) {
				al_draw_bitmap(progresso->cenario->fase3->potassioMesa, 880, 500, 0);
			}

			if (progresso->cenario->acucar->naEstante == false) {
				al_draw_bitmap(progresso->cenario->fase3->acucarMesa, 1100, 490, 0);
			}

			//switch case do estado para controlar os desenhos
			switch (estado) {

			case inicio:
				al_draw_bitmap(progresso->cenario->recipiente->imagemEstante, 650, 360, 0);
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 460, 430, 0);
				break;

			case clicouAgua:
				al_draw_bitmap(progresso->cenario->recipiente->imagemEstante, 650, 360, 0);
				al_draw_bitmap(progresso->cenario->fase3->aguaMesa, 460, 430, 0);
				break;

			case clicouSoda:
				al_draw_bitmap(progresso->cenario->recipiente->imagemEstante, 650, 360, 0);
				al_draw_bitmap(progresso->cenario->fase3->beckerAguaSoda, 460, 430, 0);
				break;

			case clicouAcucar:
				al_draw_bitmap(progresso->cenario->recipiente->imagemEstante, 650, 360, 0);
				al_draw_bitmap(progresso->cenario->fase3->beckerAguaSodaAcucar, 460, 430, 0);

				break;

			case transferiu:
				al_draw_bitmap(progresso->cenario->fase3->recipienteMisturado, 650, 360, 0);
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 460, 430, 0);
				break;

			case clicouAgua2:
				al_draw_bitmap(progresso->cenario->fase3->recipienteMisturado, 650, 360, 0);
				al_draw_bitmap(progresso->cenario->fase3->aguaMesa, 460, 430, 0);
				break;

			case clicouPotassio:
				al_draw_bitmap(progresso->cenario->fase3->recipienteMisturado, 650, 360, 0);
				al_draw_bitmap(progresso->cenario->fase3->beckerAguaPotassio, 460, 430, 0);

				break;

			case transferiu2:
				bloquearCliques(progresso);
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 460, 430, 0);
				
				timer++;
				if (timer < 120) {
					al_draw_bitmap(progresso->cenario->fase3->recipienteRoxo, 650, 360, 0);
				}
				else if (timer >= 120 && timer <= 360) {
					al_draw_bitmap(progresso->cenario->fase3->recipienteLaranja, 650, 360, 0);
				}
				else if (timer >= 360 && timer <= 480) {
					al_draw_bitmap(progresso->cenario->fase3->recipienteVerde, 650, 360, 0);
					estado = acertou;
					timer = 0;
				}

				break;

			case acertou:
				bloquearCliques(progresso);
				if (mouseHover(mouseX, mouseY, progresso->cenario->btProx->x, progresso->cenario->btProx->y, progresso->cenario->btProx->largura, progresso->cenario->btProx->altura))
					al_draw_bitmap(progresso->cenario->btProx->hover, progresso->cenario->btProx->x, progresso->cenario->btProx->y, 0);

				else
					al_draw_bitmap(progresso->cenario->btProx->norm, progresso->cenario->btProx->x, progresso->cenario->btProx->y, 0);

				if (mouseHover(mouseX, mouseY, progresso->cenario->btReset->x, progresso->cenario->btReset->y, progresso->cenario->btReset->largura, progresso->cenario->btReset->altura))
					al_draw_bitmap(progresso->cenario->btReset->hover, progresso->cenario->btReset->x, progresso->cenario->btReset->y, 0);

				else
					al_draw_bitmap(progresso->cenario->btReset->norm, progresso->cenario->btReset->x, progresso->cenario->btReset->y, 0);

				if (mouseHover(mouseX, mouseY, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, progresso->cenario->btMenu->largura, progresso->cenario->btMenu->altura))
					al_draw_bitmap(progresso->cenario->btMenu->hover, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, 0);

				else
					al_draw_bitmap(progresso->cenario->btMenu->norm, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, 0);
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 460, 430, 0);

				timer++;
				if (timer >=  0 && timer < 120) {
					al_draw_bitmap(progresso->cenario->fase3->recipienteVerde, 650, 360, 0);
					
				}
				else if (timer >= 120 && timer <= 240) {
					al_draw_bitmap(progresso->cenario->fase3->recipienteLaranja, 650, 360, 0);
				}
				else if (timer >= 240 && timer <= 360) {
					
					al_draw_bitmap(progresso->cenario->fase3->recipienteRoxo, 650, 360, 0);
					
					if(timer == 360)
						timer = 0;
				}
				
				break;


			case errou:
				bloquearCliques(progresso);
				if (mouseHover(mouseX, mouseY, progresso->cenario->btReset->x, progresso->cenario->btReset->y, progresso->cenario->btReset->largura, progresso->cenario->btReset->altura))
					al_draw_bitmap(progresso->cenario->btReset->hover, progresso->cenario->btReset->x, progresso->cenario->btReset->y, 0);

				else
					al_draw_bitmap(progresso->cenario->btReset->norm, progresso->cenario->btReset->x, progresso->cenario->btReset->y, 0);

				if (mouseHover(mouseX, mouseY, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, progresso->cenario->btMenu->largura, progresso->cenario->btMenu->altura))
					al_draw_bitmap(progresso->cenario->btMenu->hover, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, 0);

				else
					al_draw_bitmap(progresso->cenario->btMenu->norm, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, 0);
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

	return 0;
}


