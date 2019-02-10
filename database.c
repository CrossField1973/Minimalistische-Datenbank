#include "database.h"



void CreateEntries(Games_Database* pDatabase)
{
	//Lies Eintrag ein
	
	int input;
	int i;
	
	printf("Wie viele Einträge wollen sie erstellen?\n");
	scanf("%d", &input);
	fflush(stdin);
    
    for(i = 0; i < input; i++)
    {	
    	system("cls");
    	printf("%d. Eintrag\n\n", i + 1);
    	
    	
        printf("\nGib den Namen des Spiels ein.\n");
        scanf("%[^\n]%*c", pDatabase->name);
        fflush(stdin);

        printf("\nGib die Konsole ein.\n");
        scanf("%[^\n]%*c", pDatabase->konsole);
        fflush(stdin);

        printf("\nGib die Spielstunden ein.\n");
        scanf("%f", &(pDatabase->spielStunden));
	    fflush(stdin);
	    
	    printf("\nHast du das Spiel durchgezockt?[Ja/Nein]\n");
        scanf("%s", pDatabase->completed);
	    fflush(stdin);
	    

        up_listeAdd(pDatabase);
	}
	
	printf("\nDatensatz erfolgreich hinzugefügt!");
}



void up_listeAdd(Games_Database* pDatabase)
{
    pDatabase->mom = (Game*)malloc(sizeof(Game));
    up_struct_liste(pDatabase);
    pDatabase->mom->davor = pDatabase->zwischen;
    pDatabase->mom->danach = 0;
    
    if(pDatabase->zwischen == 0)
    {
        pDatabase->start = pDatabase->mom;
    }

    else
    {
        pDatabase->zwischen->danach = pDatabase->mom;
    }
    
    pDatabase->zwischen = pDatabase->mom;
}

void up_struct_liste(Games_Database* pDatabase)
{
    strcpy(pDatabase->mom->name, pDatabase->name);
    strcpy(pDatabase->mom->konsole, pDatabase->konsole);
    pDatabase->mom->spielStunden = pDatabase->spielStunden;
    
    if((strcmp(pDatabase->completed, "Ja") == 0) || (strcmp(pDatabase->completed, "ja") == 0))
	{
		strcpy(pDatabase->mom->completed, "completed");
	}
	else if((strcmp(pDatabase->completed, "Nein") == 0) || (strcmp(pDatabase->completed, "nein") == 0))
	{
		strcpy(pDatabase->mom->completed, "uncompleted");
	}
}

void up_hex(Games_Database* pDatabase)
{
    pDatabase->mom = pDatabase->start;
    while(pDatabase->mom)
    {
        printf("\n--%15s-- %12X %12X %12X", pDatabase->mom->name, pDatabase->mom->davor, pDatabase->mom, pDatabase->mom->danach);
        pDatabase->mom = pDatabase->mom->danach;
    }
}

void up_loesche(Games_Database* pDatabase)
{
	system("cls");
	
    int i = 1;
    int eingabe;

    ausgabe(pDatabase);
    printf("Wählen sie bitte den zu lÃ¶schenden Datensatz aus\n");
    fflush(stdin);
    scanf("%d", &eingabe);
    fflush(stdin);

    pDatabase->mom = pDatabase->start;
    while(pDatabase->mom && i++ < eingabe)
    {
        pDatabase->mom = pDatabase->mom->danach;
    }

    //Fallunterscheidung

    //Kein Datensatz
    if(pDatabase->mom)
    {
        printf("Erstell erstmal nen Datensatz\n");
    }

    //Mitte
    if(pDatabase->mom->danach && pDatabase->mom->davor)
    {
        pDatabase->mom->davor->danach = pDatabase->mom->danach;
        pDatabase->mom->danach->davor = pDatabase->mom->davor;
        free(pDatabase->mom);
        pDatabase->mom = pDatabase->start;
    }

    //Ende
    if(pDatabase->mom->davor)
    {
        pDatabase->mom->davor->danach = 0;
        free(pDatabase->mom);
        pDatabase->mom = pDatabase->start;
    }

    //Anfang
    if(pDatabase->mom->danach)
    {
        pDatabase->mom->danach->davor = 0;
        free(pDatabase->mom);
        pDatabase->mom = pDatabase->start;
    }

    //Einzigste
    else
    {
        printf("Liste ist jetzt leer\n");
    }
}

