#include "MorraCinese.h"

int game_MorraCinese(Gioco* game, Gruppo gruppo)
{
    _Bool finita = false;
    int id_vincitore;
    Player_MorraCinese* players_MorraCinese = initPlayers_MorraCinese(gruppo);

    font_title("MORRA CINESE", FG_CYAN);

    do
    {
        faseScelta(game, players_MorraCinese);
        switch (trovaVincitore_MorraCinese(players_MorraCinese))
        {
            case primoPlayer:
                finita = true;
                id_vincitore = players_MorraCinese[primoPlayer].id;
                break;
            case secondoPlayer:
                finita = true;
                id_vincitore = players_MorraCinese[secondoPlayer].id;
                break;
        }
    } while (!finita);

    free(players_MorraCinese);

    return id_vincitore;
}

Player_MorraCinese* initPlayers_MorraCinese(Gruppo gruppo)
{
    int i;
    Player_MorraCinese* players_MorraCinese = (Player_MorraCinese*) malloc(sizeof(Player_MorraCinese) * gruppo.sizeGruppo);
    for (i = 0; i < gruppo.sizeGruppo; ++i)
    {
        players_MorraCinese[i].id = gruppo.id_membri[i];
        players_MorraCinese[i].scelta = NULL_SCELTA;
    }
    return players_MorraCinese;
}

void faseScelta(Gioco* game, Player_MorraCinese* players_MorraCinese)
{
    int index_turno;
    for (index_turno = primoPlayer; index_turno < NUMPLAYERS_MORRACINESE; ++index_turno)
    {
        if(isCPU(game, players_MorraCinese[index_turno].id)) //Turno CPU
        {
            players_MorraCinese[index_turno].scelta = randNumInRange(Sasso_mc, Forbici_mc);
            printNomefromID(game, players_MorraCinese[index_turno].id);
            printf(" scegli\nSasso [1], Carta[2], o Forbici[3]?\n");
            usleep(GAMES_SPEED);//Simula l'attesa dell'input
            printNomefromID(game, players_MorraCinese[index_turno].id);
            printf(" ha scelto\n");
        }
        else //Turno ProfiloGiocatore
        {
            printNomefromID(game, players_MorraCinese[index_turno].id);
            printf(" scegli\nSasso [1], Carta[2], o Forbici[3]?\n");
            //Il numero viene chiesto all'utente nel range 1-3 per comodità, poi viene decrementato per corrispondere all'enumerazione
            players_MorraCinese[index_turno].scelta = getIntInRange("Il numero deve essere nel range[1-3]",1,3);
            players_MorraCinese[index_turno].scelta--;
        }
        printf("\n");
    }

}

int trovaVincitore_MorraCinese(Player_MorraCinese* players_MorraCinese)
{
    //Dichiarazione e inizializzazione variabili
    Scf p1_SCF = players_MorraCinese[primoPlayer].scelta;
    Scf p2_SCF = players_MorraCinese[secondoPlayer].scelta;

    if(p1_SCF == (p2_SCF + 1) % 3)
    {
        printf("%s batte %s\n\n",intToString(p1_SCF), intToString(p2_SCF));
        return primoPlayer;
    }
    if(p2_SCF == (p1_SCF + 1) % 3)
    {
        printf("%s batte %s\n\n",intToString(p2_SCF), intToString(p1_SCF));
        return secondoPlayer;
    }
    printf("Pareggio!\n");
    premereInvio();
    clearScreen();

    font_title("MORRA CINESE", FG_CYAN);

    return -1;
}

char* intToString(Scf SCF)
{
    switch (SCF)
    {
        case Sasso_mc:
            return "Sasso";
        case Carta_mc:
            return "Carta";
        case Forbici_mc:
            return "Forbici";
        default:
            return NULL;
    }
}
