struct carta{
    char valor[2];
    int pts;
    struct carta *prox;
    struct carta *ant;
    struct carta *abaixo;
};
typedef struct carta carta;

struct Jogador{
    int pos;
    int pts;
    carta *mao;
};
typedef struct Jogador jogador;

struct Opcoes{
    int num_jog;
    int modo;
};
typedef struct Opcoes opcoes;

struct Jogo{
    carta* mesa;
    carta* deck;
    jogador* jogadores;
};
typedef struct Jogo jogo;
//----------------------------------------------------------------------------------------------------------

void Cria_lista_encadeada(carta **lista,carta *novo, carta **aux){
    if(*lista==NULL){
        *lista=novo;
    }
    else{
        (*aux) = (*lista);
        while((*aux)->prox){
            (*aux)=(*aux)->prox;
        }
        (*aux)->prox = novo;
        novo->ant = (*aux);
    }
}
//----------------------------------------------------------------------------------------------------------
carta* Cria_lista_encadeada_mesa(carta **lista, carta *novo){
    int i=0;
    carta *auxA, *auxB;
    if(*lista==NULL){
        *lista=novo;
    }
    else{
        auxA = *lista;
            do{
                while(auxA->prox!=NULL){
                    auxB=auxA;
                    auxA=auxA->prox;
                    auxA->ant=auxB;
                }
                if(auxA->abaixo==NULL){//cria o segundo
                    auxA->abaixo = novo;
                }
                else{
                    auxA=auxA->abaixo;
                    while(auxA->abaixo!=NULL)auxA=auxA->abaixo;
                }
                i++;
            }while(auxA->prox!=NULL || auxA->abaixo!=NULL);
            if(i==1)auxA->abaixo=novo;
    }
    return (*lista);
}
//----------------------------------------------------------------------------------------------------------
carta* Carta_para_mesa_grupo(carta **mesa, carta *nova, int grupo){
    carta *aux;
    int i=1;
    aux = *mesa;
    while(i!=grupo){
        while(aux->prox!=NULL){
            aux=aux->prox;
        }
        if(aux->abaixo!=NULL){
            aux=aux->abaixo;
        i++;}
        if(aux->abaixo==NULL && aux->prox==NULL){
            i++;
        }
    }
    if(i==grupo){
        while(aux->prox!=NULL){
            aux=aux->prox;
        }
        aux->prox=nova;
        nova->abaixo=aux->abaixo;
        nova->ant=aux;
        aux->abaixo=NULL;
    }
    return(*mesa);
}

//----------------------------------------------------------------------------------------------------------
void busca_printa(carta *lista){
    int i=0;
    carta *b;
    b=lista;
    while(b!=NULL){
        i++;
        if(i%15==0)printf("\n");
        printf("%s ",b->valor);
        b=b->prox;
    }
}

