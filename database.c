#include "database.h"



void Create_Entries(Games_Database* pDatabase)
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
	    

        Liste_Add(pDatabase);
	}
	
	printf("\nDatensatz erfolgreich hinzugefügt!");
}



void Liste_Add(Games_Database* pDatabase)
{
    pDatabase->mom = (Game*)malloc(sizeof(Game));
    Struct_Liste(pDatabase);
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

void Struct_Liste(Games_Database* pDatabase)
{
    strcpy(pDatabase->mom->name, pDatabase->name);
    strcpy(pDatabase->mom->konsole, pDatabase->konsole);
    pDatabase->mom->spielStunden = pDatabase->spielStunden;
    
    if((strcmp(pDatabase->completed, "Ja") == 0) || (strcmp(pDatabase->completed, "ja") == 0) || (strcmp(pDatabase->completed, "completed") == 0))
	{
		strcpy(pDatabase->mom->completed, "completed");
	}
	else if((strcmp(pDatabase->completed, "Nein") == 0) || (strcmp(pDatabase->completed, "nein") == 0) || (strcmp(pDatabase->completed, "uncompleted") == 0))
	{
		strcpy(pDatabase->mom->completed, "uncompleted");
	}
}

void hex(Games_Database* pDatabase)
{
    pDatabase->mom = pDatabase->start;
    while(pDatabase->mom)
    {
        printf("\n%30s %12X %12X %12X", pDatabase->mom->name, pDatabase->mom->davor, pDatabase->mom, pDatabase->mom->danach);
        pDatabase->mom = pDatabase->mom->danach;
    }
}

void delete(Games_Database* pDatabase)
{
	system("cls");
	
	//Kein Datensatz
    if(!pDatabase->mom)
    {
        printf("Erstell erstmal nen Datensatz\n");
        
        return;
    }
	
    int i = 1;
    int eingabe;
    int von;
    int von2;
    int bis;

    output(pDatabase);
    printf("W\x84hlen sie bitte den zu l\x94schenden Datensatz aus\n");
    printf("W\x84hlen sie die '0', um mehrfach zu l\x94schen\n");
    scanf("%d", &eingabe);
    fflush(stdin);

	if(eingabe == 0)
	{
		system("cls");
		printf("Von: ");
		scanf("%d", &von);
		printf("\nBis: ");
		scanf("%d", &bis);
		
		von2 = von;		
	
   		//Fallunterscheidung

		while(von <= bis)
		{
			i = 1;
			pDatabase->mom = pDatabase->start;
    		while(pDatabase->mom && i++ < von2)
    		{
    	    	pDatabase->mom = pDatabase->mom->danach;
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
    		else if(pDatabase->mom->davor)
    		{
    		    pDatabase->mom->davor->danach = 0;
    		    free(pDatabase->mom);
    		    pDatabase->mom = pDatabase->start;
    		}
		
		    //Anfang
		    else if(pDatabase->mom->danach)
		    {
		        pDatabase->mom->danach->davor = 0;
		        pDatabase->start = pDatabase->mom->danach;
		        free(pDatabase->mom);
		        pDatabase->mom = pDatabase->start;
		    }
		
	    	//Einzigste
	    	else
	    	{
	    		free(pDatabase->mom);
	    		pDatabase->mom = 0;
	    		pDatabase->start = 0;
	    		pDatabase->zwischen = 0;
	    	    printf("Liste ist jetzt leer\n");
	    	}
	    	
	    	von++;
		}
		printf("Eintr\x84ge erfolgreich gel\x94scht");
	}

	else
	{
    	pDatabase->mom = pDatabase->start;
    	while(pDatabase->mom && i++ < eingabe)
    	{
    	    pDatabase->mom = pDatabase->mom->danach;
    	}

	    //Fallunterscheidung
	
	
	    //Mitte
	    if(pDatabase->mom->danach && pDatabase->mom->davor)
	    {
	        pDatabase->mom->davor->danach = pDatabase->mom->danach;
	        pDatabase->mom->danach->davor = pDatabase->mom->davor;
	        free(pDatabase->mom);
	        pDatabase->mom = pDatabase->start;
	        printf("Eintrag erfolgreich gel\x94scht");
	    }
	
	    //Ende
	    else if(pDatabase->mom->davor)
	    {
	        pDatabase->mom->davor->danach = 0;
	        free(pDatabase->mom);
	        pDatabase->mom = pDatabase->start;
	        printf("Eintrag erfolgreich gel\x94scht");
	    }
	
	    //Anfang
	    else if(pDatabase->mom->danach)
	    {
	        pDatabase->mom->danach->davor = 0;
	        pDatabase->start = pDatabase->mom->danach;
	        free(pDatabase->mom);
	        pDatabase->mom = pDatabase->start;
	        printf("Eintrag erfolgreich gel\x94scht");
	    }
	
    	//Einzigste
    	else
    	{
    		free(pDatabase->mom);
    		pDatabase->mom = 0;
    		pDatabase->start = 0;
    		pDatabase->zwischen = 0;
    	    printf("Liste ist jetzt leer");
   		}
	}
	printf("\n\nDr\x81""cke Enter um fortzufahren");
	scanf("abc");
	fflush(stdin);
}

void Table_Design()
{
	printf(" Nr.                    Game Titel    Konsole Spielstunden  durchgezockt\n");
	printf("-----------------------------------------------------------------------\n\n");
}

void Read_File(Games_Database* pDatabase)
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
	
	
	printf("Bitte geben sie den vollst\x84ndigen Dateipfad mit Dateiendung an.\n");
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
        
        while((text[0] =='*') && (text[1] =='*') && (text[2] =='*'))
        {
        	fgets(text, 100, einlesen);
		}
        
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
						while(original[counter] != 'd')
						{
							counter++;
						}
						counter++;
						original[counter] = '\0';
					}
					
					index++;
						
					
				}			
				counter++;
			}
			index = 0;
        
            strcpy(pDatabase->name, original);
        	strcpy(pDatabase->konsole, original + konsole);
        	pDatabase->spielStunden = atoi(original + spielStunden);
        	strcpy(pDatabase->completed, original + completed);
            
    		Liste_Add(pDatabase);
            

            fgets(text, 80, einlesen);
            
            strcpy(original, text);
            
            counter = 0;
        }
        
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
					while(original[counter] != 'd')
					{
						counter++;
					}
					counter++;
					original[counter] = '\0';
				}
				
				index++;	
				
			}			
			counter++;
		}
		
		strcpy(pDatabase->name, original);
        strcpy(pDatabase->konsole, original + konsole);
        pDatabase->spielStunden = atoi(original + spielStunden);
        strcpy(pDatabase->completed, original + completed);
            
    	Liste_Add(pDatabase);

        fclose(einlesen);
    }	
}

