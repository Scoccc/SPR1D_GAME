#include "PonteDiVetro.h"

void printPonte(Gioco* game, Vetro ponte[NUM_RIGHE][NUM_COLONNE], Player_PDV player)
{
    int i, j;

    font_title("PONTE DI VETRO", FG_CYAN);

    printNomefromID(game, player.id);
    printf(" deve attraversare il ponte!\n");

    if(player.riga == START) //Se il giocatore è alla posizione di partenza
    {
        printf("      ");
        font_changeFGColor(getColoreFromID(player.id));
        printf("██");
        font_reset();
    }
    printf("\n");

    for (i = 0; i < NUM_RIGHE; ++i) //Il giocatore si trova sopra il ponte
    {
        for(j = sinistra; j <= destra; j++)
        {
            if(j == sinistra)
                printf(" "); //Si lascia uno spazio a sinistra
            if(ponte[i][j].integro)
                printf("┌────┐"); //parte alta della lastra di vetro
            else
                printf("      "); //lastra caduta
        }
        printf("\n");

        for(j = sinistra; j <= destra; j++)
        {
            if(j == sinistra)
                printf("↓"); //freccia per far capire la direzione di attraversamento

            if(ponte[i][j].integro) //Se la lastra non è caduta
            {
                if(player.riga == i && player.posizione == j) //Se il player è sopra questa lastra
                {
                    printf("│ "); //lato della lastra
                    font_changeFGColor(getColoreFromID(player.id));
                    printf("██"); //Giocatore sopra la lastra
                    font_reset();
                    printf(" │"); //lato sinistro della lastra
                }
                else
                    printf("│    │"); //Parte centrale della lastra, senza giocatore sopra
            }
            else
                printf("      "); //lastra crollata
        }
        printf("↓\n"); //freccia per far capire la direzione di attraversamento
        for(j = sinistra; j <= destra; j++)
        {
            if(j == sinistra)
                printf(" "); //Si lascia uno spazio a sinistra
            if(ponte[i][j].integro)
                printf("└────┘"); //parte inferiore della lastra
            else
                printf("      "); //lastra crollata
        }
        printf("\n");
    }

    if(player.riga == END) //Il giocatore ha attraversato il ponte
    {
        printf("      ");
        font_changeFGColor(getColoreFromID(player.id));
        printf("██");
        font_reset();
    }

    printf("\n");
}

int game_PonteDiVetro(Gioco* game, Gruppo gruppo)
{
    Vetro ponte[NUM_RIGHE][NUM_COLONNE];
    Player_PDV* players_PDV = initPlayers_PDV(gruppo);
    _Bool finita = false;
    Turno indexTurno;
    Posizione nonFragili[NUM_RIGHE];
    int id_vincitore;

    initNonFragili(nonFragili);
    randOrdinePlayers(players_PDV);
    initPonte(ponte);

    indexTurno = primoPlayer; //Si inizia dal primo player
    while(indexTurno < quartoPlayer  && !finita) //Si gioca finchè non rimane un solo giocatore oppure qualcuno ha vinto
    {
        finita = attraversaPonte(game, players_PDV[indexTurno], ponte, nonFragili);
        if(!finita)
            indexTurno++; //Se non è finita si incrementa il turno
    }

    if(indexTurno == quartoPlayer)
        printf("\n\nE' rimasto un solo giocatore\n");

    id_vincitore = players_PDV[indexTurno].id;

    free(players_PDV);

    return id_vincitore;
}

Player_PDV* initPlayers_PDV(Gruppo gruppo)
{
    int i;
    Player_PDV* players_PDV = (Player_PDV*) malloc(sizeof(Player_PDV) * gruppo.sizeGruppo);

    for (i = 0; i < NUMPLAYERS_PONTEDIVETRO; ++i)
    {
        players_PDV[i].id = gruppo.id_membri[i];
        players_PDV[i].riga = START;
        players_PDV[i].posizione = START;
    }

    return players_PDV;
}

void initPonte(Vetro ponte[NUM_RIGHE][NUM_COLONNE])
{
    int i;
    for (i = 0; i < NUM_RIGHE; ++i)
    {
        ponte[i][sinistra].integro = true;
        ponte[i][destra].integro = true;

        ponte[i][sinistra].fragile = randNumInRange(false,true); //Si sceglie casualmente se è fragile o no
        ponte[i][destra].fragile = !(ponte[i][sinistra].fragile); //La lastra destra sarà l'opposto della lastra sinistra
    }
}

_Bool attraversaPonte(Gioco* game, Player_PDV player, Vetro ponte[NUM_RIGHE][NUM_COLONNE], Posizione nonFragili[NUM_RIGHE])
{
    int riga;
    Posizione DoS;

    for (riga = 0; riga < NUM_RIGHE; ++riga)
    {
        clearScreen();

        printPonte(game, ponte,player);

        printNomefromID(game, player.id);

        if(isCPU(game, player.id))
        {
            if(nonFragili[riga] == SCONOSCIUTO)
                DoS = randNumInRange(sinistra,destra);
            else
                DoS = nonFragili[riga];
            printf(" sinistra o destra? [1-2]\n");
            usleep(GAMES_SPEED);//Simula l'attesa dell'input
            printf( "%d\n", DoS + 1);
        }
        else
        {
            printf(" sinistra [1] o destra [2]?\n");
            DoS = getIntInRange("Inserire 1 o 2",1,2);
            DoS--;
        }

        clearScreen();

        player.riga = riga;
        player.posizione = DoS;

        if(ponte[riga][DoS].fragile) //il giocatore  andato su una lastra fragile
        {
            printPonte(game, ponte,player);
            usleep(GAMES_SPEED);
            clearScreen();
            ponte[riga][DoS].integro = false;
            player.riga = CADUTO;
            printPonte(game, ponte,player);
            printf("Sei caduto!\n");
            premereInvio();
            clearScreen();
            nonFragili[riga] = !DoS;
            return false;
        }
        else
            nonFragili[riga] = DoS;

        printPonte(game, ponte,player);
    }
    player.riga = END;
    usleep(GAMES_SPEED);
    clearScreen();
    printPonte(game, ponte,player);
    printf("\nHai superato il ponte\n");

    return true;
}

void initNonFragili(Posizione nonFragili[NUM_RIGHE])
{
    int i;
    for (i = 0; i < NUM_RIGHE; ++i)
        nonFragili[i] = SCONOSCIUTO;
}

void randOrdinePlayers(Player_PDV* players_PDV)
{
    int i, randIndex;
    Player_PDV tmp;
    for (i = 0; i < NUMPLAYERS_PONTEDIVETRO; ++i)
    {
        randIndex = randNumInRange(0,NUMPLAYERS_PONTEDIVETRO - 1);

        if(i != randIndex)
        {
            tmp = players_PDV[i];
            players_PDV[i] = players_PDV[randIndex];
            players_PDV[randIndex] = tmp;
        }
    }
}