void busca_printa_mesa(carta *lista){
    carta *auxA;
    auxA= lista;
    int i=1,j=0;

    do{
        if(auxA->ant==NULL && j==0){
            printf("  %d- |%s",i,auxA->valor);
            j++;
        }
        while(auxA->prox!=NULL){
            printf("|%s",auxA->prox->valor);
            auxA=auxA->prox;
        }
        if(auxA->abaixo!=NULL){
            i++;
            printf("  %d- |%s",i,auxA->abaixo->valor);
            auxA=auxA->abaixo;
        }
        if(i%4==0){
            printf("\n");
        }
    }while(auxA->prox!=NULL || auxA->abaixo!=NULL);
}
//----------------------------------------------------------------------------------------------------------
//void busca_printa_mesa(carta *mesa){
//    carta *b, *b_aux;
//    b=mesa;
//    b_aux=b->prox;
//    int i=1;
//    do{
//        if(b->ant==NULL){
//            printf("  %d- ",i);
//        }
//        if(b_aux==NULL)printf("%s",b->valor);
//        while(b_aux!=NULL){
//            printf("%s",b->valor);
//            b_aux=b_aux->prox;
//            b=b->prox;
//        }
//        if(b->abaixo!=NULL){
//            b=b->abaixo;
//            b_aux=b->prox;
//            i++;
//            if(i%6==0)printf("\n\n");
//        }
//    }while(b_aux!=NULL);
//}
//----------------------------------------------------------------------------------------------------------
void printa_baralho(carta *deck){
    carta *b;
    b=deck;
    int i=0;
    if(b==NULL){i=0;}
    while(b!=NULL){
        b=b->prox;
        i++;
    }
    printf("--------------------------\n");
    printf("|Cartas no baralho: %d   |",i);
    printf("\n--------------------------\n");
}
//----------------------------------------------------------------------------------------------------------
void criar_carta(int i, int j, char* valor, int pts){
    char numero= '0';
    char letra= '7';
        if(i<10){
            if(j==1){
                valor[0]= numero+i;
                valor[1]= '!';
                valor[2]='\0';
                pts=i;
            }
            if(j==2){
                valor[0]= numero+i;
                valor[1]= '@';
                valor[2]='\0';
                pts=i;
            }
            if(j==3){
                valor[0]= numero+i;
                valor[1]= '#';
                valor[2]='\0';
                pts=i;
            }
            if(j==4){
                valor[0]= numero+i;
                valor[1]= '$';
                valor[2]='\0';
                pts=i;
            }
        }
        else{
            if(j==1){
                valor[0]=letra+i;
                valor[1]='!';
                valor[2]='\0';
                pts=i;
            }
            if(j==2){
                valor[0]=letra+i;
                valor[1]='@';
                valor[2]='\0';
                pts=i;
            }
            if(j==3){
                valor[0]=letra+i;
                valor[1]='#';
                valor[2]='\0';
                pts=i;
            }
            if(j==4){
                valor[0]=letra+i;
                valor[1]='$';
                valor[2]='\0';
                pts=i;
            }
        }
}
//----------------------------------------------------------------------------------------------------------
void carta_para_baralho(carta **deck, char* valor, int pts){
    carta *p, *q;
    p= (carta*)malloc(sizeof(carta));
    p->ant=NULL;
    p->abaixo=NULL;
    p->prox=NULL;
    p->pts=pts;
    strcpy(p->valor,valor);
    Cria_lista_encadeada(deck,p,&q);
}

void baralho(carta **deck){
    int i,j,k;
    char valor[3];
    int pts=0;
        for(i=1;i<14;i++){
            for(j=1;j<=4;j++){
                for(k=0;k<2;k++){
                    criar_carta(i,j,valor,pts);
                    carta_para_baralho(deck,valor,pts);
                }
            }
        }
    //strcpy(valor,"**");
    //pts=20;
    strcpy(valor,"1!");//Nao consegui implementar o coringa na validaçao de jogadas.
    pts=1;
    carta_para_baralho(deck,valor,pts);
    carta_para_baralho(deck,valor,pts);
}
//----------------------------------------------------------------------------------------------------------
carta* le_arquivo(){
    carta *deck=NULL;
    char numero='0', letra='7';
    FILE *arquivo;
    arquivo = fopen("baralho.txt","r");
    if(arquivo!=NULL){
        int ponto,i;
        char info[4];
        while (fgets(info, sizeof(info),arquivo)!=NULL){
            //  printf("%c",info[0]);
            for(i=1; i<=14; i++){
                if(i<10){
                    if(info[0]==(numero+i)){
                        ponto=i;
                        info[2]='\0';
                    }
                }
                if(i>=10 && i<14){
                    if (info[0]==(letra+i)){
                        ponto=i;
                        info[2]='\0';
                    }
                }
                if(i==14){
                    if(info[0]=='*'){
                        ponto=20;
                        info[2]='\0';
                    }
                }
            }
//            info[2]='\0';
            carta_para_baralho(&deck,info,ponto);
        }
    }
    else{
        printf("Nao foi possivel abrir o arquivo");
    }
    return deck;
}
//----------------------------------------------------------------------------------------------------------
jogador* entrega_aleatoria(carta **deck, int num_jog, jogador *jog){
    int n,x,i,j;
    carta *p, *q, *r;
    srand(time(NULL));
    jog=(jogador*)malloc(num_jog*sizeof(jogador));
        for(j=0;j<num_jog;j++){
            jog[j].mao=NULL;
        }
        for(n=0;n<MAO_INICIO*num_jog;n++){
            x= rand()%CARTA_MAX-n;
            q=(*deck);
            p=q->prox;
            for(i=0;i<x;i++){
                p = p->prox;
                q = q->prox;
            }
            if(p!=NULL){
                q->prox=p->prox;
                p->prox=NULL;
                p->ant=NULL;
                Cria_lista_encadeada(&jog[n%num_jog].mao,p,&r);
            }
            else{
                Cria_lista_encadeada(&jog[n%num_jog].mao,q,&r);
            }
            if(n<num_jog){
                    jog[n%num_jog].pos=(n+1);
                }
        }
        return jog;
}