void Write_File(Games_Database* pDatabase)
{
	FILE *fptr;
	char file_path[80 + 1];
	char str[5 + 1];
	int i;
	int length;
		
	printf("Bitte gebe den Dateipfad ein\n");
	scanf("%s", file_path);
  	fptr = fopen(file_path, "w+");
	
	system("cls");
	
	if (fptr == NULL) 
	{
	    printf("Datei konnte nicht geöffnet werden.\n");
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
				length = 30 - strlen(pDatabase->mom->name);
				for(i = 0; i < length; i++)
				{
					fputs(" ", fptr);
				}
				
				fputs(pDatabase->mom->konsole, fptr);
				length = 10 - strlen(pDatabase->mom->konsole);
				for(i = 0; i < length; i++)
				{
					fputs(" ", fptr);
				}
				
				itoa(pDatabase->mom->spielStunden, str, 10);
				fputs(str, fptr);
				length = 15 - strlen(str);
				for(i = 0; i < length; i++)
				{
					fputs(" ", fptr);
				}

				fputs(pDatabase->mom->completed, fptr);
				length = 13 - strlen(pDatabase->mom->completed);
				for(i = 0; i < length; i++)
				{
					fputs(" ", fptr);
				}

				fputs("\n", fptr);
				
				pDatabase->mom = pDatabase->mom->danach;
			}
			
			fputs(pDatabase->mom->name, fptr);
			length = 30 - strlen(pDatabase->mom->name);
			for(i = 0; i < length; i++)
			{
				fputs(" ", fptr);
			}
			
			fputs(pDatabase->mom->konsole, fptr);
			length = 10 - strlen(pDatabase->mom->konsole);
			for(i = 0; i < length; i++)
			{
				fputs(" ", fptr);
			}
			
			itoa(pDatabase->mom->spielStunden, str, 10);
			fputs(str, fptr);
			length = 15 - strlen(str);
			for(i = 0; i < length; i++)
			{
				fputs(" ", fptr);
			}

			fputs(pDatabase->mom->completed, fptr);
			length = 13 - strlen(pDatabase->mom->completed);
			for(i = 0; i < length; i++)
			{
				fputs(" ", fptr);
			}
		}
	}
	fclose(fptr);
	
	printf("Datenbank wurde erfolgreich in Datei exportiert\n\n");
}

