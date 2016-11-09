// UNIVERSIDADE FEDERAL DO TOCANTINS
//DISCENTES: ADRIANNE ALVES E OSMIR MARIANO
//DISCIPLINA : ALGORITMOS E ESTRUTURA DE DADOS I

#include<stdio.h>
#include<stdlib.h>

#define MAXC 10 // Maximo de conteiners
#define MAXE 4// Maximo de embarcações em espera

//---------------------------------------------ESTRUTURAS ------------------------------------------------------------------

// INFORMAÇÃO DO CONTEINER
typedef struct conteiner{
    int identificacao;
    int destino;
    char origem[20]; // String de até 20 caracteres
}conteiner;

//LISTA DE CONTEINERS DAS EMBARCACOES
typedef struct embarcaconteiner{ // Controle de cada lista de conteiners
    conteiner ConteinerEmbarca[MAXC];
    int fim;
}embarcaconteiner;

typedef struct ListaConteiner{ // Lista geral composta de três listas
    embarcaconteiner Destino1;
    embarcaconteiner Destino2;
    embarcaconteiner Destino3;
    int Total;
}ListaConteiner;

//INFORMAÇÃO SOBRE EMBARCAÇÃO
typedef struct embarcacao{
    char nome[10];// Linha1, Linha 2,Linha 3, Linha 4
    int destinos[3]; // cada embarcacao tem 3 destinos
    ListaConteiner Conteiners; // Criando listas de conteiners para embarcação
    int Status; // 1- Aportou 2-Navegando 3- Em espera
}embarcacao;

//LISTA DE EMBARCAÇÃO EM ESPERA - COM COMPORTAMENTO DE FILA -
typedef struct ListaEspera{
    embarcacao Espera[MAXE]; // So pode haver quatro embarcações (lista estática de embarcações)
    int fim;
}ListaEspera;

// FILA DE CONTEINERS NO PORTO ( FILA DINÂMICA)
typedef struct NoConteiner{ //Nós
    conteiner Conteiner;
    struct NoConteiner *prox;
}NoConteiner;

typedef struct FilaConteiner{//Fila
    NoConteiner *Inicio;
    NoConteiner *Fim;
}FilaConteiner;

//-------------------------------------------FUNÇÕES -------------------------------------------------------------------------

//CHEGADA DE CONTEINER
conteiner chegaconteiner(FilaConteiner *f,conteiner C){ //ENFILEIRA CONTEINER NO PORTO
    NoConteiner *Novo;
    conteiner e;
    Novo=(NoConteiner*)malloc(sizeof(NoConteiner));
    if(Novo!=NULL){ // Checa se há memória
        Novo->Conteiner=C; // Inicializa os valores do conteiner para o nó
        Novo->prox=NULL; // Inicializa o próximo de novo, já que ele ainda não está ligado à fila
        if(f->Inicio==NULL)
            f->Inicio=Novo;  // Se vazia o ponteiro inicio aponta para o novo elemento
        else
            f->Fim->prox=Novo; // Proximo do fim aponta para novo
        f->Fim=Novo; // Fim aponta para novo
    }
    else{
        f->Fim->Conteiner.destino=0;// Se não tiver memoria modifica valor de destino para funcionar como codigo de erro
    }
    e=f->Fim->Conteiner; // Retorna o elemento inserido
    return e;
}
int ChecaCompatibilidade(int c,int *Destinos){//CHECA COMPATIBILIDADE DO CONTEINER COM DESTINOS DO PORTO
    int a;
    for(a=0;a<=5;a++){
        if(c==Destinos[a]){
            return 1;
        }
    }
    return 0;
}

// INICIA ESTRUTURAS
void iniciafilaC(FilaConteiner *f){ // Fila de conteiners do porto
    f->Inicio=NULL;
    f->Fim=NULL;
}
void iniciaListaConteiner(ListaConteiner *embarcacoes){ // Lista de conteiners das embarcações
    embarcacoes->Destino1.fim=0;
    embarcacoes->Destino2.fim=0;
    embarcacoes->Destino3.fim=0;
    embarcacoes->Total=0;
}
void iniciaListaEspera(ListaEspera *L){ // Lista de espera
    L->fim=0;
}

// ATRIBUI DESTINOS ÀS EMBARCAÇÕES (Poderia vir de um banco de dados)
void atribuidestinos(embarcacao *chegou){
    if(strcmp (chegou->nome,"Linha 1" ) == 0){
        chegou->destinos[0]=4;
        chegou->destinos[1]=5;
        chegou->destinos[2]=6;
    }
    else{
        if(strcmp (chegou->nome,"Linha 2") == 0){
        chegou->destinos[0]=2;
        chegou->destinos[1]=3;
        chegou->destinos[2]=5;
        }
        else{
            if(strcmp (chegou->nome,"Linha 3") == 0){
            chegou->destinos[0]=1;
            chegou->destinos[1]=4;
            chegou->destinos[2]=6;
            }
            else{
                if(strcmp (chegou->nome,"Linha 4") == 0){
                chegou->destinos[0]=1;
                chegou->destinos[1]=2;
                chegou->destinos[2]=3;
                }
                else{
                    chegou->destinos[0]=1001;
                }
            }
        }
    }

}