jogador* entrega_controlada(carta **deck, int num_jog, jogador *jog){
    int n,j;
    carta *p, *q, *r;
    jog=(jogador*)malloc(num_jog*sizeof(jogador));
        for(j=0;j<num_jog;j++){
            jog[j].mao=NULL;
        }
        for(n=0;n<MAO_INICIO*num_jog;n++){
            q=(*deck);
            p=q->prox;
            *deck = p;
            q->prox = NULL;
            (*deck)->ant = NULL;
                if(n<num_jog){
                    jog[n%num_jog].pos=(n+1);
                }
        Cria_lista_encadeada(&jog[n%num_jog].mao,q,&r);
        }
        return jog;
}

//----------------------------------------------------------------------------------------------------------
carta* Posicionar(carta *carta1, carta **mesa){//poe carta na mesa
    int resp, grupo;
    carta* mesa_aux;
    if((*mesa)!=NULL){
        printf("1- Sozinha\n");
        printf("2- Em um grupo\n");
        printf("\nOpcao desejada: "),setbuf(stdin,NULL),scanf("%d",&resp);
        if(resp==1){
            mesa_aux=Cria_lista_encadeada_mesa(mesa, carta1);
        }
        if(resp==2){
            printf("Numero do grupo: "),fflush(stdin),scanf("%d",&grupo);
            mesa_aux=Carta_para_mesa_grupo(mesa, carta1, grupo);
        }
    }
    else{
        mesa_aux=Cria_lista_encadeada_mesa(mesa, carta1);
    }
    return mesa_aux;
}
//----------------------------------------------------------------------------------------------------------
carta* busca_mao(carta** mao, carta **mesa, int *flag2){
    int x,y;
    carta *carta_aux, *aux, *rtrn;
    aux=*mao;
    carta_aux=aux->prox;
    char valor[2];
    printf("Digite a carta que deseja posicionar: "),fflush(stdin),fgets(valor,4,stdin);
    valor[2]='\0';

    if(carta_aux!=NULL){
        x=strcmp(carta_aux->valor,valor);
        y=strcmp(aux->valor,valor);
    }

    while(carta_aux!=NULL && x!=0 && y!=0){
        carta_aux=carta_aux->prox;
        aux=aux->prox;
        if(carta_aux!=NULL){
            x=strcmp(carta_aux->valor,valor);
        }
    }
    y=strcmp(aux->valor,valor);
//    if(carta_aux==NULL && aux!=NULL && x!=0){
//        y=strcmp(aux->valor,valor);
//    }
    if(x==0){
        aux->prox=carta_aux->prox;
        carta_aux->prox=NULL;
        carta_aux->ant=NULL;
        carta_aux->abaixo=NULL;
        rtrn=Posicionar(carta_aux, mesa);//poe carta na mesa
    }
    else if(y==0){
        *mao=(*mao)->prox;
        aux->prox=NULL;
        aux->ant=NULL;
        aux->abaixo=NULL;
        rtrn=Posicionar(aux,mesa);
    }
    else{
        printf("Carta nao encontrada.");
        Sleep(2500);
        rtrn=*mesa;
        *flag2=*flag2 - 1;
    }
    return rtrn;
}

carta* Reposicao2(carta *repos, carta **mesa){
    int grupo;
    printf("Digite o grupo que a carta sera reposicionada:"),fflush(stdin),scanf("%d",&grupo);
    return Carta_para_mesa_grupo(mesa,repos,grupo);
}

