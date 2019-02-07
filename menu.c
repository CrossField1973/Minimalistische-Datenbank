#include "menu.h"
#include "database.h"

void watermark()
{
	printf("                              \\\\\\\\\\\\\\ \n");
	printf("                            \\\\\\\\\\\\\\\\\\\\\\\\ \n");
	printf("                          \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	printf("  -----------,-|           |C>   // )\\\\\\\\| \n");
	printf("           ,','|          /    || ,'/////| 		//////////////////////////////////////////////////\n");
	printf("---------,','  |         (,    ||   ///// 		//Ver. 0.4                                      //\n");
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
	
	printf("1.) Display Current Database*\n");
	printf("2.) Create new Entries\n");
	printf("3.) Delete Entries\\\n");
	printf("4.) Open Database-File\\\n");
	printf("5.) Export Current Database\\\n");
	printf("6.) Sort Current Database by Kategory\\\n");
	printf("7.) Exit Application\n");
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
	
	while(1)
	{
		watermark();
		
		printf("\nSelection: ");
		scanf("%d", &input);
		fflush(stdin);
		
		switch(input)
		{		
			case 1:
				system("cls");
				ausgabe(pDatabase);
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 2:
				system("cls");
				CreateEntries(pDatabase);
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 3:
				up_loesche(pDatabase);
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 4:
				system("cls");
				readFile(pDatabase);
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 5:
				system("cls");
				printf("Case 05");
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 6:
				system("cls");
				Sort_Menu();
				
				break;
				
			case 7:
				return;
				
				break;
				
			default:
				system("cls");
				printf("Gib bitte eine Valide Eingabe ein");
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
		}
		
		system("cls");
	}
}

void Sort_Menu()
{
	int input;
	char kategory[80 + 1] = { };
	char algorithm[80 + 1] = { };
		
	while(1)
	{	
		printf("Sort by Kategory Sub-Menu\n");
	
		printf("Selected Kategory to sort by : %s\n", kategory);
		printf("Selected Sorting-Algorithm   : %s\n\n", algorithm);
	
		printf("1.) Sort by 'Name'\n");
		printf("2.) Sort by 'Platform'\n");
		printf("3.) Sort by 'Hours_played'\n");
		printf("4.) Sort by Input_Order \n\n");
		
		printf("5.) Sort with Quick-Sort\n");
		printf("6.) Sort with Bubble-Sort\n\n");

		
		printf("7.) Sort now\n\n");
		
		printf("8.) Return to Main Menu\n");
	
		printf("\nSelection: ");
		scanf("%d", &input);
		fflush(stdin);
	
		switch(input)
		{		
			case 1:
				strcpy(kategory, "Name");
				break;
				
			case 2:
				strcpy(kategory, "Platform");
				break;
				
			case 3:
				strcpy(kategory, "Hours_played");
				break;
				
			case 5:
				strcpy(algorithm, "Quick-Sort");
				break;
				
			case 6:
				strcpy(algorithm, "Bubble-Sort");
				break;
				
			case 7:
				system("cls");
				printf("Database Sorted by: with:");
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 8:
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