// MOSTRA ESTRUTURAS - QUANTIDADES
void MostraFilaConteinerPorto(FilaConteiner *FPorto){ //CONTEINERS DO PORTO
    NoConteiner *PercorreFila;
    if(FPorto->Inicio!=NULL){
        PercorreFila=FPorto->Inicio;
        do{
           printf("\nConteiner %d - Origem: %s - Destino: %d\n", PercorreFila->Conteiner.identificacao,&PercorreFila->Conteiner.origem,PercorreFila->Conteiner.destino);
           PercorreFila=PercorreFila->prox;
        }while(PercorreFila!=NULL);
    }
}
void MostraConteinerEmbarcacao(embarcacao *chegou){ // CONTEINERS DAS EMBARCAÇÕES
    int x;
    if(chegou->Conteiners.Total!=0){
        if(chegou->Conteiners.Destino1.fim!=0){
            printf("\nDestino 1:\n ");
            for(x=0;x<chegou->Conteiners.Destino1.fim;x++){
                printf(" Conteiner %d - Destino : %d -Origem %s\n",chegou->Conteiners.Destino1.ConteinerEmbarca[x].identificacao,
                       chegou->Conteiners.Destino1.ConteinerEmbarca[x].destino,&chegou->Conteiners.Destino1.ConteinerEmbarca[x].origem);
            }
        }
         if(chegou->Conteiners.Destino2.fim!=0){
            printf("\nDestino 2:\n ");
            for(x=0;x<chegou->Conteiners.Destino2.fim;x++){
                printf(" Conteiner %d - Destino : %d -Origem %s\n",chegou->Conteiners.Destino2.ConteinerEmbarca[x].identificacao,
                       chegou->Conteiners.Destino2.ConteinerEmbarca[x].destino,&chegou->Conteiners.Destino2.ConteinerEmbarca[x].origem);
            }
        }
         if(chegou->Conteiners.Destino3.fim!=0){
            printf("\nDestino 3:\n ");
            for(x=0;x<chegou->Conteiners.Destino3.fim;x++){
                printf(" Conteiner %d - Destino : %d -Origem %s\n",chegou->Conteiners.Destino3.ConteinerEmbarca[x].identificacao,
                       chegou->Conteiners.Destino3.ConteinerEmbarca[x].destino,&chegou->Conteiners.Destino3.ConteinerEmbarca[x].origem);
            }
        }
    }
    else
        printf("\n Nao ha conteiners nessa embarcacao!");
    if(chegou->Conteiners.Total!=0){
        printf("\nLotacao : %d conteiners embarcados",chegou->Conteiners.Total);
    }
}
int QuantidadeFilaPorto(FilaConteiner FPorto){ // QUANTIDADE CONTEINER PORTO
    NoConteiner *aux;
    int q=0;
    aux=FPorto.Inicio;
    while(aux!=NULL){
        q++;
        aux=aux->prox;
    }
    return q;
}