carta* Reposicao(carta *aux, carta *aux2, carta **mesa, char *valor){
    carta *rtrn;
    int flag;
    if(aux->abaixo==aux2 && aux2!=NULL){
        flag=strcmp(valor,aux2->valor);
        if(flag==0){
            aux->abaixo=aux2->prox;
            aux2->prox=NULL;
            rtrn=Reposicao2(aux2,mesa);
        }
        else{
            *mesa=(*mesa)->abaixo;
            aux->abaixo=NULL;
            rtrn=Reposicao2(aux,mesa);
        }
    }
    if(aux->prox==aux2 && aux2!=NULL && aux2->prox!=NULL && aux2->abaixo==NULL){//esse
        flag=strcmp(aux->valor,valor);
        if(flag!=0){
            aux->prox=aux2->prox;
            aux2->prox=NULL;
            aux2->ant=NULL;
            rtrn=Reposicao2(aux2,mesa);
        }
        else{
            aux->prox=NULL;
            aux2->ant=NULL;
            rtrn=Reposicao2(aux,mesa);
        }
    }
    if(flag!=0){
        if(aux->prox==aux2 && aux2!=NULL && aux2->abaixo!=NULL){//esse
            flag=strcmp(aux->valor,valor);
            if(flag!=0){
                aux->abaixo=aux2->abaixo;
                aux->prox=NULL;
                aux2->abaixo=NULL;
                aux2->ant=NULL;
                rtrn=Reposicao2(aux2,mesa);
            }
            else{
                aux->prox=NULL;
                aux2->ant=NULL;
                rtrn=Reposicao2(aux,mesa);
            }
        }
    }
    if(flag!=0){
        if(aux->prox==aux2 && aux2!=NULL && aux2->prox==NULL && aux2->abaixo==NULL){
            aux->prox=NULL;
            aux2->ant=NULL;
            rtrn=Reposicao2(aux2,mesa);
        }
    }
    if(aux->ant==NULL && aux2==NULL){
        rtrn=Reposicao2(aux,mesa);
    }
    return rtrn;
}
//----------------------------------------------------------------------------------------------------------
carta* busca_reposicao(carta *aux, carta **mesa, int grupo, int x, char *valor){
    carta *aux2, *rtrn;//aux apontado pra lista
    int y,i=1;
    aux2=aux->prox;
    if(aux2==NULL && aux->abaixo!=NULL){
        aux2=aux->abaixo;
    }
    while(i!=grupo){
        while(aux->prox!=NULL && aux2!=NULL && aux2->prox!=NULL){
            aux2=aux2->prox;
            aux=aux->prox;
        }
        if(aux2 && aux2->abaixo!=NULL && aux->prox!=NULL){
            aux2=aux2->abaixo;
            aux=aux->prox;
            aux->abaixo=aux2;
        i++;}
        if(aux2!=NULL && aux2->abaixo!=NULL && aux->prox==NULL){
            aux2=aux2->abaixo;
            aux=aux->abaixo;
            i++;
        }
        if(aux2!=NULL && aux2->prox!=NULL && aux->abaixo==aux2){
            aux2=aux2->prox;
            aux=aux->abaixo;
        }
        if(aux->ant==NULL && aux->abaixo!=NULL){
            aux=aux->abaixo;
            if(aux2->prox!=NULL){
                aux2=aux2->prox;
                aux->prox=aux2;
                i++;
            }
            else if(aux2->abaixo!=NULL){
                aux2=aux2->abaixo;
                aux->abaixo=aux2;
            }
        }
    }
    x=strcmp(valor,aux->valor);

    if(x!=0){
        do{
            x=strcmp(valor,aux2->valor);
            if(x!=0){
                aux=aux2;
                aux2=aux2->prox;
                if(aux2!=NULL)
                    x=strcmp(valor,aux2->valor);
            }
            if(aux2==NULL)y=0;
        }while(y!=0 && x!=0);
    }
    if(x==0){
        rtrn=Reposicao(aux,aux2,mesa,valor);
    }
    else{
        printf("\nCarta nao encontrada."),Sleep(2500);
        rtrn=*mesa;
    }
    return rtrn;
}
//----------------------------------------------------------------------------------------------------------
carta* busca_carta_mesa(carta **mesa){
    carta *aux;
    aux= *mesa;
    int x,grupo;
    char valor[3];
    printf("Digite o grupo da carta: "),fflush(stdin),scanf("%d",&grupo);
    printf("Digite a carta que deseja reposicionar: "),fflush(stdin),fgets(valor,3,stdin);
    valor[2]='\0';
    x=strcmp(valor,aux->valor);
    return busca_reposicao(aux,mesa,grupo,x,valor);
}
//----------------------------------------------------------------------------------------------------------
carta* compra_funcao(carta **mesa, carta **mao, carta **deck){
    carta *p,*q,*r,*aux;
    int x, n, i;
    srand(time(NULL));
    aux=*deck;
    for(n=1;(aux!=NULL && aux->prox!=NULL);n++){
        aux=aux->prox;
    }
    x= rand()%n;
    q=(*deck);
    p=q->prox;
        for(i=0;i<x;i++){
            p = p->prox;
            q = q->prox;
        }
        if(p!=NULL){
            q->prox=p->prox;
            p->prox=NULL;
            p->ant=NULL;
            Cria_lista_encadeada(mao,p,&r);
        }
        else{
        Cria_lista_encadeada(mao,q,&r);
        }
    return *mesa;
}

