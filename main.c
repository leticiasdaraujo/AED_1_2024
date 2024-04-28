#include <stdio.h>
#include <stdlib.h>
#include "cabecalho.h"

int main(void){

    int produto,setor,assentoL, assentoC,confirmador, confirmaProd, perfil;
    float soma = 0.0;
    float valor_final = 0.0;
    char marcar = 'X';
    char porcento = '%';
    int codigoProduto[12] = {10,15,20,25,30,35,40,45,50,55,60,65};
    int matLugares[linhas][colunas];
    Pilha* P_produtos;
    Pilha* descontos;
    Fila* F_pedidos;

    F_pedidos = fila_cria();//fila de pedidos do entregador

    while(fila_elementos(F_pedidos) != 4){
	descontos = pilha_cria(); //cria a pilha de descontos
        empilha_descontos(descontos); //a pilha de descontos cheia

        printf("\nOla, seja bem vindo(a)!\nCaso deseja entrar como entregador e vizualizar seus pedidos a serem entregues, digite(1)\n\n");
        printf("Caso deseja entrar como cliente e fazer o seu pedido, digite(2)\n");

        scanf("%d", &perfil);

        if(perfil == 2){ //parte para o cliente

                printf("\n");

                do{
                printf("Bem vindo(a)!\n");

                printf("Para iniciar o seu atendimento, informe-nos em qual setor do estadio voce se encontra (digite o numero correspondente ao seu setor): \n");
                printf(" 1- Setor Norte\n 2- Setor Sul\n 3- Setor Leste\n 4- Setor Oeste\n");

                scanf("%d", &setor);
		confirmaSetor(setor);

                printf("\nPara continuar, informe-nos o seu assento (Digite assim como esta na tela, com o espaco entre os numeros): \n");

                matrizLugares(matLugares);

                printf("\n Assento: ");
                scanf("%d %d",&assentoL, &assentoC);

                marcaLugar(marcar,assentoL,assentoC,matLugares);

                confirmaLugar(matLugares,marcar);

                imprimeMenu();

                printf("Digite o codigo do produto desejado: \n");
                printf("Para finalizar o pedido digite 0(zero) \n");
                printf("Saiba que a partir de 3 produtos voce recebe um desconto no valor final de sua compra ;)\n");
                printf("\n");
                printf("Insira o codigo do produto:\n ");

                P_produtos = pilha_cria(); //criacao da pilha para guardar os produtos inseridos pelo cliente

                while(scanf("%d", &produto), produto != 0){ //ler os produtos, se for igual a zero, para a leitura

                    for(int i = 0; i < 12; i++){

                        if(codigoProduto[i] == produto){

                            Produto novoProd;

                            switch(produto){
                                case 10 : novoProd = cria_prod("Cachorro quente (Codigo: 10)- R$ 6.00", 6.0); break;
                                case 15 : novoProd = cria_prod("Sanduiche Natural (Codigo: 15) - R$ 9.00",9.0);break;
                                case 20 : novoProd = cria_prod("Pipoca pequena (Codigo: 20)- R$ 6.00",6.0);break;
                                case 25 : novoProd = cria_prod("Pipoca media (Codigo: 25)- R$ 8.00",8.0);break;
                                case 30 : novoProd = cria_prod( "Pipoca grande (Codigo: 30) - R$ 10.00",10.0);break;
                                case 35 : novoProd = cria_prod("Batata Frita (Codigo: 35)- R$ 6.00",6.0);break;
                                case 40 : novoProd = cria_prod("Pastel (Codigo: 40) - R$ 8.00",8.0);break;
                                case 45 : novoProd = cria_prod("Picole (Codigo: 45)- R$ 5.00",5.0);break;
                                case 50 : novoProd = cria_prod( "Agua (Codigo: 50)- R$ 3.00",3.0);break;
                                case 55 : novoProd = cria_prod("Refrigerante (Codigo:55)- R$ 8.00",8.0);break;
                                case 60 : novoProd = cria_prod("Suco (Codigo:60)- R$ 8.50",8.50);break;
                                case 65 : novoProd = cria_prod("Cerveja (Codigo:65)- R$ 10.00",10.0);break;

                        }

                         empilha_produto(P_produtos,novoProd); //empilhando os produtos na pilha
                    }

                }

                    printf("Seu pedido atual eh :\n");
                    imprime_produto(P_produtos); //imprime os produtos atuais na pilha
                    printf("\n");

                    printf("Digite (1) para confirmar o ultimo produto adicionado ou (2) para remover o produto\n");

                    scanf("%d", &confirmaProd);

                    if(confirmaProd == 2){
                        Produto desempilhado;
                        desempilhado = desempilha_produto(P_produtos);// retira o ultimo produto da pilha e coloca em uma variavel produto
                        printf("o item: %s\n", desempilhado.frase);//imprime o produto desempilhado
                        printf("---- PRODUTO REMOVIDO----\n");
                        printf("\n");
                    }

                    if(quant_elementos_pilha(P_produtos) > 2){ //aplica o desconto
                        pilha_pop(descontos);
                    }
                    else{
                        printf("--> Lembre-se que a partir de 3 produtos vc recebera desconto!!\n");
                        printf("\n");
                    }

                    printf("Insira a codigo do proximo produto: ");

                }// final do while dos codigos


                Pedido novoPedido; // pedidos para fila

                switch(setor){
                    case 1 : novoPedido = cria_pedido("Setor Norte" , assentoL, assentoC,P_produtos);break;
                    case 2 : novoPedido = cria_pedido("Setor Sul", assentoL, assentoC,P_produtos);break;
                    case 3 : novoPedido = cria_pedido("Setor Leste" , assentoL, assentoC,P_produtos);break;
                    case 4 : novoPedido = cria_pedido("Setor Oeste" , assentoL, assentoC,P_produtos);break;
                }

                fila_insere(F_pedidos, novoPedido);// coloca na fila o novo pedido


                soma = soma_produtos(P_produtos); // soma do preco da pilha de produtos

                if(quant_elementos_pilha(P_produtos) > 2){ // verifica o desconto disponivel

                    valor_final = calculaDesconto(soma, retorna_topo(descontos));//preco final com desconto aplicado
                    printf("\nDe acordo com sua quantidade de produtos voce possui '%.2f %c' de desconto em sua compra\n", retorna_topo(descontos),porcento);
                }
                else{
                    valor_final = soma;// preco final sem desconto
                    printf("\nDe acordo com sua quantidade de pedidos: %d, voce nao possui desconto em sua compra", quant_elementos_pilha(P_produtos));
                }

                printf("\nO seu pedido final eh:\n");
                printf("\n");

                imprime_produto(P_produtos);

                if(valor_final != soma){
                    printf("+ %.2f %c de desconto ao final\n", retorna_topo(descontos), porcento);
                    printf("\n");
                }

                printf("Para confirmar o pedido digite 1: ");
                scanf("%d", &confirmador);

            }while(confirmador != 1);

            printf("\nO valor total da sua compra eh: R$ %.2f\n",valor_final);
            printf("\nAgora selecione a sua forma de pagamento: \n");
            printf("Para pagamento via pix, digite 1\nPara cartao de credito, digite 2\nPara cartao de debito, digite 3\n");

            formaDePagar();

            printf("\n");
            printf("Agradecemos a preferencia! O seu pedido logo chegara ate voce.\n");

            pilha_libera(descontos); //libera a memoria alocada da pilha de descontos


        }//final do if do perfil
        else if(perfil == 1){
            printf("Ola entregador!\n");
            printf("\nOs pedidos a serem entregue sao: \n");
            imprime_fila(F_pedidos);
        }

    }//final do whiler das entregas

    printf("\nAgora estao liberadas as entregas dos pedidos\n");
    printf("\n");
    printf("Os pedidos a serem entregue sao: \n");
    imprime_fila(F_pedidos);
    printf("Tenha um bom trabalho!");

    for (FilaNo* q = F_pedidos->ini; q != NULL; q = q->prox){

        pilha_libera(q->pedido.produtos);

    }

    fila_libera(F_pedidos);


    return 0;
}
