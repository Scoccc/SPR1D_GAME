#include "Dadi.h"

int lanciaDueDadi_Player(Gioco* game, Player_Dadi player)
{
    int dado1, dado2, somma;

    font_title("DADI",FG_CYAN);

    if(player.somme[0] != 0) //Se il giocatore ha già lanciato dei dati
    {
        printNomefromID(game, player.id);
        printf(" non devi fare meno di %d\n\n", player.somme[0]);
    }
    else //Se il giocatore non ha già lanciato dei dati
    {
        printNomefromID(game, player.id);
        printf(" è il tuo primo lancio\n\n");
    }

    printNomefromID(game, player.id);
    printf(" premi invio per lanciare i dadi");

    fflush(stdin);
    fflush(stdout);
    while (getchar() != '\n'); //Si aspetta l'invio

    printf("\n");
    dado1 = rollD6();
    dado2 = rollD6();
    printf("\n");
    printNomefromID(game, player.id);
    printf(": %d + %d = ",dado1, dado2);

    somma = dado1 + dado2;

    if(somma < player.somme[0])
    {
        font_changeFGColor(FG_RED);
        printf(" %d\n\n", somma);
        printf("LA SOMMA E' MINORE DELLA PRECEDENTE\n");
        font_reset();
    }
    else
    {
        font_changeFGColor(FG_GREEN);
        printf(" %d\n", somma);
        font_reset();

        premereInvio();
        clearScreen();
    }

    return somma;
}

int rollD6()
{
    int roll = randNumInRange(1,6);

    switch (roll)
    {
        case 1:
            printf("┌───────┐\n");
            printf("│       │\n");
            printf("│   ●   │\n");
            printf("│       │\n");
            printf("└───────┘\n");
            break;
        case 2:
            printf("┌───────┐\n");
            printf("│ ●     │\n");
            printf("│       │\n");
            printf("│     ● │\n");
            printf("└───────┘\n");
            break;
        case 3:
            printf("┌───────┐\n");
            printf("│ ●     │\n");
            printf("│   ●   │\n");
            printf("│     ● │\n");
            printf("└───────┘\n");
            break;
        case 4:
            printf("┌───────┐\n");
            printf("│ ●   ● │\n");
            printf("│       │\n");
            printf("│ ●   ● │\n");
            printf("└───────┘\n");
            break;
        case 5:
            printf("┌───────┐\n");
            printf("│ ●   ● │\n");
            printf("│   ●   │\n");
            printf("│ ●   ● │\n");
            printf("└───────┘\n");
            break;
        case 6:
            printf("┌───────┐\n");
            printf("│ ●   ● │\n");
            printf("│ ●   ● │\n");
            printf("│ ●   ● │\n");
            printf("└───────┘\n");
            break;
        default:
            break;
    }

    return roll;
}

int game_Dadi(Gioco* game, Gruppo gruppo)
{
    //Chi inizia si sceglie a caso
    Turno index_turno = randNumInRange(primoPlayer,secondoPlayer);
    _Bool finita = false;
    int id_vincitore;
    Player_Dadi* players_Dadi = initPlayerDadi(gruppo);

    while(!finita)
    {
        faseLancioDadi(game, &players_Dadi[index_turno]);
        if (haPerso(players_Dadi[index_turno]))
            finita = true;
        cambiaTurno(&index_turno,NUMPLAYERS_DADI);
    }

    id_vincitore = players_Dadi[index_turno].id;

    free(players_Dadi);

    return id_vincitore;
}

Player_Dadi* initPlayerDadi(Gruppo gruppo)
{
    Player_Dadi* players_Dadi = (Player_Dadi*) malloc(sizeof(Player_Dadi) * gruppo.sizeGruppo);
    int i;
    for (i = 0; i < gruppo.sizeGruppo; ++i)
    {
        players_Dadi[i].id = gruppo.id_membri[i];
        players_Dadi[i].somme[0] = 0;
        players_Dadi[i].somme[1] = 0;
    }
    return players_Dadi;
}

int lanciaDueDadi_CPU(Gioco* game, Player_Dadi cpu)
{
    int dado1, dado2, somma;

    font_title("DADI",FG_CYAN);
    if(cpu.somme[0] != 0)
    {
        printNomefromID(game, cpu.id);
        printf(" non devi fare meno di %d\n\n", cpu.somme[0]);
    }
    else
    {
        printNomefromID(game, cpu.id);
        printf(" è il tuo primo lancio\n\n");
    }

    printNomefromID(game, cpu.id);
    printf( " premi invio per lanciare i dadi\n\n" );

    usleep(GAMES_SPEED);//Simula l'attesa dell'input

    dado1 = rollD6();
    dado2 = rollD6();

    printf("\n");
    printNomefromID(game, cpu.id);
    printf(": %d + %d = ",dado1, dado2);

    somma = dado1 + dado2;

    if(somma < cpu.somme[0])
    {
        font_changeFGColor(FG_RED);
        printf(" %d\n\n", somma);
        printf("LA SOMMA E' MINORE DELLA PRECEDENTE\n");
        font_reset();
    }
    else
    {
        font_changeFGColor(FG_GREEN);
        printf(" %d\n", somma);
        font_reset();
        premereInvio();
        clearScreen();
    }

    return somma;
}

void faseLancioDadi(Gioco* game, Player_Dadi *player_Dadi)
{
    player_Dadi->somme[0] = player_Dadi->somme[1];

    if(isCPU(game, player_Dadi->id))
        player_Dadi->somme[1] = lanciaDueDadi_CPU(game, *player_Dadi);
    else
        player_Dadi->somme[1] = lanciaDueDadi_Player(game, *player_Dadi);
}



_Bool haPerso(Player_Dadi player_Dadi)
{
    return player_Dadi.somme[1] < player_Dadi.somme[0];
}
