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


//posições

//eixos do mouse
int mouseX;
int mouseY;

//temporizador para a animação

//Função central da fase
int jogarAurora(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* filaDeEventos, Prog* progresso) {
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
	ALLEGRO_BITMAP*	acidoMesa= al_load_bitmap("imagens/acidoMesa.png");
	ALLEGRO_BITMAP* aluminioMesa= al_load_bitmap("imagens/papelAlum.png");
	ALLEGRO_BITMAP* macaricoMesa = al_load_bitmap("imagens/macaricoMesa.png");
	ALLEGRO_BITMAP* cDeCobreMesa = al_load_bitmap("imagens/cDeCobreMesa.png");
	ALLEGRO_BITMAP* recipiente = al_load_bitmap("imagens/recipiente.png");
	ALLEGRO_BITMAP* recipienteAcidoCobre = al_load_bitmap("imagens/reciAcidoCobre.png");
	ALLEGRO_BITMAP* recipienteACA = al_load_bitmap("imagens/reciACA.png");
	ALLEGRO_BITMAP* recipienteAcido = al_load_bitmap("imagens/reciAcido.png");
	ALLEGRO_BITMAP* recipienteFeito1 = al_load_bitmap("imagens/aurora1.png");
	ALLEGRO_BITMAP* recipienteFeito2= al_load_bitmap("imagens/aurora2.png");
	ALLEGRO_BITMAP* recipienteFeito3 = al_load_bitmap("imagens/aurora3.png");
	ALLEGRO_BITMAP* aviso = al_load_bitmap("imagens/aviso.png");
	ALLEGRO_BITMAP* btProxN = al_load_bitmap("imagens/btProx.png");
	ALLEGRO_BITMAP* btProxH = al_load_bitmap("imagens/btProxH.png");
	ALLEGRO_BITMAP* btResetN = al_load_bitmap("imagens/btReset.png");
	ALLEGRO_BITMAP* btResetH = al_load_bitmap("imagens/btResetH.png");
	ALLEGRO_BITMAP* btMenuN = al_load_bitmap("imagens/btMenu.png");
	ALLEGRO_BITMAP* btMenuH = al_load_bitmap("imagens/btMenuH.png");
	ALLEGRO_BITMAP* escritorio = al_load_bitmap("imagens/escritorio2.png");
	ALLEGRO_BITMAP* fundoEscuro = al_load_bitmap("imagens/fundoEscuro.png");
	ALLEGRO_BITMAP* fala1 = al_load_bitmap("imagens/fase5H1.png");
	ALLEGRO_BITMAP* fala2 = al_load_bitmap("imagens/fase5H2.png");
	ALLEGRO_BITMAP* fala3 = al_load_bitmap("imagens/fase5H3.png");
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
	bool sair = false;
	int hist = 1;

	//estados da fase
	enum Estados {
		historia,
		inicio,
		clicouAcido,
		clicouCloreto,
		clicouAlum,
		clicouFogo,
		apagarLuz,
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
				if (hist > 3) {
					estado = inicio;
				}
			}
			
			//verifivações, se clicou no elemento errado == gameover, caso contrario, continua jogando

			else
				if (mouseHover(mouseX, mouseY, progresso->cenario->acido->x, progresso->cenario->acido->y, progresso->cenario->acido->largura, progresso->cenario->acido->altura) && progresso->cenario->acido->podeClicar) {
					progresso->cenario->acido->naEstante = false;
					
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->acucar->x, progresso->cenario->acucar->y, progresso->cenario->acucar->largura, progresso->cenario->acucar->altura) && progresso->cenario->acucar->podeClicar) {
					estado = errou;
					
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->agua->x, progresso->cenario->agua->y, progresso->cenario->agua->largura, progresso->cenario->agua->altura) && progresso->cenario->agua->podeClicar) {
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->aluminio->x, progresso->cenario->aluminio->y, progresso->cenario->aluminio->largura, progresso->cenario->aluminio->altura) && progresso->cenario->aluminio->podeClicar) {
					progresso->cenario->aluminio->naEstante = false;

				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->bicarbonato->x, progresso->cenario->bicarbonato->y, progresso->cenario->bicarbonato->largura, progresso->cenario->bicarbonato->altura) && progresso->cenario->bicarbonato->podeClicar) {
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->cDeCobre->x, progresso->cenario->cDeCobre->y, progresso->cenario->cDeCobre->largura, progresso->cenario->cDeCobre->altura) && progresso->cenario->cDeCobre->podeClicar) {
					progresso->cenario->cDeCobre->naEstante = false;

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
					//colocando luminol na mesa
					estado = errou;
				}

				else if (mouseHover(mouseX, mouseY, progresso->cenario->macarico->x, progresso->cenario->macarico->y, progresso->cenario->macarico->largura, progresso->cenario->macarico->altura) && progresso->cenario->macarico->podeClicar) {
					
					progresso->cenario->macarico->naEstante = false;

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

			if (progresso->cenario->acido->naEstante == false && progresso->cenario->acido->podeClicar == true) {
				//clique no acido
				if (mouseHover(mouseX, mouseY, 80, 430, 150, 203)) {

					estado = clicouAcido;
						bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouAcido;
							progresso->cenario->acido->podeClicar = false;
						}
						
						else
							estado = errou;
						
					}

				
			}

			if (progresso->cenario->cDeCobre->naEstante == false && progresso->cenario->cDeCobre->podeClicar == true) {
				//clique no hidrogenio
				if (mouseHover(mouseX, mouseY, 280, 470, 150, 153)) {

					//skill test do hidrogenio

					if (estado == clicouAcido) {

						estado = clicouCloreto;
						/*bool resultado = acerteVerde(display, filaDeEventos, progresso);

						if (resultado == true) {
							estado = clicouHidrogenio;
							progresso->cenario->hidrogenio->podeClicar = false;
						}
						else
							estado = errou;*/
						progresso->cenario->cDeCobre->podeClicar = false;
					}

					else
						estado = errou;
				}
			}

			if (progresso->cenario->aluminio->naEstante == false && progresso->cenario->aluminio->podeClicar == true) {

				if (mouseHover(mouseX, mouseY, 1100, 500, 75, 71)) {
					//skill test da agua

					if (estado == clicouCloreto) {
						
						estado = clicouAlum;

					}

					else
						estado = errou;
				}
			}

			if (progresso->cenario->macarico->naEstante == false && progresso->cenario->macarico->podeClicar == true) {
				if (mouseHover(mouseX, mouseY, 800, 430, 150, 149)) {
					if (estado == clicouAlum) {
						estado = clicouFogo;
					}
					else
						estado = errou;

				}

			}

			else if (estado == acertou) {
				//cliques nos botões em caso de acerto
				if (mouseHover(mouseX, mouseY, btProx->x, btProx->y, btProx->largura, btProx->altura)) {

					sair = true;
					progresso->proximaReacao = 7;
				}

				if (mouseHover(mouseX, mouseY, btReset->x, btReset->y, btReset->largura, btReset->altura)) {
					progresso->proximaReacao = 6;
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
					progresso->proximaReacao = 6;
				}

				if (mouseHover(mouseX, mouseY, btMenu->x, btMenu->y, btMenu->largura, btMenu->altura)) {
					sair = true;
					progresso->proximaReacao = 0;
				}
			}
			
}
			

		//mudando imagem do botão quando o mouse passar em cima
		if (estado == acertou || estado == errou)

			if (mouseHover(mouseX, mouseY, btProx->x, btProx->y, btProx->largura, btProx->altura))
				btProx->imagem = btProxH;

			else
				btProx->imagem = btProxN;

		if (mouseHover(mouseX, mouseY, btReset->x, btReset->y, btReset->largura, btReset->altura))
			btReset->imagem = btResetH;

		else
			btReset->imagem = btResetN;

		if (mouseHover(mouseX, mouseY, btMenu->x, btMenu->y, btMenu->largura, btMenu->altura))
			btMenu->imagem = btMenuH;


		else
			btMenu->imagem = btMenuN;


		//desenhos da historia
		if (estado == historia) {

			if (hist == 1)
				dialogo = fala1;


			else if (hist == 2)
				dialogo = fala2;


			else if (hist == 3)
				dialogo = fala3;


			al_draw_bitmap(escritorio, 0, 0, 0);
			al_draw_bitmap(dialogo, 0, 0, 0);

		}

		//desenhos da fase em geral
		else {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(progresso->cenario->fundo, 0, 0, 0);
			desenhaRegentes(progresso);
			desenharTextos(progresso, font, mouseX, mouseY);
			al_draw_bitmap(progresso->cenario->aluminio->imagemEstante, progresso->cenario->aluminio->x, progresso->cenario->aluminio->y, 0);


			if (progresso->cenario->acido->naEstante == false)
				al_draw_bitmap(acidoMesa, 80, 430, 0);

			if (progresso->cenario->cDeCobre->naEstante == false)
				al_draw_bitmap(cDeCobreMesa, 280, 470, 0);

			if (progresso->cenario->macarico->naEstante == false)
				al_draw_bitmap(macaricoMesa, 800, 430, 0);


			//switch case do estado para controlar os desenhos
			switch (estado) {

			case inicio:
				al_draw_bitmap(recipiente, 600, 360, 0);

				if (progresso->cenario->aluminio->naEstante == false)
					al_draw_bitmap(aluminioMesa, 1100, 500, 0);

				break;

			case clicouAcido:
				al_draw_bitmap(recipienteAcido, 600, 360, 0);
				if (progresso->cenario->aluminio->naEstante == false)
					al_draw_bitmap(aluminioMesa, 1100, 500, 0);
				break;

			case clicouCloreto:
				al_draw_bitmap(recipienteAcidoCobre, 600, 360, 0);
				if (progresso->cenario->aluminio->naEstante == false)
					al_draw_bitmap(aluminioMesa, 1100, 500, 0);
				break;

			case clicouAlum:
				al_draw_bitmap(recipienteACA, 600, 250, 0);
				break;

			case clicouFogo:
				al_draw_bitmap(recipienteFeito1, 600, 270, 0);
				timer++;
				al_draw_bitmap(aviso, 0, 0, 0);
				if (timer == 180) {
					estado = apagarLuz;
					timer = 0;
				}
				break;

			case apagarLuz:
				al_draw_bitmap(fundoEscuro, 0, 0, 0);
				al_draw_bitmap(recipienteFeito1, 600, 270, 0);
				timer++;
				if (timer >= 0 && timer <= 80) {
					al_draw_bitmap(recipienteFeito2, 600, 277, 0);
				
				}
				else if (timer >= 80 && timer <= 160) {
					al_draw_bitmap(recipienteFeito3, 600, 270, 0);
					estado = acertou;

				}
				else if (timer >= 160 && timer <= 220) {
					estado = acertou;
					timer = 0;
				}
				break;

			case acertou:
				al_draw_bitmap(fundoEscuro, 0, 0, 0);
				bloquearCliques(progresso);
				al_draw_bitmap(btProx->imagem, btProx->x, btProx->y, 0);
				al_draw_bitmap(btReset->imagem, btReset->x, btReset->y, 0);
				al_draw_bitmap(btMenu->imagem, btMenu->x, btMenu->y, 0);
				al_draw_bitmap(recipienteFeito1, 600, 270, 0);
				timer++;

				if (timer >= 0 && timer <= 80) {
					al_draw_bitmap(recipienteFeito2, 600, 277, 0);

				}
				else if (timer >= 80 && timer <= 160) {
					al_draw_bitmap(recipienteFeito3, 600, 270, 0);
					estado = acertou;

				}
				else if (timer >= 160 && timer <= 220) {
					estado = acertou;
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

	progresso->cenario->acido->naEstante = true;
	progresso->cenario->aluminio->naEstante = true;
	progresso->cenario->cDeCobre->naEstante = true;
	progresso->cenario->macarico->naEstante = true;
	


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

