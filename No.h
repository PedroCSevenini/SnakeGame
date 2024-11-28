#pragma once
class No
{
public:
    No();
    ~No();
    void setProx(No* p) { prox = p; };
    No* getProx() { return prox; };
    void setCoord(int vet[2]);
    int getCoordX() { return coord[0]; };
    int getCoordY() { return coord[1]; };
   


private:
    int coord[2] = {};
    No* prox;
};

