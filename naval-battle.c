/*The program below simulates a naval battle game, a 21st century classic, in which the user will type a quadrant to order a launch
of a torpedo, for example: "A1", having a maximum of six torpedoes, that is, six attempts to hit three submarines, if it hits all submarines
the game reports that he won, otherwise the game reports that he lost. If a torpedo hits a submarine, a "*" sign will appear in the Ocean (matrix)
indicating the sinking of the vessel, but if the shot misses, "W" will appear indicating the torpedo has sunk in the water. However here's a tip:
if the user can find a submarine, around this transport, that is, in the other quadrants around it, it will not be possible to find another vessel,
so use your attempts wisely. This way, the game only ends when the total number of attempts are reached, or if the user manages to sink the three submarines.

By Caio Couto, Lucas Daniel and Matheus Henrique, 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int L = 5; /* Declaring constant to generate matrix/ocean */
const int C = 6; /* Constant to generate matrix/ocean */
const int MAXLOCA = 2; /* Declaring a constant to locate the torpedoes in the form of an array with a value equal to two */

int pv = 30; /* Declaring a variable of type integer with value equal to thirty, pv = vertical plane */
int ph = 30; /* A variable of type integer with value equal to thirty, ph = horizontal plane */
int pvv; /* Declaring another variable of type integer to make a conversion, pvv = vertical plane 2 */ 
int phh; /* Another variable of type integer to make a conversion, phh = horizontal plane 2 */
int MD; /* Declaring variable to run the game in two modes: PLAY and RUN */

enum modes {PLAY , CORR};  /* Function to generate PLAY or CORR mode */

void apfundo(int quadrante[L][C]);
void geraOceano(int quadrante[L][C]);
void locaatk(char LOCA[MAXLOCA]);
void marcaatk(int quadrante[L][C], char LOCA[MAXLOCA]);
void tabeladados(int SUB, int TORP, int DESTR);
int verificaatk(char LOCA[MAXLOCA] , int quadrante[L][C]);


