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
	printf("4.) Open Database-File*\n");
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
				ausgabe(pDatabase);
				
				printf("\nPress enter to continue");
				scanf("abc");
				fflush(stdin);
				break;
				
			case 5:
				system("cls");
				writeFile(pDatabase);
				
				break;
				
			case 6:
				system("cls");
				Sort_Menu(pDatabase);
				
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


