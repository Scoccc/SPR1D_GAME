#include "spr1dgamelib.h"

void printSaves()
{
    //Dichiarazione variabili
    FILE* saveInfo;           //File contenente i nomi dei file di salvataggio
    int i;                    //Variabile contatore
    char nomeFile[NAME_SIZE]; //Nome del file letto

    saveInfo = fopen(SAVEINFO_LOCATION,"r"); //Si apre il file in lettura

    if(saveInfo == NULL)
    {
        //Errore nell'apertura del file
        perror("Errore durante l' apertura aprire il file saveFileInfo.txt"); //Stampa del messaggio d'errore
        return; //Termine della procedura
    }
    else
    {
        //File aperto correttamente
        printf(P_BG_BLUE P_FG_BRIGHT_WHITE " ID  %-64s" P_RESET "\n", "NOME DEL FILE"); //Prima rida della tabella
        i = 0;
        while (fscanf(saveInfo,"%s", nomeFile) == 1) //Cicla finchè fscanf legge una stringa
        {
            printf(P_BG_BLUE P_FG_BRIGHT_WHITE " %2d ",i); //Si scrive il numero su sfondo blu e testo bianco

            //Scrittura del nome del file
            if(pari(i)) //Le righe pari avranno un colore, le dispari un altro
                printf(P_BG_CYAN P_FG_BLACK " %-64s" P_RESET "\n",nomeFile); //Sfondo ciano, testo nero
            else
                printf(P_BG_BRIGHT_BLUE P_FG_BLACK " %-64s" P_RESET "\n",nomeFile); //Sfondo blu chiaro, testo nero

                /* * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                 * %-64s in questo caso viene utilizzato per rendere tutte le righe della seconda colonna *
                 * della stessa larghezza, ovvero 64 caratteri, il meno allinea il testo a sinistra       *
                 * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

            i++; //Incremento della variabile
        }
    }

    fclose(saveInfo); //Chiusura del file
}

void printNomefromID(Gioco* game, int id)
{
    //Dichiarazione variabili
    ProfiloGiocatore player; //Profilo Giocatore di cui si vuole stampare il nome

    if(isCPU(game,id))
    {
        //Se l'ID corrisponde ad una CPU
        font_changeFGColor(getColoreFromID(id)); //Si cambia il colore con quello associato all'ID
        printf("CONCORRENTE #%03d",id); //Stampa nome della CPU
        font_reset(); //Si resetta il colore
    }
    else
    {
        //Se l'ID corrisponde a un Profilo Giocatore
        player = getPGfromID(game, id); //Si ricava il Profilo Giocatore
        font_changeFGColor(getColoreFromID(player.id)); //Si cambia il colore con quello associato all'ID
        printf("%s",player.nome); //Stampa del nome
        font_reset(); //Si resetta il colore
    }
}

Colore getColoreFromID(int id)
{
    //Dichiarazione variabili
    int j;

    j = (id % NUM_COLORI);

    if(isInRange(j, 0, (NUM_COLORI / 2) - 1))
        return FG_RED + j;
    else
        return FG_BRIGHT_RED + j - (NUM_COLORI / 2);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * I colori non sono associati a numeri progressivi, ma sono progressivi                 *
     * a gruppi i colori chiari e i colori scuri, con un gap tra i due gruppi.               *
     *                                                                                       *
     * Quindi per ricavare il colore corretto partendo da un' ID bisogna:                    *
     * 1)trovare un valore j facendo id % NUM_COLORI, in modo che si ottenga un valore       *
     *   sempre compreso tra 0 e il numero di colori disponibili - 1.                        *
     * 2)Verificare in che gruppo di colori ci si trova (chiari o scuri)                     *
     *   Da 0 a [(NUM_COLORI / 2) - 1] (5) ci sono i colori scuri;                           *
     *   Da (NUM_COLORI / 2) (6) a NUM_COLORI - 1 ci sono i colori chiari;                   *
     * 3)Se il colore è un colore scuro basterà sommare al valore del colore con numero      *
     *   più basso (rosso scuro) la j trovata.                                               *
     *   Se invece ci si trova tra i colori scuri, bisognerà sottrarre alla nostra j la metà *
     *   dei colori possibili, per riottenere un numero che vada da 0 a 5, e sommare questo  *
     *   numero al colore chiaro con numero più basso (rosso chiaro).                        *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
}

void printMenuPGs(Gioco* game)
{
    //Dichiarazione variabili
    int i;

    printf(P_BG_BLUE P_FG_BRIGHT_WHITE " NUM  %-64s" P_RESET "\n", "NOME DEL GIOCATORE"); //Sfondo blu, scritta in bianca
    for (i = 0; i < game->numProfiliCreati; ++i)
        if(checkProfiloScelto(game, i)) //Si visualizzano solo i Profili Utente disponibili
        {
            //si stampa il numero corrispondente al Profilo Giocatore
            printf(P_BG_BLUE P_FG_BRIGHT_WHITE " %3d " P_RESET , i); //Sfondo blu, scritta in bianca

            //Si stampa il nome del Profilo Giocatore corrente
            if(pari(i)) //Le righe pari avranno un colore, le dispari un altro
                printf(P_BG_CYAN P_FG_BLACK " %-64s" P_RESET,game->profiliGiocatore[i].nome); //Sfondo ciano, testo nero
            else
                printf(P_BG_BRIGHT_BLUE P_FG_BLACK " %-64s" P_RESET,game->profiliGiocatore[i].nome); //Sfondo blu chiaro, testo nero

            /* * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
             * %-64s in questo caso viene utilizzato per rendere tutte le righe della seconda colonna *
             * della stessa larghezza, ovvero 64 caratteri, il meno allinea il testo a sinistra       *
             * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

            printf("\n");
        }
}

int getNumGruppiScrematura(int numPlayers)
{
    //Dichiarazione variabili
    int esp = 0, res;

    while (pow(2,esp) < numPlayers) //Si cicla finchè 2^esp è strettamente minore di numPlayers
        esp ++; //Si incrementa l'esponente
    // Si esce dal ciclo quando 2^esp è maggiore-uguale al numero di players,
    // quindi l'esponente va decrementato di uno per ottenere la potenza di 2
    //subito minore la numero dato.
    esp--;

    //Il numero restituito sarà la potenza di due data dall'esponente trovato - 1.
    res = (int) pow(2,esp - 1);

    return res;
}

Gruppo* formaGruppiScrematura(Gioco* game, int numGruppi)
{
    //Dichiarazione variabili
    int i, j, sizeGruppo, resto, index_gruppo;
    Gruppo* gruppi;
    int* PlayersInGruppo; //array

    gruppi = (Gruppo*) malloc(numGruppi * sizeof(Gruppo));

    PlayersInGruppo = (int*) calloc(numGruppi,sizeof(int));
    //Si calcola il resto della divisione numPlayers / numGruppi, questo
    //corrisponderà al numero di gruppi che avranno un giocatore in più
    resto = game->numGiocatori % numGruppi;

    for (i = 0; i < numGruppi; ++i)
    {
        if(i < resto) //Si aggiunge un giocatore a un numero di gruppi pari a 'resto'
            sizeGruppo = (game->numGiocatori / numGruppi) + 1;
        else
            sizeGruppo = (game->numGiocatori / numGruppi);

        gruppi[i].sizeGruppo = sizeGruppo;
        gruppi[i].id_membri = (int *) malloc(sizeGruppo * sizeof(int));
    }

    for (i = 0; i < game->numGiocatori; ++i)
    {
        do
        {
            //Si cerca di generare il numero corrispondente a un gruppo che non ha già
            //superato il numero massimo di giocatori che può contenere
            index_gruppo = randNumInRange(0,numGruppi - 1);
        }
        while (PlayersInGruppo[index_gruppo] >= gruppi[index_gruppo].sizeGruppo);

        gruppi[index_gruppo].id_membri[PlayersInGruppo[index_gruppo]] = i;

        PlayersInGruppo[index_gruppo]++;
    }
    printf("\nGRUPPI SCREMATURA\n\n");
    for(i = 0; i < numGruppi; ++i)
    {
        printf("Gruppo %d:\t",i);
        for (j = 0; j < gruppi[i].sizeGruppo; ++j)
        {
            if (!isCPU(game,gruppi[i].id_membri[j]))
                font_changeFGColor(getColoreFromID(gruppi[i].id_membri[j]));
            else
                font_changeFGColor(FG_BRIGHT_BLACK);
            printf("%4d\t" P_RESET, gruppi[i].id_membri[j]);
        }
        printf("\n");
    }
    printf("\n");

    free(PlayersInGruppo);

    return gruppi;
}

Gruppo* formaGruppiSvolgimento(Gioco* game, int numPlayerGruppo)
{
    //Dichiarazione variabili
    int i, j, sizeGruppo, index_gruppo, numGruppi;
    Gruppo* gruppi;
    int* PlayersInGruppo;

    numGruppi = numInGioco(game) / numPlayerGruppo;
    gruppi = (Gruppo*) malloc(numGruppi * sizeof(Gruppo));
    PlayersInGruppo = (int*) calloc(numGruppi,sizeof(int));

    for (i = 0; i < numGruppi; ++i)
    {
        gruppi[i].sizeGruppo = numPlayerGruppo;
        gruppi[i].id_membri = (int*) malloc(sizeGruppo * sizeof(int));
    }

    for (i = 0; i < game->numGiocatori; ++i)
    {
        if(game->inGioco[i])
        {
            do
            {
                //Si cerca di generare il numero corrispondente a un gruppo che non ha già
                //Superato il numero massimo di giocatori che può contenere
                index_gruppo = randNumInRange(0, numGruppi - 1);
            }
            while (PlayersInGruppo[index_gruppo] >= gruppi[index_gruppo].sizeGruppo);

            gruppi[index_gruppo].id_membri[PlayersInGruppo[index_gruppo]] = i;

            PlayersInGruppo[index_gruppo]++;
        }
    }

    printf("\nGRUPPI FORMATI\n\n");
    for(i = 0; i < numGruppi; ++i)
    {
        printf("Gruppo %d:\t",i);
        for (j = 0; j < gruppi[i].sizeGruppo; ++j)
        {
            if (!isCPU(game,gruppi[i].id_membri[j]))
                font_changeFGColor(getColoreFromID(gruppi[i].id_membri[j]));
            else
                font_changeFGColor(FG_BRIGHT_BLACK);
            printf("%4d\t" P_RESET, gruppi[i].id_membri[j]);
        }
        printf("\n");
    }
    printf("\n");

    free(PlayersInGruppo);

    return gruppi;
}

Gruppo formaGruppoFinale(Gioco* game)
{
    Gruppo gruppo;
    int i, inserimento;
    //inserimento = 0, bisogna inserire il primo id
    //inserimento = 1, bisogna inserire il secondo id
    //inserimento > 1, non bisogna più inserire id


    gruppo.sizeGruppo = 2; //In finale ci saranno sempre 2 giocatori
    gruppo.id_membri = (int*) malloc(sizeof(int) * gruppo.sizeGruppo); //Si alloca lo spazio per contenere gli id dei partecipanti

    inserimento = 0; //Inizializzazione inserimento
    for(i = 0; i < game->numGiocatori; i++) //Si scorrono tutti i giocatori dello SPR1D GAME
        if(game->inGioco[i]) //Se il giocatore non è stato eliminato
        {
            gruppo.id_membri[inserimento] = i; //Si aggiunge il giocatore al gruppo per la finale
            inserimento++;
            if(inserimento > 1)
                i = game->numGiocatori; //Si forza la termine del ciclo
        }

    return gruppo;
}

_Bool isCPU(Gioco* game, int id)
{
    //Dichiarazione variabili
    int i;

    for (i = 0; i < game->numGiocatoriUtente; ++i)
        if(PGfromIndiceGU(i).id == id)
            return false;

    return true;
}

ProfiloGiocatore createNewPG(char nome[NAME_SIZE])
{
    //Dichiarazione variabili
    ProfiloGiocatore nuovoProfiloUtente;

    strcpy(nuovoProfiloUtente.nome,nome);

    nuovoProfiloUtente.id = NULL_ID;
    nuovoProfiloUtente.numSGVinti = 0;
    nuovoProfiloUtente.numSGGiocati = 0;
    nuovoProfiloUtente.numFinali = 0;
    nuovoProfiloUtente.numGiochiGiocati = 0;
    nuovoProfiloUtente.numGiochiVinti = 0;

    return nuovoProfiloUtente;
}

_Bool checkNomeUnivoco(char nome[NAME_SIZE], Gioco* game)
{
    int i;
    for (i = 0; i < game->numProfiliCreati; ++i)
        if (strcmp(nome, game->profiliGiocatore[i].nome) == 0)
            return false;
    return true;
}

void printPG(Gioco* game, ProfiloGiocatore player)
{
    if(game->inCorso)
    {
        //Si stampa lo stato attuale del player
        printf("Stato: ");
        if(player.id == NULL_ID)
            printf("non selezionato\n");
        else if(game->inGioco[player.id])
            printf("in gara\n");
        else
            printf("eliminato\n");

        //Si stampa il nome del player
        printf(" Nome: ");
        if (!game->inGioco[player.id] || player.id == NULL_ID)       //Se è stato eliminato o non è stato selezionato
            font_changeFGColor(FG_BRIGHT_BLACK);                //si scrive il nome in grigio
        else                                                         //altrimenti
            font_changeFGColor(getColoreFromID(player.id)); //si scrive il nome colorato
        printf("%s\n", player.nome);
        font_reset();

        //Si stampa l'ID del player
        printf("   ID: ");
        if (!game->inGioco[player.id] || player.id == NULL_ID)       //Se è stato eliminato o non è stato selezionato
            font_changeFGColor(FG_BRIGHT_BLACK);                //si scrive l' ID in grigio
        else                                                         //altrimenti
            font_changeFGColor(getColoreFromID(player.id)); //si scrive l' ID colorato
        printf("%d\n", player.id);
        font_reset();

        //Si stampano le statistiche
        printSPR1DGAMEtotali(player);
        printGiochiTotali(player);
        //Si lasciano due righe vuote
        printf("\n\n");
    }
    else
    {
        //Si scrive il nome del player
        printf(" NOME: %s\n", player.nome);
        //Si stampano le statistiche
        printSPR1DGAMEtotali(player);
        printGiochiTotali(player);
        //Si lasciano due righe vuote
        printf("\n\n");
    }
}

void printAllPGs(Gioco* game)
{
    int i;
    for (i = 0; i < game->numProfiliCreati; ++i)
        printPG(game, game->profiliGiocatore[i]);
}

Gioco* loadGame(const char saveFilePath[PATH_SIZE])
{
    Gioco* game = (Gioco*) malloc(sizeof(Gioco));
    FILE* sf;
    int i, j, n;

    if(strcmp("", saveFilePath) == 0)
        return initGame();

    sf = fopen(saveFilePath,"rb");

    if(sf == NULL)
    {
        fclose(sf);
        return NULL;
    }

    if(fread(&game->numProfiliCreati, sizeof(int), 1, sf) == 0)
    {
        fclose(sf);
        return NULL;
    }

    game->profiliGiocatore = (ProfiloGiocatore*) malloc(sizeof(ProfiloGiocatore) * game->numProfiliCreati);

    for (i = 0; i < game->numProfiliCreati; ++i)
    {
        if
        (
                fread(&game->profiliGiocatore[i].id, sizeof(int), 1, sf) == 0 ||
                fread(&game->profiliGiocatore[i].nome, sizeof(char) * 64, 1, sf) == 0 ||
                fread(&game->profiliGiocatore[i].numSGVinti, sizeof(int), 1, sf) == 0 ||
                fread(&game->profiliGiocatore[i].numSGGiocati, sizeof(int), 1, sf) == 0 ||
                fread(&game->profiliGiocatore[i].numFinali, sizeof(int), 1, sf) == 0 ||
                fread(&game->profiliGiocatore[i].numGiochiGiocati, sizeof(int), 1, sf) == 0 ||
                fread(&game->profiliGiocatore[i].numGiochiVinti, sizeof(int), 1, sf) == 0
        )
        {
            fclose(sf);
            return NULL;
        }
    }

    if(fread(&game->inCorso, sizeof(int), 1, sf) == 0)
    {
        fclose(sf);
        return NULL;
    }

    if(game->inCorso)
    {
        if
        (
                fread(&game->numGiocatori, sizeof(int), 1, sf) == 0 ||
                fread(&game->numGiocatoriUtente, sizeof(int), 1, sf) == 0
        )
        {
            fclose(sf);
            return NULL;
        }

        game->indiciGU = (int*) malloc(sizeof (int) * game->numGiocatoriUtente);

        for (j = 0; j < game->numGiocatoriUtente; ++j)
            if (fread(&game->indiciGU[j], sizeof(int), 1, sf) == 0)
            {
                fclose(sf);
                return NULL;
            }

        game->inGioco = (int*) malloc(sizeof (int) * game->numGiocatori);

        for (j = 0; j < game->numGiocatori; ++j)
            if (fread(&game->inGioco[j], sizeof(int), 1, sf) == 0)
            {
                fclose(sf);
                return NULL;
            }
    }
    else
    {
        game->numGiocatori = 0;
        game->numGiocatoriUtente = 0;
    }

    fclose(sf);

    //Controllo che il numero di giocatori non eliminati sia una potenza di 2
    n = numInGioco(game);
    if(potenzaDiDue(n))
        return game;
    else
        return NULL;
}

char* getFullPath(char* nome)
{
    //Dichiarazione variabili
    char* fullPath = (char*) malloc(sizeof(char) * PATH_SIZE);

    strcpy(fullPath,"");
    strcat(fullPath,PREFISSO_SAVES); //Si aggiunge il prefisso
    strcat(fullPath,nome); //SI aggiunge il nome del file
    strcat(fullPath,ESTENSIONE_SAVES); //Si aggiunge l'estensione del file

    return fullPath;
}

char* selectSaveFile()
{
    //Dichiarazione variabili
    FILE* tmpfile;
    char saveName[NAME_SIZE];
    _Bool inserito;
    int id;
    char* ptr;

    printSaves();

    do
    {
        printf("Inserire il nome o il numero corrispondente al salvataggio\nOppure premere invio per tornare indietro\n");
        fflush(stdin);
        fgets(saveName,NAME_SIZE,stdin);
        saveName[strlen(saveName)-1] = '\0';

        if(strcmp(NULL_NAME, saveName) == 0)
        {
            return NULL_NAME;
        }
        else if(isdigit(saveName[0]) || saveName[0] == '-')
        {
            id =  strtol(saveName, &ptr, 10);
            if(!isInRange(id, 0, numRigheFile(SAVEINFO_LOCATION) - 1))
            {
                printf("\nNon esiste nessun salvataggio con questo ID\n");
                inserito = false;
            }
            else
                return getSaveFromNum(id);
        }
        else if(strcmp("secretGame",saveName) == 0) //EASTER EGG: partita segreta
        {
            return "secretGame.bin";
        }
        else
        {
            if(isSaveFileValid(saveName))
            {
                tmpfile = fopen(getFullPath(saveName), "rb");

                if (tmpfile == NULL)
                {
                    inserito = false;
                    printf("\nNome non corretto o file inesistente\n");
                }
                else
                {
                    aggiungiSalvataggio(saveName);
                    clearScreen();
                    printf("File aggiunto correttamente\n");
                    printSaves();
                }
                fclose(tmpfile);
            }
            else
                inserito = true;
        }
    }
    while (!inserito);

    return getFullPath(saveName);
}

void printGame(Gioco* gioco)
{
    //Dichiarazione variabili
    int i;

    if(gioco == NULL)
    {
        printf("Gioco non valido\n");
        return;
    }
    printf("numProfiliCreati: %d\n\n", gioco->numProfiliCreati);
    printf("Profili creati:\n\n");
    for (i = 0; i < gioco->numProfiliCreati; ++i)
        printPG(gioco, gioco->profiliGiocatore[i]);
    printf("La partita %s è in corso\n\n", gioco->inCorso ? "" : "non");
    printf("numGiocatori: %d\n\n", gioco->numGiocatori);
    printf("numGiocatoriUtente: %d\n\n", gioco->numGiocatoriUtente);
    for (i = 0; i < gioco->numGiocatoriUtente; ++i)
        printf("indiciGU[%d]: %d\n", i, gioco->indiciGU[i]);
    printf("\n");
    for (i = 0; i < gioco->numGiocatori; ++i)
    {
        if(gioco->inGioco[i])
        {
            font_changeBGColor(BG_BRIGHT_GREEN);
            font_changeFGColor(FG_BLACK);
        }
        printf("eliminati[%d]: %d" P_RESET "\n", i, gioco->inGioco[i]);
    }
}

void fineGioco(Gioco* game)
{
    //Si dealloca lo spazio usato da game e dai suoi campi allocati dinamicamente
    free(game->profiliGiocatore);
    free(game->indiciGU);
    free(game->inGioco);
    free(game);
}

int NumSaves()
{
    //Dichiarazione variabili
    FILE* saveInfo = fopen(SAVEINFO_LOCATION,"r");

    int count;
    char nomeFile[NAME_SIZE];

    if(saveInfo == NULL)
        return 0;
    else
    {
        count = 0;
        while (fscanf(saveInfo,"%s", nomeFile) == 1)
            count++;
    }
    fclose(saveInfo);

    return count;
}

char* getSaveFromNum(int num)
{
    //Dichiarazione variabili
    FILE* saveInfo = fopen(SAVEINFO_LOCATION,"r");

    int i;
    char nomeFile[NAME_SIZE];

    if(saveInfo == NULL || num < 0)
        return NULL_NAME;
    else
    {
        i = 0;
        while (fscanf(saveInfo,"%s", nomeFile) == 1)
        {
            if(i == num)
                return getFullPath(nomeFile);
            i++;
        }
    }
    fclose(saveInfo);

    return NULL_NAME;
}

void aggiungiSalvataggio(char nome[PATH_SIZE])
{
    //Dichiarazione variabili
    FILE * fp = fopen(SAVEINFO_LOCATION,"a");

    fprintf(fp,"%s\n",nome);
    fclose(fp);
}

_Bool isSaveFileValid(char saveFileName[NAME_SIZE])
{
    //Dichiarazione variabili
    FILE* saveInfo = fopen(SAVEINFO_LOCATION,"r");

    char nomeFile[NAME_SIZE];

    if(saveInfo == NULL)
        return false;
    else
    {
        while (fscanf(saveInfo,"%s", nomeFile) == 1)
            if(strcmp(nomeFile,saveFileName) == 0)
            {
                fclose(saveInfo);
                return false;
            }
    }
    fclose(saveInfo);
    return true;
}

void getSaveName(Gioco* game)
{
    //Dichiarazione variabili
    char nomeFile [NAME_SIZE];
    char tmpstr [NAME_SIZE];
    char* ptr;
    int i = 0, id;
    _Bool valid = false, sovrascrivere = true;
    FILE* saveinfo;

    //Si chiede d' inserire un nume da dare al salvataggio finché non si sceglie un file valido
    do
    {
        do
        {
            //Si stampano i salvataggi già esistenti
            printSaves();
            printf("\nInserire il nome del nuovo salvataggio o del salvataggio da sovrascrivere\nOppure inserire il numero del salvataggio da sovrascrivere\n");
            fflush(stdin);
            scanf("%s", tmpstr);

            if (isdigit(tmpstr[0]) || tmpstr[0] == '-')
            {
                saveinfo = fopen(SAVEINFO_LOCATION, "r");
                if (saveinfo != NULL)
                {
                    id = strtol(tmpstr, &ptr, 10);

                    if (isInRange(id, 0, NumSaves() - 1))
                    {
                        while (fscanf(saveinfo, "%s", nomeFile) == 1 && i < id)
                            i++;
                        valid = true;
                    } else
                    {
                        printf("\nNumero scelto non valido\n");
                        strcpy(tmpstr, NULL_NAME);
                        valid = false;
                    }
                } else
                {
                    printf("\nErrore lettura saveInfo\n");
                    strcpy(tmpstr, NULL_NAME);
                    valid = false;
                }
            } else
            {
                i = 0;
                //Si rimuove l'estensione se è stata inserita
                while (i < strlen(tmpstr) && tmpstr[i] != '.')
                {
                    nomeFile[i] = tmpstr[i];
                    i++;
                }
                valid = true;
            }
        } while (!valid);

        //Si aggiunge il salvataggio in saveFileInfo.txt se non è un file sovrascritto
        if (isSaveFileValid(nomeFile))
            aggiungiSalvataggio(nomeFile);
        else
        {
            printf("Sei sicuro di voler sovrascrivere il salvataggio? [s/n]\nI dati sovrascritti saranno persi\n");
            sovrascrivere = getYesNo();
        }
    }
    while(!sovrascrivere);

    saveGame(game, nomeFile);
}

Gioco* initGame()
{
    //Dichiarazione variabili
    Gioco* newGame = (Gioco*) malloc(sizeof(Gioco));

    newGame->numProfiliCreati = 0;
    newGame->profiliGiocatore = (ProfiloGiocatore*) malloc(0);
    newGame->inCorso = 0;
    newGame->numGiocatori = 0;
    newGame->numGiocatoriUtente = 0;
    newGame->indiciGU = (int*) malloc(0);
    newGame->inGioco = (int*) malloc(0);

    return newGame;
}

_Bool inserimentoPG(Gioco* game)
{
    //Dichiarazione variabili
    _Bool continua = false;
    char nome[NAME_SIZE];
    int numAggiunti = 0;

    do
    {
        printf("Inserire nome del nuovo giocatore\nOppure premere invio per non aggiungere altri giocatori\n\n");
        fflush(stdin);
        fgets(nome,NAME_SIZE,stdin);

        nome[strlen(nome) - 1] = '\0'; //Si sostituisce il carattere finale '\n' con '\0'

        if(strcmp(nome, NULL_NAME) != 0) //Se non è stato premuto invio ma è stato inserito un nome
        {
            continua = true;
            if(!checkNomeUnivoco(nome,game))
                printf("\nNome già inserito\nGiocatore non aggiunto\n");
            else
            {
                game->numProfiliCreati++;
                game->profiliGiocatore = realloc(game->profiliGiocatore, sizeof(ProfiloGiocatore) * game->numProfiliCreati);
                game->profiliGiocatore[game->numProfiliCreati - 1] = createNewPG(nome);
                numAggiunti ++;
            }
        }
        else
            continua = false;

        printf("\n");
    }
    while (continua);

    if(numAggiunti > 0) //Se sono stati aggiunti nuovi Profili Utente
        return true;
    else  //Se non sono stati aggiunti nuovi giocatori
        return false;



}

void saveGame(Gioco* game, char nomeFile[NAME_SIZE])
{
    //Dichiarazione variabili
    FILE* saveFile;
    int i;

    saveFile = fopen(getFullPath(nomeFile),"wb");

    if(saveFile == NULL) exit(-1);

    fwrite(&game->numProfiliCreati, sizeof(int), 1, saveFile);

    for (i = 0; i < game->numProfiliCreati; ++i)
    {
        fwrite(&game->profiliGiocatore[i].id, sizeof(int), 1, saveFile);
        fwrite(&game->profiliGiocatore[i].nome, sizeof(char) * 64, 1, saveFile);
        fwrite(&game->profiliGiocatore[i].numSGVinti, sizeof(int), 1, saveFile);
        fwrite(&game->profiliGiocatore[i].numSGGiocati, sizeof(int), 1, saveFile);
        fwrite(&game->profiliGiocatore[i].numFinali, sizeof(int), 1, saveFile);
        fwrite(&game->profiliGiocatore[i].numGiochiGiocati, sizeof(int), 1, saveFile);
        fwrite(&game->profiliGiocatore[i].numGiochiVinti, sizeof(int), 1, saveFile);
    }

    fwrite(&game->inCorso, sizeof(int), 1, saveFile);

    if(game->inCorso)
    {
        fwrite(&game->numGiocatori, sizeof(int), 1, saveFile);
        fwrite(&game->numGiocatoriUtente, sizeof(int), 1, saveFile);

        for (i = 0; i < game->numGiocatoriUtente; ++i)
            fwrite(&game->indiciGU[i], sizeof(int), 1, saveFile);

        for (i = 0; i < game->numGiocatori; ++i)
            fwrite(&game->inGioco[i], sizeof(int), 1, saveFile);
    }

    fclose(saveFile);
}

void sceltaPG(Gioco* game)
{
    //Dichiarazione variabili
    int i, scelta;

    switch (game->numGiocatoriUtente)
    {
        case 0: //Se non si vuole controllare nessun profilo utente non si fa nulla
            break;

        case 1: // Se si vuole controllare un solo profilo utente si hanno due casi:

            // -Si ha un solo profilo utente disponibile, quindi è necessario
            //  chiedere solo l'id da assegnare a quell'utente
            if(game->numProfiliCreati == 1)
            {
                game->indiciGU[0] = 0;
                game->profiliGiocatore[0].id = getIdPg(game);
            }
            // -Si hanno più profili utente tra cui scegliere, quindi
            //  si sceglie il profilo utente e gli si assegna un id.
            else
            {
                printMenuPGs(game);
                printf("\nOra scegli il profilo utente da utilizzare\n");
                game->indiciGU[0] = getIntInRange("Inserire un numero nel giusto range",0,game->numProfiliCreati - 1);
                game->profiliGiocatore[game->indiciGU[0]].id = getIdPg(game);
            }
            break;
        default:
            for (i = 0; i < game->numGiocatoriUtente; ++i)
            {
                clearScreen();
                printMenuPGs(game);
                printf("\nScegli un profilo utente [0 - %d]\n",game->numProfiliCreati - 1);
                do
                {
                    scelta = getIntInRange("Inserire un numero nel giusto range",0,game->numProfiliCreati - 1);
                    if(!checkProfiloScelto(game,scelta))
                        printf("Profilo già in uso\n");
                }
                while (!checkProfiloScelto(game,scelta));
                game->indiciGU[i] = scelta;
                PGfromIndiceGU(i).id = getIdPg(game);
            }
            break;
    }
}

void inserimentoMeN(Gioco* game)
{
    //Dichiarazione variabili
    int i;

    printf("Quanti giocatori parteciperanno allo SPR1D GAME? [almeno 16]\n");
    game->numGiocatori = getIntInRange("Il numero deve essere compreso tra 16 e 100000",MIN_NUM_PLAYERS,MAX_NUM_PLAYERS);

    clearScreen();

    game->inGioco = (int*) malloc(game->numGiocatori * sizeof(int));
    for (i = 0; i < game->numGiocatori; ++i)
        game->inGioco[i] = (int) true;

    if(game->numProfiliCreati > 0) //Se non si sono creati profili utente non ha senso chiedere quanti usarne
    {
        printf("Quanti giocatori saranno controllati dall'utente? [0 - %d]\n", (int) fmin(game->numGiocatori, game->numProfiliCreati));
        game->numGiocatoriUtente = getIntInRange("Il numero deve essere nel giusto range", 0, (int) fmin(game->numGiocatori, game->numProfiliCreati));
    }
    else
        game->numGiocatoriUtente = 0;

    clearScreen();

    game->indiciGU = (int*) malloc(game->numGiocatoriUtente * sizeof(int));
    for (i = 0; i < game->numGiocatoriUtente; ++i)
        game->indiciGU[i] = NULL_ID;
}

int getIdPg(Gioco* game)
{
    //Dichiarazione variabili
    int id;

    printf("Scegli un ID da associare al giocatore[0 - %d]\n",game->numGiocatori - 1);
    do
    {
        id = getIntInRange("Scegli un valore nel giusto range",0,game->numGiocatori -1);
        if(!checkIDunivoco(game,id))
            printf("Id già in uso\n");
    }
    while(!checkIDunivoco(game,id));
    return id;
}

_Bool checkIDunivoco(Gioco* game, int id)
{
    //Dichiarazione variabili
    int i;

    for (i = 0; i < game->numProfiliCreati; ++i)
        if(game->profiliGiocatore[i].id == id)
            return false;
    return true;
}

_Bool checkProfiloScelto(Gioco* game, int id)
{
    //Dichiarazione variabili
    int i;

    for (i = 0; i < game->numGiocatoriUtente; ++i)
        if(game->indiciGU[i] == id)
            return false;
    return true;
}

ProfiloGiocatore getPGfromID(Gioco* game, int id)
{
    //Dichiarazione variabili
    int i;
    ProfiloGiocatore null_player = {NULL_ID, NULL_NAME, 0, 0, 0, 0, 0};

    for (i = 0; i < game->numGiocatoriUtente; ++i)
        if(PGfromIndiceGU(i).id == id)
            return PGfromIndiceGU(i);

    return null_player;
}

_Bool isInGruppo(int id, Gruppo gruppo)
{
    //Dichiarazione variabili
    int i;

    for (i = 0; i < gruppo.sizeGruppo; ++i) //Si controllano tutti i membri di un gruppo
        if(gruppo.id_membri[i] == id)       //se si trova l'id corrispondete a quello cercato
            return true;                    //si interrompe il sottopragramma restituendo true.
    return false; //Se dopo la scansione di tutti i membri non si è trovato l'ID cercato di restituisce false.
}

int randIDfromGruppo(Gruppo gruppo)
{
    int rand_id;
    rand_id = randNumInRange(0,gruppo.sizeGruppo - 1);
    return gruppo.id_membri[rand_id];
}

_Bool isCPUvsCPU(Gioco* game,Gruppo gruppo)
{
    //Dichiarazione variabili
    int i;

    for (i = 0; i < gruppo.sizeGruppo; ++i)     //Si controllano tutti i membri di un gruppo
        if(!isCPU(game,gruppo.id_membri[i])) //se anche solo un membro non è una CPU
            return false;                       //si termina il sottoprogramma restituendo false
    return true; //Se dopo la scansione di tutti i membri erano tutti delle CPU si restituisce true.
}

void cambiaTurno(Turno *indexTurno, int numPlayers)
{
    //Si fa ruotare il turno in avanti con un' operazione in modulo.
    *indexTurno = (*indexTurno + 1) % numPlayers;
}

unsigned int indexLowestIDinGruppo(Gruppo gruppo)
{
    //Dichiarazione variabili
    int min_id = INT_MAX, i, res;

    for (i = 0; i < gruppo.sizeGruppo; i++)
        if(gruppo.id_membri[i] < min_id)
        {
            min_id = gruppo.id_membri[i];
            res = i;
        }
    return res;
}

_Bool RiccardoScateniInGioco(Gioco* game)
{
    int i;
    for (i = 0; i < game->numGiocatoriUtente; ++i)
        if(strcmp(PGfromIndiceGU(i).nome, "Riccardo Scateni") == 0)
            return true;
    return false;
}

void FrontmanDelloSPR1DGAME(Gioco* game, Gruppo gruppo, int* id_vincitore)
{
    //Dichiarazione variabili
    int i, id_Scateni = -1;

    //Ricerca dell'id di Riccardo Scateni se in gioco
    for (i = 0; i < game->numGiocatoriUtente; ++i)
        if(strcmp(PGfromIndiceGU(i).nome, "Riccardo Scateni") == 0)
            id_Scateni = PGfromIndiceGU(i).id;

    //Se Riccardo Scateni fa parte del gruppo diventa automaticamente il vincitore del gioco
    for(i = 0; i < gruppo.sizeGruppo; i++)
        if(gruppo.id_membri[i] == id_Scateni)
            *id_vincitore = id_Scateni;
}

void FallitoDelloSPR1DGAME(Gioco* game, Gruppo gruppo, int* id_vincitore)
{
    //Dichiarazione variabili
    int i, id_Michele = -1, id_newVincitore;

    //Ricerca dell'id di Michele Cocco se in gioco
    for (i = 0; i < game->numGiocatoriUtente; ++i)
        if(strcmp(PGfromIndiceGU(i).nome, "Michele Cocco") == 0)
            id_Michele = PGfromIndiceGU(i).id;

    if(*id_vincitore == id_Michele) //Se Michele Cocco ha vinto il gioco
    {
        //Si genera un nuovo vincitore scelto casualmente tra gli altri membri del gruppo
        do
        {
            id_newVincitore = gruppo.id_membri[randNumInRange(0,gruppo.sizeGruppo-1)];
        }
        while (id_newVincitore == id_Michele);

        //Si cambia il vincitore dle gioco
        *id_vincitore = id_newVincitore;
    }
}

int numInGioco(Gioco* game)
{
    //Dichiarazione variabili
    int i, count = 0;

    for(i = 0; i < game->numGiocatori; i++)
        if(game->inGioco[i])
            count++; //Si contano tutti i giocatori non eliminati

    return count;
}

void printInfo(char* info)
{
    FILE* fp = fopen(info,"r");
    char c;

    if(fp == NULL)
        printf("Impossibile leggere le istruzioni di questo gioco!\n");
    else
    {
        c = (char) fgetc(fp);
        while (c != EOF)
        {
            printf ("%c", c);
            c = (char) fgetc(fp);
        }
    }
    printf("\n");
}

_Bool giocatoriUtenteEliminati(Gioco* game)
{
    //Dichiarazione variabili
    int i;

    //Si esaminano tutti i Profili Giocatore
    for (i = 0; i < game->numGiocatoriUtente; ++i)
        if(game->inGioco[PGfromIndiceGU(i).id]) //Si controlla se il Profili Giocatore corrente è stato eliminato
            return false; //Ne basta almeno uno ancora in gioco per interrompere il sottobragramma restituendo false

    return true; //Si restituisce true se dopo la scansione di tutti i Profili Giocatore nessuno è ancora in gioco
}

void printSPR1DGAMEtotali(ProfiloGiocatore profilo)
{
    int i, vittorie, vittorie_percentuale, finali, finali_percentuale;

    if(profilo.numSGGiocati != 0) //Si evita la divisione per 0
    {
        //Proporzione per adattare i numeri alla lunghezza della barra
        vittorie = LUNGHEZZA_BARRA * profilo.numSGVinti / profilo.numSGGiocati;
        finali = LUNGHEZZA_BARRA * profilo.numFinali / profilo.numSGGiocati;

        //Calcolo percentuali
        vittorie_percentuale = 100 * profilo.numSGVinti / profilo.numSGGiocati;
        finali_percentuale = 100 * profilo.numFinali / profilo.numSGGiocati;
    }
    else
    {
        vittorie = 0;
        finali = 0;

        vittorie_percentuale = 0;
        finali_percentuale = 0;
    }

    printf(" ╒═[SPR1D GAME GIOCATI]═╕    %3d S.G. totali\n", profilo.numSGGiocati);
    printf(" │");

    //Stampa della barra colorata
    for (i = 0; i < LUNGHEZZA_BARRA; ++i)
    {
        if(i < vittorie)
            font_changeBGColor(BG_GREEN);
        else if(i < finali)
            font_changeBGColor(BG_CYAN);
        else
            font_changeBGColor(BG_BRIGHT_BLACK);

        printf( " ");
    }

    font_reset();

    printf("│    " P_FG_GREEN "%3d S.G. vinti (%d%%)\n" P_RESET, profilo.numSGVinti, vittorie_percentuale);

    printf(" ╘══════════════════════╛    " P_FG_CYAN "%3d volte in finale (%d%%)\n" P_RESET, profilo.numFinali, finali_percentuale);
}

void printGiochiTotali(ProfiloGiocatore profilo)
{
    int i, vittorie, vittorie_percentuale;

    if(profilo.numGiochiGiocati != 0) //Si evita la divisione per 0
    {
        //Proporzione per adattare i numeri alla lunghezza della barra
        vittorie = LUNGHEZZA_BARRA * profilo.numGiochiVinti / profilo.numGiochiGiocati;
        //Calcolo della percentuale
        vittorie_percentuale = 100 * profilo.numGiochiVinti / profilo.numGiochiGiocati;
    }
    else
    {
        vittorie = 0;
        vittorie_percentuale = 0;
    }

    printf(" ╒═══[GIOCHI GIOCATI]═══╕    %3d giochi totali\n", profilo.numGiochiGiocati);
    printf(" │");

    //Stampa della barra colorata
    for (i = 0; i < LUNGHEZZA_BARRA; ++i)
    {
        if(i < vittorie)
            font_changeBGColor(BG_GREEN);
        else
            font_changeBGColor(BG_BRIGHT_BLACK);

        printf( " ");
    }

    font_reset();

    printf("│    " P_FG_GREEN "%3d giochi vinti (%d%%)\n" P_RESET, profilo.numGiochiVinti, vittorie_percentuale);

    printf(" ╘══════════════════════╛\n");
}

_Bool potenzaDiDue(int n)
{
    return !(n & (n - 1));

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *                CONTROLLO CHE IL NUMERO SIA UNA POTENZA DI 2                 *
     *                                                                             *
     * In binario un numero N uguale a una potenza di due è sempre composto da un  *
     * solo bit con valore 1 e tutti i restati con valore 0.                       *
     *                                                                             *                                                                             *
     * Esempio:                                                                    *
     *  4 = 000100                                                                 *
     * 16 = 010000                                                                 *
     *                                                                             *
     * Mentre un numero N-1 è composto da bit pari a 0 fino al bit con valore 1    *
     * in N, e poi una serie di bit con valore 1                                   *
     *                                                                             *
     * Esempio:                                                                    *
     *   N = 4 = 000100                                                            *
     * N-1 = 3 = 000011                                                            *
     *                                                                             *
     *   N = 16 = 010000                                                           *
     * N-1 = 15 = 001111                                                           *
     *                                                                             *
     * Facendo quindi l'AND bit a bit tra N e N-1 si ottiene 0.                    *
     * Se N non fosse una potenza di 2 quindi il risultato dell'AND sarebbe 1.     *
     * Si ottiene quindi la formula n & (n-1).                                     *
     * Ora ci basta solo negare l'espressione per ottenere true quando             *
     * l'espressione vale 0 e false quando vale 1.                                 *
     * Ottenendo: !(n & (n-1)).                                                    *
     *                                                                             *
     * Questa funzione restituisce true anche per n = 0, anche se 0 non è potenza  *
     * di 2, ma in questo programma è utile questo funzionamento "sbagliato".      *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
}