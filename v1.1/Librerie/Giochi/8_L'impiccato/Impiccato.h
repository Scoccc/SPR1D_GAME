#ifndef IMPICCATO_H
#define IMPICCATO_H

#include <stdio.h>
#include <stdlib.h>
#include "../../SPR1D_GAME/spr1dgamelib.h"
#include <string.h>

#define NUMPLAYERS_IMPICCATO 4
#define BUFFSIZE 120
#define NUM_TENTATIVI_MAX 4
#define DIM 50

#define DEFAULT_DICTIONARY "default.txt"
#define ISTRUZIONI_IMPICCATO "Infos/Istruzioni_L'impiccato.txt"

#include "ImpiccatoTypes.h"

/*
 * L’impiccato
 * I 4 giocatori dovranno cercare di indovinare una parola (o frase) selezionata a caso da un dizionario di
 * parole. All’inizio, sarà noto solamente da quante lettere è composta la parola (verrà visualizzato un
 * numero di caratteri “_” pari al numero di lettere della parola). A turno, i giocatori inseriranno una lettera
 * che pensano possa essere presente, e il gioco verificherà se tale lettera è presente nella parola. Se è
 * presente, viene visualizzata la parola e i caratteri “_” saranno sostituiti con la lettera inserita, e il turno
 * passa al giocatore successivo. Se la lettera non è presente, il giocatore ha fallito e il turno passerà
 * comunque al giocatore successivo. Ogni giocatore ha un numero massimo di fallimenti pari a 4,
 * dopodiché verrà eliminato. Vince il giocatore che completa la parola (indovina l’ultima lettera che rivela
 * la parola finale), oppure l’ultimo superstite.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_Impiccato(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Impiccato".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Impiccato".
 */
Player_Impiccato* initPlayersImpiccato(Gruppo gruppo);

/*
 * Permette di offuscare una parola, sostituendo ogni lettera con il carattere '_'
 *
 * Parola* parola: parola da offuscare
 */
void offuscaParola(Parola* parola);

/*
 * Permette di scegliere una parola casualmente da un file testuale di parole
 *
 * char* filePath: percorso al file di testo
 *
 * returns: parola scelta
 */
Parola scegliParola();

/*
 * Permette a un player di tentare di indovinare una lettera contenuta nella parola
 *
 * Player_Impiccato *player: giocatore che deve fare il turno
 *
 * Parola* parola: parola da indovinare
 *
 * Tentativo** tentativi: puntatore alla lista di tentativi
 */
char faiTentativo(Gioco* game, Player_Impiccato *player, Parola* parola, Tentativo** tentativi);

/*
 * Controlla se una lettera è presente all'interno di una parola
 *
 * Parola* parola: parola in cui bisogna cercare la lettera
 *
 * char lettera: lettera da cercare
 *
 * returns:
 * - true: la lettera è presente all'interno della parola
 * - false: la lettera non è presente all'interno della parola
 */
_Bool checkLettera(Parola* parola, char lettera);

/*
 * Permette di scrivere una parola offuscata.
 * Su windows e linux il carattere '_' verrà scritto in grigio
 * l'ultima lettera trovata berrà scritta in verde chiaro e le restati letter ein bianco
 * Negli altri sistemi operativi l'ultima lettera trovata sarà scritta in maiuscolo.
 *
 * Parola parola: parola da scrivere
 *
 * char lastChar: ultima lettere trovata (' ' se non bisogna mettere in risalto nessuna lettera)
 */
void printParolaOffuscata(Parola parola, char lastChar);

/*
 * Permette di visualizzare il patibolo di un giocatore in base al numero di tentativi rimasti.
 *
 * 4 tentativi:   3 tentativi:   2 tentativi:   1 tentativi:   0 tentativi:
 *  ╔═══╤          ╔═══╤          ╔═══╤          ╔═══╤          ╔═══╤
 *  ║              ║   O          ║   O          ║   O          ║   O
 *  ║              ║   |          ║  /|\         ║  /|\         ║  /|\
 *  ║              ║              ║              ║  /           ║  / \
 * ─╨─            ─╨─            ─╨─            ─╨─            ─╨─
 */
 void printPatibolo(Player_Impiccato player);

/*
 * Controlla se la parola è stata indovinata
 *
 * Parola parola: parola da indovinare
 *
 * Returns:
 * - true: un giocatore ha vinto
 * - false: nessuno ha vinto
 */
_Bool checkVittoria(Parola parola);

/*
 * Permette di sapere se esisto o no un tentativo nella lista
 *
 * Tentativo* tentativi: tentativi già effettuati
 *
 * char c: tentativo da cercare
 *
 * Returns:
 * - true: il tentativo esiste
 * - false: il tentativo non esiste
 */
_Bool cercaTentativo(Tentativo* tentativi, char c);

/*
 * Permette di aggiungere in cima alla lista di tentativi un nuovo tentativo
 *
 * char c: lettera da aggiungere in cima alla lista
 *
 * Tentativo* tentativi: tentativi già effettuati
 *
 * Returns
 * Lista aggiornata
 */
Tentativo* aggiuntiTentativo(char c, Tentativo* tentativi);

#endif //IMPICCATO_H
