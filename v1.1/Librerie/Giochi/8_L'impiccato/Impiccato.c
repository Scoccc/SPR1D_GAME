#include "Impiccato.h"

int game_Impiccato(Gioco* game, Gruppo gruppo)
{
    int id_vincitore;
    Player_Impiccato* players_Impiccato = initPlayersImpiccato(gruppo);
    Parola parola = scegliParola();
    _Bool finita = false;
    Turno index_turno = randNumInRange(primoPlayer,quartoPlayer);
    int numInGioco = NUMPLAYERS_IMPICCATO;
    Tentativo* tentativi = NULL;
    char lastChar;

    font_title("IMPICCATO", FG_CYAN);

    while(!finita)
    {
        if(players_Impiccato[index_turno].numTentativi > 0)
        {
            if(numInGioco == 1)
            {
                printf(P_FG_GREEN "E' rimasto un solo giocatore!\n\n" P_RESET);
                finita = true;
                id_vincitore = players_Impiccato[index_turno].id;
            }
            else
            {
                printNomefromID(game, players_Impiccato[index_turno].id);
                printf(" tocca a te!\n\n");
                printPatibolo(players_Impiccato[index_turno]);
                printParolaOffuscata(parola,lastChar);
                lastChar = faiTentativo(game, &players_Impiccato[index_turno], &parola, &tentativi);
                clearScreen();
                font_title("L' IMPICCATO", FG_CYAN);
                if (checkVittoria(parola))
                {
                    finita = true;
                    id_vincitore = players_Impiccato[index_turno].id;
                }
                else if (players_Impiccato[index_turno].numTentativi == 0)
                {
                    printNomefromID(game, players_Impiccato[index_turno].id);
                    printf(" sei stato eliminato!\n\n");
                    printPatibolo(players_Impiccato[index_turno]);
                    printParolaOffuscata(parola,' ');
                    printf("\n");
                    numInGioco--;
                    premereInvio();
                    clearScreen();
                    font_title("L' IMPICCATO", FG_CYAN);
                }
            }
        }
        cambiaTurno(&index_turno,NUMPLAYERS_IMPICCATO);
    }

    printNomefromID(game, id_vincitore);
    printf(" ha indovinato la parola!\n");

    printf("La parola era: " P_FG_BRIGHT_GREEN "%s\n" P_RESET,parola.completa);

    free(players_Impiccato);

    return id_vincitore;
}

void printPatibolo(Player_Impiccato player_Impiccato)
{
    //Initialization delle parti del corpo da disegnare
    char testaChar     = player_Impiccato.numTentativi < 4 ? testa : ' ';
    char corpoChar     = player_Impiccato.numTentativi < 4 ? corpo : ' ';
    char braccioSXChar = player_Impiccato.numTentativi < 3 ? artoSX : ' ';
    char braccioDxChar = player_Impiccato.numTentativi < 3 ? artoDX : ' ';
    char gambaSXChar   = player_Impiccato.numTentativi < 2 ? artoSX : ' ';
    char gambaDXChar   = player_Impiccato.numTentativi < 1 ? artoDX : ' ';
    //Prima riga del patibolo
    printf(" ╔═══╤\n");
    //Seconda riga del patibolo
    printf(" ║   ");
    //Testa colorata con il colore del player
    font_changeFGColor(getColoreFromID(player_Impiccato.id));
    printf("%c\n",testaChar);
    font_reset();
    //Terza riga del patibolo
    printf(" ║  ");
    //Corpo e braccia colorate con il colore del player
    font_changeFGColor(getColoreFromID(player_Impiccato.id));
    printf("%c%c%c\n",braccioSXChar,corpoChar,braccioDxChar);
    font_reset();
    //Quarta riga del patibolo
    printf(" ║  ");
    //Gambe colorate con il colore del player
    font_changeFGColor(getColoreFromID(player_Impiccato.id));
    printf("%c %c\n", gambaSXChar, gambaDXChar);
    font_reset();
    //Base del patibolo
    printf("─╨─\n");

    /* * * * * *
     *  ╔═══╤  *
     *  ║   O  *
     *  ║  /|\ *
     *  ║  / \ *
     * ─╨─     *
     * * * * * */
}

void printParolaOffuscata(Parola parola, char lastChar)
{
    int i;
    for(i = 0; i < strlen(parola.offuscata); ++i)
    {
        if(parola.offuscata[i] == '_')
                font_changeFGColor(FG_BRIGHT_BLACK);
        else if(toLower(parola.offuscata[i]) == lastChar)
            font_changeFGColor(FG_BRIGHT_GREEN);
        printf("%c",parola.offuscata[i]);
        font_reset();
    }
    printf("\n");
}

