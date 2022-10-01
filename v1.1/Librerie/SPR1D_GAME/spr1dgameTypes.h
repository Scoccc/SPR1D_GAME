/*
 * Enumerazione che associa:
 * Pari = 0 (resto divindendo per 2 un numero pari)
 * Dispari = 1 (resto divindendo per 2 un numero pari)
 */
typedef enum {Pari, Dispari} pd;

/*
 * Enumerazione che associa al turno di un giocatore la sua posizione dell'array id_membri, in un Gruppo:
 * primoPlayer = 0 (id_membri[0] è il primo giocatore);
 * secondoPlayer = 1 (id_membri[1] è il secondo giocatore);
 * terzoPlayer = 2 (id_membri[2] è il terzo giocatore);
 * quartoPlayer = 3 (id_membri[3] è il quarto giocatore);
 */
typedef enum {primoPlayer, secondoPlayer, terzoPlayer, quartoPlayer} Turno;

typedef struct
{
    int id;                //ID univoco per ogni giocatore, se diverso da NULL_ID
    char nome[NAME_SIZE];  //Nome univoco per ogni giocatore
    int numSGVinti;        //Numero di SPR1D GAME vinti in totale
    int numSGGiocati;      //Numero di SPR1D GAME giocati in totale
    int numFinali;         //Numero di volte in cui si è arrivati in finale
    int numGiochiGiocati;  //Numero di giochi giocati in totale
    int numGiochiVinti;    //Numero di giochi vinti in totale
}ProfiloGiocatore;

typedef struct
{
    int sizeGruppo; //Numero di giocatori che il gruppo può contenere
    int* id_membri; //Array di dimensione sizeGruppo contenente gli id dei membri del gruppo
}Gruppo;

typedef struct
{
    int numProfiliCreati;               //Numero di Profili Giocatore creati in questa partita;
    ProfiloGiocatore* profiliGiocatore; //Array di Profili Giocatore allocato dinamicamente, contenente tutti i profili creati;
    _Bool inCorso;                      //true: la partita è in corso    false: la partita non è in corso;
    int numGiocatori;                   //Numero di giocatori totali (sia CPU che Giocatori Utente);
    int numGiocatoriUtente;             //Numero di giocatori controllati dall' Utente;
    int* indiciGU;                      //Array contenente le posizioni all'interno di profiliGiocatore[] dei giocatori controllati dall' utente;
    int* inGioco;                       //Array che associa ad ogni ID un valore 0 o 1 (0: eliminato, 1: in gara).
}Gioco;