void Sort_Logic(Games_Database* pDatabase, char algorithm[12 + 1], char category[12 + 1])
{
	int size = 0;
	int i;
	
	if(category == 0 || algorithm == 0)
	{
		printf("Du musst zuerst den Sortieralgorithmus und die Kategorie, \nnach der sortiert werden soll eingeben.\n\n");
		printf("\nDr\x81""cke Enter um fortzufahren");
		scanf("abc");
		fflush(stdin);
		
		return;
	}
	
	if(pDatabase->mom == 0)
	{
		printf("Erstell erstmal eine Datenbank\n\n");
		
		printf("Dr\x81""cke Enter um fortzufahren");
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
	
	//Quick-Sort
	if(strcmp(algorithm, "Quick-Sort") == 0)
	{
		if(strcmp(category, "Spielstunden") == 0)
		{
			Quick_Sort(pDatabase, 1, size + 1);
			printf("Datenbank erfolgreich sortiert\n");
		}
		
		else if(strcmp(category, "Platform") == 0 || strcmp(category, "Name") == 0)
		{
			Quick_Sort_Names(pDatabase, 1, size + 1, category);
			printf("Datenbank erfolgreich sortiert\n");
		}
		

	}
	
	//Bubble-Sort
	if(strcmp(algorithm, "Bubble-Sort") == 0)
	{
		if(strcmp(category, "Spielstunden") == 0)
		{	
			Bubble_Sortieren(pDatabase,size - 1);
			printf("Datenbank erfolgreich sortiert\n");
		}
		
		if(strcmp(category, "Platform") == 0 || strcmp(category, "Name") == 0)
		{
			Bubble_Sortieren_Namen(pDatabase,size - 1, category);
			printf("Datenbank erfolgreich sortiert\n");
		}
	}
}

/*----------------Quick Sort--------------*/
void Quick_Sort_Names(Games_Database* pDatabase, int left, int right, char category[80 + 1])
{
	int iLi, iRe, med;
	int i;
	
	char buffer[50 + 1];
	
	Game* tmp1;
	Game* tmp2;
	
	iLi = left;
	iRe = right;

	med = (left + right) / 2;
	
	
	while(iLi < iRe)
	{	
		pDatabase->mom = pDatabase->start;
		for(i = 1; i < med; i++)
		{
			pDatabase->mom = pDatabase->mom->danach;
		}
		
		if(strcmp(category, "Platform") == 0)
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
		
		else if(strcmp(category, "Name") == 0)
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
		Swap_Entries(pDatabase, iLi, iRe);
		
		
		
		if		(iLi == med)	med = iRe;
		else if	(iRe == med)	med = iLi;
		
		
		if(iLi < med)		iLi++;
		if(iRe > med)		iRe--;
		
	}
	
	if(left < med - 1)
	{
		Quick_Sort_Names(pDatabase, left, med - 1, category);
	}
	
	if(right > med + 1)
	{
		Quick_Sort_Names(pDatabase, med + 1, right, category);
	}
}
/*----------------------------------------*/



void Set_Mom_To_Selected(Games_Database* pDatabase, int position)
{
	int i;
	pDatabase->mom = pDatabase->start;
	for(i = 1; i < position; i++)
	{
		pDatabase->mom = pDatabase->mom->danach;
	}
	
}

/*----------------Quick Sort--------------*/
void Quick_Sort(Games_Database* pDatabase, int left, int right)
{
	int iLi, iRe, med;
	float buffer;
	int i;
	
	iLi = left;
	iRe = right;

	med = (left + right) / 2;
	
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
		Swap_Entries(pDatabase, iLi, iRe);
		
		if		(iLi == med)	med = iRe;
		else if	(iRe == med)	med = iLi;
		
		
		if(iLi < med)		iLi++;
		if(iRe > med)		iRe--;
		
	}
	
	if(left < med - 1)
	{
		Quick_Sort(pDatabase, left, med - 1);
	}
	
	if(right > med + 1)
	{
		Quick_Sort(pDatabase, med + 1, right);
	}
}
/*----------------------------------------*/


