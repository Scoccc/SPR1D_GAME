#include "Murra.h"

int game_Murra(Gioco* game, Gruppo gruppo)
{
    Player_Murra* players_Murra = initPlayers_Murra(gruppo);
    _Bool finita = false;
    Turno indexVincitore;
    int id_vincitore;

    font_title("MURRA", FG_CYAN);

    while(!finita)
    {
        faseMurra(game, players_Murra);
        indexVincitore = checkVincitore(game, players_Murra);
        if(indexVincitore != NULLPLAYER)
            finita = true;
    }

    id_vincitore = gruppo.id_membri[indexVincitore];

    free(players_Murra);

    return id_vincitore;
}

Turno checkVincitore(Gioco* game, Player_Murra* players_Murra)
{
    int somma = players_Murra[primoPlayer].numScelto + players_Murra[secondoPlayer].numScelto;

    font_changeFGColor(getColoreFromID(players_Murra[primoPlayer].id));
    printf("%d", players_Murra[primoPlayer]. numScelto);
    font_reset();

    printf(" + ");

    font_changeFGColor(getColoreFromID(players_Murra[secondoPlayer].id));
    printf("%d", players_Murra[secondoPlayer]. numScelto);
    font_reset();

    printf(" = %d\n",somma);

    if(players_Murra[primoPlayer].previsione == somma && players_Murra[secondoPlayer].previsione == somma)
    {
        printf("Entrambi i giocatori hanno indovinato!\nPAREGGIO!\n\n");
        return NULLPLAYER;
    }
    else if (players_Murra[primoPlayer].previsione == somma)
    {
        printNomefromID(game, players_Murra[primoPlayer].id);
        printf(" ha indovinato!\n\n");
        return primoPlayer;
    }
    else if (players_Murra[secondoPlayer].previsione == somma)
    {
        printNomefromID(game, players_Murra[secondoPlayer].id);
        printf(" ha indovinato!\n\n");
        return secondoPlayer;
    }
    else
    {
        printf("Nessuno ha indovinato!\n\n");
        return NULLPLAYER;
    }
}

void sceltaPrevisione(Gioco* game, Player_Murra* player_Murra)
{
    if(isCPU(game, player_Murra->id))
    {
        player_Murra->previsione = randNumInRange(2,10);
        printNomefromID(game, player_Murra->id);
        printf(" quanto varrà la somma? [2-10]:\n");
        printf("%d\n", player_Murra->previsione);
    }
    else
    {
        printNomefromID(game, player_Murra->id);
        printf(" quanto varrà la somma? [2-10]?\n");
        player_Murra->previsione = getIntInRange("Scegli un numero nel range [2-10]",2,10);
    }
}

Player_Murra* initPlayers_Murra(Gruppo gruppo)
{
    int i;
    Player_Murra* players_Murra = (Player_Murra*) malloc(sizeof(Player_Murra) * gruppo.sizeGruppo);

    for (i = 0; i < NUMPLAYERS_MURRA; ++i)
    {
        players_Murra[i].id = gruppo.id_membri[i];
        players_Murra[i].numScelto = 0;
        players_Murra[i].previsione = 0;
    }
    return players_Murra;
}

void sceltaNumero(Gioco* game, Player_Murra* player_Murra)
{
    if(isCPU(game, player_Murra->id))
    {
        player_Murra->numScelto = randNumInRange(1,5);
        printNomefromID(game, player_Murra->id);
        printf(" ha scelto il numero\n");
    }
    else
    {
        printNomefromID(game, player_Murra->id);
        printf(" scegli un numero[1-5]\n");
        player_Murra->numScelto = getIntInRange("Scegli un numero nel range [1-5]",1,5);
    }
}

void faseMurra(Gioco* game, Player_Murra* players_Murra)
{
    Turno indexTurno;
    for (indexTurno = primoPlayer; indexTurno < NUMPLAYERS_MURRA; ++indexTurno)
    {
        sceltaNumero(game, &players_Murra[indexTurno]);
        sceltaPrevisione(game, &players_Murra[indexTurno]);
        printf("\n");
    }
}