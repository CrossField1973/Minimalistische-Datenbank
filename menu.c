#include "menu.h"
#include "database.h"

void watermark()
{
	printf("                              \\\\\\\\\\\\\\ \n");
	printf("                            \\\\\\\\\\\\\\\\\\\\\\\\ \n");
	printf("                          \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	printf("  -----------,-|           |C>   // )\\\\\\\\| \n");
	printf("           ,','|          /    || ,'/////| 		//////////////////////////////////////////////////\n");
	printf("---------,','  |         (,    ||   ///// 		//Ver. 1.03                                     //\n");
	printf("         ||    |          \\\\  ||||//''''| 		//                                              //\n");
	printf("         ||    |           |||||||     _| 		//                                              //\n");
	printf("         ||    |______      `````\\____/ \\ 		//                                              //\n");
	printf("         ||    |     ,|         _/_____/ \\ 		//           Ingenious Game-Database            //\n");
	printf("         ||  ,'    ,' |        /          | 		//             Developed by Kevin Weis          //\n");
	printf("         ||,'    ,'   |       |         \\  | 		//                                              //\n");
	printf("_________|/    ,'     |      /           | | 		//                                              //\n");
	printf("_____________,'      ,',_____|      |    | | 		//////////////////////////////////////////////////\n");
	printf("             |     ,','      |      |    | | \n");
	printf("             |   ,','    ____|_____/    /  | \n");
	printf("             | ,','  __/ |             /   | \n");
	printf("_____________|','   ///_/-------------/   |  \n");
	printf("              |===========,' 				 \n");
	
	printf("\n");
	
	printf("1.) Datenbank anzeigen\n");
	printf("2.) Neue Eintr\x84ge erstellen\n");
	printf("3.) Eintr\x84ge l\x94schen\n");
	printf("4.) Datenbank von Datei importieren\n");
	printf("5.) Datenbank in  Datei exportieren\n");
	printf("6.) Datenbank nach Kategorie sortieren\n");
	printf("7.) Zeiger anzeigen\n");
	printf("8.) Anwendung beenden\n");
}

void Main_Menu()
{
	// Erschaffe Datenbank
    Games_Database database;
    Games_Database* pDatabase = &database;
    pDatabase->mom = 0;
    pDatabase->start = 0;
    pDatabase->zwischen = 0;
	int input;	
	int numoutput = 25;
	
	while(1)
	{
		watermark();
		
		printf("\nAuswahl: ");
		scanf("%d", &input);
		fflush(stdin);
		
		switch(input)
		{		
			case 1:
				system("cls");
				Output_Menu(pDatabase, numoutput);
				break;
				
			case 2:
				system("cls");
				Create_Entries(pDatabase);
				
				printf("\nDr\x81""cke Enter um fortzufahren");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 3:
				delete(pDatabase);
			
				break;
				
			case 4:
				system("cls");
				Read_File(pDatabase);
				output(pDatabase);
				
				printf("\nDr\x81""cke Enter um fortzufahren");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 5:
				system("cls");
				Write_File(pDatabase);
				
				printf("Dr\x81""cke Enter um fortzufahren");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 6:
				system("cls");
				Sort_Menu(pDatabase);
				
				break;
				
			case 7:
				system("cls");
				hex(pDatabase);
				printf("\n\nDr\x81""cke Enter um fortzufahren");
				scanf("abc");
				fflush(stdin);
				
				break;
				
			case 8:
				return;
				
				break;
				
			default:
				system("cls");
				printf("Gib bitte eine Valide Eingabe ein");
				
				printf("\nDr\x81""cke Enter um fortzufahren");
				scanf("abc");
				fflush(stdin);
				break;
		}
		
		system("cls");
	}
}


void Sort_Menu(Games_Database* pDatabase)
{
	int input;
	char category[12 + 1] = { };
	char algorithm[12 + 1] = { };
		
	while(1)
	{	
		printf("Sortier-Untermen\x81\n");
	
		printf("Nach dieser Kategorie soll sortiert werden : %s\n", category);
		printf("Mit diesem Sortier-Algorithmus soll sortiert werden : %s\n\n", algorithm);
	
		printf("1.) Nach 'Namen' sortieren\n");
		printf("2.) Nach 'Platform' sortieren\n");
		printf("3.) Nach 'Spielstunden' sortieren\n\n");
		
		printf("4.) Mit dem Quick-Sort sortieren\n");
		printf("5.) Mit dem Bubble-Sort sortieren\n\n");

		
		printf("6.) Jetzt sortieren\n\n");
		
		printf("7.) Zum Hauptmen\x81 zur\x81""ckkehren\n");
	
		printf("\nAuswahl: ");
		scanf("%d", &input);
		fflush(stdin);
	
		switch(input)
		{		
			case 1:
				strcpy(category, "Name");
				break;
				
			case 2:
				strcpy(category, "Platform");
				break;
				
			case 3:
				strcpy(category, "Spielstunden");
				break;
				
			case 4:
				strcpy(algorithm, "Quick-Sort");
				break;
				
			case 5:
				strcpy(algorithm, "Bubble-Sort");
				break;
				
			case 6:
				system("cls");
				Sort_Logic(pDatabase, algorithm, category);
				
				printf("\nDr\x81""cke Enter um fortzufahren");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 7:
				return;
				break;
				
			default:
				system("cls");
				printf("Gib bitte eine Valide Eingabe ein");
				break;
		}
		
		
		
		system("cls");
	}
}
