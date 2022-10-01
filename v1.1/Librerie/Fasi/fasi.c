#include "fasi.h"

Gioco* Fase0_pregame()
{
    //Dichiarazione variabili
    _Bool inizio = false; //Se vale true si può iniziare lo SPR1D GAME, altrimenti non ancora
    int scelta; //Scelta dell'utente in base al menu visualizzato
    Gioco* game; //Partita da caricare o iniziare da capo

    do
    {
        //STAMPA DEL MENU
        printf(P_FG_BRIGHT_CYAN "   BENVENUTI ALLO SPR1D GAME\n\n");
        printf(P_BG_BRIGHT_BLACK P_FG_BRIGHT_WHITE "          Cosa vorresti fare?          " P_RESET "\n");
        printf(P_BG_BLUE P_FG_BRIGHT_WHITE " 1 " P_BG_CYAN P_FG_BLACK        " Leggere le info                    " P_RESET "\n");
        printf(P_BG_BLUE P_FG_BRIGHT_WHITE " 2 " P_BG_BRIGHT_BLUE P_FG_BLACK " Aggiungere profili giocatore       " P_RESET "\n");
        printf(P_BG_BLUE P_FG_BRIGHT_WHITE " 3 " P_BG_CYAN P_FG_BLACK        " Caricare una partita               " P_RESET "\n");
        printf(P_BG_BLUE P_FG_BRIGHT_WHITE " 4 " P_BG_BRIGHT_BLUE P_FG_BLACK " Gioca un gioco liberamente         " P_RESET "\n");
        printf(P_BG_BLUE P_FG_BRIGHT_WHITE " 5 " P_BG_CYAN P_FG_BLACK        " Esci dallo SPR1D GAME              " P_RESET "\n");

        printf("Scegli un numero:");
        scelta = getIntInRange("Scegli tra 1, 2, 3 , 4 o 5", 1 , 5);

        clearScreen();

        switch (scelta)
        {
            case 1: //Lettura delle info di gioco
                printInfo(INFO_SPR1DGAME);
                premereInvio();
                clearScreen();
                break;
            case 2: //Aggiungere PG
                game = initGame();

                if(inserimentoPG(game))
                {
                    clearScreen();

                    printf("Vuoi salvare questi profili? [s/n]\n");
                    if(getYesNo())
                        getSaveName(game);

                    clearScreen();
                }

                printf("Vuoi iniziare una partita con questi profili? [s/n]\n");
                inizio = getYesNo();

                clearScreen();
                break;
            case 3: //Caricamento partita
                if(NumSaves() > 0)
                {
                    //Caso in cui siano presenti salvataggi
                    do
                    {
                        game = loadGame(selectSaveFile()); //Si carica una partita da un salvataggio

                        if (game == NULL)
                        {
                            //Caso in cui non si è riusciti a caricare il salvataggio
                            printf("\nImpossibile avviare il gioco, probabilmente il salvataggio è corrotto\nProva a scegliere un nuovo salvataggio\n\n");
                            premereInvio();
                            clearScreen();
                            inizio = false;
                        }
                        else
                        {
                            //Caso in cui si è riusciti a caricare il salvataggio
                            if (game->numProfiliCreati != 0)
                            {
                                //Caso in cui ci sono dei Profili Utenti all'interno del salvataggio
                                clearScreen();
                                printf("Giocatori caricati\n\n");
                                printAllPGs(game);
                                if (game->inCorso) //Si fa vedere il numero di giocatori ancora in gara solo se la partita è in corso
                                    printf("Sono rimasti %d giocatori\n\n", numInGioco(game));

                                premereInvio();
                                clearScreen();

                                inizio = true;
                            }
                            else
                            {
                                //Caso in cui si sia voluti tornare indietro
                                clearScreen();
                                inizio = false;
                            }
                        }
                    }
                    while(game == NULL); //Si ripete il ciclo finchè non si riesce a caricare un salvataggio o si inizia una nuova partita
                }
                else
                {
                    //Caso in cui non siano presenti salvataggi
                    printf("Non ci sono salvataggi!\n");
                    premereInvio();
                    clearScreen();
                    inizio = false;
                }
                break;
            case 4://Gioco libero di un minigioco a scelta
                clearScreen();
                Fase0_1_provaMinigioco();
                inizio = false;
                break;
            default:
                return NULL;
        }
    }
    while (!inizio); //Si esce dal ciclo quando si è deciso se iniziare una partita o quando si è caricata correttamente una partita

    if(!game->inCorso) //Se la partita non è in corso
    {
        inserimentoMeN(game); //Vanno inseriti il numero di giocatori totali e di giocatori utente

        sceltaPG(game); //Vanno scelti i Profili Giocatore che parteciperanno al gioco

        //Da questo momento la partita è in corso
        game->inCorso = true;
    }

    return game;
}

