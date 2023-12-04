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
int jogarHajaLuz(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
	int timer = 0;
	
	//liberando cliques nas imagens
	liberearCliques(progresso);

	ALLEGRO_BITMAP* dialogo = NULL;
	
	//variaveis de controle
	bool sair = false;
	int hist = 1;

	//estados da fase
	enum Estados {
		historia,
		inicio,
		clicouLuminol,
		clicouHidrogenio,
		apagarLuz,
		animar,
		errou,
		acertou

	};
	
	enum Reacao {
		e1,
		e2
	};
	enum Reacao reacao = e1;
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
				if (hist > 3) {
					estado = inicio;
				}
			}

			//verifivações, se clicou no elemento errado == gameover, caso contrario, continua jogando

			else
				if (mouseHover(mouseX, mouseY, progresso->cenario->acido->x, progresso->cenario->acido->y, progresso->cenario->acido->largura, progresso->cenario->acido->altura) && progresso->cenario->acido->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->acucar->x, progresso->cenario->acucar->y, progresso->cenario->acucar->largura, progresso->cenario->acucar->altura) && progresso->cenario->acucar->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->agua->x, progresso->cenario->agua->y, progresso->cenario->agua->largura, progresso->cenario->agua->altura) && progresso->cenario->agua->podeClicar) {
					estado = errou;
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
					//colocando hidrogenio na mesa
					progresso->cenario->hidrogenio->naEstante = false;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->luminol->x, progresso->cenario->luminol->y, progresso->cenario->luminol->largura, progresso->cenario->luminol->altura) && progresso->cenario->luminol->podeClicar) {
					//colocando luminol na mesa
					progresso->cenario->luminol->naEstante = false;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->macarico->x, progresso->cenario->macarico->y, progresso->cenario->macarico->largura, progresso->cenario->macarico->altura) && progresso->cenario->macarico->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->oleo->x, progresso->cenario->oleo->y, progresso->cenario->oleo->largura, progresso->cenario->oleo->altura) && progresso->cenario->oleo->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->potassio->x, progresso->cenario->potassio->y, progresso->cenario->potassio->largura, progresso->cenario->potassio->altura) && progresso->cenario->potassio->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->soda->x, progresso->cenario->soda->y, progresso->cenario->soda->largura, progresso->cenario->soda->altura) && progresso->cenario->soda->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->vinagre->x, progresso->cenario->vinagre->y, progresso->cenario->vinagre->largura, progresso->cenario->vinagre->altura) && progresso->cenario->vinagre->podeClicar) {
					estado = errou;
				}

				 if (progresso->cenario->luminol->naEstante == false && progresso->cenario->luminol->podeClicar == true) {

					if (mouseHover(mouseX, mouseY, 300, 430, 150, 203)) {
						//skill test do luminol
						bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouLuminol;
							progresso->cenario->luminol->podeClicar = false;
						}

						else {
							estado = errou;
						}
					}
				}

				 if (progresso->cenario->hidrogenio->naEstante == false && progresso->cenario->hidrogenio->podeClicar == true) {
					//clique no hidrogenio
					if (mouseHover(mouseX, mouseY, 900, 470, 150, 203)) {
						
						//skill test do hidrogenio
						
						if (estado == clicouLuminol) {
							
							bool resultado = acerteVerde(display, filaDeEventos, progresso);
							
							if (resultado == true) {
								estado = clicouHidrogenio;
								progresso->cenario->hidrogenio->podeClicar = false;
							}
							else
								estado = errou;
						}
						
						else
							estado = errou;
					}
				}



				else if (estado == acertou) {
					//cliques nos botões em caso de acerto
					if (mouseHover(mouseX, mouseY, progresso->cenario->btProx->x, progresso->cenario->btProx->y, progresso->cenario->btProx->largura, progresso->cenario->btProx->altura)) {

						sair = true;
						progresso->proximaReacao = 4;
					}

					if (mouseHover(mouseX, mouseY, progresso->cenario->btReset->x, progresso->cenario->btReset->y, progresso->cenario->btReset->largura, progresso->cenario->btReset->altura)) {
						progresso->proximaReacao = 3;
						sair = true;

					}

					if (mouseHover(mouseX, mouseY, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, progresso->cenario->btMenu->largura, progresso->cenario->btMenu->altura)) {
						sair = true;
						progresso->proximaReacao = 0;


					}

				}

				else if (estado == errou) {
					//cliques nos botões em caso de erro
					if (mouseHover(mouseX, mouseY, progresso->cenario->btReset->x, progresso->cenario->btReset->y, progresso->cenario->btReset->largura, progresso->cenario->btReset->altura)) {
						sair = true;
						progresso->proximaReacao = 3;
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
				dialogo = progresso->cenario->fase2->fala1;
			}

			else if (hist == 2) {
				dialogo = progresso->cenario->fase2->fala2;
			}

			else if (hist == 3) {
				dialogo = progresso->cenario->fase2->fala3;
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
			//luminol e hidro na mesa
			if (progresso->cenario->luminol->naEstante == false) {
				al_draw_bitmap(progresso->cenario->fase2->luminolMesa, 300, 430, 0);
			}

			if (progresso->cenario->hidrogenio->naEstante == false) {
				al_draw_bitmap(progresso->cenario->fase2->hidrogenioMesa, 900, 430, 0);
			}

			//switch case do estado para controlar os desenhos
			switch (estado) {

			case inicio:
				al_draw_bitmap(progresso->cenario->recipiente->imagemEstante, 600, 360, 0);
				break;

			case clicouLuminol:
				al_draw_bitmap(progresso->cenario->fase2->recipienteLuminol, 600, 360, 0);
				break;

			case clicouHidrogenio:
				al_draw_bitmap(progresso->cenario->fase2->lumiE1, 600, 360, 0);
				timer++;
				al_draw_bitmap(progresso->cenario->fase2->aviso,0,0,0);
				if (timer == 240) {
					estado = apagarLuz;
					timer = 0;
				}
				break;

			case apagarLuz:
				al_draw_bitmap(progresso->cenario->fase2->fundoEscuro, 0, 0, 0);
				al_draw_bitmap(progresso->cenario->fase2->lumiE1, 600, 360, 0);
				timer++;
				if (timer == 90) {
					al_draw_bitmap(progresso->cenario->fase2->lumiE2, 600, 360, 0);
					timer = 0;
					estado = acertou;
				}
				break;

			case acertou:
				bloquearCliques(progresso);
				al_draw_bitmap(progresso->cenario->fase2->fundoEscuro, 0, 0, 0);
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
	
				timer++;
				
				if (reacao == e1) {
					al_draw_bitmap(progresso->cenario->fase2->lumiE1, 600, 360, 0);
				
				}
				
				else if(reacao == e2) {
					al_draw_bitmap(progresso->cenario->fase2->lumiE2, 600, 360, 0);
				}
				
				if (timer == 90) {
					
					if (reacao == e1) {
						reacao = e2;
						timer = 0;
					
					}
					
					else {
						reacao = e1;
						timer = 0;
						
					}

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
	progresso->cenario->hidrogenio->naEstante = true;
	progresso->cenario->luminol->naEstante = true;

	
	return 0;
}