//Bestimmte anzahl anzeigen
void ausgabe(Games_Database* pDatabase)
{
    pDatabase->mom = pDatabase->start;

    //Print alle - letztes

    //Wenn es keine Datensätze gibt
    if(!pDatabase->mom)
    {
        printf("Erstell erst mal eine Datenbank\n");
    }

    //Es gibt nur eines
    else if(!pDatabase->mom->danach)
    {
        //print mom
        
        tableDesign();
        printf("%20s %10s %12.2f %13s\n\n", pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
    }

	else
	{
		//Mitte
		
		tableDesign();
    	while(pDatabase->mom->danach)
    	{
    	    //print mom
    	    printf("%20s %10s %12.2f %13s\n\n", pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
    	    pDatabase->mom = pDatabase->mom->danach;

    	}

    	//Print Letztes (mom)
    	printf("%20s %10s %12.2f %13s\n\n", pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
	}
}

void printPointers(Games_Database* pDatabase)
{
	printf("%x       start\n", pDatabase->start);
    printf("%x       mom\n", pDatabase->mom);
    printf("%x       zwischen\n", pDatabase->zwischen);
    printf("%x       danach\n", pDatabase->mom->danach);
    printf("%x       davor\n", pDatabase->mom->davor);
    scanf("abc");
}

void tableDesign()
{
	printf("          Game Title    Konsole Spielstunden  durchgezockt\n");
	printf("----------------------------------------------------------\n\n");
}

void readFile(Games_Database* pDatabase)
{
	FILE* einlesen;
    char text[100 + 1];
    char original[100 + 1];
	char file_path[80 + 1];
	int counter = 0;	
	int konsole = 0;
	int spielStunden = 0;
	int completed = 0;
	int index = 0;
	
	
	printf("Bitte geben sie den vollst?ndigen Dateipfad mit Dateiendung an.\n");
	printf("1. Die Dateiendung muss vorhanden sein (z.B. '.txt').\n");
	printf("2. Einfache Backslash(\\) m?ssen mit Doppelten(\\\\) erstetzt werden.\n");
	scanf("%[^\n]%*c", file_path);
	fflush(stdin);
	system("cls");
	

    einlesen = fopen(file_path, "r");

    if(!einlesen)
    {
        printf("Nehm nen gescheiten Dateinamen");
    }

    else
    {
        fgets(text, 100, einlesen);
        
        strcpy(original, text);
        
        while(!feof(einlesen))
        {
        	//Während du noch nicht am Ende des Strings bist
        	while(counter <= 100)
        	{
        		//Wenn du ein Doppel-Leerzeichen gefunden hast
        		if((text[counter] == ' ') && (text[counter + 1] == ' '))
        		{	
        			//Schreib terminierende 0
        			original[counter] = '\0';
        			
        			
        			counter++;
        			
        			while((text[counter] == ' ') && (text[counter + 1] == ' '))
        			{
        				counter++;
					}
        			counter++;
        			
        			//Am Anfang des nächsten Eintrags	
        			if(index == 0)
        			{
        				konsole = counter;
					}
					
					else if(index == 1)
					{
						spielStunden = counter;
					}
					
					else if(index == 2)
					{
						completed = counter;
					}
					
					index++;
					strcpy(text, text + counter);
						
					
				}			
				counter++;
			}
			index = 0;
        
            strcpy(pDatabase->name, original);
            strcpy(pDatabase->konsole, original + konsole);
            pDatabase->spielStunden = atoi(original + spielStunden);
            strcpy(pDatabase->completed, original + completed);
            
            up_listeAdd(pDatabase);
            

            fgets(text, 80, einlesen);
            
            strcpy(original, text);
            
            counter = 0;
        }
        
        //Während du noch nicht am Ende des Strings bist
        while(counter <= 80)
        {
        	//Wenn du ein Doppel-Leerzeichen gefunden hast
        	if((text[counter] == ' ') && (text[counter + 1] == ' '))
        	{	
        		//Schreib terminierende 0
        		original[counter] = '\0';
        		
        		
        		counter++;
        		
        		while((text[counter] == ' ') && (text[counter + 1] == ' '))
        		{
        			counter++;
				}
        		counter++;
        		
        		//Am Anfang des nächsten Eintrags	
        		if(index == 0)
        		{
        			konsole = counter;
				}
				
				else if(index == 1)
				{
					spielStunden = counter;
				}
				
				else if(index == 2)
				{
					completed = counter;
				}
				
				index++;
				strcpy(text, text + counter);	
				
			}			
			counter++;
		}
		
		strcpy(pDatabase->name, original);
        strcpy(pDatabase->konsole, original + konsole);
        pDatabase->spielStunden = atoi(original + spielStunden);
        strcpy(pDatabase->completed, original + completed);
            
    	up_listeAdd(pDatabase);

        fclose(einlesen);
    }	
}

void writeFile(Games_Database* pDatabase)
{
	FILE *fptr;
	char file_path[80 + 1];
	char str[5 + 1];
		
	printf("Bitte gebe den Dateipfad ein\n");
	scanf("%s", file_path);
  	fptr = fopen(file_path, "w+");
	
	system("cls");
	
	if (fptr == NULL) 
	{
	    printf("Error opening file.\n");
	}
	
	else
	{
		if(pDatabase->mom == 0)
		{
			printf("Erstell erst einmal einen Eintrag\n");
		}
		
		else
		{			
			pDatabase->mom = pDatabase->start;
			
			while(pDatabase->mom->danach != 0)
			{
				fputs(pDatabase->mom->name, fptr);
				//print spaces
				fputs(pDatabase->mom->konsole, fptr);
				//print spaces
				itoa(pDatabase->mom->spielStunden, str, 10);
				fputs(str, fptr);
				//print spaces
				fputs(pDatabase->mom->completed, fptr);
				//print spaces
				fputs("\n", fptr);
				
				pDatabase->mom = pDatabase->mom->danach;
			}
			
			fputs(pDatabase->mom->name, fptr);
			fputs(pDatabase->mom->konsole, fptr);
			itoa(pDatabase->mom->spielStunden, str, 10);
			fputs(str, fptr);
				
			printf("Datenbank wurde erfolgreich in Datei geschrieben");
		}
	}
	fclose(fptr);
	
	printf("\n\nPress enter to continue");
	scanf("abc");
	fflush(stdin);
}

void Sort_Logic(char kategory[12 + 1], char algorithm[12 + 1], Games_Database* pDatabase)
{
	int size = 0;
	int i;
	
	if(kategory == 0 || algorithm == 0)
	{
		printf("Du musst zuerst den Sortieralgorithmus und die Kategorie, \nnach der Sortiert werden soll eingeben.\n\n");
		printf("\nPress enter to continue");
		scanf("abc");
		fflush(stdin);
		
		return;
	}
	
	if(pDatabase->mom == 0)
	{
		printf("Erstell erstmal eine Datenbank\n\n");
		
		printf("Press enter to continue");
		scanf("abc");
		fflush(stdin);
		
		return;
	}
	
	//count elements in pDatabase
	pDatabase->mom = pDatabase->start;
	while(pDatabase->mom->danach != 0)
	{
		size++;
		pDatabase->mom = pDatabase->mom->danach;
	}
	size = size + 2;
	
	//Quick-Sort
	if(strcmp(algorithm, "Quick-Sort") == 0)
	{
		if(strcmp(kategory, "Hours_played") == 0)
		{
			quickSortieren(pDatabase, 0, size - 1);
		}
		
		else if(strcmp(kategory, "Platform") == 0 || strcmp(kategory, "Name") == 0)
		{
			quickSortierenNamen(pDatabase, 0, size - 1, kategory);
		}
		

	}
	
	//Bubble-Sort
	if(strcmp(algorithm, "Bubble-Sort") == 0)
	{
		if(strcmp(kategory, "Hours_played") == 0)
		{
			
		}
		
		if(strcmp(kategory, "Platform") == 0)
		{
			
		}
		
		if(strcmp(kategory, "Name") == 0)
		{
			
		}
	}
}

/*----------------Quick Sort--------------*/
void quickSortierenNamen(Games_Database* pDatabase, int links, int rechts, char kategory[80 + 1])
{
	int iLi, iRe, med;
	int i;
	
	char buffer[50 + 1];
	
	Game* tmp1;
	Game* tmp2;
	
	iLi = links;
	iRe = rechts;

	med = (links + rechts) / 2;
	
	
	while(iLi < iRe)
	{
		pDatabase->mom = pDatabase->start;
		for(i = 1; i < med; i++)
		{
			pDatabase->mom = pDatabase->mom->danach;
		}
		
		if(strcmp(kategory, "Platform") == 0)
		{
			strcpy(buffer, pDatabase->mom->konsole);
			//
			
			pDatabase->mom = pDatabase->start;
			for(i = 1; i < iLi; i++)
			{
				pDatabase->mom = pDatabase->mom->danach;
			}
			
			while( strcmp(pDatabase->mom->konsole, buffer) < 0 ) 
			{
				pDatabase->mom = pDatabase->mom->danach;
				iLi++;
			}
			//
			
			pDatabase->mom = pDatabase->start;
			for(i = 1; i < iRe; i++)
			{
				pDatabase->mom = pDatabase->mom->danach;
			}
			
			while( strcmp(pDatabase->mom->konsole, buffer) > 0 )
			{
				pDatabase->mom = pDatabase->mom->davor;
				iRe--;
			}
		}
		
		else if(strcmp(kategory, "Name") == 0)
		{	
			strcpy(buffer, pDatabase->mom->name);
			//
			
			pDatabase->mom = pDatabase->start;
			for(i = 1; i < iLi; i++)
			{
				pDatabase->mom = pDatabase->mom->danach;
			}
			
			while( strcmp(pDatabase->mom->name, buffer) < 0 ) 
			{
				pDatabase->mom = pDatabase->mom->danach;
				iLi++;
			}
			//
			
			pDatabase->mom = pDatabase->start;
			for(i = 1; i < iRe; i++)
			{
				pDatabase->mom = pDatabase->mom->danach;
			}
			
			while( strcmp(pDatabase->mom->name, buffer) > 0 )
			{
				pDatabase->mom = pDatabase->mom->davor;
				iRe--;
			}
		}
		
		
		//Tausche (feld[iLi], feld[iRe])
		swapIt(iLi, iRe, pDatabase);
		
		
		if		(iLi == med)	med = iRe;
		else if	(iRe == med)	med = iLi;
		
		
		if(iLi < med)		iLi++;
		if(iRe > med)		iRe--;
		
	}
	
	if(links < med - 1)
	{
		quickSortierenNamen(pDatabase, links, med - 1, kategory);
	}
	
	if(rechts > med + 1)
	{
		quickSortierenNamen(pDatabase, med + 1, rechts, kategory);
	}
}
/*----------------------------------------*/

void Sort_Menu(Games_Database* pDatabase)
{
	int input;
	char kategory[12 + 1] = { };
	char algorithm[12 + 1] = { };
		
	while(1)
	{	
		printf("Sort by Kategory Sub-Menu\n");
	
		printf("Selected Kategory to sort by : %s\n", kategory);
		printf("Selected Sorting-Algorithm   : %s\n\n", algorithm);
	
		printf("1.) Sort by 'Name'\n");
		printf("2.) Sort by 'Platform'\n");
		printf("3.) Sort by 'Hours_played'\n");
		
		printf("4.) Sort with Quick-Sort\n");
		printf("5.) Sort with Bubble-Sort\n\n");

		
		printf("6.) Sort now\n\n");
		
		printf("7.) Return to Main Menu\n");
	
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
				
			case 4:
				strcpy(algorithm, "Quick-Sort");
				break;
				
			case 5:
				strcpy(algorithm, "Bubble-Sort");
				break;
				
			case 6:
				system("cls");
				Sort_Logic(kategory, algorithm, pDatabase);
				
				printf("\nPress enter to continue");
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

void setMomToSelected(Games_Database* pDatabase, int position)
{
	int i;
	pDatabase->mom = pDatabase->start;
	for(i = 1; i < position; i++)
	{
		pDatabase->mom = pDatabase->mom->danach;
	}
	
}

void swapIt(int left, int right, Games_Database* pDatabase)
{
	Game* rightEntry;
	Game* leftEntry;
	
	
	setMomToSelected(pDatabase, left);
	leftEntry = pDatabase->mom;
	
	setMomToSelected(pDatabase, right);
	rightEntry = pDatabase->mom;
	
	char  tmpName[80 + 1];
	char  tmpKonsole[80 + 1];
	float tmpspielStunden;
	char tmpCompleted[80 + 1];
	
	strcpy(tmpName, leftEntry->name);
	strcpy(tmpKonsole, leftEntry->konsole);
	tmpspielStunden = leftEntry->spielStunden;
	strcpy(tmpCompleted, leftEntry->completed);
	
	strcpy(leftEntry->name, rightEntry->name);
	strcpy(leftEntry->konsole, rightEntry->konsole);
	leftEntry->spielStunden = rightEntry->spielStunden;
	strcpy(leftEntry->completed, rightEntry->completed);
	
	strcpy(rightEntry->name, tmpName);
	strcpy(rightEntry->konsole, tmpKonsole);
	rightEntry->spielStunden = tmpspielStunden;
	strcpy(rightEntry->completed, tmpCompleted);
}

/*----------------Quick Sort--------------*/
void quickSortieren(Games_Database* pDatabase, int links, int rechts)
{
	int iLi, iRe, med;
	float buffer;
	int i;
	
	iLi = links;
	iRe = rechts;

	med = (links + rechts) / 2;
	
	while(iLi < iRe)
	{
		pDatabase->mom = pDatabase->start;
		for(i = 1; i < med; i++)
		{
			pDatabase->mom = pDatabase->mom->danach;
		}
		buffer = pDatabase->mom->spielStunden;
		//
		
		pDatabase->mom = pDatabase->start;
		for(i = 1; i < iLi; i++)
		{
			pDatabase->mom = pDatabase->mom->danach;
		}
		
		while(pDatabase->mom->spielStunden < buffer) 
		{
			pDatabase->mom = pDatabase->mom->danach;
			iLi++;
		}
		//
		
		pDatabase->mom = pDatabase->start;
		for(i = 1; i < iRe; i++)
		{
			pDatabase->mom = pDatabase->mom->danach;
		}
		
		while(pDatabase->mom->spielStunden > buffer)
		{
			pDatabase->mom = pDatabase->mom->davor;
			iRe--;
		}
		
		//Tausche (feld[iLi], feld[iRe])
		swapIt(iLi, iRe, pDatabase);
		
		if		(iLi == med)	med = iRe;
		else if	(iRe == med)	med = iLi;
		
		
		if(iLi < med)		iLi++;
		if(iRe > med)		iRe--;
		
	}
	
	if(links < med - 1)
	{
		quickSortieren(pDatabase, links, med - 1);
	}
	
	if(rechts > med + 1)
	{
		quickSortieren(pDatabase, med + 1, rechts);
	}
}
/*----------------------------------------*/

