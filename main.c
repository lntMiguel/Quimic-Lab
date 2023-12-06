#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include "Jogo 2D/Struct.h"
#include "Jogo 2D/mudarReacao.h"
#include <allegro5/allegro_primitives.h>
//Ajustar Acido carbonico: Elementos conseguem sair da estante no estado errou | tirar o else do clique no bicarbonato para garantir que o jogador perca
// colocar nome dos ingredientes na mesa camaleao
//redimensionar imagens lampada
// Colocar mais fundos
//variaveis globais

int main() {
	//inicialização
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_init_primitives_addon();
	
	//Display
	ALLEGRO_DISPLAY* display = al_create_display(1500, 844);
	al_set_window_title(display, "Teste - Nova Lógica");

	//Fila de eventos
	ALLEGRO_EVENT_QUEUE* filaDeEventos =  al_create_event_queue();
	al_register_event_source(filaDeEventos, al_get_display_event_source(display));

	//Load da fonte
	ALLEGRO_FONT* font, * fonteBalao;
	font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	fonteBalao = al_load_ttf_font("fontes/fonteBalao.ttf", 20, 0);

	if (!al_install_mouse()) {	
		fprintf(stderr, "Falha ao iniciar o mouse\n");
		al_destroy_display(display);
		al_destroy_event_queue(filaDeEventos);

		return -1;
	}


	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

	//registrando eventos
	al_register_event_source(filaDeEventos, al_get_timer_event_source(timer));
	al_register_event_source(filaDeEventos, al_get_mouse_event_source());

	//start timer
	al_start_timer(timer);

	Prog progresso;
	
	progresso.proximaReacao = 0;
	progresso.fimDeJogo = 0;
	progresso.reacoes[0] = 0;
	progresso.reacoes[1] = 0;
	progresso.reacoes[2] = 0;
	progresso.reacoes[3] = 0;
	progresso.reacoes[4] = 0;
	progresso.reacoes[5] = 0;
	progresso.reacoes[6] = 0;

	progresso.cenario = (Cenario*)malloc(sizeof(Cenario));
	
	progresso.cenario->bicarbonato = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->bicarbonato->imagemEstante = al_load_bitmap("imagens/bicarbonatoEstante.png");
	progresso.cenario->bicarbonato->altura = 100;
	progresso.cenario->bicarbonato->largura = 108;
	progresso.cenario->bicarbonato->wx = 0;
	progresso.cenario->bicarbonato->wy = 0;
	progresso.cenario->bicarbonato->x = 1010;
	progresso.cenario->bicarbonato->y = 130;
	progresso.cenario->bicarbonato->podeClicar = true;
	progresso.cenario->bicarbonato->naEstante = true;
	                   
	progresso.cenario->vinagre = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->vinagre->imagemEstante = al_load_bitmap("imagens/vinagreEstante.png");
	progresso.cenario->vinagre->altura = 95;
	progresso.cenario->vinagre->largura = 70;
	progresso.cenario->vinagre->wx = 0;
	progresso.cenario->vinagre->wy = 0;
	progresso.cenario->vinagre->x = 1010;
	progresso.cenario->vinagre->y = 325;
	progresso.cenario->vinagre->podeClicar = true;
	progresso.cenario->vinagre->naEstante = true;

	progresso.cenario->bicarbonatoColher = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->bicarbonatoColher->imagemEstante = al_load_bitmap("imagens/bicarbonatoEstante.png");
	progresso.cenario->bicarbonatoColher->altura = 100;
	progresso.cenario->bicarbonatoColher->largura = 108;
	progresso.cenario->bicarbonatoColher->wx = 0;
	progresso.cenario->bicarbonatoColher->wy = 0;
	progresso.cenario->bicarbonatoColher->x = 1010;
	progresso.cenario->bicarbonatoColher->y = 130;
	progresso.cenario->bicarbonatoColher->podeClicar = true;
	progresso.cenario->bicarbonatoColher->naEstante = true;

	progresso.cenario->acido = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->acido->imagemEstante = al_load_bitmap("imagens/acidoEstante.png");
	progresso.cenario->acido->altura = 95;
	progresso.cenario->acido->largura = 70;
	progresso.cenario->acido->wx = 0;
	progresso.cenario->acido->wy = 0;
	progresso.cenario->acido->x = 1130;
	progresso.cenario->acido->y = 115;
	progresso.cenario->acido->podeClicar = true;
	progresso.cenario->acido->naEstante = true;

	progresso.cenario->cDeCobre = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->cDeCobre->imagemEstante = al_load_bitmap("imagens/cDeCobreEstante.png");
	progresso.cenario->cDeCobre->altura = 75;
	progresso.cenario->cDeCobre->largura = 70;
	progresso.cenario->cDeCobre->wx = 0;
	progresso.cenario->cDeCobre->wy = 0;
	progresso.cenario->cDeCobre->x = 1250;
	progresso.cenario->cDeCobre->y = 130;
	progresso.cenario->cDeCobre->podeClicar = true;
	progresso.cenario->cDeCobre->naEstante = true;

	progresso.cenario->acucar = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->acucar->imagemEstante = al_load_bitmap("imagens/acucarEstante.png");
	progresso.cenario->acucar->altura = 66;
	progresso.cenario->acucar->largura = 70;
	progresso.cenario->acucar->wx = 0;
	progresso.cenario->acucar->wy = 0;
	progresso.cenario->acucar->x = 1370;
	progresso.cenario->acucar->y = 247;
	progresso.cenario->acucar->podeClicar = true;
	progresso.cenario->acucar->naEstante = true;

	progresso.cenario->agua = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->agua->imagemEstante = al_load_bitmap("imagens/aguaEstante.png");
	progresso.cenario->agua->altura = 95;
	progresso.cenario->agua->largura = 70;
	progresso.cenario->agua->wx = 0;
	progresso.cenario->agua->wy = 0;
	progresso.cenario->agua->x = 1370;
	progresso.cenario->agua->y = 115;
	progresso.cenario->agua->podeClicar = true;
	progresso.cenario->agua->naEstante = true;

	progresso.cenario->aluminio = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->aluminio->imagemEstante = al_load_bitmap("imagens/aluminioEstante.png");
	progresso.cenario->aluminio->altura = 27;
	progresso.cenario->aluminio->largura = 120;
	progresso.cenario->aluminio->wx = 0;
	progresso.cenario->aluminio->wy = 0;
	progresso.cenario->aluminio->x = 1100;
	progresso.cenario->aluminio->y = 375;
	progresso.cenario->aluminio->podeClicar = true;
	progresso.cenario->aluminio->naEstante = true;

	progresso.cenario->comprimido = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->comprimido->imagemEstante = al_load_bitmap("imagens/comprimidoEstante.png");
	progresso.cenario->comprimido->altura = 59;
	progresso.cenario->comprimido->largura = 70;
	progresso.cenario->comprimido->wx = 0;
	progresso.cenario->comprimido->wy = 0;
	progresso.cenario->comprimido->x = 1010;
	progresso.cenario->comprimido->y = 248;
	progresso.cenario->comprimido->podeClicar = true;
	progresso.cenario->comprimido->naEstante = true;

	progresso.cenario->coranteG = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->coranteG->imagemEstante = al_load_bitmap("imagens/coranteGEstante.png");
	progresso.cenario->coranteG->altura = 85;
	progresso.cenario->coranteG->largura = 40;
	progresso.cenario->coranteG->wx = 0;
	progresso.cenario->coranteG->wy = 0;
	progresso.cenario->coranteG->x = 1145;
	progresso.cenario->coranteG->y = 225	;
	progresso.cenario->coranteG->podeClicar = true;
	progresso.cenario->coranteG->naEstante = true;

	progresso.cenario->coranteR = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->coranteR->imagemEstante = al_load_bitmap("imagens/coranteREstante.png");
	progresso.cenario->coranteR->altura = 83;
	progresso.cenario->coranteR->largura = 40;
	progresso.cenario->coranteR->wx = 0;
	progresso.cenario->coranteR->wy = 0;
	progresso.cenario->coranteR->x = 1265;
	progresso.cenario->coranteR->y = 335;
	progresso.cenario->coranteR->podeClicar = true;
	progresso.cenario->coranteR->naEstante = true;

	progresso.cenario->hidrogenio = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->hidrogenio->imagemEstante = al_load_bitmap("imagens/hidrogenioEstante.png");
	progresso.cenario->hidrogenio->altura = 95;
	progresso.cenario->hidrogenio->largura = 70;
	progresso.cenario->hidrogenio->wx = 0;
	progresso.cenario->hidrogenio->wy = 0;
	progresso.cenario->hidrogenio->x = 1130;
	progresso.cenario->hidrogenio->y = 15;
	progresso.cenario->hidrogenio->podeClicar = true;
	progresso.cenario->hidrogenio->naEstante = true;

	progresso.cenario->luminol = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->luminol->imagemEstante = al_load_bitmap("imagens/luminolEstante.png");
	progresso.cenario->luminol->altura = 95;
	progresso.cenario->luminol->largura = 70;
	progresso.cenario->luminol->wx = 0;
	progresso.cenario->luminol->wy = 0;
	progresso.cenario->luminol->x = 1010;
	progresso.cenario->luminol->y = 15;
	progresso.cenario->luminol->podeClicar = true;
	progresso.cenario->luminol->naEstante = true;

	progresso.cenario->macarico = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->macarico->imagemEstante = al_load_bitmap("imagens/macaricoEstante.png");
	progresso.cenario->macarico->altura = 89;
	progresso.cenario->macarico->largura = 90;
	progresso.cenario->macarico->wx = 0;
	progresso.cenario->macarico->wy = 0;
	progresso.cenario->macarico->x = 1360;
	progresso.cenario->macarico->y = 15;
	progresso.cenario->macarico->podeClicar = true;
	progresso.cenario->macarico->naEstante = true;

	progresso.cenario->oleo = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->oleo->imagemEstante = al_load_bitmap("imagens/oleoEstante.png");
	progresso.cenario->oleo->altura = 95;
	progresso.cenario->oleo->largura = 70;
	progresso.cenario->oleo->wx = 0;
	progresso.cenario->oleo->wy = 0;
	progresso.cenario->oleo->x = 1250;
	progresso.cenario->oleo->y = 220;
	progresso.cenario->oleo->podeClicar = true;
	progresso.cenario->oleo->naEstante = true;

	progresso.cenario->potassio = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->potassio->imagemEstante = al_load_bitmap("imagens/potassioEstante.png");
	progresso.cenario->potassio->altura = 59;
	progresso.cenario->potassio->largura = 70;
	progresso.cenario->potassio->wx = 0;
	progresso.cenario->potassio->wy = 0;
	progresso.cenario->potassio->x = 1250;
	progresso.cenario->potassio->y = 36;
	progresso.cenario->potassio->podeClicar = true;
	progresso.cenario->potassio->naEstante = true;

	progresso.cenario->soda = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->soda->imagemEstante = al_load_bitmap("imagens/sodaEstante.png");
	progresso.cenario->soda->altura = 100;
	progresso.cenario->soda->largura = 108;
	progresso.cenario->soda->wx = 0;
	progresso.cenario->soda->wy = 0;
	progresso.cenario->soda->x = 1370;
	progresso.cenario->soda->y = 340;
	progresso.cenario->soda->podeClicar = true;
	progresso.cenario->soda->naEstante = true;

	progresso.cenario->recipiente = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->recipiente->imagemEstante = al_load_bitmap("imagens/recipiente.png");
	progresso.cenario->recipiente->altura = 100;
	progresso.cenario->recipiente->largura = 108;
	progresso.cenario->recipiente->wx = 0;
	progresso.cenario->recipiente->wy = 0;
	progresso.cenario->recipiente->x = 1370;
	progresso.cenario->recipiente->y = 340;
	progresso.cenario->recipiente->podeClicar = true;
	progresso.cenario->recipiente->naEstante = true;

	progresso.cenario->becker = (Reagente*)malloc(sizeof(Reagente));
	progresso.cenario->becker->imagemEstante = al_load_bitmap("imagens/beckerMesa.png");
	progresso.cenario->becker->altura = 100;
	progresso.cenario->becker->largura = 108;
	progresso.cenario->becker->wx = 0;
	progresso.cenario->becker->wy = 0;
	progresso.cenario->becker->x = 1370;
	progresso.cenario->becker->y = 340;
	progresso.cenario->becker->podeClicar = true;
	progresso.cenario->becker->naEstante = true;


	progresso.cenario->lab = al_load_bitmap("imagens/fundo.png");
	progresso.cenario->escritorio = al_load_bitmap("imagens/escritorio2.png");
	progresso.cenario->menuFundo = al_load_bitmap("imagens/escritorio1.png");
	progresso.cenario->cjFundo = al_load_bitmap("imagens/cjFundo.png");
	

	progresso.cenario->fase1 = (Fase1*)malloc(sizeof(Fase1));
	progresso.cenario->fase1->ACestagio1 = al_load_bitmap("imagens/fase1/ACestagio1.png");
	progresso.cenario->fase1->ACestagio2 = al_load_bitmap("imagens/fase1/ACestagio2.png");
	progresso.cenario->fase1->ACestagio3 = al_load_bitmap("imagens/fase1/ACestagio3.png");
	progresso.cenario->fase1->reciVinagre = al_load_bitmap("imagens/fase1/reciVinagre.png");
	progresso.cenario->fase1->Vapor = al_load_bitmap("imagens/fase1/Vapor.png");
	progresso.cenario->fase1->fala1 = al_load_bitmap("imagens/fase1/fase1H1.png");
	progresso.cenario->fase1->fala2 = al_load_bitmap("imagens/fase1/fase1H2.png");
	progresso.cenario->fase1->fala3 = al_load_bitmap("imagens/fase1/fase1H3.png");
	progresso.cenario->fase1->vinagreMesa = al_load_bitmap("imagens/fase1/vinagre.png");
	progresso.cenario->fase1->bicarbonatoMesa = al_load_bitmap("imagens/fase1/bicarbonato.png");

	progresso.cenario->fase2 = (Fase2*)malloc(sizeof(Fase2));
	progresso.cenario->fase2->lumiE1 = al_load_bitmap("imagens/fase2/lumiE1.png");
	progresso.cenario->fase2->lumiE2 = al_load_bitmap("imagens/fase2/lumiE2.png");
	progresso.cenario->fase2->luminolMesa = al_load_bitmap("imagens/fase2/lumiMesa.png");
	progresso.cenario->fase2->recipienteLuminol = al_load_bitmap("imagens/fase2/reciLumi.png");
	progresso.cenario->fase2->fundoEscuro = al_load_bitmap("imagens/fase2/fundoEscuro.png");
	progresso.cenario->fase2->fala1 = al_load_bitmap("imagens/fase2/fase2H1.png");
	progresso.cenario->fase2->fala2 = al_load_bitmap("imagens/fase2/fase2H2.png");
	progresso.cenario->fase2->fala3 = al_load_bitmap("imagens/fase2/fase2H3.png");
	progresso.cenario->fase2->hidrogenioMesa = al_load_bitmap("imagens/fase2/hidrogenioMesa.png");
	progresso.cenario->fase2->aviso = al_load_bitmap("imagens/fase2/aviso.png");

	progresso.cenario->fase3 = (Fase3*)malloc(sizeof(Fase3));
	progresso.cenario->fase3->acucarMesa = al_load_bitmap("imagens/fase3/acucarMesa.png");
	progresso.cenario->fase3->aguaMesa = al_load_bitmap("imagens/fase3/aguaMesa.png");
	progresso.cenario->fase3->sodaMesa = al_load_bitmap("imagens/fase3/sodaMesa.png");
	progresso.cenario->fase3->beckerAguaSoda = al_load_bitmap("imagens/fase3/beckerAguaSoda.png");
	progresso.cenario->fase3->beckerAguaPotassio = al_load_bitmap("imagens/fase3/beckerAguaPotassio.png");
	progresso.cenario->fase3->fala1 = al_load_bitmap("imagens/fase3/fase3H1.png");
	progresso.cenario->fase3->fala2 = al_load_bitmap("imagens/fase3/fase3H2.png");
	progresso.cenario->fase3->fala3 = al_load_bitmap("imagens/fase3/fase3H3.png");
	progresso.cenario->fase3->beckerAguaSodaAcucar = al_load_bitmap("imagens/fase3/beckerAguaSodaAcucar.png");
	progresso.cenario->fase3->recipienteMisturado = al_load_bitmap("imagens/fase3/recipienteMisturado.png");
	progresso.cenario->fase3->recipienteRoxo = al_load_bitmap("imagens/fase3/recipienteRoxo.png");
	progresso.cenario->fase3->recipienteLaranja = al_load_bitmap("imagens/fase3/recipienteLaranja.png");
	progresso.cenario->fase3->recipienteVerde = al_load_bitmap("imagens/fase3/recipienteVerde.png");
	progresso.cenario->fase3->fala4= al_load_bitmap("imagens/fase3/fase3H4.png");
	progresso.cenario->fase3->potassioMesa = al_load_bitmap("imagens/fase3/potassioMesa.png");

	progresso.cenario->fase4 = (Fase4*)malloc(sizeof(Fase4));
	progresso.cenario->fase4->coranteGMesa = al_load_bitmap("imagens/fase4/coranteGMesa.png");
	progresso.cenario->fase4->coranteRMesa = al_load_bitmap("imagens/fase4/coranteRMesa.png");
	progresso.cenario->fase4->aguaMesa = al_load_bitmap("imagens/fase4/aguaMesa.png");
	progresso.cenario->fase4->aguaG = al_load_bitmap("imagens/fase4/aguaG.png");
	progresso.cenario->fase4->aguaR= al_load_bitmap("imagens/fase4/aguaR.png");
	progresso.cenario->fase4->fala1 = al_load_bitmap("imagens/fase4/fase4H1.png");
	progresso.cenario->fase4->fala2 = al_load_bitmap("imagens/fase4/fase4H2.png");
	progresso.cenario->fase4->fala3 = al_load_bitmap("imagens/fase4/fase4H3.png");
	progresso.cenario->fase4->oleoMesa = al_load_bitmap("imagens/fase4/oleoMesa.png");
	progresso.cenario->fase4->reciAguaOleoG= al_load_bitmap("imagens/fase4/reciAguaOleoG.png");
	progresso.cenario->fase4->reciAguaOleoR = al_load_bitmap("imagens/fase4/reciAguaOleoR.png");
	progresso.cenario->fase4->reciAguaG = al_load_bitmap("imagens/fase4/reciAguaG.png");
	progresso.cenario->fase4->reciAguaR = al_load_bitmap("imagens/fase4/reciAguaR.png");
	progresso.cenario->fase4->lampadaG1 = al_load_bitmap("imagens/fase4/lampadaG1.png");
	progresso.cenario->fase4->lampadaG2 = al_load_bitmap("imagens/fase4/lampadaG2.png");
	progresso.cenario->fase4->lampadaR1 = al_load_bitmap("imagens/fase4/lampadaR1.png");
	progresso.cenario->fase4->lampadaR2 = al_load_bitmap("imagens/fase4/lampadaR2.png");
	progresso.cenario->fase4->comprimidoMesa = al_load_bitmap("imagens/fase4/comprimidoMesa.png");

	progresso.cenario->fase5 = (Fase5*)malloc(sizeof(Fase5));
	progresso.cenario->fase5->acidoMesa = al_load_bitmap("imagens/fase5/acidoMesa.png");
	progresso.cenario->fase5->papelAlum = al_load_bitmap("imagens/fase5/papelAlum.png");
	progresso.cenario->fase5->macaricoMesa = al_load_bitmap("imagens/fase5/macaricoMesa.png");
	progresso.cenario->fase5->cDeCobreMesa = al_load_bitmap("imagens/fase5/cDeCobreMesa.png");
	progresso.cenario->fase5->reciAcidoCobre = al_load_bitmap("imagens/fase5/reciAcidoCobre.png");
	progresso.cenario->fase5->reciACA = al_load_bitmap("imagens/fase5/reciACA.png");
	progresso.cenario->fase5->reciAcido = al_load_bitmap("imagens/fase5/reciAcido.png");
	progresso.cenario->fase5->aurora1 = al_load_bitmap("imagens/fase5/aurora1.png");
	progresso.cenario->fase5->aurora2 = al_load_bitmap("imagens/fase5/aurora2.png");
	progresso.cenario->fase5->aurora3 = al_load_bitmap("imagens/fase5/aurora3.png");
	progresso.cenario->fase5->aviso = al_load_bitmap("imagens/fase5/aviso.png");
	progresso.cenario->fase5->fundoEscuro = al_load_bitmap("imagens/fase5/fundoEscuro.png");
	progresso.cenario->fase5->fala1= al_load_bitmap("imagens/fase5/fase5H1.png");
	progresso.cenario->fase5->fala2 = al_load_bitmap("imagens/fase5/fase5H2.png");
	progresso.cenario->fase5->fala3 = al_load_bitmap("imagens/fase5/fase5H3.png");

	progresso.cenario->fase6 = (Fase6*)malloc(sizeof(Fase6));
	progresso.cenario->fase6->acucarMesa = al_load_bitmap("imagens/fas6/acucarMesa.png");
	progresso.cenario->fase6->bicarbonatoMesa = al_load_bitmap("imagens/fase6/bicarbonato.png");
	progresso.cenario->fase6->macaricoMesa = al_load_bitmap("imagens/fase6/macaricoMesa.png");
	progresso.cenario->fase6->bandeja = al_load_bitmap("imagens/fase6/bandeja.png");
	progresso.cenario->fase6->bandejaCubos = al_load_bitmap("imagens/fase6/bandejaCubos.png");
	progresso.cenario->fase6->serpente1 = al_load_bitmap("imagens/fase6/serpente1.png");
	progresso.cenario->fase6->serpente2 = al_load_bitmap("imagens/fase6/serpente2.png");
	progresso.cenario->fase6->serpente3 = al_load_bitmap("imagens/fase6/serpente3.png");
	progresso.cenario->fase6->serpente4 = al_load_bitmap("imagens/fase6/serpente4.png");
	progresso.cenario->fase6->serpente5 = al_load_bitmap("imagens/fase6/serpente5.png");
	progresso.cenario->fase6->serpente6 = al_load_bitmap("imagens/fase6/serpente6.png");
	progresso.cenario->fase6->serpente7 = al_load_bitmap("imagens/fase6/serpente7.png");
	progresso.cenario->fase6->fala1 = al_load_bitmap("imagens/fase6/fase6H1.png");
	progresso.cenario->fase6->fala2 = al_load_bitmap("imagens/fase6/fase6H2.png");
	progresso.cenario->fase6->fala3 = al_load_bitmap("imagens/fase6/fase6H3.png");
	progresso.cenario->fase6->serpente8 = al_load_bitmap("imagens/fase6/serpente8.png");
	progresso.cenario->fase6->cubos = al_load_bitmap("imagens/fase6/cubos.png");

	



	progresso.cenario->btMenu = (Botao*)malloc(sizeof(Botao));
	progresso.cenario->btMenu->altura = 98;
	progresso.cenario->btMenu->largura = 310;
	progresso.cenario->btMenu->desenho = NULL;
	progresso.cenario->btMenu->norm = al_load_bitmap("imagens/btMenu.png");
	progresso.cenario->btMenu->hover = al_load_bitmap("imagens/btMenuH.png");
	progresso.cenario->btMenu->wx = 0;
	progresso.cenario->btMenu->wy = 0;
	progresso.cenario->btMenu->x = 1010;
	progresso.cenario->btMenu->y = 720;
	
	progresso.cenario->btProx = (Botao*)malloc(sizeof(Botao));
	progresso.cenario->btProx->altura = 98;
	progresso.cenario->btProx->largura = 310;
	progresso.cenario->btProx->desenho = NULL;
	progresso.cenario->btProx->norm = al_load_bitmap("imagens/btProx.png");
	progresso.cenario->btProx->hover = al_load_bitmap("imagens/btProxH.png");
	progresso.cenario->btProx->wx = 0;
	progresso.cenario->btProx->wy = 0;
	progresso.cenario->btProx->x = 1010;
	progresso.cenario->btProx->y = 480;

	progresso.cenario->btReset = (Botao*)malloc(sizeof(Botao));
	progresso.cenario->btReset->altura = 98;
	progresso.cenario->btReset->largura = 310;
	progresso.cenario->btReset->desenho = NULL;
	progresso.cenario->btReset->norm = al_load_bitmap("imagens/btReset.png");
	progresso.cenario->btReset->hover = al_load_bitmap("imagens/btResetH.png");
	progresso.cenario->btReset->wx = 0;
	progresso.cenario->btReset->wy = 0;
	progresso.cenario->btReset->x = 1010;
	progresso.cenario->btReset->y = 600;
	
	progresso.cenario->final = (Final*)malloc(sizeof(Final));
	progresso.cenario->final->contrato = al_load_bitmap("imagens/Contrato.png");
	progresso.cenario->final->falaFinal = al_load_bitmap("imagens/final.png");
	
	progresso.cenario->font = al_load_ttf_font("fontes/fonte2.ttf", 20, 0);
	Prog* prog = &progresso;

	while (!prog->fimDeJogo) {
		
		selecionaReacao(display, filaDeEventos, prog);
		
	}
	
	al_destroy_event_queue(filaDeEventos);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_destroy_display(display);
	
	return 0;
}
