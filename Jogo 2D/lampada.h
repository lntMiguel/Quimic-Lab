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
int jogarLampada(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
	//temporizador para a animação
	int timer = 0;
	
	//liberando cliques nas imagens
	liberearCliques(progresso);

	ALLEGRO_BITMAP* dialogo = NULL;
	ALLEGRO_BITMAP* reciFinal = NULL;
	ALLEGRO_BITMAP* reciFinal2 = NULL;
	
	//variaveis de controle
	bool sair = false;
	int hist = 1;

	//estados da fase
	enum Estados {
		historia,
		inicio,
		clicouCoranteG,
		clicouCoranteR,
		reciG,
		reciR,
		clicouOleoR,
		clicouOleoG,
		clicouCompR,
		clicouCompG,
		errou,
		acertou,
	
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
				if (hist > 3) 
					estado = inicio;
				
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
					progresso->cenario->comprimido->naEstante = false;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->coranteG->x, progresso->cenario->coranteG->y, progresso->cenario->coranteG->largura, progresso->cenario->coranteG->altura) && progresso->cenario->coranteG->podeClicar) {
					if (progresso->cenario->coranteR->naEstante == false) {
						estado = errou;
						
					}
						
					
					else {
						progresso->cenario->coranteG->naEstante = false; 
						
					}
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->coranteR->x, progresso->cenario->coranteR->y, progresso->cenario->coranteR->largura, progresso->cenario->coranteR->altura) && progresso->cenario->coranteR->podeClicar) {
					if (progresso->cenario->coranteG->naEstante == false)
						estado = errou;

					else {
						progresso->cenario->coranteR->naEstante = false;
						
					}
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->hidrogenio->x, progresso->cenario->hidrogenio->y, progresso->cenario->hidrogenio->largura, progresso->cenario->hidrogenio->altura) && progresso->cenario->hidrogenio->podeClicar) {
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->luminol->x, progresso->cenario->luminol->y, progresso->cenario->luminol->largura, progresso->cenario->luminol->altura) && progresso->cenario->luminol->podeClicar) {
					//colocando luminol na mesa
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->macarico->x, progresso->cenario->macarico->y, progresso->cenario->macarico->largura, progresso->cenario->macarico->altura) && progresso->cenario->macarico->podeClicar) {
					estado = errou;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->oleo->x, progresso->cenario->oleo->y, progresso->cenario->oleo->largura, progresso->cenario->oleo->altura) && progresso->cenario->oleo->podeClicar) {
					progresso->cenario->oleo->naEstante = false;

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

			if (progresso->cenario->coranteG->naEstante == false && progresso->cenario->coranteG->podeClicar == true) {
				if (mouseHover(mouseX, mouseY, 280, 470, 150, 153)) {


					if (progresso->cenario->agua->naEstante == false) {

						estado = clicouCoranteG;
						/*bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouHidrogenio;
							progresso->cenario->hidrogenio->podeClicar = false;
						}
						else
							estado = errou;*/
						progresso->cenario->coranteG->podeClicar = false;
					}

					else
						estado = errou;
				}
			}

			if (progresso->cenario->coranteR->naEstante == false && progresso->cenario->coranteR->podeClicar == true) {
				if (mouseHover(mouseX, mouseY, 280, 470, 150, 153)) {

					if (progresso->cenario->agua->naEstante == false) {

						estado = clicouCoranteR;
						/*bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouHidrogenio;
							progresso->cenario->hidrogenio->podeClicar = false;
						}
						else
							estado = errou;*/
						progresso->cenario->coranteR->podeClicar = false;
					}

					else
						estado = errou;
				}
			}

			if (progresso->cenario->agua->naEstante == false && progresso->cenario->agua->podeClicar == true) {

				if (mouseHover(mouseX, mouseY, 80, 430, 150, 203)) {
					
					if (estado == clicouCoranteG || estado == clicouCoranteR) {
						bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							
							if (progresso->cenario->coranteG->naEstante == false) 
								estado = reciG;
							
							if (progresso->cenario->coranteR->naEstante == false) 
								estado = reciR;
						
							progresso->cenario->agua->podeClicar = false;
						}
						
						else 
							estado = errou;

					}
					
					else
						estado = errou;
				}
			}
			if (progresso->cenario->oleo->naEstante == false && progresso->cenario->oleo->podeClicar == true) {
				if (mouseHover(mouseX, mouseY, 800, 430, 150, 203)) {
					if (estado == reciG || estado == reciR) {
						bool resultado = acerteVerde(display, filaDeEventos, progresso);
						if (resultado == true) {
							if(estado == reciR)
								estado = clicouOleoR;
							else
								estado = clicouOleoG;
							progresso->cenario->oleo->podeClicar = false;
							}
						else 
							estado = errou;
						}
					else
						estado = errou;
				}
			}
		
			if (progresso->cenario->comprimido->naEstante == false && progresso->cenario->comprimido->podeClicar == true) {
				if (mouseHover(mouseX, mouseY, 950, 500, 150, 203)) {
					if (estado == clicouOleoG || estado == clicouOleoR) {
							if (estado == clicouOleoG)
								estado = clicouCompG;
							else
								estado = clicouCompR;
							progresso->cenario->comprimido->podeClicar = false;
					}
					else
						estado = errou;
				}
			}
			else if (estado == acertou) {
				//cliques nos botões em caso de acerto
				if (mouseHover(mouseX, mouseY, progresso->cenario->btProx->x, progresso->cenario->btProx->y, progresso->cenario->btProx->largura, progresso->cenario->btProx->altura)) {

					sair = true;
					progresso->proximaReacao = 6;
				}

				if (mouseHover(mouseX, mouseY, progresso->cenario->btReset->x, progresso->cenario->btReset->y, progresso->cenario->btReset->largura, progresso->cenario->btReset->altura)) {
					progresso->proximaReacao = 5;
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
					progresso->proximaReacao = 5;
				}

				if (mouseHover(mouseX, mouseY, progresso->cenario->btMenu->x, progresso->cenario->btMenu->y, progresso->cenario->btMenu->largura, progresso->cenario->btMenu->altura)) {
					sair = true;
					progresso->proximaReacao = 0;
				}
			}

}

		//desenhos da historia
		if (estado == historia) {

			if (hist == 1) 
				dialogo = progresso->cenario->fase4->fala1;
			

			else if (hist == 2) 
				dialogo = progresso->cenario->fase4->fala2;


			else if (hist == 3) 
				dialogo = progresso->cenario->fase4->fala3;


			al_draw_bitmap(progresso->cenario->escritorio, 0, 0, 0);
			al_draw_bitmap(dialogo, 0, 0, 0);

		}

		//desenhos da fase em geral
		else {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(progresso->cenario->lab, 0, 0, 0);
			desenhaRegentes(progresso);
			desenharTextos(progresso, progresso->cenario->font, mouseX, mouseY);
			al_draw_bitmap(progresso->cenario->recipiente->imagemEstante, 600, 360, 0);
			
			if (progresso->cenario->coranteG->naEstante == false) 
				al_draw_bitmap(progresso->cenario->fase4->coranteGMesa, 280, 460, 0);
			

			if (progresso->cenario->coranteR->naEstante == false) 
				al_draw_bitmap(progresso->cenario->fase4->coranteRMesa, 280, 460, 0);
			
			
			if (progresso->cenario->oleo->naEstante == false) 
				al_draw_bitmap(progresso->cenario->fase4->oleoMesa, 800, 430, 0);
			
			if (progresso->cenario->comprimido->naEstante == false) 
				al_draw_bitmap(progresso->cenario->fase4->comprimidoMesa,950, 500, 0);
			
			
			//switch case do estado para controlar os desenhos
			switch (estado) {
	
			case inicio:
				if (progresso->cenario->agua->naEstante == false)
					al_draw_bitmap(progresso->cenario->fase4->aguaMesa, 80, 430, 0);
				break;
					
			case clicouCoranteG:
				al_draw_bitmap(progresso->cenario->fase4->aguaG, 80, 430, 0);
				break;

			case clicouCoranteR:
				al_draw_bitmap(progresso->cenario->fase4->aguaR, 80, 430, 0);
				break;

			case reciG:
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);
				al_draw_bitmap(progresso->cenario->fase4->reciAguaG, 600, 360, 0);
				break;

			case reciR:
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);
				al_draw_bitmap(progresso->cenario->fase4->reciAguaR, 600, 360, 0);
				break;

			case clicouOleoR:
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);
				al_draw_bitmap(progresso->cenario->fase4->reciAguaOleoR, 600, 360, 0);
				break;

			case clicouOleoG:
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);
				al_draw_bitmap(progresso->cenario->fase4->reciAguaOleoG, 600, 360, 0);
				break;

			case clicouCompR:
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);
				reciFinal = progresso->cenario->fase4->lampadaR1;
				reciFinal2 = progresso->cenario->fase4->lampadaR2;
				estado = acertou;
				break;

			case clicouCompG:
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);
				reciFinal = progresso->cenario->fase4->lampadaG1;
				reciFinal2 = progresso->cenario->fase4->lampadaG2;
				estado = acertou;
				break;

			case acertou:
				al_draw_bitmap(progresso->cenario->becker->imagemEstante, 80, 430, 0);
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

				timer++;

				if (timer >= 0 && timer <= 60)
					al_draw_bitmap(reciFinal, 600, 360, 0);

				else if (timer >= 60 && timer <= 120) {
					al_draw_bitmap(reciFinal2, 600, 360, 0);
					
					if (timer >= 120 && timer <= 180) {
					
						timer = 0;
				
					}
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

	progresso->cenario->agua->naEstante = true;
	progresso->cenario->oleo->naEstante = true;
	progresso->cenario->comprimido->naEstante = true;
	progresso->cenario->coranteG->naEstante = true;
	progresso->cenario->coranteR->naEstante = true;
	
	return 0;
}

