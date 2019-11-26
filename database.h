#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys\timeb.h>


typedef struct muster_Game
{
    char 	name[80 + 1];
    char 	konsole[80 + 1];
    float 	spielStunden;
    char 	completed[11 + 1];
    struct 	muster_Game* davor;
    struct 	muster_Game* danach;
}Game;



typedef struct
{
    char 	name[80 + 1];
    char 	konsole[80 + 1];
    float 	spielStunden;
    char 	completed[11 + 1];

    Game* mom;
    Game* zwischen;
    Game* start;

}Games_Database;





void Table_Design();
void Read_File();
void Write_File();
void delete			(Games_Database* pDatabase);
void Sort_Menu		(Games_Database* pDatabase);
void Liste_Add		(Games_Database* pDatabase);
void hex			(Games_Database* pDatabase);
void Struct_Liste	(Games_Database* pDatabase);
void output			(Games_Database* pDatabase);
void Create_Entries	(Games_Database* pDatabase);

void Sort_Logic				(Games_Database* pDatabase, char algorithm[12 + 1], char category[12 + 1]);
void Quick_Sort_Names		(Games_Database* pDatabase, int left, int right,    char category[80 + 1]);
void Quick_Sort				(Games_Database* pDatabase, int left, int right);
void Swap_Entries			(Games_Database* pDatabase, int left, int right);
void Swap_Entries_Lite		(Games_Database* pDatabase, int left, int right);
void Set_Mom_To_Selected	(Games_Database* pDatabase, int position);
void Output_Menu			(Games_Database* pDatabase, int numOutput);
void Bubble_Sortieren		(Games_Database* pDatabase, int length);
void Bubble_Sortieren_Namen	(Games_Database* pDatabase, int length, char category[]);
