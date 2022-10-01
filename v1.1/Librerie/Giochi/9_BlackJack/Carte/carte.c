#include "carte.h"

char* semeConvertion(Seme seme)
{
    switch (seme)
    {
        case Cuori:
            return "♥";
        case Quadri:
            return "♦";
        case Fiori:
            return "♣";
        case Picche:
            return "♠";
        default:
            return "seme non valido";
    }
}

void printCarta(Carta carta)
{
    char* coloreSeme;
    char* seme = semeConvertion(carta.seme);

    if(carta.seme == Quadri ||carta.seme == Cuori)
        coloreSeme = P_FG_RED;
    else
        coloreSeme = P_FG_BLACK;

    switch (carta.val)
    {
        case 1:
            printf( P_BG_BRIGHT_WHITE "%s%s A" P_RESET "\n", coloreSeme, seme);
            printf( P_BG_BRIGHT_WHITE "%sA %s" P_RESET "\n", coloreSeme, seme);
            break;
        case 13:
            printf( P_BG_BRIGHT_WHITE "%s%s K" P_RESET "\n", coloreSeme, seme);
            printf( P_BG_BRIGHT_WHITE "%sK %s" P_RESET "\n", coloreSeme, seme);
            break;
        case 12:
            printf( P_BG_BRIGHT_WHITE "%s%s Q" P_RESET "\n", coloreSeme, seme);
            printf( P_BG_BRIGHT_WHITE "%sQ %s" P_RESET "\n", coloreSeme, seme);
            break;
        case 11:
            printf( P_BG_BRIGHT_WHITE "%s%s J" P_RESET "\n", coloreSeme, seme);
            printf( P_BG_BRIGHT_WHITE "%sJ %s" P_RESET "\n", coloreSeme, seme);
            break;
        default:
            printf( P_BG_BRIGHT_WHITE "%s%s%2d" P_RESET "\n", coloreSeme, seme, carta.val);
            printf( P_BG_BRIGHT_WHITE "%s%-2d%s" P_RESET "\n", coloreSeme, carta.val, seme);
    }
}

Carta creaCarta()
{
    Carta carta;
    int tmp;
    printf("%s = 1\n", semeConvertion(Cuori));
    printf("%s = 2\n",semeConvertion(Quadri));
    printf("%s = 3\n",semeConvertion(Fiori));
    printf("%s = 4\n",semeConvertion(Picche));
    printf("Inserire il seme della carta:");
    tmp = getIntInRange("Il numero deve essere nel range 1-4:",1,4);
    carta.seme = tmp - 1;
    printf("Inserire il valore della carta:");
    carta.val = getIntInRange("Il numero deve essere nel range 1-13:",1,13);
    return carta;
}

void printCartaSU(Carta carta)
{
    char* coloreSeme;
    char* seme = semeConvertion(carta.seme);

    if(carta.seme == Quadri ||carta.seme == Cuori)
        coloreSeme = P_FG_RED;
    else
        coloreSeme = P_FG_BLACK;

    switch (carta.val)
    {
        case 1:
            printf( P_BG_BRIGHT_WHITE "%s%s A" P_RESET, coloreSeme, seme);
            break;
        case 13:
            printf( P_BG_BRIGHT_WHITE "%s%s K" P_RESET, coloreSeme, seme);
            break;
        case 12:
            printf( P_BG_BRIGHT_WHITE "%s%s Q" P_RESET, coloreSeme, seme);
            break;
        case 11:
            printf( P_BG_BRIGHT_WHITE "%s%s J" P_RESET, coloreSeme, seme);
            break;
        default:
            printf( P_BG_BRIGHT_WHITE "%s%s%2d" P_RESET, coloreSeme, seme, carta.val);
    }
}

void printCartaGIU(Carta carta)
{
    char* coloreSeme;
    char* seme = semeConvertion(carta.seme);

    if(carta.seme == Quadri ||carta.seme == Cuori)
        coloreSeme = P_FG_RED;
    else
        coloreSeme = P_FG_BLACK;

    switch (carta.val)
    {
        case 1:
            printf( P_BG_BRIGHT_WHITE "%sA %s" P_RESET, coloreSeme, seme);
            break;
        case 13:
            printf( P_BG_BRIGHT_WHITE "%sK %s" P_RESET, coloreSeme, seme);
            break;
        case 12:
            printf( P_BG_BRIGHT_WHITE "%sQ %s" P_RESET, coloreSeme, seme);
            break;
        case 11:
            printf( P_BG_BRIGHT_WHITE "%sJ %s" P_RESET, coloreSeme, seme);
            break;
        default:
            printf( P_BG_BRIGHT_WHITE "%s%-2d%s" P_RESET, coloreSeme, carta.val, seme);
    }
}

void printDueCarte(Carta cartaSX, Carta cartaDX)
{
    printCartaSU(cartaSX);
    printf("%36s","");
    printCartaSU(cartaDX);
    printf("\n");
    printCartaGIU(cartaSX);
    printf("%36s","");
    printCartaGIU(cartaDX);
    printf("\n");
}

void printMazzoDX(Mazzo* mazzo)
{
    if(mazzo!=NULL)
    {
        printf("%39s","");
        printCartaSU(mazzo->carta);
        printf("\n%39s","");
        printCartaGIU(mazzo->carta);
        printf("\n\n");
        printMazzoDX(mazzo->next);
    }
}

Carta creaCartaParam(Seme seme, int val)
{
    Carta carta;
    if(isInRange(seme, Cuori, Picche))
        carta.seme = seme;
    else
    {
        printf( "SEME NON VALIDO!\n");
        carta.seme = 0;
    }
    if(isInRange(val, 1, 13))
        carta.val = val;
    else
    {
        printf("VALORE NON VALIDO!\n");
        carta.val = 0;
    }
    return carta;
}

