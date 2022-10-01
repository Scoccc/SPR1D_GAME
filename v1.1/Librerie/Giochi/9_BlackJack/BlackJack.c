#include "BlackJack.h"

int game_Blackjack(Gioco* game, Gruppo gruppo)
{
    //Inizializzazione variabili
    int id_vincitore;
    _Bool finita = false;
    Player_Blackjack* players_BlackJack = initPlayerBlackjack(gruppo);
    Turno index_turno = primoPlayer;
    Mazzo* mazzo = creaMazzoCompleto();
    Status stato;

    mischiaMazzo(&mazzo,LOOPS);

    font_title("BLACKJACK",FG_BRIGHT_GREEN);

    fasePrimeDueCarte(players_BlackJack,&mazzo);

    printCartePlayers(game, players_BlackJack);

    printf("\n");

    if(players_BlackJack[primoPlayer].somma == SOGLIA)
    {
        printNomefromID(game, players_BlackJack[primoPlayer].id);
        printf(" ha raggiunto 21!\n\n");
        premereInvio();
    }

    if(players_BlackJack[secondoPlayer].somma == SOGLIA)
    {
        printNomefromID(game, players_BlackJack[secondoPlayer].id);
        printf(" ha raggiunto 21!\n\n");
        premereInvio();
    }

    while(!finita)
    {
        if(!players_BlackJack[index_turno].stop)
        {
            faseCartaOFermarsi(game, &players_BlackJack[index_turno],&mazzo);

            printCartePlayers(game, players_BlackJack);
            printf("\n");

            stato = checkStatusPlayer(players_BlackJack[index_turno]);

            switch (stato)
            {
                case sbancato:
                    printNomefromID(game, players_BlackJack[index_turno].id);
                    printf(" ha sbancato!\n");
                    id_vincitore = players_BlackJack[(index_turno + 1) % NUMPLAYERS_BLACKJACK].id;
                    finita = true;
                    break;
                case ventuno:
                    printNomefromID(game, players_BlackJack[index_turno].id);
                    printf(" ha raggiunto 21!\n");
                    break;
                default:
                    break;
            }
        }

        if(!finita && players_BlackJack[primoPlayer].stop && players_BlackJack[secondoPlayer].stop)
        {
            if(players_BlackJack[primoPlayer].somma != players_BlackJack[secondoPlayer].somma)
            {
                printf("Entrambi i giocatori si sono fermati!\n");
                id_vincitore = players_BlackJack[primoPlayer].somma > players_BlackJack[secondoPlayer].somma ? gruppo.id_membri[primoPlayer] : gruppo.id_membri[secondoPlayer];
                finita = true;
            }
            else
            {
                printf( "PAREGGIO!\n");
                premereInvio();
                clearScreen();
                players_BlackJack = initPlayerBlackjack(gruppo);
                free(mazzo);
                mazzo = creaMazzoCompleto();
                mischiaMazzo(&mazzo,LOOPS);
                fasePrimeDueCarte(players_BlackJack,&mazzo);
                printCartePlayers(game, players_BlackJack);
            }
        }
        else
            cambiaTurno(&index_turno,NUMPLAYERS_BLACKJACK);
    }

    free(players_BlackJack);
    free(mazzo);

    return id_vincitore;
}

void printSommaPlayer(Player_Blackjack player_BlackJack)
{
    Status status = checkStatusPlayer(player_BlackJack);

    printf("Somma: ");

    switch (status)
    {
        case fermo:
            font_changeFGColor(FG_BLUE);
            break;
        case sbancato:
            font_changeFGColor(FG_RED);
            break;
        case ventuno:
            font_changeFGColor(FG_GREEN);
            break;
        default:
            font_changeFGColor(FG_CYAN);
            break;
    }
    printf("%2d" P_RESET,player_BlackJack.somma);
}

void faseCartaOFermarsi(Gioco* game, Player_Blackjack *player_BlackJack, Mazzo **mazzo)
{
    _Bool scelta;

    printNomefromID(game, player_BlackJack->id);
    printf(" vuoi restare? [s/n]\n");

    if(isCPU(game, player_BlackJack->id))
    {
        if(player_BlackJack->somma < 12)
            scelta = false;
        else if(player_BlackJack->somma < 17)
            scelta = randNumInRange(false,true);
        else
            scelta = true;

        usleep(GAMES_SPEED);//Simula l'attesa dell'input
        printf(P_FG_CYAN "%c\n" P_RESET, scelta ? 's' : 'n');
    }
    else
        scelta = getYesNo();

    player_BlackJack->stop = scelta;

    if(!scelta)
        daiCarta(player_BlackJack, mazzo);

    clearScreen();
    font_title("BLACKJACK",FG_BRIGHT_GREEN);
}

