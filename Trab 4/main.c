#define MAO_INICIO 14
#define CARTA_MAX 105
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "Funções.h"
#include "Menus.h"


int main(){
int resp;
opcoes op;
opcoes *op2;
op.modo=1;
op.num_jog=2;
op2=&op;
jogador *jog=NULL;
carta *deck= NULL;
carta *mesa=NULL;
carta *mesa_aux=NULL;

    printf("\n\n");
    printf("        ///////   //      //  ////     ////  ////     ////  //////////  //     //  //      //  ///////     \n");
    printf("        //    //  //      //  // //   // //  // //   // //      //      //    //   //      //  //    //       \n");
    printf("        //    //  //      //  //  // //  //  //  // //  //      //      //   //    //      //  //    //        \n");
    printf("        //    //  //      //  //   //    //  //   //    //      //      //  //     //      //  //    //    \n");
    printf("        ///////   //      //  //         //  //         //      //      //////     //      //  ////////   \n");
    printf("        //  //    //      //  //         //  //         //      //      //  //     //      //  //     //   \n");
    printf("        //   //   //      //  //         //  //         //      //      //   //    //      //  //     //    \n");
    printf("        //    //  //      //  //         //  //         //      //      //    //   //      //  //     //             \n");
    printf("        //     // //////////  //         //  //         //  //////////  //     //  //////////  ////////    \n");
    Sleep(3000);

    do{
    system("CLS");
    printf("\tBem vindo ao Rummikub!\n");
    printf("1- Comecar um novo jogo\n");
  //  printf("- Continuar ultimo jogo\n");
    printf("2- Opcoes\n");
    printf("3- Sair\n----------------------------------\n");
    printf("Opcao desejada: "), scanf("%d",&resp);
        if(resp==1){
            if(op2->modo==1){
                baralho(&deck);
                jog=entrega_aleatoria(&deck, op2->num_jog, jog);
            }
            if(op2->modo==2){
                deck=le_arquivo();
                jog=entrega_controlada(&deck, op2->num_jog, jog);
            }
            int turno=0;
            do{
                mesa_aux=mesa;//Cria uma copia da mesa
                mesa=Acoes_menu(jog[turno%op2->num_jog].pos, jog, mesa_aux, deck);//Usa a copia da mesa para fazer as jogadas, se tudo der certo, a copia é salva.
                turno++;
                if (deck==NULL ||jog[turno%op2->num_jog].mao==NULL)vitoria_pts(jog,turno,op2->num_jog);
            }while(deck!=NULL);//Condição de vitoria, caso o baralho acabe.
            if(deck!=NULL){
            }
        }
    if(resp==2){op2=Opcoes(op2);}
    if (resp>3 || resp<1){printf("\nOpcao invalida, tente novamente."), Sleep(2000);}
    }while(resp!=3);
}