char faiTentativo(Gioco* game, Player_Impiccato *player, Parola* parola, Tentativo** tentativi)
{
    char lettera;

    if(isCPU(game, player->id))
    {
        //La CPU genera lettere finché non ne genera una che non è gia stata trovata
        do
        {
            lettera = (char) randNumInRange('a','z');
        } while (IsCharInString(parola->offuscata,lettera) || cercaTentativo(*tentativi, lettera));
        //Si scrive la lettera che ha tentato
        printf("\nInserire una lettera:");
        usleep(GAMES_SPEED); //Simula l'attesa dell'input
        printf( P_FG_CYAN "%c" P_RESET, lettera);
        usleep(GAMES_SPEED); //Simula l'attesa dell'input
    }
    else
    {
        printf("\nInserire una lettera:");
        do
        {
            fflush(stdin);
            //Input della lettera
            scanf("%c%*c", &lettera);
            //Se è stata inserita una lettera maiuscola la si rende minuscola
            lettera = toLower(lettera);
            //Caso in cui si sia inserito un carattere che non è una lettera
            if (!isInRange(lettera, 'a', 'z'))
                printf("Inserire una lettera:");
                //Caso in cui si è inserita una lettera già trovata
            else if (IsCharInString(parola->offuscata,lettera))
                printf("Lettera gia' trovata\nInserire una lettera:");
            else if( cercaTentativo(*tentativi, lettera))
                printf("Lettera gia' cercata\nInserire una lettera:");
        } while (!isInRange(lettera, 'a', 'z') || cercaTentativo(*tentativi, lettera));
    }

    *tentativi = aggiuntiTentativo(lettera, *tentativi);

    if(!checkLettera(parola,lettera))
    {
        player->numTentativi--; //Se la lettera non era nella parola si decrementa il numero di tentativi possibili
        lettera = ' ';
    }
    return lettera;
}

Player_Impiccato* initPlayersImpiccato(Gruppo gruppo)
{
    int i;
    Player_Impiccato* players_Impiccato = (Player_Impiccato*) malloc(sizeof(Player_Impiccato) * gruppo.sizeGruppo);
    for (i = 0; i < NUMPLAYERS_IMPICCATO; ++i)
    {
        players_Impiccato[i].id = gruppo.id_membri[i];
        players_Impiccato[i].numTentativi = NUM_TENTATIVI_MAX;
    }
    return players_Impiccato;
}

void offuscaParola(Parola* parola)
{
    int i;
    strcpy(parola->offuscata,parola->completa);

    //Si trasformano tutte le lettere nel carattere '_'
    for (i = 0; i < strlen(parola->completa); ++i)
        if(isInRange(toLower(parola->completa[i]), 'a', 'z'))
            parola->offuscata[i] = '_';
}

Parola scegliParola()
{
    FILE *fp;
    char riga[BUFFSIZE];
    int parolaSize, i = 1, randNum, dim;
    Parola parola;

    fp = fopen(DEFAULT_DICTIONARY,"r");

    if(fp == NULL)
    {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    else
    {
        fscanf(fp,"%d",&dim);

        randNum = randNumInRange(1, dim);
        //Assegnando a dim il valore minore tra dim e DIM (50) si fa in modo che dim sia <= 50;
        dim = (int) fmin(dim,DIM);

        while(fgets(riga,BUFFSIZE,fp) != NULL)
        {
            if(i == randNum)
            {
                parolaSize = (int) strlen(riga);
                if(riga[parolaSize - 1] == '\n')
                    riga[parolaSize - 1] = '\0';
                strcpy(parola.completa,riga);
                offuscaParola(&parola);
            }
            i++;
        }
    }
    fclose(fp);

    return parola;
}

_Bool checkLettera(Parola* parola, char lettera)
{
    int i;
    _Bool trovata = false;
    for(i = 0; i < strlen(parola->completa);++i)
    {
        if(toLower(parola->completa[i])  == lettera)
        {
            trovata = true;
            parola->offuscata[i] = parola->completa[i];
        }
    }
    return trovata;
}

_Bool checkVittoria(Parola parola)
{
    int i;
    for (i = 0; i < strlen(parola.completa); ++i)
        if(parola.completa[i] != parola.offuscata[i])
            return false;
    return true;
}

_Bool cercaTentativo(Tentativo* tentativi, char c)
{
    if(tentativi == NULL)
        return false;
    else if(tentativi->c == c)
        return true;
    else
        return cercaTentativo(tentativi->next, c);
}

Tentativo* aggiuntiTentativo(char c, Tentativo* tentativi)
{
    Tentativo* nuovoTentativo = (Tentativo*) malloc(sizeof(Tentativo));
    nuovoTentativo->c = c;
    nuovoTentativo->next = tentativi;
    tentativi = nuovoTentativo;
    return tentativi;
}