int 
main()
{

    int quadrante[L][C]; /* Declaring variable to generate an array */
    char LOCA[MAXLOCA]; /*  Variable of type char to check quadrant */
    int SUB = 3; /* Declaring an integer variable to mention the number of submarine numbers available */
    int TORP = 6; /* An integer variable to mention the number of torpedo numbers available */
    int DESTR = 0; /* An integer variable to mention the number of numbers available from Destroyers */
    int r; /* Declaring a constant */
    int l = 0; /* Declaring a constant with an initial value of zero */
    
    MD = PLAY;  /* Variable to show the game in an interactive way, that is, in PLAY mode */
   
        if(MD == PLAY) /* If the MD is the same as PLAY it will display interactive mode with the game, switching to CORR will show the location of the submarines */
        {   
            while(TORP > 0 || SUB != 0) /* Loop to run the progarama while the torpedo number is greater than zero or the submarine number is non-zero, if the values are different it will show You Won!!! */
            {
                system("clear"); /* Function for cleaning the ocean screen */
                printf("-------NAVAL BATTLE-------\n");
                if(l == 0)
                {
                    geraOceano(quadrante); /* Generating the ocean on the game screen */
                    l++;
                }
                else
                    marcaatk(quadrante, LOCA);
    
                printf("\n");
                tabeladados(SUB, TORP, DESTR); /* Showing the values of submarines, torpedoes and destroyers on the game screen */
                locaatk(LOCA); /* Generating torpedo attack location on game screen */
                if(verificaatk(LOCA, quadrante) == 0) /* Showing the attack verification and decreasing the hit attempts, that is, decreasing the number of submarines (if sunk) and torpedoes */
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
                    system("clear"); /* Function for cleaning the ocean screen, to show on the screen only the quadrant where the torpedo fell into the ocean, informed by the program user */
                    printf("-------NAVAL BATTLE-------\n");
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
                    system("clear"); /* Function for clearing the ocean screen, to show on the screen only the quadrant where the torpedo fell into the ocean, informed by the program user, and showing whether it won or reached the maximum number of attempts */
                    printf("-------NAVAL BATTLE-------\n");
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
            printf("Trial program, access PLAY to play!\n");
            apfundo(quadrante);
        }
    return 0;
}
/*
    Location generator
    -----------------
    Generates the location of submarines
    0 = sea
    1 = submarine
    is displayed in CORR mode for better viewing.
*/
void
apfundo(int quadrante[L][C])
{
    int numer[L]; /* Declaring variable to generate an array */
    int i, j; /* Declaring constants of type integer */
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
            quadrante[i][j] = rand()%7; /* Generating numbers from 0 to 6 */
            (quadrante[i][j] == 5) ? (quadrante[i][j] = 1) : (quadrante[i][j] = 0); /* If the number generated is equal to 5, change it to 1, if it is different from 5, equal to 0 */
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
    Ocean generator
    -----------------
    Generates the ocean on the screen
*/
void
geraOceano (int quadrante[L][C])
{
    int numer[L]; /* Declaring variable to generate an array */
    int i, j; /* Declaring constants of type integer */
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

    for(i = 0;i < L; i++) /* Loop to generate the letters "ABCDE" in the vertical part of the ocean */
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
            if(i == 2 && j == 2) /* Generating the numbers "12345" horizontally across the ocean */
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
    
    Data reading
    -----------------
    Check which position the player typed to attack.
*/
void
locaatk(char LOCA[MAXLOCA])
{
    printf("\tEnter the quadrant you want to attack: ");
    scanf("%s", LOCA); /* Storing the location of the quadrant in which the torpedo will be launched, informed by the user */
}
/* Check which quadrant the torpedo attack was in and mark the value in the matrix/ocean
------------------------------------------------- ---------------------------------------------------------
  If the torpedo hits a submarine, the "*" will appear on the game screen instead of the quadrant.
  indicating that a submarine has sunk. If the torpedo has not hit any vessel, the "W" will appear
  indicating that the torpedo sinks into the ocean.
*/
void
marcaatk(int quadrante[L][C], char LOCA[MAXLOCA])
{
    int numer[L]; /* Declaring variable to generate an array */
    int i, j; /* Declaring constants */
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

    for(i = 0;i < L; i++) /* Loop to show "*" and "W" values in the ocean */
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
/*
    Displays the data
    -----------------
    Generates the data on the screen of the number of:
    Torpedoes, destroyers and submarines
*/
void
tabeladados(int SUB, int TORP, int DESTR)
{
    printf("\tDestroyers:\t%d\n", DESTR); 
    printf("\tSubmarines:\t%d\n", SUB);
    printf("\tTorpedos:\t%d\n", TORP);
}
/*
    Check if the attack hit
    -----------------
    Function returns 1 if attack hits.
    returns 0 if the attack failed.
*/
int
verificaatk(char LOCA[MAXLOCA] , int quadrante[L][C])
{
    int i; /* Declaring a constant */
    int k; /* Constant */
    char conv[1]; /* Declaring a variable of type char to convert to integer type in the form of an array */
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
    k = 0; /* Declaring a constant with a value of zero */
    pv = LOCA[k]; /* Vertical position, related to the letters "ABCDE", is the same as the location of the quadrants */
    ph = atoi(conv); /* Declaring the horizontal position, related to the numbers "12345", using the "atoi" function, to convert char to int */
    pvv = pv; /* Declaring another vertical position to store in pv, to later be converted to "*" or "W" (from water = water) in a possible torpedo launch */
    phh = ph; /* Another horizontal position to store in ph, to later be converted to "*" or "W" (from water = water) in a possible torpedo launch */
    if(quadrante[pv][ph] == 1)   
        return 1;
    else
    {
        pv = 30;
        ph = 30;
        return 0;
    }
}


