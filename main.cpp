#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>


#include "Cobrinha.h"


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD posicao;

const int larguraTela = 15;
const int alturaTela = 30;

const char pedacoCobra = ('%c',219);
const char pedacoVazio = ' ';
const char comida = ('%c', 4);
const char borda = ('%c', 219);


void static resetDisplay(char malha[larguraTela][alturaTela]) {

    for (int i = 0; i < larguraTela; i++) {
        for (int j = 0; j < alturaTela; j++) {
            if (i == 0 || i == larguraTela - 1 || j == 0 || j == alturaTela - 1){
                malha[i][j] = borda;
            }
            else {
                malha[i][j] = pedacoVazio;
            }
        }
    }

}

void cobraInsert(Cobrinha &cobra, char malha[larguraTela][alturaTela]){
    int cont = 0;
    No* aux = cobra.getPrimeiro();
    while(aux != NULL){
        malha[aux->getCoordX()][aux->getCoordY()] = pedacoCobra;
        aux = aux->getProx();
    }

}

void display(char malha[larguraTela][alturaTela]) {
    posicao.X = 46;
    posicao.Y = 6;
    SetConsoleCursorPosition(hConsole, posicao);

    for (int i = 1; i < larguraTela-1; i++) {
        for (int j = 1; j < alturaTela-1; j++) {
            if (malha[i][j] == pedacoCobra) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            }
            if (malha[i][j] == comida) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            }
            std::cout << malha[i][j];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        std::cout << "\n";
        posicao.Y++;
        SetConsoleCursorPosition(hConsole, posicao);

        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 1;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

       
    }
}

int* geraComida(char malha[larguraTela][alturaTela]){
    srand(time(NULL));
    int *vet = new int[2];
    int tentativa = 0;
    int x;
    int y;
    while (tentativa == 0) {
        x = rand() % larguraTela;
        y = rand() % alturaTela;
        if (malha[x][y] == pedacoVazio) {
            malha[x][y] = comida;
            tentativa++;
        }

    }
    vet[0] = x;
    vet[1] = y;
    return vet;
    
}

static char Key(Cobrinha &cobra)
{
    if (_kbhit()){
        return _getch(); // Obtém a tecla pressionada
    }
    return cobra.getDirecao();
    
}


static int verificaColisao(int x, int y, char malha[larguraTela][alturaTela])
{
    if (malha[x][y] == borda || malha[x][y] == pedacoCobra) {
        return 1;
    }
    return 0;

}

void pontosDisplay(){
    posicao.X = 80;
    posicao.Y = 8;
    SetConsoleCursorPosition(hConsole, posicao);
    std::cout << "Pontos: ";
}

void pontosAtualiza(int pontos) {
    posicao.X = 90;
    posicao.Y = 8;
    SetConsoleCursorPosition(hConsole, posicao);
    std::cout << pontos;

}


int main(){
    
    char malha[larguraTela][alturaTela];
    Cobrinha cobra;
    int gameover = 0;
    int pontos = 0;
    int reset = 0;
    int recorde = 0;
    resetDisplay(malha);
    int* coordComida = geraComida(malha);
    
    
    while (reset==0){
        resetDisplay(malha);
        cobra.insereInicio(0, 0);
        cobra.insereInicio(4, 5);
        

        /* Imprime as bordas do display e o placar*/
        posicao.X = 45;
        posicao.Y = 5;
        SetConsoleCursorPosition(hConsole, posicao);
        for (int i = 0; i < larguraTela; i++) {
            for (int j = 0; j < alturaTela; j++) {
                std::cout << malha[i][j];
            }
            std::cout << "\n";
            posicao.Y++;
            SetConsoleCursorPosition(hConsole, posicao);
        }
        pontosDisplay();
        /* Fim da impressão*/
        while (gameover == 0) {
            resetDisplay(malha);//Reseta a malha do display a cada movimento
            malha[coordComida[0]][coordComida[1]] = comida; //Insere a comida no Display
            cobraInsert(cobra, malha);//Insere a cobra na malha do display
            display(malha);//Imprime o display com a cobra
            pontosAtualiza(pontos);//Atualiza os pontos no display

            Sleep(150); //Segura o jogo por tempo para diminuir a velocidade da cobra

            cobra.atualizaDirecao(Key(cobra));//Atualiza a direção com base na key pressionada

            cobra.movimentoCobra();//Movimento da cobra
            gameover = verificaColisao(cobra.getPrimeiro()->getCoordX(), cobra.getPrimeiro()->getCoordY(), malha);//Verifica se a cobra colidiu com o proprio corpo ou com a borda
            if (cobra.getPrimeiro()->getCoordX() == coordComida[0] && cobra.getPrimeiro()->getCoordY() == coordComida[1]) {//Verifica se comeu
                cobra.insereInicio(coordComida[0], coordComida[1]);//Cobra cresce com base na posição da comida
                pontos += 10;//Soma pontos
                coordComida = geraComida(malha);//Reseta a comida
            }
        }
        system("cls");
        posicao.X = 45;
        posicao.Y = 5;
        SetConsoleCursorPosition(hConsole, posicao);
        std::cout << "Seus pontos: " << pontos;
        if (pontos > recorde) {
            recorde = pontos;
        }
        posicao.X = 45;
        posicao.Y = 6;
        SetConsoleCursorPosition(hConsole, posicao);
        std::cout << "Recorde: " << recorde;
        posicao.X = 45;
        posicao.Y = 7;
        SetConsoleCursorPosition(hConsole, posicao);
        std::cout << "Deseja continuar? (PRESSIONE F)";
        posicao.X = 45;
        posicao.Y = 8;
        SetConsoleCursorPosition(hConsole, posicao);
        std::cout << "Para sair aperte (G)";
        reset = 2;
        do{
            char press = _getch();
            if (press == 'f' || press == 'F') {
                reset = 0;
                system("cls");
                gameover = 0;
                pontos = 0;
                cobra.limpar();
                
            }
            else if(press == 'g' || press == 'G') {
                reset = 1;
                system("cls");
                posicao.X = 45;
                posicao.Y = 5;
                SetConsoleCursorPosition(hConsole, posicao);
                std::cout << "Finalizando programa...";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);


            }
        }while (reset == 2);
            


    }

    delete[] coordComida;

   
    return 0;
}
