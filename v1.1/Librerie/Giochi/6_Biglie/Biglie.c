#include "Biglie.h"

//Versione per Windows e Linux
int game_Biglie(Gioco* game, Gruppo gruppo)
{
    //Dichiarazione e inizializzazione variabili
    Player_Biglie* players_Biglie = initPlayerBiglie(gruppo);
    Turno index_turno = primoPlayer;
    _Bool finita = false;
    int id_vincitore;

    font_title("BIGLIE", FG_CYAN);

    while(!finita)
    {
        turnoScommessa(game, players_Biglie);
        turnoIndovinare(game, players_Biglie, index_turno);
        finita = checkPerdita(game, players_Biglie);
        cambiaTurno(&index_turno,NUMPLAYERS_BIGLIE);
    }

    if(players_Biglie[primoPlayer].numBiglie == 0)
        id_vincitore = players_Biglie[secondoPlayer].id;
    else
        id_vincitore = players_Biglie[primoPlayer].id;

    free(players_Biglie);

    return  id_vincitore;
}

Player_Biglie* initPlayerBiglie(Gruppo gruppo)
{
    int i;
    Player_Biglie* players_Biglie = (Player_Biglie*) malloc(sizeof(Player_Biglie) * gruppo.sizeGruppo);
    for (i = 0; i < NUMPLAYERS_BIGLIE; ++i)
    {
        players_Biglie[i].id = gruppo.id_membri[i];
        players_Biglie[i].numBiglie = NUMBIGLIEINIZIO;
        players_Biglie[i].scommessa = 0;
    }
    return players_Biglie;
}

_Bool checkPerdita(Gioco* game, Player_Biglie* players_Biglie)
{
    Turno index_turno;
    for (index_turno = primoPlayer; index_turno < NUMPLAYERS_BIGLIE; ++index_turno)
        if(players_Biglie[index_turno].numBiglie == 0)
        {
            printNomefromID(game, players_Biglie[index_turno].id);
            printf(" non ha piu' biglie!\n");
            return true;
        }
    return false;
}

void turnoScommessa(Gioco* game, Player_Biglie* players_Biglie)
{
    Turno index_turno;
    for (index_turno = primoPlayer; index_turno < NUMPLAYERS_BIGLIE; ++index_turno)
    {
        if (isCPU(game, players_Biglie[index_turno].id))
        {
            printf("\n");
            printNomefromID(game, players_Biglie[index_turno].id);
            printf(" quante biglie vuoi scommettere?\n");
            usleep(GAMES_SPEED);//Simula l'attesa dell'input
            players_Biglie[index_turno].scommessa = randNumInRange(1, players_Biglie[index_turno].numBiglie);
            printNomefromID(game, players_Biglie[index_turno].id);
            printf(" ha scommesso\n\n");
        }
        else
        {
            printNomefromID(game, players_Biglie[index_turno].id);
            printf(" quante biglie vuoi scommettere? [1-%d]\n", players_Biglie[index_turno].numBiglie);
            players_Biglie[index_turno].scommessa = getIntInRange("Inserire un valore nel range valido", 1, players_Biglie[index_turno].numBiglie);
        }
    }
}

void turnoIndovinare(Gioco* game, Player_Biglie* players_Biglie, Turno index_turno)
{
    pd previsione;
    Turno index_nextTurno = (index_turno + 1) % NUMPLAYERS_BIGLIE;
    char tempChar;

    if (isCPU(game, players_Biglie[index_turno].id))
    {
        printf("\n");
        tempChar = rand() % 2 ? 'P' : 'D';
        printNomefromID(game, players_Biglie[index_turno].id);
        printf(" l'altro giocatore ha scommesso un numero pari o dispari?[P/D]\n");
        usleep(GAMES_SPEED);//Simula l'attesa dell'input
        printf("%c\n",tempChar);
    }
    else
    {
        printNomefromID(game, players_Biglie[index_turno].id);
        printf(" l'altro giocatore ha scommesso un numero pari o dispari?[P/D]\n");
        do
        {
            scanf(" %c",&tempChar);
            tempChar = toUpper(tempChar);
            if(tempChar != 'P' && tempChar != 'D')
                printf("Inserire 'P' o 'D'\n");
        } while (tempChar != 'P' && tempChar != 'D');
    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * La previsione viene convertita da un valore letterale a un numero:    *
     * - previsione "Pari": 'P' --> 0, ovvero il resto ottenuto dividendo    *
     *   per 2 un numero pari;                                               *
     * - previsione "Dispari": 'D' --> 1, ovvero il resto ottenuto dividendo *
     *   per 2 un numero dispari.                                            *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    previsione = tempChar == 'P' ? Pari : Dispari;

    if(players_Biglie[index_nextTurno].scommessa % 2 == previsione)
    {
        //Caso in cui la tempChar fosse giusta
        printf("Hai indovinato!\n");
        //Dal numero di biglie dell'avversario si sottrae il numero di biglie scommesse dall'avversario
        players_Biglie[index_nextTurno].numBiglie -= players_Biglie[index_nextTurno].scommessa;
        //Il giocatore riceve il numero di biglie scommesse dall'avversario
        players_Biglie[index_turno].numBiglie += players_Biglie[index_nextTurno].scommessa;
    }
    else
    {
        //Caso in cui la tempChar fosse sbagliata
        printf("Non hai indovinato!\n");
        //Dal numero di biglie del giocatore si sottrae il numero di biglie scommesse dal giocatore
        players_Biglie[index_turno].numBiglie -= players_Biglie[index_turno].scommessa;
        //L'avversario riceve il numero di biglie scommesse dal giocatore
        players_Biglie[index_nextTurno].numBiglie += players_Biglie[index_turno].scommessa;
    }
    printf("\n");
    //Si resetta la scommessa del giocatore
    players_Biglie[index_turno].scommessa = 0;
}