Mazzo* allocaMazzo()
{
    return (Mazzo*) malloc(sizeof (Mazzo));
}

Mazzo* creaMazzo()
{
    Mazzo* mazzo = allocaMazzo();
    int inserire;
    printf("Inserire un'altra carta? [s/n]\n");
    inserire = getYesNo();
    if(inserire)
    {
        Carta carta = creaCarta();
        mazzo->carta = carta;
        mazzo->next = creaMazzo();
    }
    else
        mazzo = NULL;
    return mazzo;
}

void printMazzo(Mazzo* mazzo)
{
    if(mazzo!=NULL)
    {
        printCarta(mazzo->carta);
        printf("\n");
        printMazzo(mazzo->next);
    }
}

void printDueMazzi(Mazzo* mazzoSX, Mazzo* mazzoDX)
{
    if(mazzoSX != NULL && mazzoDX != NULL)
    {
        printDueCarte(mazzoSX->carta,mazzoDX->carta);
        printf("\n");
        printDueMazzi(mazzoSX->next,mazzoDX->next);
    }
    else if(mazzoSX != NULL)
    {
        printMazzo(mazzoSX);
    }
    else if(mazzoDX != NULL)
    {
        printMazzoDX(mazzoDX);
    }
}

void printMazzoCounter(Mazzo* mazzo, int i)
{
    if(mazzo!=NULL)
    {
        printf("carta num. %d\n",i);
        printCarta(mazzo->carta);
        printf("\n");
        printMazzoCounter(mazzo->next, i+1);
    }
}

void aggiungiCartaInCima(Mazzo** mazzo, Carta carta)
{
    Mazzo* nuovaCarta = allocaMazzo();
    nuovaCarta->carta = carta;
    nuovaCarta->next = *mazzo;
    *mazzo = nuovaCarta;
}

void aggiungiCartaInfondo(Mazzo** mazzo, Carta carta)
{
    if(*mazzo == NULL)
    {
        *mazzo = allocaMazzo();
        (*mazzo)->carta = carta;
        (*mazzo)->next = NULL;
    }
    else if((*mazzo)->next == NULL)
    {
        Mazzo* mazzo_new = allocaMazzo();
        mazzo_new->carta = carta;
        mazzo_new->next = NULL;
        (*mazzo)->next = mazzo_new;
    }
    else
        aggiungiCartaInfondo(&(*mazzo)->next, carta);
}

Carta pescaCarta(Mazzo** mazzo)
{
    Carta carta;
    if(mazzo == NULL)
    {
        carta.seme = 1;
        carta.val = 0;
        printf("MAZZO VUOTO!\n");
        return carta;
    }
    Mazzo* prima_carta = *mazzo;
    carta = prima_carta->carta;
    (*mazzo) = (*mazzo)->next;
    free(prima_carta);
    return carta;
}

Mazzo* creaMazzoCompleto()
{
    return creaMazzoCompleto_rec(0);
}

Mazzo* creaMazzoCompleto_rec(int i)
{
    Mazzo* mazzo = allocaMazzo();
    if(i < NUM_CARTE)
    {
        mazzo->carta = creaCartaParam(i / NUM_CARTEPERSEME ,
                                      i % NUM_CARTEPERSEME + 1);
        mazzo->next = creaMazzoCompleto_rec(i + 1);
        return mazzo;
    }
    else
        return NULL;
}

void mischiaMazzo(Mazzo** mazzo, int loops)
{
    int i;
    Mazzo* mazzo_tmp = allocaMazzo();
    mazzo_tmp = NULL;
    for (i = 0; i < loops; ++i)
    {
        riffleShuffle(mazzo);
        mazzo_tmp = smezza(*mazzo, randNumInRange(1,NUM_CARTE-1));
        unisciMazzi(mazzo_tmp,*mazzo);
        riffleShuffle(&mazzo_tmp);
        *mazzo = smezza(mazzo_tmp, randNumInRange(1,NUM_CARTE-1));
        unisciMazzi(*mazzo,mazzo_tmp);
    }
}

void riffleShuffle(Mazzo** mazzo)
{
    Mazzo* mazzo2 = allocaMazzo();
    Mazzo* mazzo_res = allocaMazzo();
    mazzo_res = NULL;
    Carta carta;
    mazzo2 = smezza(*mazzo,NUM_CARTE/2);

    while (*mazzo != NULL)
    {
        carta = pescaCarta(mazzo);
        aggiungiCartaInfondo(&mazzo_res,carta);
        carta = pescaCarta(&mazzo2);
        aggiungiCartaInfondo(&mazzo_res,carta);
    }
    *mazzo = mazzo_res;
}

Mazzo* smezza(Mazzo* mazzo, int numCartePrimoMazzo)
{
    if(numCartePrimoMazzo < 1)
    {
        perror("Fornire un numero maggiore di 1\n");
        return NULL;
    }
    if(numCartePrimoMazzo == 1)
    {
        Mazzo* mazzo_res = allocaMazzo();
        mazzo_res = mazzo->next;
        mazzo->next = NULL;
        return mazzo_res;
    }
    else
        smezza(mazzo->next, numCartePrimoMazzo - 1);
}

void unisciMazzi(Mazzo* mazzo, Mazzo* mazzo_aggiunto)
{
    if(mazzo->next == NULL)
        mazzo->next = mazzo_aggiunto;
    else
        unisciMazzi(mazzo->next,mazzo_aggiunto);
}