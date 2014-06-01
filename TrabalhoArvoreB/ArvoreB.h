#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include "ArvoreB_Arquivo.h"
#include <stdlib.h>

//BTREE
#define MAX_KEYS 4
#define MIN_KEYS 2
// INSERÇÃO
#define ERROR -1
#define NO_PROMOTION 0
#define PROMOTION 1
//BUSCA
#define KEY_FOUND 1
#define KEY_NOT_FOUND 0
// ARQUIVO
#define A_ARVOREB "ArvoreB.txt"
#define A_DISPONIVEL "Disponivel.txt"
//OUTROS
#define NULL -1

typedef struct{ //Registro
    int chave;
    int byteOffSet;
} Registro;

typedef struct { //BTPage
    int numeroChaves;
    Registro registro[MAX_KEYS];
    int child[MAX_KEYS + 1];
} BTPage;


//ARQUIVO
BTPage CarregaPagina(int RRN){
    BTPage p;
    return p;
}

int AtualizarCabecalho(int RRN) {
}

int SalvarPagina(BTPage page, int RRN) {
}

int AchaRRNRaiz(){
    FILE *arquivo;
    if ((arquivo = fopen(A_ARVOREB ,"r")) == NULL) {
        return AcharRRNDisponivel();
    }

    char recBuff[4];
    if (fgets(recBuff, 3, arquivo)!=NULL) {
            recBuff[4] = '/0';
            return (atoi(recBuff));
    }

    fclose(arquivo);

}

int AcharRRNDisponivel(){
    FILE *arquivo;
    if ((arquivo = fopen(A_DISPONIVEL ,"a+")) == NULL) {
        if ((arquivo = fopen(A_DISPONIVEL ,"w+")) == NULL) {
                system("cls");
                printf("\nNenhum registro encontrado\n");
                getch();
                return NULL;
        }
        else return 1;
    }
    fseek(arquivo, -3, SEEK_END);
    char recBuff[4];
    if (fgets(recBuff, 3, arquivo)!=NULL) {
            recBuff[4] = '/0';
            return (atoi(recBuff));
    }

    fclose(arquivo);
}

void MontarArvoreB(){
 /*       FILE *arquivo;
    if ((arquivo = fopen(A_PRINCIPAL ,"r+")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return 0;
            }
    char Buff[9];
    char SubBuff[7];
    char SubBuffOffset[4];
    int posicaoOffset = 0;
    int inscricao = 0;
    int i=0;
    rewind(arquivo);
    while (fgets(Buff, 10, arquivo) != NULL) {
        SubBuff[6] = '\0';
        SubBuffOffset[3]= '\0';
     Chave   strncpy(SubBuffOffset, &Buff[0], 3);
        strncpy(SubBuff, &Buff[3], 6);
        if (SubBuff[0] != '*') {
            InserirBTPage(inscricao(SubBuff), byteoffset(SubBuffOffset))
        _IndicesPrimario.Indice[i].ByteOffSet = posicaoOffset;
        inscricao = atoi(SubBuff);
        _IndicesPrimario.Indice[i].ID = inscricao;
        i =  i + 1;
        }
    Chave    posicaoOffset += atoi(SubBuffOffset) + 3;
        fseek(arquivo, posicaoOffset, SEEK_SET);
    };
    _IndicesPrimario.Tamanho = i;
    fclose(arquivo);chave
    */
}

int Buscar(int Chave, int RRN){
  	if (RRN == NULL){ //se ficar loop infinito, colocar verificação para NULL (ponteiro de pagina nao existente(depois da folha))
            return (KEY_NOT_FOUND);
    } else {
        BTPage p;
        //p =carregaBTPage(RRN); //carrega em memoria primaria pagina apontado por RRN
		int i = 0;
		int achou = KEY_NOT_FOUND;
		for (i = 0; ((i <= p.numeroChaves) //p procura Chave na pagina carregada
            && (Chave <= p.registro[i].chave )); i++) {
                if (p.registro[i].chave == Chave)
                    achou = KEY_FOUND;
            }
		if (achou == KEY_FOUND) {
			return (achou);
		}
		else {
		    if (Chave < p.registro[i].chave){//ponteiro = ponteiro para a próxima página da possível ocorrência de Chave
                RRN = p.child[i];
		    }else{
                RRN = p.child[i+1];
            }
			return (Buscar (Chave, RRN));
		}
	}
}

void Insercao(Registro registro){
    /*se o arquivo B-tree existe, então
    abra o arquivo B-tree
    senão
    crie um arquivo B-tree e coloque a primeira chave na raiz
    recupere o RRN da página raiz do arquivo e armazene em ROOT*/
    int ROOT = AchaRRNRaiz();
    if (ROOT == NULL) {
        BTPage p;
        p.numeroChaves = 1;
        p.registro[0] = registro;
        AtualizarCabecalho(1);
        SalvarPagina(p,1);
    }
    else {
        int PromoChave = 0;
        int RRNPromoFilha = 0;
        if (InsercaoInterna(ROOT, registro, PromoChave, RRNPromoFilha) == PROMOTION) {
            DivisaoRaiz(PromoChave, RRNPromoFilha);
        }
    }
}

int InsercaoInterna(int RRN, Registro registro, int ChavePromovida, int RRNPromoFilha) {
    BTPage p; //carrega em memoria primaria pagina apontado por RRN
    p = CarregaPagina(RRN);
    int achou;
	if (RRN == NULL) { //se ponteiroRaiz nao aponta para nenhuma pagina
		ChavePromovida = registro.chave;
		return(PROMOTION);
	} else {
	    int i;
        for (i = 0; ((i <= p.numeroChaves) //p procura Chave na pagina carregada
            && (registro.chave <= p.registro[i].chave )); i++) {
                if (p.registro[i].chave == registro.chave)
                    achou = KEY_FOUND;
        }

        if (achou == KEY_NOT_FOUND) {
            if (registro.chave < p.registro[i].chave){//ponteiro = ponteiro para a próxima página da possível ocorrência de Chave
                RRN = p.child[i];
            } else {
                RRN = p.child[i+1];
            }
        }
	}

	if (achou == KEY_FOUND) {
		return(ERROR); //chave ja esta na arvore, retorne uma flag de erro -nao pode inserir 2 chaves iguais
	}

	int flagRetorno = InsercaoInterna(RRN, registro, ChavePromovida, RRNPromoFilha);//procedimento recursivo

	if (flagRetorno != PROMOTION) {
		return(flagRetorno);
	} else if (p.numeroChaves < MAX_KEYS) {
		/*
		insere chavePromovida na página P
		escreve página P em arquivo
		*/
		return(NO_PROMOTION);

    } else { //nao ha espaço em P para key
		/*
		realize operação de split em P
		escreva em arquivo  a nova página e a página P
		*/
		return(PROMOTION);
	}
}

void DivisaoRaiz(Registro registro, int RRNPRomoFilha) {
    BTPage novaRaiz;
    int novoRRNRaiz = AcharRRNDisponivel();
    novaRaiz.numeroChaves = 1;
    novaRaiz.registro[0] = registro;
    novaRaiz.child[0] = AchaRRNRaiz();
    novaRaiz.child[1] = RRNPRomoFilha;
    SalvarPagina(novaRaiz, novoRRNRaiz);
    AtualizarCabecalho(novoRRNRaiz);
}

#endif // ARVOREB_H_INCLUDED
