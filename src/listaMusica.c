#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/listaMusica.h"

typedef struct celula_musica CelMusica;

struct celula_musica{
    Musica* msc;
    CelMusica* prox;
};

struct lista_musica{
    CelMusica* prim;
    CelMusica* ult;
};

ListaMusica* iniciaListaMusica(){
    ListaMusica* lista = (ListaMusica*)malloc(sizeof(ListaMusica));
    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

void insereListaMusica(ListaMusica* lista, Musica* msc){
    CelMusica* cel_nova = (CelMusica*)malloc(sizeof(CelMusica));

    cel_nova->msc = msc;
    cel_nova->prox = NULL;
    if(lista->prim == NULL){
        lista->prim = cel_nova;
        lista->ult = cel_nova;
    }
    else{
        lista->ult->prox = cel_nova; 
        lista->ult = cel_nova;
    }
}

void refatoraListaMusica(ListaMusica* lista, char* caminho){
    FILE* arq;
    CelMusica* cel_aux;
    char nome_arquivo[100], caminho_aux[100];
    strcpy(caminho_aux, caminho);

    for(cel_aux = lista->prim; cel_aux != NULL; cel_aux = cel_aux->prox){
        strcpy(caminho, caminho_aux);
        strcpy(nome_arquivo, getBandaMusica(cel_aux->msc));
        strcat(nome_arquivo, ".txt");
        strcat(caminho, nome_arquivo);
        arq = fopen(caminho, "a");
        fclose(arq);
    }
}

void imprimeListaMusica(ListaMusica* lista){
    CelMusica* cel_aux;
    for(cel_aux = lista->prim; cel_aux != NULL; cel_aux = cel_aux->prox){
        imprimeMusica(cel_aux->msc);
    }
}

void destroiListaMusica(ListaMusica* lista){
    CelMusica* cel_atual = lista->prim;
    CelMusica* cel_prox;

    while(cel_atual != NULL){
        cel_prox = cel_atual->prox;

        destroiMusica(cel_atual->msc);
        free(cel_atual);

        cel_atual = cel_prox;
    }
    free(lista);
}