Player_Blackjack* initPlayerBlackjack(Gruppo gruppo)
{
    Player_Blackjack* players_BlackJack = (Player_Blackjack*) malloc(sizeof(Player_Blackjack) * gruppo.sizeGruppo);
    int i;

    for (i = 0; i < NUMPLAYERS_BLACKJACK; ++i)
    {
        players_BlackJack[i].id = gruppo.id_membri[i];
        players_BlackJack[i].carte = allocaMazzo();
        players_BlackJack[i].carte = NULL;
        players_BlackJack[i].somma = 0;
        players_BlackJack[i].stop = false;
    }

    return players_BlackJack;
}


void daiCarta(Player_Blackjack *player_BlackJack, Mazzo** mazzo)
{
    //Si pesca la carta
    Carta cartaPescata = pescaCarta(mazzo);
    //Si aggiunge la carta alle carte del giocatore
    aggiungiCartaInfondo(&(player_BlackJack->carte),cartaPescata);
    //Si ricalcola la somma con la carta attuale
    calcolaSommaCarte(player_BlackJack);
}

void calcolaSommaCarte(Player_Blackjack* player)
{
    int somma = 0, assiTrovati = 0;
    Mazzo* ptr = player->carte; //Alias del mazzo

    while (ptr != NULL)
    {
        if(ptr->carta.val == 1)
            assiTrovati ++;
        else if(ptr->carta.val >= 10)
            somma += 10;
        else
            somma += ptr->carta.val;

        ptr = ptr->next;
    }

    while (assiTrovati > 0)
    {
        if(somma <= SOGLIA - 11 && assiTrovati == 1)
            somma += 11;
        else
            somma += 1;

        assiTrovati--;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * L'asso può valere 11 o 1, quindi si sceglie quanto farlo valere in base     *
     * alla somma ottenuta dalle altre carte, quindi ogni volta che tra le carte   *
     * si trova un asso non si sceglie subito il valore ma si contano tutti gli    *
     * assi trovati per calcolarne il valore alla fine.                            *
     * Un asso ha senso che valga 11 solo nel caso in cui non faccia sbancare un   *
     * giocatore, e dato che si sbanca con 21 non ha neanche senso avere più di un *
     * asso con valore 11, dato che solo quelle 2 carte varrebbero 22.             *
     * Quindi gli assi vengono fatti valere 1, e la scelta se farlo valere 1 o 11  *
     * si fa solo con l'ultimo asso da calcolare (assiTrovati == 1).               *
     * Quindi se scegliendo 11 non si sbancherebbe (somma <= SOGLIA - 11) l'asso   *
     * può valere 11, altrimenti pure quell'asso varrà 1.                          *
     * Si sceglie di far calcolare sempre l'asso da parte del computer e non di    *
     * chiedere all'utente ogni volta quanto vuole far valere un asso perché si    *
     * presuppone che il giocatore voglia sempre fare la scelta migliore, evitanto *
     * che scelga il valore sbagliato per distrazione o cause esterne.             *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


    player->somma = somma;

    player->stop = player->somma >= 21;
}

void fasePrimeDueCarte(Player_Blackjack players_BlackJack[NUMPLAYERS_BLACKJACK], Mazzo **mazzo)
{
    int i;
    for (i = primoPlayer; i < NUMPLAYERS_BLACKJACK; ++i)
    {
        daiCarta(&players_BlackJack[i],mazzo);
        daiCarta(&players_BlackJack[i],mazzo);
    }
}

void printCartePlayers(Gioco* game, Player_Blackjack* players_BlackJack)
{
    printf("Carte di ");

    font_changeFGColor(getColoreFromID(players_BlackJack[primoPlayer].id));
    printf("%-30d",players_BlackJack[primoPlayer].id);
    font_reset();

    printf("Carte di ");

    font_changeFGColor(getColoreFromID(players_BlackJack[secondoPlayer].id));
    printf("%d\n\n",players_BlackJack[secondoPlayer].id);
    font_reset();

    printDueMazzi(players_BlackJack[primoPlayer].carte,players_BlackJack[secondoPlayer].carte);

    printSommaPlayer(players_BlackJack[primoPlayer]);

    printf("%30s","");

    printSommaPlayer(players_BlackJack[secondoPlayer]);

    printf("\n");
}

Status checkStatusPlayer (Player_Blackjack player)
{
    if(player.somma == SOGLIA)
        return ventuno;
    else if(player.somma > SOGLIA)
        return sbancato;
    else if(player.stop)
        return fermo;
    else
        return inGioco;
}