// CHEGADA DE EMBARCAÇÃO
void embarcarconteiner(FilaConteiner *FPorto,embarcacao *chegou){ // PASSA DE FILA DO PORTO PARA EMBARCAÇÃO
    NoConteiner *CorreFilaConteiner,*aux,*ArmazenaAnterior;
    int a,fim,GlobalControle=0;
    printf("\n\n------Embarcacao %s\n\n",chegou->nome);
    if(FPorto->Inicio != NULL  ){// SE HÁ CONTEINER NO PORTO
        if(chegou->Conteiners.Total<MAXC){ //SE HÁ ESPAÇO NA LISTA DE CONTEINER DA EMBARCACAO
            CorreFilaConteiner=FPorto->Inicio; // CORRE A FILA DO INICIO
            ArmazenaAnterior=FPorto->Inicio; // INICIALIZA ANTERIOR COM O ATUAL
           do{
                for(a=0;a<=2;a++){   // TESTAR DESTINO DO CONTEINER COM OS DA EMBARCAÇÃO
                    if(chegou->destinos[a]==CorreFilaConteiner->Conteiner.destino){ // SE COMPATÍVEL COM ALGUM
                        aux=CorreFilaConteiner;// AUXILIAR PARA EXCLUSÃO
                        if(a==0 && chegou->Conteiners.Destino1.fim<MAXC){ // DESTINAR À FILA CORRETA
                            fim = chegou->Conteiners.Destino1.fim; // APENAS PARA PARAR COM BUG
                            chegou->Conteiners.Destino1.ConteinerEmbarca[fim]=aux->Conteiner;
                            chegou->Conteiners.Destino1.fim++;
                            printf("Conteiner de id %d - Origem : %s - Destino : %d Foi embarcado na %s\n",
                                   chegou->Conteiners.Destino1.ConteinerEmbarca[fim].identificacao,
                                   chegou->Conteiners.Destino1.ConteinerEmbarca[fim].origem,
                                   chegou->Conteiners.Destino1.ConteinerEmbarca[fim].destino,
                                   chegou->nome);
                        }
                        else {
                            if(a==1 && chegou->Conteiners.Destino2.fim<MAXC){
                                fim=chegou->Conteiners.Destino2.fim;
                                chegou->Conteiners.Destino2.ConteinerEmbarca[fim]=aux->Conteiner;
                                chegou->Conteiners.Destino2.fim++;
                                printf("Conteiner de id %d - Origem : %s - Destino : %d Foi embarcado na %s\n",
                                       chegou->Conteiners.Destino2.ConteinerEmbarca[fim].identificacao,
                                       chegou->Conteiners.Destino2.ConteinerEmbarca[fim].origem,
                                       chegou->Conteiners.Destino2.ConteinerEmbarca[fim].destino,
                                       chegou->nome);
                            }
                            else{
                                if(a==2 && chegou->Conteiners.Destino3.fim<MAXC){
                                    fim=chegou->Conteiners.Destino3.fim;
                                    chegou->Conteiners.Destino3.ConteinerEmbarca[fim]=aux->Conteiner;
                                    chegou->Conteiners.Destino3.fim++;
                                    printf("Conteiner de id %d - Origem : %s - Destino : %d Foi embarcado na %s\n",
                                       chegou->Conteiners.Destino3.ConteinerEmbarca[fim].identificacao,
                                       chegou->Conteiners.Destino3.ConteinerEmbarca[fim].origem,
                                       chegou->Conteiners.Destino3.ConteinerEmbarca[fim].destino,
                                       chegou->nome);
                                }
                            }
                        }
                        chegou->Conteiners.Total++;
                        // TROCA DE PONTEIROS
                        if(FPorto->Inicio==FPorto->Fim){ // SÓ UM ELEMENTO NA FILA
                            FPorto->Fim=NULL;
                            FPorto->Inicio=NULL;
                        }
                        else{
                            if(CorreFilaConteiner==FPorto->Inicio){ //SE FOR PRIMEIRO ELEMENTO DA FILA
                                FPorto->Inicio=FPorto->Inicio->prox;
                            }
                            else{
                                if(aux->prox!=NULL){//SE FOR ÚLTIMO ELEMENTO DA FILA
                                    FPorto->Fim=ArmazenaAnterior;
                                    FPorto->Fim->prox=NULL;
                                }
                                else{ // MEIO DA FILA
                                    ArmazenaAnterior->prox=CorreFilaConteiner->prox;//PULA ELEMENTO
                               }
                            }
                        }
                        free(aux);
                        a=3; //PARAR DE COMPARAR DESTINOS
                        GlobalControle++; // Para saber se ao menos um conteiner foi embarcado
                    }
                }
                ArmazenaAnterior=CorreFilaConteiner;
                CorreFilaConteiner=CorreFilaConteiner->prox;
            }while(CorreFilaConteiner!=NULL && chegou->Conteiners.Total<MAXC);
            if(GlobalControle==0){
                chegou->Status=3; // ESPERA
            }
            else
                chegou->Status=2; //NAVEGANDO
        }
        else
            chegou->Status=2; // SE NÃO TIVER MAIS ESPAÇO STATUS NAVEGANDO
    }
    else{
     chegou->Status=3;//SE NÃO TIVER CONTEINER EM ESPERA
    }
}

//LISTA DE ESPERA
void PoeEspera(embarcacao *chegou,ListaEspera *Esperando){
    if(Esperando->fim>MAXE){
        printf("\nNao ha espaco para mais uma embarcacao em espera\n");
    }
     else{
         Esperando->Espera[Esperando->fim]=*chegou; //ADICIONA À LISTA DE ESPERA
         printf("\nStatus: Em Espera!\n");
         Esperando->fim++;
    }
}
void RetiraEspera(ListaEspera *Esperando, int aux){
    int x;
    for(x=aux;x<Esperando->fim;x++){
        Esperando->Espera[x]=Esperando->Espera[x+1];
    }
    Esperando->fim--;
}