int conta_grupo(carta *mesa){
    carta *aux=mesa;
    int i=1;
    while(aux!=NULL){
        if(aux->prox!=NULL){
            aux=aux->prox;
        }
        else if(aux->abaixo!=NULL){
            aux=aux->abaixo;
            i++;
        }
        if(aux->prox==NULL && aux->abaixo==NULL){
            aux=NULL;
        }
    }
    return i;
}

int checa_mesa(int flag, carta *mesa){
    int num_grupos=conta_grupo(mesa);
    int i=1,j=1,k=0,l,l2,m,n;
    char v1,v2,vaux[4];
    carta *auxj, *aux1, *aux2, *auxA, *auxB1, *auxB2;
    auxA=mesa;
    if(mesa!=NULL){
    while(i<=num_grupos){
        m=0,n=0,j=1;
        auxj=auxA;
        while(auxj!=NULL){
            auxj=auxj->prox;
            if(auxj!=NULL){
                j++; //Numero de cartas em uma linha.
            }
        }//-----------------------------------------------------
        if(j<3){return k=1;}
        aux1=auxA;
        for(l=1;l<=j;l++){//verifica se tem cartas iguais
            aux2=aux1;
            while(aux2!=NULL){
                aux2=aux2->prox;
                if(aux2!=NULL){
                    flag=strcmp(aux1->valor,aux2->valor);
                }
                if(flag==0){return k=1;
                }
            }
            if(l<j){aux1=aux1->prox;}
        }
        for(l=0;l<j;l++){//Ordena por Numero
            aux1=auxA;
            aux2=auxA->prox;
            for(m=0;m<j-1;m++){
                v1=aux1->valor[0];
                v2=aux2->valor[0];
                if(v1>v2){
                    strcpy(vaux,aux1->valor);
                    strcpy(aux1->valor,aux2->valor);
                    strcpy(aux2->valor,vaux);
                }
                aux1=aux1->prox;
                aux2=aux2->prox;
            }
        }
        aux1=auxA;
        aux2=auxA->prox;
        for(l=0;l<j;l++){//Ordena por naipe
            aux1=auxA;
            aux2=auxA->prox;
            for(m=0;m<j-1;m++){
                v1=aux1->valor[1];
                v2=aux2->valor[1];
                if(v1>v2){
                    strcpy(vaux,aux1->valor);
                    strcpy(aux1->valor,aux2->valor);
                    strcpy(aux2->valor,vaux);
                }
                aux1=aux1->prox;
                aux2=aux2->prox;
            }
        }
        m=0,n=0;
        aux1=auxA;
        aux2=auxA->prox;
        auxB1=auxA;
        for(l=0;l<=j-1;l++){//Checa se a jogada é valida por ordenaçao de numeros
            if(aux2!=NULL){
                if(aux2->valor[0] == aux1->valor[0]){m++;}
                }
            if(m>=2){return k=0;}
            if(n>=2){
                aux1=auxB1;
                aux2=auxB1->prox;
                    for(l2=0;l2<=1;l2++){
                        if(aux2!=NULL){
                            if(aux2->valor[1]!=aux1->valor[1]){return k=1;}
                        }
                        if(l2==1){
                            n=0;
                            auxB1=auxB2;
                            if(aux2->prox!=NULL){
                            aux1=aux1->prox;
                            aux2=aux2->prox;
                            }
                        }
                        aux1=aux1->prox;
                        aux2=aux2->prox;
                    }
            }
            if(aux2!=NULL){
            if(aux2->valor[0] != aux1->valor[0]+1 && m<1){return k=1;}
            else{n++;}
            }
            auxB2=aux2;
            if(aux2!=NULL){
            aux1=aux1->prox;
            aux2=aux2->prox;
            }
        }
        //-----------------------------------------------------
        if(aux1->abaixo!=NULL){//Troca de grupo
            aux1=aux1->abaixo;
            auxA=aux1;
            i++;
        }
        else{break;}
    }
    }
    return k;
}

