/* 


*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int L = 5;
const int C = 6; 
const int MAXLOCA = 2;

int pv = 30; 
int ph = 30;
int pvv;
int phh;
int MD;

enum modes {PLAY , CORR}; 

void apfundo(int quadrante[L][C]);
void geraOceano(int quadrante[L][C]);
void locaatk(char LOCA[MAXLOCA]);
void marcaatk(int quadrante[L][C], char LOCA[MAXLOCA]);
void tabeladados(int SUB, int TORP, int DESTR);
int verificaatk(char LOCA[MAXLOCA] , int quadrante[L][C]);


int 
main()
{

    int quadrante[L][C];
    char LOCA[MAXLOCA];
    int SUB = 3;
    int TORP = 6;
    int DESTR = 0;
    int r;
    int l = 0;
    
    MD = PLAY;
   
        if(MD == PLAY)
        {   
            while(TORP > 0 || SUB != 0)
            {
                system("clear");
                printf("-------BATALHA NAVAL-------\n");
                if(l == 0)
                {
                    geraOceano(quadrante);
                    l++;
                }
                else
                    marcaatk(quadrante, LOCA);
    
                printf("\n");
                tabeladados(SUB, TORP, DESTR);
                locaatk(LOCA);
                if(verificaatk(LOCA, quadrante) == 0)
                {
                    TORP--;
                    printf("\n\n");
                }
                else
                {
                    SUB--;
                    TORP--;
                    printf("\n");
                }
                if(SUB != 0 && TORP == 0)
                {
                    system("clear");
                    printf("-------BATALHA NAVAL-------\n");
                    marcaatk(quadrante, LOCA);
                    printf("\n");
                    tabeladados(SUB, TORP, DESTR);
                    printf("\t------------\n");
                    printf("\tGame Over!!!\n");
                    printf("\t------------\n");
                    break;
                }
                else if(SUB == 0)
                {   
                    system("clear");
                    printf("-------BATALHA NAVAL-------\n");
                    marcaatk(quadrante, LOCA);
                    printf("\n");
                    tabeladados(SUB, TORP, DESTR);
                    printf("\t------------\n");
                    printf("\t|You Won!!!|\n");
                    printf("\t------------\n");
                    break;
                }
            }
        }
        else
        {
            printf("Programa teste, acesse o PLAY para jogar!\n");
            apfundo(quadrante);
        }
    return 0;
}
/*
    Gerador de localização
    -----------------
    Gera a localização dos subimarinos
    0 = mar
    1 = submarino
    é apresentada no modo CORR para melhor visualização.
*/
void
apfundo(int quadrante[L][C])
{
    int numer[L];
    int i, j;
    for(i = 0;i < C ; i++)
    {
        numer[i] = i;
        if(i == 0)
        {
            numer[i] = '\t';
            printf("%c", numer[i]);
        }
        else
            printf("  %d ", numer[i]);
    }
    printf("\n");
    printf("\t+---+---+---+---+---+\n");
    for(i = 0;i < L; i++)
    {
        for(j = 0;j < C; j++)
        {
            if(i == 0 || j == 0)
            {
                if(i == 0 && j ==0)
                {
                    quadrante[i][j] = 'A';
                    continue;
                }
                else if(i == 1 && j ==0)
                {
                    quadrante[i][j] = 'B';
                    continue;
                }
                else if(i == 2 && j ==0)
                {
                    quadrante[i][j] = 'C';
                    continue;
                }
                else if(i == 3 && j ==0)
                {
                    quadrante[i][j] = 'D';
                    continue;
                }
                else if(i == 4 && j ==0)
                { 
                    quadrante[i][j] = 'E';
                    continue;
                }
            }
            quadrante[i][j] = rand()%7;
            (quadrante[i][j] == 5) ? (quadrante[i][j] = 1) : (quadrante[i][j] = 0);
        }
    }
    for(i = 0;i < L; i++)
    {
        for(j = 0;j < C; j++)
        {
            if(j == 0)
                printf("%1c \t|", quadrante[i][j]);
            else
                printf(" %1d |", quadrante[i][j]);
        }
        printf("\n\t+---+---+---+---+---+\n");
    } 
}
/*
    Gerador de Oceano 
    -----------------
    Gera o Oceano na tela
*/
void
geraOceano (int quadrante[L][C])
{
    int numer[L];
    int i, j;
    for(i = 0;i < C ; i++)
    {
        numer[i] = i;
        if(i == 0)
        {
            numer[i] = '\t';
            printf(" %c", numer[i]);
        }
        else
            printf("  %d ", numer[i]);
    }
    printf("\n");
    printf("\t+---+---+---+---+---+\n");

    for(i = 0;i < L; i++)
    {
        for(j = 0;j < C; j++)
        {
            if(i == 0 || j == 0)
            {
                if(i == 0 && j ==0)
                {
                    quadrante[i][j] = 'A';
                    continue;
                }
                else if(i == 1 && j ==0)
                {
                    quadrante[i][j] = 'B';
                    continue;
                }
                else if(i == 2 && j ==0)
                {
                    quadrante[i][j] = 'C';
                    continue;
                }
                else if(i == 3 && j ==0)
                {
                    quadrante[i][j] = 'D';
                    continue;
                }
                else if(i == 4 && j ==0)
                {
                    quadrante[i][j] = 'E';
                    continue;
                }
            }
            if(i == 2 && j == 2)
                quadrante[i][j] = 1;
            else if(i == 4 && j == 3)
                quadrante[i][j] = 1;
            else if(i == 0 && j ==4)
                quadrante[i][j] = 1;
            else
                quadrante[i][j] = 0;
        }   
    }
    for(i = 0;i < L; i++)
    {
        for(j = 0;j < C; j++)
        {
            if(j == 0)
                printf(" %c\t|", quadrante[i][j]);
            else
                printf(" %c\t|", quadrante[i][j]);
        }
        printf("\n\t+---+---+---+---+---+\n");
    } 
}
/*
    Leitura de dados
    -----------------
    Verifica qual posição o jogador digitou para atacar.
*/
void
locaatk(char LOCA[MAXLOCA])
{
    printf("\tDigite a quadrante que deseja atacar: ");
    scanf("%s", LOCA);
}
/*
    Apresenta os dados
    -----------------
    Gera os dados na tela do numero de:
    Torpedos, destroyers e subimarinos
*/
void
tabeladados(int SUB, int TORP, int DESTR)
{
    printf("\tDestroyers:\t%d\n", DESTR);
    printf("\tSubmarines:\t%d\n", SUB);
    printf("\tTorpedos:\t%d\n", TORP);
}
/*
    Verifica se o ataque acertou
    -----------------
    função retorna 1 se o ataque acertar.
    retorna 0 se o ataque errou.
*/
int
verificaatk(char LOCA[MAXLOCA] , int quadrante[L][C])
{
    int i;
    int k;
    char conv[1];
    for(i = 0;i < MAXLOCA; i++)
    {
            if(LOCA[i] == 'A')
                LOCA[i] = 0;
            else if(LOCA[i] == 'B')
                LOCA[i] = 1;
            else if(LOCA[i] == 'C')
                LOCA[i] = 2;
            else if(LOCA[i] == 'D')
                LOCA[i] = 3;
            else if(LOCA[i] == 'E')
                LOCA[i] = 4;
            else if(isdigit(LOCA[i]) != 0)
                conv[0] = LOCA[i];
            else
                continue;
    }
    k = 0;
    pv = LOCA[k];
    ph = atoi(conv);
    pvv = pv;
    phh = ph;
    if(quadrante[pv][ph] == 1)   
        return 1;
    else
    {
        pv = 30;
        ph = 30;
        return 0;
    }
}


void
marcaatk(int quadrante[L][C], char LOCA[MAXLOCA])
{
    int numer[L];
    int i, j;
    for(i = 0;i < C ; i++)
    {
        numer[i] = i;
        if(i == 0)
        {
            numer[i] = '\t';
            printf(" %c", numer[i]);
        }
        else
            printf("  %d ", numer[i]);
    }

    printf("\n");
    printf("\t+---+---+---+---+---+\n");

    for(i = 0;i < L; i++)
    {
        for(j = 0;j < C; j++)
        {
            if(i == 0 && j == 0)
                quadrante[i][j] = 'A';
            if(pv != 30 && ph != 30)
            {
                quadrante[pv][ph] = '*';
            }
            else
            {
                quadrante[pvv][phh] = 'w';
            }
        }   
    }
    for(i = 0;i < L; i++)
    {
        for(j = 0;j < C; j++)
        {
            if(j == 0)
            {
                printf(" %c\t|", quadrante[i][j]);
            }
            else
                printf(" %c\t|", quadrante[i][j]);
        }
        printf("\n\t+---+---+---+---+---+\n");
    } 
}