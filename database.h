#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys\timeb.h>


typedef struct muster_Game
{
    char name[80 + 1];
    char konsole[80 + 1];
    float spielStunden;
    char completed[11 + 1];
    struct muster_Game* davor;
    struct muster_Game* danach;
}Game;



typedef struct
{
    char name[80 + 1];
    char konsole[80 + 1];
    float spielStunden;
    char completed[11 + 1];

    Game* mom;
    Game* zwischen;
    Game* start;

}Games_Database;


void up_listeAdd(Games_Database* pDatabase);
void up_hex(Games_Database* pDatabase);
void up_struct_liste(Games_Database* pDatabase);
void up_loesche(Games_Database* pDatabase);

void tableDesign();
void ausgabe(Games_Database* pDatabase);
void CreateEntries(Games_Database* pDatabase);
void printPointers(Games_Database* pDatabase);
void readFile();

