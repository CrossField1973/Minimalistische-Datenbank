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
        printf("\n%-10s %12X %12X %12X", pDatabase->mom->name, pDatabase->mom->davor, pDatabase->mom, pDatabase->mom->danach);
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

//BEstimmte anzahl anzeigen
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
	char file_path[80 + 1];
	
	printf("Bitte geben sie den vollständigen Dateipfad mit Dateiendung u an.\n");
	printf("1. Die Dateiendung muss vorhanden sein (z.B. '.txt').\n");
	printf("2. Einfache Backslash(\\) müssen mit Doppelten(\\\\) erstetzt werden.\n");
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
    	char* ptr;
		int counter = 0;	

        fgets(text, 80, einlesen);
        while(!feof(einlesen))
        {
        	ptr = strtok(text, "   ");
        	printf("%s", ptr);
        	
        	//TESTTEST	
			while(ptr != 0)
			{	
		
    			ptr = strtok(text, "   ");
    			if(counter == 0)
    			{
    				printf("%s", ptr);
    			    strcpy(pDatabase->name, ptr);
    			}

    			else if(counter == 1)
    			{	
    				printf("%s", ptr);
    			    strcpy(pDatabase->konsole, ptr);
    			}
		
	    		else if(counter == 2)
	    		{
	    			printf("%s", ptr);
	    	    	pDatabase->spielStunden = atoi(ptr);	
    			}
	
    			else if(counter == 3)
    			{
    				printf("%s", ptr);
    		    	strcpy(pDatabase->completed, ptr);
    			}
			
    			counter++;
			}
			printf("%s %s %f %s", pDatabase->name, pDatabase->konsole, pDatabase->spielStunden, pDatabase->completed);
			
			scanf("abc");
			fflush(stdin);
        	
        	counter = 0;
        	//TESTTEST
        	
            printf("%s", text);
            fgets(text, 80, einlesen);
        }
        
        printf("%s", text);

        fclose(einlesen);
    }
}


