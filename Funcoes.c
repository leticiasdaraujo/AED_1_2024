#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

//pilha dinamica
struct pilhano{
     Produto prod;
     float info;
     PilhaNo* prox;
};
struct pilha{
    PilhaNo* prim;
    int num_elementos;
};


////// funcoes pilha dinamica
Pilha* pilha_cria(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->prim = NULL;
    p->num_elementos = 0;
    return p;
}

Produto cria_prod(char* frase , float preco){
        Produto prod;
        strcpy(prod.frase, frase);
        prod.preco = preco;
        return prod;
}

void pilha_push(Pilha* p, float elemento){
    PilhaNo* n = malloc(sizeof(PilhaNo));
    n->info = elemento;
    n->prox = p->prim;
    p->prim = n;

    p->num_elementos++;
}

void pilha_pop(Pilha* p){
    if (p->prim == NULL) {
        printf("pilha já vazia\n");
        exit(0);
    }

    PilhaNo* t = p->prim;
    p->prim = t->prox;
    free(t);

    p->num_elementos--;
}

void pilha_libera(Pilha* p){
    PilhaNo* temp = p->prim;
    while (temp != NULL) {
        PilhaNo* t = temp->prox;
        free(temp);
        temp = t;
    }
    free(temp);
}


void empilha_produto(Pilha* p, Produto prod) {
    PilhaNo* novo = malloc(sizeof(PilhaNo));
    novo->prod = prod;
    novo->prox = p->prim;
    p->prim = novo;

    p->num_elementos++;
}

Produto desempilha_produto(Pilha* p) {
    if (p->prim == NULL) {
        printf("pilha já vazia\n");
        exit(0);
    }

    PilhaNo* t = p->prim;
    Produto produto = t->prod;
    p->prim = t->prox;
    free(t);

    p->num_elementos--;
    return produto;
}

float soma_produtos(Pilha* p){
	PilhaNo* no;
	float soma = 0.0;
	for(no = p->prim; no != NULL; no = no->prox){
		soma += no->prod.preco;
	}

	return soma;
}

void imprime_produto(Pilha* p) {
    PilhaNo* no;
    for (no = p->prim; no != NULL; no = no->prox) {
        printf("%s\n", no->prod.frase);
    }
}

int quant_elementos_pilha(Pilha* p){
    return p->num_elementos;
}

float retorna_topo(Pilha* p){
    return p->prim->info;
}


///desconto
void empilha_descontos(Pilha* p){
    float desc = 15.0;

    for(int i = 0; i < 12; i++){

        pilha_push(p, desc);
        desc = desc - 1.2;
    }
}

float calculaDesconto(float p_original, float percentualDesconto){
    float novoPreco, valorDesconto;

    valorDesconto = p_original * (percentualDesconto / 100.0);

    novoPreco = p_original - valorDesconto;

    return novoPreco;
}


///// funções Fila

Pedido cria_pedido(char* setor , int num_cad1, int num_cad2, Pilha* p){
        Pedido ped;
        strcpy(ped.setor, setor);
        ped.cadeira[0] = num_cad1;
        ped.cadeira[1] = num_cad2;
        ped.produtos = p;

        return ped;
}

Fila* fila_cria(void){
    Fila* f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;

    f->num_elementos = 0;
    return f;
}

void fila_insere(Fila* f, Pedido pedido){
    FilaNo* n = malloc(sizeof(FilaNo));
    n->pedido = pedido;
    n->prox = NULL;

    if (f->ini == NULL){ 
       f->ini = n;
       f->fim = n;
    } 
    else { 
       f->fim->prox = n;
       f->fim = n; 
    }

    f->num_elementos++;
}

int fila_elementos(Fila* f){
    return f->num_elementos;
}

void fila_libera(Fila* f){
    FilaNo* q = f->ini;
    while (q != NULL) {
        FilaNo* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}

void imprime_fila(Fila *f){
 FilaNo* q;

 if(f->ini == NULL){
    printf("Fila de pedidos vazia\n");
 }
 else{
    for(q = f->ini; q != NULL; q = q->prox){
        printf("Local: [%d %d] %s\n", q->pedido.cadeira[0], q->pedido.cadeira[1], q->pedido.setor);
        printf("Pedido: \n");
        imprime_produto(q->pedido.produtos);
        printf("\n");
    }
 }

}


//////////// outras funcoes

void matrizLugares(int matriz[linhas][colunas]){

    for(int l = 0; l < linhas; l++){
        printf("\n");
        for(int c = 0; c < colunas; c++){
            printf("[%d %d]", c,l);
        }
    }
}

void marcaLugar(char marcar,int assentoL, int assentoC, int matriz[linhas][colunas]){

    for(int l = 0; l < linhas; l++){
        printf("\n");
        for(int c = 0; c < colunas; c++){
            if(c == assentoL && l == assentoC){
               printf("[ %c ]", marcar);
            }
            else{
                printf("[%d %d]", c,l);
            }
        }
    }
}


void confirmaLugar(int matriz[linhas][colunas],char marcar){
    int confirmador, assentoL, assentoC;

    printf("\n Digite (1) para confirmar seu assento ou (2) para voltar: ");

    scanf("%d", &confirmador);

    while(confirmador!= 1){
        printf("Informe o seu assento: \n");

        matrizLugares(matriz);

        printf("\n Assento: ");
        scanf("%d %d",&assentoL, &assentoC);

        marcaLugar(marcar,assentoL,assentoC,matriz);

        printf("\n Digite (1) para confirmar seu assento ou (2) para voltar: ");

        scanf("%d", &confirmador);
    }
}

void imprimeMenu(){
    printf("\n");
    printf("===============================================\n");
    printf("Menu: \n");
    printf("===============================================\n");
    printf("Cachorro quente\t\t |6.00 R$\t - codigo: 10\n");
    printf("Sanduiche natural\t |9.00 R$\t - codigo: 15\n");
    printf("Pipoca pequena\t\t |6.00 R$\t - codigo: 20\n");
    printf("Pipoca media\t\t |8.00 R$\t - codigo: 25\n");
    printf("Pipoca grande\t\t |10.00 R$\t - codigo: 30\n");
    printf("Batata frita\t\t |6.00 R$\t - codigo: 35\n");
    printf("Pastel\t\t\t |8.00 R$\t - codigo: 40\n");
    printf("Picole\t\t\t |5.00 R$\t - codigo: 45\n");
    printf("Agua\t\t\t |3.00 R$\t - codigo: 50\n");
    printf("Refrigerante\t\t |8.00 R$\t - codigo: 55\n");
    printf("Suco\t\t\t |8.50 R$\t - codigo: 60\n");
    printf("Cerveja\t\t\t |10.00 R$\t - codigo: 65\n");
    printf("===============================================\n");
    printf("\n");

}

void formaDePagar(){

    int pag;
    scanf("%d", &pag);

    while(pag < 1 || pag > 3){
        printf("Entrada invalida! Digite uma das tres opcoes acima \n");
        scanf("%d", &pag);
    }

    if(pag == 1){
        printf(" Chave pix: 1234-5678-9012 \n Banco: Banco do Brasil \n Nome: LS Delivery \n CNPJ: 12.345.012/0001-00 \n");
        printf("\nNo recebimento do seu pedido, mostre seu comprovante para o entregador. \n");
    }

    else{
        printf("\nPara essa opcao eh necessario efetuar o pagamento na entrega. \n");
    }
}

void confirmaSetor(int setor){

    while(setor < 1 || setor > 4){
        printf("Entrada invalida! Tente novamente e digite uma das quatro opcoes acima \n");
        scanf("%d", &setor);
    }
}
