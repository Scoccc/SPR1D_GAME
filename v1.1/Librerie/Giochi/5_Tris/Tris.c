#include "Tris.h"

void printGriglia(int griglia[SIZE][SIZE], Gruppo gruppo)
{
    int i,j;
    char carattere[] = {'X','O'};
    printf("\n");
    for (i = 0; i < SIZE; ++i)
    {
        for (j = 0; j < SIZE; ++j)
        {
            if(griglia[i][j] == BLANK_SPACE)
            {
                font_changeFGColor(FG_BRIGHT_BLACK);
                printf(" %d ", i*SIZE+j+1);
            }
            else
            {
                font_changeFGColor(getColoreFromID(gruppo.id_membri[griglia[i][j]]));
                printf(" %c ", carattere[griglia[i][j]]);
            }
            font_reset();
            if(j == SIZE - 1)
                printf("\n");
            else
                printf("│");
        }
        if(i < SIZE - 1)
            printf("───┼───┼───\n");
    }
}

int game_Tris(Gioco* game, Gruppo gruppo)
{
    int griglia[SIZE][SIZE] = {};
    int row, col, id_vincitore;
    Turno index_turno = indexLowestIDinGruppo(gruppo);
    _Bool finita = false;

    font_title("TRIS", FG_CYAN);

    clearGriglia(griglia);

    while(!finita)
    {
        printf("Turno di ");
        printNomefromID(game, gruppo.id_membri[index_turno]);
        printf("\n");

        printGriglia(griglia, gruppo);
        printf("\n");

        if(isCPU(game, gruppo.id_membri[index_turno]))
            turnoCPU_tris(griglia,&col,&row);
        else
            turnoPlayer_tris(griglia,&col,&row);

        griglia[row][col] = index_turno;

        clearScreen();

        font_title("TRIS",FG_CYAN);

        if(ceckVittoria(griglia,index_turno,row,col))
        {
            printf("Partita finita!\n");
            printGriglia(griglia, gruppo);
            id_vincitore = gruppo.id_membri[index_turno];
            finita = true;
        }
        else if(isGrigliaPiena(griglia))
        {
            printf("PAREGGIO\n");
            printGriglia(griglia, gruppo);
            printf("\n");
            premereInvio();
            clearScreen();
            clearGriglia(griglia);
            font_title("TRIS",FG_CYAN);
            // Nel caso di pareggio l'ultima mossa sarà sempre quella di chi ha
            // iniziato, quindi non servono controlli aggiuntivi per vedere chi
            // inizierà la prossima partita, basta solo cambiare il turno
        }
        cambiaTurno(&index_turno,NUMPLAYERS_TRIS);
    }

    return id_vincitore;
}

void clearGriglia(int griglia[SIZE][SIZE])
{
    int i,j;
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE; ++j)
            griglia[i][j] = BLANK_SPACE;
}

_Bool ceckVittoriaVerticale(int griglia[SIZE][SIZE], int last_col, Turno turno)
{
    int i;
    for (i = 0; i < SIZE; ++i)
        if(griglia[i][last_col] != turno)
            return false;
    return true;
}

_Bool ceckVittoriaOrizzontale(int griglia[SIZE][SIZE], int last_row, Turno turno)
{
    int i;
    for (i = 0; i < SIZE; ++i)
        if(griglia[last_row][i] != turno)
            return false;
    return true;
}

_Bool ceckVittoriaDiagonaleDecrescente(int griglia[SIZE][SIZE], Turno turno)
{
    int i;
    for (i = 0; i < SIZE; ++i)
        if(griglia[i][i] != turno)
            return false;
    return true;
}

_Bool ceckVittoriaDiagonaleCrescente(int griglia[SIZE][SIZE], Turno turno)
{
    int i;
    for (i = 0; i < SIZE; ++i)
        if(griglia[SIZE - i - 1][i] != turno)
            return false;
    return true;
}

_Bool ceckVittoria(int griglia[SIZE][SIZE], Turno turno, int row, int col)
{
    return ceckVittoriaVerticale(griglia,col,turno) ||
           ceckVittoriaOrizzontale(griglia,row,turno) ||
           ceckVittoriaDiagonaleCrescente(griglia,turno) ||
           ceckVittoriaDiagonaleDecrescente(griglia,turno);
}

_Bool isGrigliaPiena(int griglia[SIZE][SIZE])
{
    int i,j;
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE; ++j)
            if(griglia[i][j] == BLANK_SPACE)
                return false;
    return true;
}

void turnoPlayer_tris(int griglia[SIZE][SIZE], int *col, int *row)
{
    int posizione;
    do
    {
        printf("Dove vuoi disegnare?\n");
        posizione = getIntInRange("Inserire un valore nel range[1,9]", 1, SIZE * SIZE);
        posizione--;
        *col = posizione % SIZE;
        *row = posizione / SIZE;
        if(griglia[*row][*col] != BLANK_SPACE)
            printf("Cella gia' occupata\n");
    }
    while (griglia[*row][*col] != BLANK_SPACE);
}

void turnoCPU_tris(int griglia[SIZE][SIZE], int *col, int *row)
{
    printf("Dove vuoi disegnare?\n");
    usleep(GAMES_SPEED);//Simula l'attesa dell'input
    do
    {
        *col = randNumInRange(0,SIZE - 1);
        *row = randNumInRange(0,SIZE - 1);
    }
    while (griglia[*row][*col] != BLANK_SPACE);
}
