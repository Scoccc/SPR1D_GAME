#include "mchlib.h"
#ifdef _WIN32
void initMultiPiattaforma()
{
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), 0b111);//Permette di usare correttamente gli escape codes ANSI anche sul terminale Windows
    SetConsoleOutputCP(CP_UTF8); //Permette di usare i caratteri UTF-8 su windows
}

#else

void initMultiPiattaforma() {}

#endif

void premereInvio()
{
    printf(P_FG_GREEN "Premere invio per continuare...\n" P_RESET);
    //Pulizia del buffer
    fflush(stdin);
    fflush(stdout);

    while (getchar() != '\n');//Si rimane all'interno del ciclo finché il carattere letto è diverso da INVIO.
}

void font_title(char* title, Colore color)
{
    int i;

    //angolo superiore a sinistra
    printf("╔");

    //lato superiore
    for (i = 0; i < strlen(title) + 2; ++i)
        printf("═");

    //angolo superiore a destra
    printf("╗\n");

    //lato a sinistra
    printf("║ ");

    //stringa da stampare del colore scelto
    font_changeFGColor(color);
    printf("%s", title);
    font_reset();

    //lato a destra
    printf(" ║\n");

    //angolo in basso a sinistra
    printf("╚");

    //lato inferiore
    for (i = 0; i < strlen(title) + 2; ++i)
        printf("═");

    //angolo inferiore a destra
    printf("╝\n");
    printf("\n");
}

void font_Bold() { printf("\033[1m"); }

void font_changeFGColor(Colore color)
{
    if (isInRange((int) color, FG_BLACK, FG_WHITE) || isInRange((int) color, FG_BRIGHT_BLACK, FG_BRIGHT_WHITE))
        printf("\033[%dm",color);
    else
    {
        printf("\033[%dm",FG_RED);
        font_Bold();
        printf("COLORE NON VALIDO!");
        font_reset();
    }
}

void font_changeBGColor(Colore color)
{
    if (isInRange((int) color, BG_BLACK, BG_WHITE) || isInRange((int) color, BG_BRIGHT_BLACK, BG_BRIGHT_WHITE))
        printf("\033[%dm",color);
    else
    {
        printf("\033[%dm",FG_RED);
        font_Bold();
        printf("COLORE NON VALIDO!");
        font_reset();
    }

}

void font_reset() { printf("\033[0m"); }

int randNumInRange(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int isInRange(int n, int min, int max)
{
    return n >= min && n <= max;
}

int getIntInRange(const char* message,int min, int max)
{
    int range_max, range_min, num;
    char str[NUMBUFF];
    char* ptr;

    if(min > max) //Se il minimo passato è maggione del massimo passato vanno invertiti
    {
        range_max = max;
        range_min = min;
    }
    else
    {
        range_max = min;
        range_min = max;
    }

    do
    {
        fflush(stdin); //Pulizia del buffer
        fgets(str,NUMBUFF,stdin); //Lettura della stringa dal buffer

        num = strtol(str, &ptr, 10);//Conversione della stringa a numero

        if (ptr == str) //Se è stata inserita una stringa e nessun numero (il puntatore al primo carattere coincide all'inizio della stringa ricevuta)
            printf("Inserire un numero\n");

        else if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE) //è stato passato un numero intero troppo grande (sia tra i positivi che tra i negativi)
            printf("Numero troppo grande\n");

        else if(num < range_max || num > range_min) //Il numero è fuori dal range ricevuto
            printf("%s\n",message); //Stampa del messaggio ricevuto tramite parametro
    }
    while (num < range_max || num > range_min || (ptr == str) || ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)); //Unione di tutte l condizioni di errore

    return num;
}

void clearScreen()
{
    printf("\033[1;1H\033[2J");
}

_Bool getYesNo()
{
    char c;

    do
    {
        fflush(stdin); //Pulizia del buffer
        c = (char) getchar(); //lettura del carattere
        c = toLower(c); //Il carattere si rende minuscolo

        if(c != 'y' && c != 'n' && c != 's') //Se il carattere non è valido
            printf("Inserire 'si', 's', 'yes' oppure 'y' per confermare\nInserire 'no' oppure 'n' per negare\n");
    }
    while (c != 'y' && c != 'n' && c != 's'); //Il ciclo si ripete finchè non viene inserito un carattere valido

    return c == 'y' || c == 's'; // 'y' o 's' equivale a true, altrimenti false
}

int numRigheFile(char* filePath)
{
    FILE* fp;
    int i = 0;
    char riga[BUFFSZ];
    fp = fopen(filePath,"r");
    if(fp == NULL)
    {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }

    while(fgets(riga,BUFFSZ,fp)) { i++; }

    fclose(fp);
    return i;
}

char toUpper(char c)
{
    if(isInRange(c, 'a', 'z'))
        c -= OFFSET;
    return c;
}

char toLower(char c)
{
    if(isInRange(c, 'A', 'Z'))
        c += OFFSET;
    return c;
}

_Bool IsCharInString(const char* stringa, char lettera)
{
    int i;
    for (i = 0; i < strlen(stringa); ++i)
        if(toLower(stringa[i]) == lettera)
            return true; //Carattere trovato
    return false; //Carattere non trovato
}
