opcoes* Opcoes(opcoes *op2){
    int resp2;
    do{
    system("CLS");
    printf("----------------------Opcoes----------------------\n");
    printf("1- Alterar Modo de Jogo          Atual:");
    if(op2->modo==1)printf(" Aleatorio\n");
    else printf(" Controlado\n");
    printf("2- Alterar numero de jogadores   Atual: %d\n",op2->num_jog);
    printf("3- Voltar\n--------------------------------------------------\n");
    printf("Opcao desejada: "), scanf("%d",&resp2);
    if(resp2==1){
        if(op2->modo==1)op2->modo++;
        else op2->modo--;
                }
    if(resp2==2){
        do{
        printf("\nNumero de jogadores desejado(2-5): "),setbuf(stdin,NULL),scanf("%d",&op2->num_jog);
        if(op2->num_jog>5 || op2->num_jog<2){printf("\nNumero invalido, tente novamente!"),Sleep(2000);}
        }while(op2->num_jog>5 || op2->num_jog<2);
                }
    if (resp2>3 || resp2<1){printf("\nOpcao invalida, tente novamente."), Sleep(2000);}
    }while(resp2!=3);
    return op2;
}

void Mesa_menu(carta *mesa, carta *deck){
    printf("------------------------MESA------------------------\n");
    if(mesa==NULL){
        printf("\n\n----------------------------------------------------\n");
    }
    else {
        busca_printa_mesa(mesa);
        printf("\n\n----------------------------------------------------\n");
    }
    printa_baralho(deck);
}


carta* Acoes_menu(int posi_jog, jogador *jog, carta *mesa, carta *deck){
    int resp=0;
    int flag=0, flag2=0,flagvez=0,flagmesa;
    carta *mesa_aux=mesa;
    carta *mao_aux=jog[posi_jog-1].mao;
//    jogo *jogocopia;
//    jogocopia->deck=NULL;
//    jogocopia->jogadores=NULL;
//    jogocopia->mesa=NULL;
        do{
            system("CLS");
            Mesa_menu(mesa_aux, deck);
            printf("\n***Jogador %d***\n",posi_jog);//Numero do jogador baseado nos turnos do jogo.
            printf("\nCartas na mao:\n");
            busca_printa(mao_aux);
            printf("\n\n1- Posicionar uma carta na mesa\n");
            printf("2- Reposicionar uma carta da mesa\n");
            printf("3- Comprar uma carta\n");
            //printf("4- Desfazer jogadas\n");
            printf("4- Finalizar jogada\n");
//            printf("5- Sair\n");
            printf("\nOpcao desejada: "),setbuf(stdin,NULL),scanf("%d",&resp);
            if(resp==1){
                if(flag==0){
                    mesa_aux = busca_mao(&mao_aux, &mesa_aux,&flag2);
                    flag2++;
                }
                else{
                    printf("Uma carta foi comprada. Passe a vez."),Sleep(2500);
                }
            }
            if(resp==2){
                if(flag2>=1){
                    if(mesa_aux->prox==NULL && flag2==1){
                    printf("Ha apenas uma carta na mesa."),Sleep(2500);
                    }
                    else{
                        mesa_aux = busca_carta_mesa(&mesa_aux);
                    }
                }
                else{
                    printf("Jogue uma carta antes de reposicionar alguma carta"),Sleep(2000);
                }
            }
            if(resp==3){
                if(flag!=0){
                    printf("A compra ja foi realizada, finalize sua jogada."),Sleep(2500);
                }
                if(flag==0 &&  flag2==0){
                    mesa_aux = compra_funcao(&mesa_aux,&mao_aux,&deck);
                    flag++;
                }
                if(flag2!=0){
                    printf("Uma carta ja foi posicionada, a compra nao esta disponivel."),Sleep(2500);
                }
            }
//            if(resp==4){
//                    if(flag==1){
//                        printf("Voce comprou uma carta, nao ha o que desfazer."),Sleep(2000);
//                    }
//                    if(flag2==0){
//                        printf("Nenhum jogada foi feita."),Sleep(2500);
//                    }
//                    if(flag==0 && flag2!=0){
//                        mesa_aux=mesa;
//                        mao_aux=jog[posi_jog-1].mao;
//                        flag2=0;
//                    }
//                }
            if(resp==4){
                if(flag==0 && flag2==0){
                    printf("Nao houve uma jogada. Compre uma carta antes de passar a vez."),Sleep(2500);
                }
                else{
                    flagmesa = checa_mesa(flagmesa,mesa_aux);
                    if(flagmesa==0){
                        flagvez=1;
                    }

                    else{
                        printf("Alguma jogada foi inválida. Refaca suas jogadas."), Sleep(2000);
                    }
                }
            }
//            if(resp==6){
//                exit(0);
//            }
        }while(flagvez!=1);//Finalizar retorna resp=6 para passar o turno.

        mesa=mesa_aux;
        return mesa;
}