Fase trovaFase(Gioco* game)
{
    int num = numInGioco(game);

    if(num == game->numGiocatori) //Se tutti i giocatori sono ancora in gioco
        return scrematura;        //si è alla fase di scrematura
    else if(num == 2) //Se ci sono solo 2 giocatori in gioco
        return finale;//si è alla fase finale
    else if(num == 1)   //Se è rimasto un solo giocatore
        return conclusa;//lo SPR1D GAME è concluso
    else
        return svolgimento; //Con un qualsiasi altro numero di giocatori si è nella fase di svolgimento
}

void Fase1_Scrematura(Gioco* game)
{
    //DICHIARAZIONE VARIABILI
    int i, id_vincitore, numGruppi;
    Gruppo* gruppi;

    clearScreen();

    numGruppi = getNumGruppiScrematura(game->numGiocatori);//Si calcola il numero di gruppi che verranno formati
    gruppi = formaGruppiScrematura(game, numGruppi); //Si formano i gruppi che parteciperanno alla scrematura

    premereInvio();
    clearScreen();

    if(game->numGiocatoriUtente > 0)
    {
        //Se allo SPR1D GAME partecipa almeno un giocatore reale
        printf("Vuoi leggere come si gioca a INDOVINA IL NUMERO? [s/n]\n");
        if (getYesNo())
        {
            clearScreen();
            printInfo(ISTRUZIONI_ILN);
            premereInvio();
        }
        clearScreen();
    }

    for (i = 0; i < game->numGiocatoriUtente; ++i)               //A tutti i partecipanti della scrematura si
        game->profiliGiocatore[game->indiciGU[i]].numSGGiocati++;//aggiunge +1 al numero di SPR1D GAME giocati

    for (i = 0; i < numGruppi; ++i)
    {
        if(isCPUvsCPU(game, gruppi[i]))
        {
            //Caso in cui sia  il gruppo sia formato da sole CPU
            id_vincitore = randIDfromGruppo(gruppi[i]);
            updateStats(game, id_vincitore, gruppi[i],scrematura);
        }
        else
        {
            id_vincitore = game_IndovinaIlNumero(game, gruppi[i]);

            //Applicazione dei cheat
            FrontmanDelloSPR1DGAME(game, gruppi[i], &id_vincitore);
            FallitoDelloSPR1DGAME(game, gruppi[i], &id_vincitore);

            updateStats(game, id_vincitore, gruppi[i],scrematura);

            printf("\n");
            printNomefromID(game, id_vincitore);
            printf(" HA VINTO\n\n");

            premereInvio();
            clearScreen();
        }
    }

    printf("Vuoi salvare la partita? [s/n]\n");
    if(getYesNo())
        getSaveName(game);
    clearScreen();

    //Si dealloca l'array di gruppi
    free(gruppi);
}