void Output_Menu(Games_Database* pDatabase,int numOutput)
{
	pDatabase->mom = pDatabase->start;
	int input;
	int i;
    //Print alle - letztes

    //Wenn es keine Datensätze gibt
    if(!pDatabase->mom)
    {
        printf("Erstell erst mal eine Datenbank\n\n");
        
        printf("Dr\x81""cke Enter um fortzufahren");
        scanf("abc");
        fflush(stdin);
    }

    //Es gibt nur eines
    else if(!pDatabase->mom->danach)
    {
        //print mom
        
        Table_Design();
        printf("%30s %10s %12.2f %13s\n\n", pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
    }

	else
	{
		while(1)
		{
			//Mitte
			pDatabase->mom = pDatabase->start;
			i = 0;
			
			Table_Design();
			
    		while((pDatabase->mom->danach) && (i < numOutput - 1))
    		{
    		   	//print mom
    		    printf("%3d %30s %10s %12.2f %13s\n\n",i + 1,  pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
    		    pDatabase->mom = pDatabase->mom->danach;
    		    i++;  
    		}
    		//Print Letztes (mom)
    		printf("%3d %30s %10s %12.2f %13s\n\n", i + 1, pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
    		
    		printf("\nAnzahl angezeigter Elemente: %d\n", numOutput);
    		printf("1) Wollen sie die Anzahl der gezeigen Elemente \x84ndern?\n");
    		printf("2) Zum Hauptmen\x81 zur\x81""ckkehren.\n");
    		
    		scanf("%d", &input);
    		fflush(stdin);
    		
    		if(input == 1)
    		{
    			system("cls");
    			printf("Wie viele Elemente wollen sie anzeigen: ");
    			scanf("%d", &input);
    			fflush(stdin);
    			numOutput = input;
    			system("cls");
			}
    		else if(input == 2)
    		{
    			return;
			}
		}
	}
}

void output(Games_Database* pDatabase)
{
	int i = 1;
	
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
        
        Table_Design();
        printf("%3d %30s %10s %12.2f %13s\n\n", i, pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
    }

	else
	{
		//Mitte
		Table_Design();
    	while(pDatabase->mom->danach)
    	{
    	   	//print mom
    	    printf("%3d %30s %10s %12.2f %13s\n\n", i, pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
    	    pDatabase->mom = pDatabase->mom->danach;
    	    i++;
    	}
    	//Print Letztes (mom)
    	printf("%3d %30s %10s %12.2f %13s\n\n", i, pDatabase->mom->name, pDatabase->mom->konsole, pDatabase->mom->spielStunden, pDatabase->mom->completed);
	}
}

void Swap_Entries(Games_Database* pDatabase, int left, int right)
{	
	Game* tmp1;
	Game* tmp2;

	//Wenn es keine einträge gibt	
	if(!pDatabase->start)
	{
		printf("Erstell erstmal eine Datenbank");
		return;
	}
	
	Set_Mom_To_Selected(pDatabase, right);
	pDatabase->zwischen = pDatabase->mom;

	Set_Mom_To_Selected(pDatabase, left);
	
	//If left and right is the same
	if(left == right)
	{
		return;
	}
	
	//if there is only one entry
	else if(!pDatabase->start->danach && !pDatabase->start->davor)
	{
		printf("Wie willst du einen einzelnen Eintrag sortieren(-_-)\n");
	}

	//Left is first, Right is last
	else if(!pDatabase->mom->davor && !pDatabase->zwischen->danach)
	{	
		//Left->danach == right
		if(pDatabase->mom->danach == pDatabase->zwischen)
		{
			pDatabase->zwischen->davor  		= 0;
			pDatabase->zwischen->danach 		= pDatabase->mom;
			
			pDatabase->mom->danach 				= 0;
			pDatabase->mom->davor  				= pDatabase->zwischen;
			
			pDatabase->start 					= pDatabase->zwischen;
		}
		
		else
		{
			pDatabase->mom->danach->davor  		= pDatabase->zwischen;
			pDatabase->zwischen->davor->danach  = pDatabase->mom;
		
			pDatabase->zwischen->davor  		= 0;
			pDatabase->zwischen->danach 		= pDatabase->mom;
			
			pDatabase->mom->danach 				= 0;
			pDatabase->mom->davor  				= pDatabase->zwischen;
			
			pDatabase->start 					= pDatabase->zwischen;
		}
		
	}

	//Left is first
	else if(!pDatabase->mom->davor)
	{	
		//Left->danach == right
		if(pDatabase->mom->danach == pDatabase->zwischen)
		{	
			pDatabase->zwischen->danach->davor 	= pDatabase->mom;
			
			pDatabase->mom->davor  				= pDatabase->zwischen;
			pDatabase->mom->danach 				= pDatabase->zwischen->danach;
			
			pDatabase->zwischen->danach 		= pDatabase->mom;
			pDatabase->zwischen->davor  		= 0;
		
			pDatabase->start 					= pDatabase->zwischen;
		}
		
		else
		{
			tmp1								= pDatabase->mom->danach;
			
			pDatabase->zwischen->danach->davor  = pDatabase->mom;
			pDatabase->zwischen->davor->danach  = pDatabase->mom;
			
			pDatabase->mom->danach->davor 		= pDatabase->zwischen;
			
			pDatabase->mom->danach 				= pDatabase->zwischen->danach;
			pDatabase->mom->davor 				= pDatabase->zwischen->davor;
			
			pDatabase->zwischen->danach			= tmp1;
			pDatabase->zwischen->davor 			= 0;
			
			pDatabase->start 					= pDatabase->zwischen;
		}
		
	}
	//Right is last
	else if(!pDatabase->zwischen->danach)
	{
		//Left->danach == right
		if(pDatabase->mom->danach == pDatabase->zwischen)
		{		
			pDatabase->mom->davor->danach 		= pDatabase->zwischen;
			
			pDatabase->zwischen->davor 			= pDatabase->mom->davor;
			pDatabase->zwischen->danach 		= pDatabase->mom;
				
			pDatabase->mom->davor 				= pDatabase->zwischen;
			pDatabase->mom->danach 				= 0;
		}
		
		else
		{
			tmp1								= pDatabase->zwischen->davor;
				
			pDatabase->mom->danach->davor   	= pDatabase->zwischen;
			pDatabase->mom->davor->danach   	= pDatabase->zwischen;
			
			pDatabase->zwischen->davor->danach 	= pDatabase->mom;
			
			pDatabase->zwischen->danach 		= pDatabase->mom->danach;
			pDatabase->zwischen->davor 			= pDatabase->mom->davor;
			
			pDatabase->mom->davor				= tmp1;
			pDatabase->mom->danach 				= 0;
		}
	}
	
	
	
	//Nothing special
	else
	{
		//Left->danach == right
		if(pDatabase->mom->danach == pDatabase->zwischen)
		{
			pDatabase->mom->davor->danach 		= pDatabase->zwischen;
			pDatabase->zwischen->danach->davor  = pDatabase->mom;
			
			pDatabase->mom->danach 				= pDatabase->zwischen->danach;
			
			pDatabase->zwischen->danach 		= pDatabase->mom;
			pDatabase->zwischen->davor 			= pDatabase->mom->davor;
			
			pDatabase->mom->davor 				= pDatabase->zwischen;
		}
		
		else
		{
			tmp1 = pDatabase->mom->davor;
			tmp2 = pDatabase->mom->danach;
			
			pDatabase->mom->davor->danach 		= pDatabase->zwischen;
			pDatabase->mom->danach->davor 		= pDatabase->zwischen;
			
			pDatabase->zwischen->davor->danach  = pDatabase->mom;
			pDatabase->zwischen->danach->davor  = pDatabase->mom;
			
			pDatabase->mom->davor 				= pDatabase->zwischen->davor;
			pDatabase->mom->danach 				= pDatabase->zwischen->danach;
			
			pDatabase->zwischen->davor 			= tmp1;
			pDatabase->zwischen->danach 		= tmp2;
		}
	}
}

void Bubble_Sortieren(Games_Database* pDatabase, int length)
{
	int i, j, tmp;
	
	for(i = 0; i < length; i++)
	{
		pDatabase->mom = pDatabase->start;
		
		for(j = 0; j < length - i; j++)
		{
			Set_Mom_To_Selected(pDatabase, j);
			
			if(pDatabase->mom->spielStunden > pDatabase->mom->danach->spielStunden)
			{
				//Tausche j und j+1
				Swap_Entries_Lite(pDatabase, j, j + 1);
			}
		}
	}
}

void Swap_Entries_Lite(Games_Database* pDatabase, int left, int right)
{	
	Game* tmp1;
	Game* tmp2;

	//Wenn es keine einträge gibt	
	if(!pDatabase->start)
	{
		printf("Erstell erstmal eine Datenbank");
		return;
	}

	Set_Mom_To_Selected(pDatabase, right);
	pDatabase->zwischen = pDatabase->mom;

	Set_Mom_To_Selected(pDatabase, left);
	
	//if there is only one entry
	if(!pDatabase->start->danach && !pDatabase->start->davor)
	{
		printf("Wie willst du einen einzelnen Eintrag sortieren(-_-)\n");
	}

	//Left is first, Right is last
	else if(!pDatabase->mom->davor && !pDatabase->zwischen->danach)
	{
		pDatabase->zwischen->davor  = 0;
		pDatabase->zwischen->danach = pDatabase->mom;
		
		pDatabase->mom->danach 		= 0;
		pDatabase->mom->davor  		= pDatabase->zwischen;
		
		pDatabase->start 			= pDatabase->zwischen;
	}

	//Left is first
	else if(!pDatabase->mom->davor)
	{	
		//Left->danach == right
		if(pDatabase->mom->danach == pDatabase->zwischen)
		{
			pDatabase->zwischen->danach->davor 			= pDatabase->mom;
			
			pDatabase->mom->davor  				= pDatabase->zwischen;
			pDatabase->mom->danach 				= pDatabase->zwischen->danach;
			
			pDatabase->zwischen->danach 		= pDatabase->mom;
			pDatabase->zwischen->davor  		= 0;
		
			pDatabase->start 					= pDatabase->zwischen;
		}
	}
	//Right is last
	else if(!pDatabase->zwischen->danach)
	{
		
		//Left->danach == right
		if(pDatabase->mom->danach == pDatabase->zwischen)
		{		
			pDatabase->mom->davor->danach 		= pDatabase->zwischen;
			
			pDatabase->zwischen->davor 			= pDatabase->mom->davor;
			pDatabase->zwischen->danach 		= pDatabase->mom;
				
			pDatabase->mom->davor 				= pDatabase->zwischen;
			pDatabase->mom->danach 				= 0;
		}
	}
	
	
	
	//Nothing special
	else
	{
		//Left->danach == right
		if(pDatabase->mom->danach == pDatabase->zwischen)
		{
			pDatabase->mom->davor->danach 		= pDatabase->zwischen;
			pDatabase->zwischen->danach->davor  = pDatabase->mom;
			
			pDatabase->mom->danach 				= pDatabase->zwischen->danach;
			
			pDatabase->zwischen->danach 		= pDatabase->mom;
			pDatabase->zwischen->davor 			= pDatabase->mom->davor;
			
			pDatabase->mom->davor 				= pDatabase->zwischen;
		}
	}
}

void Bubble_Sortieren_Namen(Games_Database* pDatabase, int length, char category[20 + 1])
{
	int i, j, tmp;
	if(strcmp(category, "Platform") == 0)
	{
		for(i = 0; i < length; i++)
		{
			pDatabase->mom = pDatabase->start;
		
			for(j = 0; j < length - i; j++)
			{
				Set_Mom_To_Selected(pDatabase, j);
			
				if(strcmp(pDatabase->mom->konsole, pDatabase->mom->danach->konsole) > 0)
				{
					//Tausche j und j+1
					Swap_Entries_Lite(pDatabase, j, j + 1);
				}
			}
		}
	}
	
	else if(strcmp(category, "Name") == 0)
	{
		for(i = 0; i < length; i++)
		{
			pDatabase->mom = pDatabase->start;
		
			for(j = 0; j < length - i; j++)
			{
				Set_Mom_To_Selected(pDatabase, j);
			
				if(strcmp(pDatabase->mom->name, pDatabase->mom->danach->name) > 0)
				{
					//Tausche j und j+1
					Swap_Entries_Lite(pDatabase, j, j + 1);
				}
			}
		}
	}
}