int Menu(){
    int op;
    printf("\n  ---------------------------------------------------------------------");
    printf("                                    PORTO FELIZ                            \n\n");
    printf("  ---------------------------------------------------------------------");
    printf("\n\n        _________________________MENU__________________________\n");
    printf("\n       | 1- CHEGAR CONTEINER      |   2- CHEGAR EMBARCACAO     |\n");
    printf("\n       | 3- VERIFICAR EMBARCACAO  |   4- MOSTRAR               |\n");
    printf("\n       |     EM ESPERA            |   0- ENCERRAR ATIVIDADE    |\n");
    printf("\n-->  ");
    scanf("%d",&op);
    return op;
}

int main(){
    int destinos[6]={1,2,3,4,5,6},menu,auxiliar,totalEmbarcacoes=0;
    FilaConteiner FPorto;
    conteiner x,aux;
    embarcacao chegou;
    ListaEspera Esperando;

    iniciafilaC(&FPorto);
    iniciaListaEspera(&Esperando);
    do{
        menu= Menu();
        switch(menu){
            case 1:
                printf("\n\nIdentidade do Conteiner: ");
                scanf("%d",&x.identificacao);
                printf("\n\nDestino: ");
                scanf("%d",&x.destino);
                setbuf(stdin,NULL);
                printf("\n\nOrigem :");
                gets(x.origem);
                auxiliar=ChecaCompatibilidade(x.destino,destinos);
                if(auxiliar==1){
                    aux=chegaconteiner(&FPorto,x);
                    if(aux.destino!=0){
                        printf("\n\nConteiner Id %d - Destino:%d - Origem: %s Foi enfileirado no Porto Feliz!\n",aux.identificacao,aux.destino,aux.origem);
                    }
                    else
                       printf("\nNao ha espaco para este conteiner no Porto Feliz!\n");
                }
                else
                    printf("\n\nEh incompativel com os destinos disponiveis!\n");
               //Quando chegar um conteiner é enfileirado se for compatível com os destinos disponiveis
            break;
            case 2:
                printf("\n\nNome da Embarcacao que atracou no Porto: ");
                setbuf(stdin,NULL);
                gets(chegou.nome);
                atribuidestinos(&chegou);
                iniciaListaConteiner(&chegou.Conteiners);
                if(chegou.destinos[0]==1001){
                    printf("\n\nEssa embarcacao nao deve atracar no Porto Feliz!!\n\n");
                }
                else{
                    chegou.Status=1; // Recebe status de aportou
                    printf("\n\n--Destinos: %d,%d,%d\n\n",chegou.destinos[0],chegou.destinos[1],chegou.destinos[2]);
                    embarcarconteiner(&FPorto,&chegou);
                    if(chegou.Status==3){// Checar se ficou em espera.
                        PoeEspera(&chegou,&Esperando);
                    }
                    totalEmbarcacoes++;
                }
            break;
            case 3:
                if(Esperando.fim>0){
                    auxiliar=0;
                    printf("\nVerificando...");
                    do{
                        chegou=Esperando.Espera[auxiliar];
                        embarcarconteiner(&FPorto,&chegou);// Checa se há conteiners para a embarcacao em espera
                        if(chegou.Status!=3){
                            RetiraEspera(&Esperando,auxiliar);
                        }
                        else
                            printf("\n-->Nao ha conteiners a serem embarcados nesta embarcacao!\n");
                        auxiliar++;
                    }while(auxiliar<Esperando.fim);
                }
                else
                    printf("\nNao ha embarcacao em espera!\n\n");
            break;
            case 4:
                printf("\n\nEmbarcacoes");
                printf("\n Total: %d",totalEmbarcacoes);
                if(totalEmbarcacoes>0){
                    printf("\n-------------------------------------------------");
                    printf("\n\nUltima embarcacao : %s",chegou.nome);
                    printf("\nStatus: %d",chegou.Status);
                    printf("\n\n Conteiners:\n");
                    MostraConteinerEmbarcacao(&chegou);
                    printf("\n-------------------------------------------------");
                    printf("\n\n--> Embarcacoes em espera (%d)\n",Esperando.fim);
                    if(Esperando.fim>0){
                        for(auxiliar=0;auxiliar<=Esperando.fim-1;auxiliar++){
                            printf("\n%s - Destinos : %d , %d, %d\n",Esperando.Espera[auxiliar].nome,
                                   Esperando.Espera[auxiliar].destinos[0],Esperando.Espera[auxiliar].destinos[1],
                                   Esperando.Espera[auxiliar].destinos[2]);
                        }
                    }
                }
                printf("\n-------------------------------------------------");
                printf("\n\nConteiners no Porto \n Total: %d\n\n",QuantidadeFilaPorto(FPorto));
                MostraFilaConteinerPorto(&FPorto);
        }
    }while(menu!=0);
}
