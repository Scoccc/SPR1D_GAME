#ifndef PARIODISPARI_H
#define PARIODISPARI_H
#include <stdio.h>
#include "../../SPR1D_GAME/spr1dgamelib.h"
#include "PariODispariTypes.h"
#define NUMPLAYERS_PARIODISPARI 2
#define ISTRUZIONI_POD "Infos/Istruzioni_PoD.txt"
#define MAX_NUMDITA 5
#define MIN_NUMDITA 0

/*
 * Pari o Dispari
 * I due giocatori scelgono se essere pari o dispari. Dopodiché, ognuno decide quante dita della mano
 * mostrare: da 0 a 5. La somma dei numeri dei due giocatori decreterà il vincitore, in base al fatto se essa
 * è pari o dispari.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
* Returns:
 * ID del vincitore del gioco
 */
int game_PariODispari(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Pari o Dispari".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Pari o Dispari".
 */
Player_PariODispari* initPlayers_PariODispari(Gruppo gruppo);

/*
 * Permette di giocare la fase in cui i giocatori scelgono se la somma sarà pari o dispari,
 * dato che questa scelta deve essere diversa tra i giocatori, si sceglie casualmente chi
 * dirà per primo "pari" o "dispari", e la scelta dell'altro giocatore verrà generata di
 * conseguenza.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_PariODispari* players_PariODispari: array di giocatori
 */
void faseSceltaPariODispari(Gioco* game, Player_PariODispari* players_PariODispari);


/*
 * Permette di giocare la fase in cui i giocatori scelgono il numero di dita da mostrare
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_PariODispari* players_PariODispari: array di giocatori
 */
void faseSceltaNumDita(Gioco* game, Player_PariODispari* players_PariODispari);


/*
 * Permette di trovare quale giocatore ha vinto la partita
 *
 * Parameters:
 * Player_PariODispari* players_PariODispari: array di giocatori
 *
 * Returns:
 * ID del vincitore
 */
int trovaVincitore(Player_PariODispari* players_PariODispari);

#endif //PARIODISPARI_H

