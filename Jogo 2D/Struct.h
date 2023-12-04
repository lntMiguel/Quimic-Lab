#ifndef Struct_H
#define Struct_H

#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>

//Aqui contem todas as structs

//"Objetos(cientista, elementos, etc)"
typedef struct obj { // <- obj recebe malloc
	int x, y, largura, altura, wx, wy;
	ALLEGRO_BITMAP* imagem; 

} Objeto;

typedef struct bt { // <- obj recebe malloc
	int x, y, largura, altura, wx, wy;
	ALLEGRO_BITMAP* desenho;
	ALLEGRO_BITMAP* hover;
	ALLEGRO_BITMAP* norm;

} Botao;

typedef struct reagentes {
	int x, y, largura, altura, wx, wy;
	ALLEGRO_BITMAP* imagemEstante;
	bool podeClicar;
	bool naEstante;

}Reagente;

typedef struct fase1 {
	ALLEGRO_BITMAP* ACestagio1;
	ALLEGRO_BITMAP* ACestagio2;
	ALLEGRO_BITMAP* ACestagio3;
	ALLEGRO_BITMAP* bicarbonatoMesa;
	ALLEGRO_BITMAP* fala1;
	ALLEGRO_BITMAP* fala2;
	ALLEGRO_BITMAP* fala3;
	ALLEGRO_BITMAP* vinagreMesa;
	ALLEGRO_BITMAP* reciVinagre;
	ALLEGRO_BITMAP* Vapor;
}Fase1;

typedef struct fase2 {
	ALLEGRO_BITMAP* aviso;
	ALLEGRO_BITMAP* lumiE1;
	ALLEGRO_BITMAP* lumiE2;
	ALLEGRO_BITMAP* fundoEscuro;
	ALLEGRO_BITMAP* fala1;
	ALLEGRO_BITMAP* fala2;
	ALLEGRO_BITMAP* fala3;
	ALLEGRO_BITMAP* luminolMesa;
	ALLEGRO_BITMAP* hidrogenioMesa;
	ALLEGRO_BITMAP* recipienteLuminol;
}Fase2;

typedef struct fase3 {
	ALLEGRO_BITMAP* acucarMesa;
	ALLEGRO_BITMAP* aguaMesa;
	ALLEGRO_BITMAP* beckerAguaPotassio;
	ALLEGRO_BITMAP* beckerAguaSoda;
	ALLEGRO_BITMAP* fala1;
	ALLEGRO_BITMAP* fala2;
	ALLEGRO_BITMAP* fala3;
	ALLEGRO_BITMAP* beckerAguaSodaAcucar;
	ALLEGRO_BITMAP* potassioMesa;
	ALLEGRO_BITMAP* recipienteLaranja;
	ALLEGRO_BITMAP* recipienteMisturado;
	ALLEGRO_BITMAP* recipienteRoxo;
	ALLEGRO_BITMAP* recipienteVerde;
	ALLEGRO_BITMAP* sodaMesa;
	ALLEGRO_BITMAP* fala4;
}Fase3;

typedef struct fase4 {
	ALLEGRO_BITMAP* aguaG;
	ALLEGRO_BITMAP* aguaR;
	ALLEGRO_BITMAP* aguaMesa;
	ALLEGRO_BITMAP*	comprimidoMesa;
	ALLEGRO_BITMAP* fala1;
	ALLEGRO_BITMAP* fala2;
	ALLEGRO_BITMAP* fala3;
	ALLEGRO_BITMAP* coranteGMesa;
	ALLEGRO_BITMAP* coranteRMesa;
	ALLEGRO_BITMAP* lampadaG1;
	ALLEGRO_BITMAP* lampadaG2;
	ALLEGRO_BITMAP* lampadaR1;
	ALLEGRO_BITMAP* lampadaR2;
	ALLEGRO_BITMAP* oleoMesa;	
	ALLEGRO_BITMAP* reciAguaG;
	ALLEGRO_BITMAP* reciAguaR;
	ALLEGRO_BITMAP* reciAguaOleoG;
	ALLEGRO_BITMAP* reciAguaOleoR;
}Fase4;

typedef struct fase5 {
	ALLEGRO_BITMAP* acidoMesa;
	ALLEGRO_BITMAP* aurora1;
	ALLEGRO_BITMAP* aurora2;
	ALLEGRO_BITMAP* aurora3;
	ALLEGRO_BITMAP* fala1;
	ALLEGRO_BITMAP* fala2;
	ALLEGRO_BITMAP* fala3;
	ALLEGRO_BITMAP* aviso;
	ALLEGRO_BITMAP* cDeCobreMesa;
	ALLEGRO_BITMAP* fundoEscuro;
	ALLEGRO_BITMAP* macaricoMesa;
	ALLEGRO_BITMAP* papelAlum;
	ALLEGRO_BITMAP* reciACA;
	ALLEGRO_BITMAP* reciAcido;
	ALLEGRO_BITMAP* reciAcidoCobre;
}Fase5;

typedef struct fase6 {
	ALLEGRO_BITMAP* acucarMesa;
	ALLEGRO_BITMAP* bicarbonatoMesa;
	ALLEGRO_BITMAP* bandeja;
	ALLEGRO_BITMAP* bandejaCubos;
	ALLEGRO_BITMAP* macaricoMesa;
	ALLEGRO_BITMAP* fala1;
	ALLEGRO_BITMAP* fala2;
	ALLEGRO_BITMAP* fala3;
	ALLEGRO_BITMAP* cubos;
	ALLEGRO_BITMAP* serpente1;
	ALLEGRO_BITMAP* serpente2;
	ALLEGRO_BITMAP* serpente3;
	ALLEGRO_BITMAP* serpente4;
	ALLEGRO_BITMAP* serpente5;
	ALLEGRO_BITMAP* serpente6;
	ALLEGRO_BITMAP* serpente7;
	ALLEGRO_BITMAP* serpente8;
}Fase6;


typedef struct cenario {
	ALLEGRO_BITMAP* lab; 
	ALLEGRO_BITMAP* escritorio;
	ALLEGRO_BITMAP* menuFundo;
	ALLEGRO_BITMAP* cjFundo;
	Reagente* bicarbonato;
	Reagente* bicarbonatoColher;
	Reagente* acido;
	Reagente* cDeCobre;
	Reagente* acucar;
	Reagente* agua;
	Reagente* aluminio;
	Reagente* comprimido;
	Reagente* coranteG;
	Reagente* coranteR;
	Reagente* hidrogenio;
	Reagente* luminol;
	Reagente* macarico;
	Reagente* oleo;
	Reagente* potassio;
	Reagente* recipiente;
	Reagente* soda;
	Reagente* vinagre;
	Reagente* becker;
	Fase1* fase1;
	Fase2* fase2;
	Fase3* fase3;
	Fase4* fase4;
	Fase5* fase5;
	Fase6* fase6;
	Botao* btReset;
	Botao* btProx;
	Botao* btMenu;
	ALLEGRO_FONT* font;
} Cenario;


typedef struct progresso {
	int proximaReacao;
	int reacoes[7];
	int fimDeJogo;
	Cenario* cenario; // <- cenario recebe malloc
} Prog;

#endif
