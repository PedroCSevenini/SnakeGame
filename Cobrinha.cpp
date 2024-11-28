#include "Cobrinha.h"


Cobrinha::Cobrinha()
{
    primeiro = NULL;

}

Cobrinha::~Cobrinha()
{
    No* p = primeiro;
    while (p != NULL) {
        No* aux = primeiro;
        p = primeiro->getProx();
        primeiro = p;
        delete aux;
    }
}

void Cobrinha::insereInicio(int x, int y)
{
    if (!primeiro) {
        No* cabeca = new No();
        int vet[2] = { 4,4 };
        cabeca->setCoord(vet);
        cabeca->setProx(NULL);
        ultimo = cabeca;
        primeiro = cabeca;
        tamanho++;
    }
    else {
        No* aux = new No();
        int vet[2] = { x, y };
        aux->setCoord(vet);
        aux->setProx(primeiro);
        primeiro = aux;
        tamanho++;
    }
}

void Cobrinha::removeFinal() {
    No* aux;
    for (aux = primeiro; aux->getProx() != ultimo; aux = aux->getProx()){
    }
    delete ultimo;
    aux->setProx(NULL);
    ultimo = aux;
    tamanho--;
}

void Cobrinha::atualizaDirecao(char direcional)
{
    if (direcional == 'A')
        direcional = 'a';
    if (direcional == 'D')
        direcional = 'd';
    if (direcional == 'S')
        direcional = 's';
    if (direcional == 'W')
        direcional = 'w';

    if(direcional == 'a' && direcao == 'd'){
        return;
    }
    if(direcional == 'd' && direcao == 'a'){
        return;
    }
    if (direcional == 'w' && direcao == 's'){
        return;
    }
    if (direcional == 's' && direcao == 'w'){
        return;
    }
    if (direcional == 'a' || direcional == 'w' || direcional == 's' || direcional == 'd') {
        direcao = direcional;
    }
    
}

void Cobrinha::movimentoCobra()
{
    switch (direcao)
    {
    case  'd'://Direita
        insereInicio(primeiro->getCoordX(), primeiro->getCoordY() + 1);
        removeFinal();
        break;

    case  'a'://Esquerda
        insereInicio(primeiro->getCoordX(), primeiro->getCoordY() - 1);
        removeFinal();
        break;

    case  'w'://Cima
        insereInicio(primeiro->getCoordX() - 1, primeiro->getCoordY());
        removeFinal();
        break;

    case  's'://Baixo
        insereInicio(primeiro->getCoordX() + 1, primeiro->getCoordY());
        removeFinal();
        break;
        
    case 'n':
        break;
    }



}

void Cobrinha::limpar() {
    No* aux;
    if (tamanho > 0){
        while (primeiro != NULL){
            aux = primeiro->getProx();
            delete primeiro;
            primeiro = aux;
           
        }
        tamanho = 0;
        direcao = 'd';
    }

}