void Fase2_Svolgimento(Gioco* game)
{
    //DICHIARAZIONE VARIABILI
    Games gioco_scelto, max_game; //Gioco estratto per il turno corrente e ultimo gioco estraibile
    Gruppo* gruppi; //Array di gruppi formati er il turno corrente
    int id_vincitore, numGruppi, i, id_finalista;
    char* nomiGiochi[] = {"Indovina il numero", "Pari o Dispari", "Dadi", "Morra Cinese", "Murra", "Tris", "Biglie", "Ponte di vetro", "L' impiccato", "Black Jack"};

    if(!giocatoriUtenteEliminati(game))
    {
        //Caso in cui ci sono ancora giocatori utente in gara

        if (numInGioco(game) > 4) //Se ci sono più di 4 giocatori rimasti
            max_game = Impiccato; //si possono estrarre anche giochi da 4 player
        else                      //altrimenti
            max_game = Biglie;    //si possono estrarre solo giochi da 2 player

        if(RiccardoScateniInGioco(game))//Se Riccardo Scateni partecipa deve scegliere il gioco
        {
            printf(P_BG_BRIGHT_BLACK P_FG_BRIGHT_WHITE " Lista giochi disponibili " P_RESET "\n"); //Sfondo grigio, scritta bianca

            //Stampa della tabella di giochi
            for (i = PariODispari; i <= max_game; ++i)
            {
                printf(P_BG_BLUE P_FG_BRIGHT_WHITE " %d " P_RESET, i);  //Sfondo blu, scritta bianca: stampa del numero corrispondente al gioco

                //Stampa nome del gioco
                if(pari(i)) //Se è una riga pari
                    printf(P_BG_CYAN P_FG_BLACK " %-21s " P_RESET "\n", nomiGiochi[i]); //Sondo ciano, scritta nera
                else //Se è una riga dispari
                    printf(P_BG_BRIGHT_BLUE P_FG_BLACK " %-21s " P_RESET "\n", nomiGiochi[i]); //Sondo celeste, scritta nera
            }

            printf("Riccardo Scateni, scegli il prossimo gioco:");
            gioco_scelto = getIntInRange("Il numero deve essere nel giusto range", PariODispari, max_game);
            clearScreen();
        }
        else
        {
            //Se Riccardo Scateni non partecipa di estrae il gioco casualmente
            gioco_scelto = randNumInRange(PariODispari, max_game);
        }

        //Si visualizza il gioco estratto
        printf("I seguenti gruppi si sfideranno nel gioco \"%s\"!\n", nomiGiochi[gioco_scelto]);

        if (gioco_scelto == PonteDiVetro || gioco_scelto == Impiccato)
        {
            //Caso in cui il gioco sia da 4 player
            gruppi = formaGruppiSvolgimento(game, NUMPLAYERS_PONTEDIVETRO);
            numGruppi = numInGioco(game) / NUMPLAYERS_PONTEDIVETRO;
        }
        else
        {
            //Caso in cui il gioco sia da 2 player
            gruppi = formaGruppiSvolgimento(game, NUMPLAYERS_PARIODISPARI);
            numGruppi = numInGioco(game) / NUMPLAYERS_PARIODISPARI;
        }

        //Si stampano le istruzioni del gioco selezionato
        printf("Vuoi leggere come si gioca a %s? [s/n]\n", nomiGiochi[gioco_scelto]);
        if (getYesNo())
        {
            switch (gioco_scelto)
            {
                case PariODispari:
                    clearScreen();
                    printInfo(ISTRUZIONI_POD);
                    break;
                case Dadi:
                    clearScreen();
                    printInfo(ISTRUZIONI_DADI);
                    break;
                case MorraCinese:
                    clearScreen();
                    printInfo(ISTRUZIONI_MC);
                    break;
                case Murra:
                    clearScreen();
                    printInfo(ISTRUZIONI_MURRA);
                    break;
                case Tris:
                    clearScreen();
                    printInfo(ISTRUZIONI_TRIS);
                    break;
                case Biglie:
                    clearScreen();
                    printInfo(ISTRUZIONI_BIGLIE);
                    break;
                case PonteDiVetro:
                    clearScreen();
                    printInfo(ISTRUZIONI_PDV);
                    break;
                case Impiccato:
                    clearScreen();
                    printInfo(ISTRUZIONI_IMPICCATO);
                    break;
                default:
                    break;
            }

            premereInvio();
            clearScreen();
        }

        clearScreen();

        for (i = 0; i < numGruppi; ++i)
        {
            if (isCPUvsCPU(game, gruppi[i])) //Se il gruppo è formato da sole CPU
                id_vincitore = randIDfromGruppo(gruppi[i]);
            else
            {
                //Se nel gruppo c'è almeno un giocatore
                switch (gioco_scelto)
                {
                    case PariODispari:
                        id_vincitore = game_PariODispari(game, gruppi[i]);
                        break;
                    case Dadi:
                        id_vincitore = game_Dadi(game, gruppi[i]);
                        break;
                    case MorraCinese:
                        id_vincitore = game_MorraCinese(game, gruppi[i]);
                        break;
                    case Murra:
                        id_vincitore = game_Murra(game, gruppi[i]);
                        break;
                    case Tris:
                        id_vincitore = game_Tris(game, gruppi[i]);
                        break;
                    case Biglie:
                        id_vincitore = game_Biglie(game, gruppi[i]);
                        break;
                    case PonteDiVetro:
                        id_vincitore = game_PonteDiVetro(game, gruppi[i]);
                        break;
                    case Impiccato:
                        id_vincitore = game_Impiccato(game, gruppi[i]);
                        break;
                    default:
                        break;
                }

                //Si applicano i cheat
                FrontmanDelloSPR1DGAME(game, gruppi[i], &id_vincitore);
                FallitoDelloSPR1DGAME(game, gruppi[i], &id_vincitore);

                //Stampa del vincitore
                printf("\n");
                printNomefromID(game, id_vincitore);
                printf(" HA VINTO\n\n");

                premereInvio();
                clearScreen();
            }
            updateStats(game, id_vincitore, gruppi[i], svolgimento);
        }

        printf("Vuoi salvare la partita? [s/n]\n");
        if (getYesNo())
            getSaveName(game);
        clearScreen();

        //Si dealloca l'array di gruppi
        free(gruppi);
    }
    else
    {
        //Caso in cui sono stati eliminati tutti i giocatori utente
        //Si genera il primo finalista
        do
        {
            id_vincitore = randNumInRange(0,game->numGiocatori - 1);
        }
        while (!game->inGioco[id_vincitore]);

        //Si genera il secondo finalista
        do
        {
            id_finalista = randNumInRange(0,game->numGiocatori - 1);
        }
        while (!game->inGioco[id_finalista] || id_vincitore == id_finalista);

        //Si eliminano tutti tranne i finalisti scelti
        for (i = 0; i < game->numGiocatori; ++i)
        {
            if(!(i == id_vincitore || i == id_finalista))
                game->inGioco[i] = false;
        }
    }
}

