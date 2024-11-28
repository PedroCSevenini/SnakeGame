#pragma once
#include "No.h"
#include <iostream>
class Cobrinha
{
public:
    Cobrinha();
    ~Cobrinha();
    void insereInicio(int x, int y);
    int getTamanho(){return tamanho;};
    No* getPrimeiro(){return primeiro;};
    void removeFinal();
    void movimentoCobra();
    void atualizaDirecao(char direcional);
    char getDirecao() { return direcao; };
    void limpar();


private:
    char direcao = 'd';
    No* primeiro;
    No* ultimo;
    int tamanho = 0; //Tamanho da cobra

};
