#include "PariODispari.h"

int game_PariODispari(Gioco* game, Gruppo gruppo)
{
    //Dichiarazione e inizializzazione variabili
    Player_PariODispari* players_PariODispari = initPlayers_PariODispari(gruppo);
    int id_vincitore;

    font_title("PARI O DISPARI", FG_CYAN);

    faseSceltaPariODispari(game, players_PariODispari);
    faseSceltaNumDita(game, players_PariODispari);
    id_vincitore = trovaVincitore(players_PariODispari);

    free(players_PariODispari);

    return id_vincitore;
}

Player_PariODispari* initPlayers_PariODispari(Gruppo gruppo)
{
    Player_PariODispari* players_PariODispari = (Player_PariODispari*) malloc(sizeof(Player_PariODispari) * gruppo.sizeGruppo);
    int i;
    for (i = 0; i < gruppo.sizeGruppo; ++i)
    {
        players_PariODispari[i].id = gruppo.id_membri[i];
        players_PariODispari[i].previsione = 0;
        players_PariODispari[i].numDita = 0;
    }
    return players_PariODispari;
}

void faseSceltaPariODispari(Gioco* game, Player_PariODispari* players_PariODispari)
{
    int index_giocatore = randNumInRange(primoPlayer,secondoPlayer); //Si sceglie casualmente chi inizia
    int index_avversario = !index_giocatore;
    char previsione;
    char* intToString[2] = {"pari", "dispari"};

    if(isCPU(game, players_PariODispari[index_giocatore].id))
    {
        //TURNO CPU

        players_PariODispari[index_giocatore].previsione = randNumInRange(Pari,Dispari);
        printNomefromID(game, players_PariODispari[index_giocatore].id);
        printf(" la somma sara' pari o dispari?[P/D]:\n");
        usleep(GAMES_SPEED);//Simula l'attesa dell'input
        printf("%c\n",players_PariODispari[index_giocatore].previsione == Pari ? 'P' : 'D');
    }
    else
    {
        //TURNO PROFILO GIOCATORE

        printNomefromID(game, players_PariODispari[index_giocatore].id);
        printf(" la somma sara' pari o dispari?[P/D]?\n");
        do
        {
            scanf(" %c",&previsione); //Si legge il carattere
            previsione = toUpper(previsione); //il carattere si rende maiuscolo
            if(previsione != 'P' && previsione != 'D') //caso in cui si sia inserito un carattere sbagliato
                printf("Inserire 'P' o 'D'\n");
        } while (previsione != 'P' && previsione != 'D'); //Ripeti finchè non viene inserito un carattere giusto ['P' o 'D']
        players_PariODispari[index_giocatore].previsione = previsione == 'P' ? Pari : Dispari; //Si da corrispondere il carattere all'enumerazione
    }
    players_PariODispari[index_avversario].previsione = players_PariODispari[index_giocatore].previsione == Pari ? Dispari : Pari; //L'avversario giocherà la previsione opposta

    printf("\n");
    printNomefromID(game, players_PariODispari[index_giocatore].id);
    printf(": %s\n", intToString[players_PariODispari[index_giocatore].previsione]);
    printNomefromID(game, players_PariODispari[index_avversario].id);
    printf(": %s\n\n", intToString[players_PariODispari[index_avversario].previsione]);
}

void faseSceltaNumDita(Gioco* game, Player_PariODispari* players_PariODispari)
{
    Turno index_turno;
    for(index_turno = primoPlayer; index_turno < NUMPLAYERS_PARIODISPARI; ++index_turno)
    {
        if(isCPU(game, players_PariODispari[index_turno].id))
        {
            players_PariODispari[index_turno].numDita = randNumInRange(MIN_NUMDITA,MAX_NUMDITA);
            printNomefromID(game, players_PariODispari[index_turno].id);
            printf(" ha scelto il numero di dita da mostrare\n");
        }
        else
        {
            printNomefromID(game, players_PariODispari[index_turno].id);
            printf(" quante dita vuoi mostrare?[0-5]?\n");
            players_PariODispari[index_turno].numDita = getIntInRange("Il numero deve essere nel range 0-5",MIN_NUMDITA,MAX_NUMDITA);
        }
    }
    printf("\n");
    printNomefromID(game, players_PariODispari[primoPlayer].id);
    printf(" mostra %d dit%c\n", players_PariODispari[primoPlayer].numDita, players_PariODispari[primoPlayer].numDita == 1 ? 'o' : 'a');
    printNomefromID(game, players_PariODispari[secondoPlayer].id);
    printf(" mostra %d dit%c\n\n", players_PariODispari[secondoPlayer].numDita, players_PariODispari[secondoPlayer].numDita == 1 ? 'o' : 'a');
}

int trovaVincitore(Player_PariODispari* players_PariODispari)
{
    int vincitore;
    int somma = players_PariODispari[primoPlayer].numDita + players_PariODispari[secondoPlayer].numDita;
    printf("La somma e' %d quindi %s\n",somma , pari(somma) ? "pari" : "dispari");
    vincitore = somma % 2 == players_PariODispari[primoPlayer].previsione ? players_PariODispari[primoPlayer].id : players_PariODispari[secondoPlayer].id;
    return vincitore;
}