void Fase3_Finale(Gioco* game)
{
    //Dichiarazione variabili
    Gruppo gruppo;
    int id_vincitore, i;

    //Formazione dell'ultimo gruppo
    gruppo = formaGruppoFinale(game);

    if(!isCPUvsCPU(game,gruppo))
    {
        printf("Vuoi leggere come si gioca a \"BlackJack\"? [s/n]\n");
        if (getYesNo())
        {
            clearScreen();
            printInfo(ISTRUZIONI_BLACKJACK);
            premereInvio();
        }
        clearScreen();
    }

    id_vincitore = game_Blackjack(game, gruppo);

    //Applicazione cheats
    FrontmanDelloSPR1DGAME(game, gruppo, &id_vincitore);
    FallitoDelloSPR1DGAME(game, gruppo, &id_vincitore);

    updateStats(game, id_vincitore, gruppo,finale);

    premereInvio();
    clearScreen();

    printNomefromID(game, id_vincitore);
    printf(" HA VINTO LO SPR1D GAME\n\n");

    if(!isCPU(game,id_vincitore))
        printPG(game, getPGfromID(game, id_vincitore));

    //Easter egg che si attiva se non ci sono stati giocatori utente
    printf("GRAZIE PER %sAVER GIOCATO!\n\n", game->numGiocatoriUtente == 0 ? "NON " : "");

    premereInvio();
    clearScreen();

    printf("Vuoi salvare la partita? [s/n]\n");
    if (getYesNo())
    {
        //Si annullano gli id di tutti i giocatori, in modo che non vengano salvati
        for (i = 0; i < game->numGiocatoriUtente; ++i)
            game->profiliGiocatore[game->indiciGU[i]].id = NULL_ID;

        game->inCorso = false; //Il gioco quando verrà caricato di nuovo non sarà in corso
        getSaveName(game);
    }
    clearScreen();
}