int soma_pts(carta *mao){
    carta *p;
    p=mao;
    int i,sum=0;
    for(i=1;p!=NULL;i++){
        sum= sum + p->pts;
        p=p->prox;
    }
    return sum;
}

void vitoria_pts(jogador *jog, int turno, int num_jog){
    int n,menorpts=100,pos;
    if(jog[turno%num_jog].mao==NULL){
        printf("O Jogador %d venceu!!!\n\n",jog[turno%num_jog].pos),system("PAUSE");
        exit(0);
    }
    for(n=0;n<num_jog;n++){
        jog[n%num_jog].pts=soma_pts(jog[n%num_jog].mao);
    }
    for(n=0;n<num_jog;n++){
        if(menorpts>jog[n%num_jog].pts){
            menorpts=jog[n%num_jog].pts;
        }
        else{
            pos=jog[n%num_jog].pos;
        }
    }
    printf("O jogador %d venceu por ter menos pontos acumulados!!!\n\n",pos),system("PAUSE");
    exit(0);
}
//--------------------------------------------------------------------------------------------------------------
//Funçao desfazer nao foi completa por incopetencia do programador.
//void copia_deck(carta **deck_copia, carta* deck){
//    carta *p;
//    p=deck;
//    if(p==NULL){
//        deck_copia=NULL;
//    }
//    while(p!=NULL){
//    carta_para_baralho(deck_copia,p->valor,p->pts);
//    p=p->prox;
//    }
//}
//
//void copia_jogadores(jogador **jogcopia, jogador *jog, int num_jog){
//    int i,j;
//    carta **aux, *p, *q;
//    jogcopia=(jogador*)malloc(num_jog*sizeof(jogador));
//    for(j=0;j<num_jog;j++){
//        jogcopia[j]->mao=NULL;
//    }
//    for(i=0;i<num_jog;i++){
//        p=jog[i%num_jog].mao;
//        while(p!=NULL){
//            carta_para_baralho(jogcopia[i%num_jog]->mao,p->valor,p->pts);
//            p=p->prox;
//        }
//    }
//}
//
//void copia_mesa(carta **mesa_copia, carta *mesa){
//    carta *p, *q;
//    p=mesa;
//    while(p!=NULL){
//        if(p->ant==NULL || p->abaixo==NULL){
//            Cria_lista_encadeada_mesa(mesa_copia,p);
//        }
//        if(p->abaixo!=NULL){
//            p=p->abaixo;
//            Carta_para_mesa_grupo()
//        }
//    }
//    Carta_para_mesa_grupo()
//}
//
//void copia_jogo(jogo* jogo, int num_jog){
//    jogo *jogoaux;
//    copiadeck(&jogoaux->deck,jogo->deck);
//    copiamaos(&jogoaux->jogadores,jogo->jogadores,num_jog);
//    copiamesa(&jogoaux->mesa,jogo->mesa);
//}
