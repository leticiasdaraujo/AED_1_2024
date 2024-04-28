#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED
#define linhas 5
#define colunas 5

//definição do produto
typedef struct produto Produto;
struct produto{ // o produto vai ter tanto seu nome quanto um preco definido
    char frase[100];
    float preco;
};

typedef struct pilhano PilhaNo;
typedef struct pilha Pilha;

 ///Pilha dinamica
Pilha* pilha_cria(); //funcao para criar as pilhas
Produto cria_prod(char* frase , float codigo); //funcao para criar o produto com seu nome e o codigo que corresponde a ele
void pilha_push(Pilha* p,float elemento); // funcao para empilhar
void pilha_pop(Pilha* p); //funcao para desempilhar
void empilha_produto(Pilha* p, Produto produto); //funcao para empilhar os produtos
Produto desempilha_produto(Pilha* p);//funcao para desempilhar os produtos
void pilha_libera(Pilha* p); //funcao para liberar espaco alocado de cada no
float soma_produtos(Pilha* p); //funcao para somar os produtos que estao na pillha e vai retornar um valor(soma)
void imprime_produto(Pilha* p); //funcao para imprimir a lista de produtos que o cliente pediu
int quant_elementos_pilha(Pilha* p); //funcao que retorna a quantidade de elemntos que estao na lista do cliente
float retorna_topo(Pilha* p); //retornar o ultimo elemento do topo da pilha, que eh o desconto que o cliente tem

 //desconto
void empilha_descontos(Pilha* p); //empilha os descontos para que a pilha comece cheia
float calculaDesconto(float p_original, float percentualDesconto); /*calcula o desconto que o cliente ganhou na compra de no minimo 3 produtos,
                                                                    o desconto varia de acordo com a quantidade de produtos*/


///Fila

// definição do pedido
 typedef struct filano FilaNo;
 typedef struct fila Fila;
 typedef struct pedido Pedido;

 struct pedido{ // a cadeira e o setor vao ser para localizacao do cliente, e a pilha com os produtos que o cliente comprou
    int cadeira[2];
    char setor[13];
    Pilha* produtos;
 };

 struct filano{
    FilaNo* prox;
    Pedido pedido;
};

struct fila{
    FilaNo* ini;
    FilaNo* fim;
    int num_elementos;
 };



 Fila* fila_cria(void); //funcao para criar uma fila
 void fila_insere(Fila* f, Pedido pedido); //funcao para inserir os pedidos feitos pelo cliente
 void fila_libera(Fila* f); //funcao para liberar a memoria alocada por cada no
 Pedido cria_pedido(char* setor , int num_cad1, int num_cad2, Pilha* p); // funcao que cria o pedido, ele recebe como parametro a localizacao e os produtos
 void imprime_fila(Fila *f); //funcao para imprimir os elementos da fila
 int fila_elementos(Fila* f); /*funcao que retorna a quantidade de elementos/pedidos que tem na fila,
                               que servem para ajudar a contar a quantidade maxima de entregas para cada entregador*/



/////////outras funcoes

void matrizLugares(int matriz[linhas][colunas]); //cria a matriz para marcacao de lugares
void marcaLugar(char marcar,int assentoL, int assentoC, int matriz[linhas][colunas]); //o cliente pode marcar o lugar que ele esta
void confirmaLugar(int matriz[linhas][colunas],char marcar); //serve para confirmar a escolha feita pelo cliente em relacao ao seu assento
void imprimeMenu(); //imprime o menu com as opcoes de produtos
void formaDePagar(); //imprime as formas de pagamento feitas pelo delivery
void confirmaSetor(int setor); //funcao que serve para confirmar se o setor que o cliente informou esta certo
#endif // CABECALHO_H_INCLUDED