void updateStats(Gioco* game, int id_vincitore, Gruppo gruppo, Fase fase)
{
    int i;

    if (fase == svolgimento || fase == scrematura)
    {
        for (i = 0; i < game->numGiocatoriUtente; ++i)
        {
            if(isInGruppo(game->profiliGiocatore[game->indiciGU[i]].id, gruppo))
            {
                //Viene incrementato il numero di giochi giocati
                game->profiliGiocatore[game->indiciGU[i]].numGiochiGiocati++;
                //Se il profilo utente ha vinto
                if(game->profiliGiocatore[game->indiciGU[i]].id == id_vincitore)
                    //Viene incrementato il numero di giochi vinti
                    game->profiliGiocatore[game->indiciGU[i]].numGiochiVinti++;
            }
        }
    }
    else if(fase == finale)
    {
        for (i = 0; i < game->numGiocatoriUtente; ++i)
        {
            if(isInGruppo(game->profiliGiocatore[game->indiciGU[i]].id, gruppo))
            {
                //Viene incrementato il numero di giochi giocati
                game->profiliGiocatore[game->indiciGU[i]].numGiochiGiocati++;
                //Viene incrementato il numero di finali giocate
                game->profiliGiocatore[game->indiciGU[i]].numFinali++;
                //Se il profilo utente ha vinto
                if(game->profiliGiocatore[game->indiciGU[i]].id == id_vincitore)
                {
                    //Viene incrementato il numero di giochi vinti
                    game->profiliGiocatore[game->indiciGU[i]].numGiochiVinti++;
                    //Viene incrementato il numero di SPR1D GAME vinti
                    game->profiliGiocatore[game->indiciGU[i]].numSGVinti++;
                }
            }
        }
    }

    //Si eliminano i giocatori che non hanno vinto
    for (i = 0; i < gruppo.sizeGruppo; ++i)
        if (gruppo.id_membri[i] != id_vincitore)
            game->inGioco[gruppo.id_membri[i]] = false;
}

