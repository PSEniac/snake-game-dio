#include <stdio.h>
#include <conio.h>
#include <windows.h>

int gameover, x, y, frutaX, frutaY, pontuacao;
int tailX[100], tailY[100];
int nTail;
enum Direcao { CIMA, BAIXO, ESQUERDA, DIREITA };
enum Direcao direcao;

void config() {
    gameover = 0;
    direcao = DIREITA;
    x = 10;
    y = 10;
    frutaX = rand() % 20;
    frutaY = rand() % 20;
    pontuacao = 0;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            direcao = ESQUERDA;
            break;
        case 'd':
            direcao = DIREITA;
            break;
        case 'w':
            direcao = CIMA;
            break;
        case 's':
            direcao = BAIXO;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direcao) {
    case ESQUERDA:
        x--;
        break;
    case DIREITA:
        x++;
        break;
    case CIMA:
        y--;
        break;
    case BAIXO:
        y++;
        break;
    }

    if (x < 0 || x >= 20 || y < 0 || y >= 20)
        gameover = 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;

    if (x == frutaX && y == frutaY) {
        pontuacao += 10;
        frutaX = rand() % 20;
        frutaY = rand() % 20;
        nTail++;
    }
}

void desenhar() {
    system("cls");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0 || i == 19 || j == 0 || j == 19)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == frutaY && j == frutaX)
                printf("F");
            else {
                int isprint = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        isprint = 1;
                    }
                }
                if (!isprint)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Pontuacao: %d\n", pontuacao);
}

int main() {
    config();
    while (!gameover) {
        desenhar();
        input();
        logic();
        Sleep(100); // Controle de velocidade do jogo
    }
    return 0;
}