void Fase0_1_provaMinigioco()
{
    //Dichiarazione variabili
    Gioco* game;
    int players, num, i, id_vincitore;
    Gruppo gruppo;
    Games gioco;

    game = loadDefaultGame(); //Si carica il gioco di default

    //STAMPA DEL MENU
    printf(P_BG_BRIGHT_BLACK P_FG_BRIGHT_WHITE " Quale gioco vuoi provare? " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  0 " P_BG_CYAN P_FG_BLACK        " Indovina il numero    " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  1 " P_BG_BRIGHT_BLUE P_FG_BLACK " Pari o Dispari        " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  2 " P_BG_CYAN P_FG_BLACK        " Dadi                  " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  3 " P_BG_BRIGHT_BLUE P_FG_BLACK " Morra cinese          " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  4 " P_BG_CYAN P_FG_BLACK        " Murra                 " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  5 " P_BG_BRIGHT_BLUE P_FG_BLACK " Tris                  " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  6 " P_BG_CYAN P_FG_BLACK        " Biglie                " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  7 " P_BG_BRIGHT_BLUE P_FG_BLACK " Ponte di vetro        " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  8 " P_BG_CYAN P_FG_BLACK        " L'impiccato           " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE "  9 " P_BG_BRIGHT_BLUE P_FG_BLACK " Blackjack             " P_RESET "\n");
    printf(P_BG_BLUE P_FG_BRIGHT_WHITE " -1 " P_BG_CYAN P_FG_BLACK        " Torna indietro        " P_RESET "\n");

    printf("Scegli un numero:");
    gioco = getIntInRange("Scegli un numero nel range -1 - 9", -1 , 9);

    if(gioco == -1)
    {
        //Caso in cui si vuole tornare indietro
        free(gruppo.id_membri);
        fineGioco(game);
        clearScreen();
        return;
    }

    if(gioco == Indovina_il_numero || gioco == Impiccato || gioco == PonteDiVetro)
        num = NUMPLAYERS_IMPICCATO; //Gioco scelto da 4 gioctori
    else
        num = NUMPLAYERS_PARIODISPARI; //Gioco scelto da 2 giocatori

    printf("\nQuanti giocatori saranno controllati dall'utente? [1-%d]:", num);
    players = getIntInRange("Scegli un numero valido", 1 , num);

    gruppo.sizeGruppo = num;
    gruppo.id_membri = (int*) malloc(sizeof(int) * num);

    for (i = 0; i < num; ++i)
    {
        //Si inseriscono i giocatori nel gruppo
        if(i < players)
            gruppo.id_membri[i] = game->profiliGiocatore[game->indiciGU[i]].id;
        else
            gruppo.id_membri[i] = i;
    }

    clearScreen();

    //Stampa delle istruzioni relative al gioco estratto
    switch (gioco)
    {
        case Indovina_il_numero:

            printf("Vuoi leggere come si gioca a \"Indovina Il numero\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_ILN);
                premereInvio();
            }
            clearScreen();

            id_vincitore = game_IndovinaIlNumero(game, gruppo);

            break;
        case PariODispari:

            printf("Vuoi leggere come si gioca a \"Pari o Dispari\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_POD);
                premereInvio();

            }
            clearScreen();

            id_vincitore = game_PariODispari(game, gruppo);

            break;
        case Dadi:

            printf("Vuoi leggere come si gioca a \"Dadi\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_DADI);
                premereInvio();
            }
            clearScreen();

            id_vincitore = game_Dadi(game, gruppo);

            break;
        case MorraCinese:

            printf("Vuoi leggere come si gioca a \"Morra Cinese\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_MC);
                premereInvio();
            }

            clearScreen();

            id_vincitore = game_MorraCinese(game, gruppo);

            break;
        case Murra:

            printf("Vuoi leggere come si gioca a \"Murra\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_MURRA);
                premereInvio();
            }

            clearScreen();

            id_vincitore = game_Murra(game, gruppo);

            break;
        case Tris:

            printf("Vuoi leggere come si gioca a \"Tris\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_TRIS);
                premereInvio();
            }

            clearScreen();

            id_vincitore = game_Tris(game, gruppo);

            break;
        case Biglie:

            printf("Vuoi leggere come si gioca a \"Biglie\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_BIGLIE);
                premereInvio();
            }

            clearScreen();

            id_vincitore = game_Biglie(game, gruppo);

            break;
        case PonteDiVetro:

            printf("Vuoi leggere come si gioca a \"Ponte di vetro\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_PDV);
                premereInvio();
            }

            clearScreen();

            id_vincitore = game_PonteDiVetro(game, gruppo);

            break;
        case Impiccato:

            printf("Vuoi leggere come si gioca a \"L' Impiccato\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_IMPICCATO);
                premereInvio();
            }

            clearScreen();

            id_vincitore = game_Impiccato(game, gruppo);

            break;
        case BlackJack:

            printf("Vuoi leggere come si gioca a \"BlackJack\"? [s/n]\n");
            if(getYesNo())
            {
                clearScreen();
                printInfo(ISTRUZIONI_BLACKJACK);
                premereInvio();
            }

            clearScreen();

            id_vincitore = game_Blackjack(game, gruppo);

            break;
        default:
            break;
    }

    printf("\n");
    printNomefromID(game, id_vincitore);
    printf(" HA VINTO\n\n");

    premereInvio();
    clearScreen();

    free(gruppo.id_membri);
    fineGioco(game);
}

Gioco* loadDefaultGame()
{
    //Dichiarazione variabili
    Gioco* game = (Gioco*) malloc(sizeof(Gioco));
    int i, id;

    game->numGiocatori = NUM_DEFAULT_PLAYERS;
    game->numProfiliCreati = NUM_DEFAULT_GU;
    game->profiliGiocatore = (ProfiloGiocatore*) malloc(sizeof(ProfiloGiocatore) * NUM_DEFAULT_GU);
    i = 0;
    id = FIRST_DEFAULD_ID;

    //Creazione primo giocatore
    game->profiliGiocatore[i] = createNewPG("Giocatore 1");
    game->profiliGiocatore[i].id = id;
    i++;
    id++;

    //Creazione secondo giocatore
    game->profiliGiocatore[i] = createNewPG("Giocatore 2");
    game->profiliGiocatore[i].id = id;
    i++;
    id++;

    //Creazione terzo giocatore
    game->profiliGiocatore[i] = createNewPG("Giocatore 3");
    game->profiliGiocatore[i].id = id;
    i++;
    id++;

    //Creazione quarto giocatore
    game->profiliGiocatore[i] = createNewPG("Giocatore 4");
    game->profiliGiocatore[i].id = id;

    //Creazione e inizializzazione dell'array indiciGU
    game->numGiocatoriUtente = NUM_DEFAULT_GU;
    game->indiciGU = (int*) malloc(sizeof(int) * NUM_DEFAULT_GU);
    for (i = 0; i < NUM_DEFAULT_GU; ++i)
        game->indiciGU[i] = i;


    game->inCorso = true;

    game->inGioco = (int*) malloc(sizeof(int) * NUM_DEFAULT_PLAYERS);
    for (i = 0; i < NUM_DEFAULT_PLAYERS; ++i)
        game->inGioco[i] = true;

    return game;
}