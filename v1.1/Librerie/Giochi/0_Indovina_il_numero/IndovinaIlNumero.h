#ifndef INDOVINAILNUMERO_H
#define INDOVINAILNUMERO_H

#include "../../SPR1D_GAME/spr1dgamelib.h"
#include "IndovinaIlNumeroTypes.h"

#define ILN_MIN 0
#define ILN_MAX 999
#define ISTRUZIONI_ILN "Infos/Istruzioni_ILN.txt"
#define NULL_TENTATIVO -1

/*
 * INDOVINA IL NUMERO
 * La CPU genera casualmente un numero
 * compreso tra 0 e 999 e, a turno (in ordine di numero identificativo), i giocatori del gruppo provano a
 * indovinare il numero. La CPU, a ogni tentativo dirà se il numero inserito è maggiore o minore del numero
 * da indovinare. Vince il giocatore che per primo indovina il numero
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
* Returns:
 * ID del vincitore del gioco
 */
int game_IndovinaIlNumero(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Indovina il numero".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Indovina il numero".
 */
Player_ILN* initPlayerILN(Gruppo gruppo);

/*
 * Permette a un giocatore (sia CPU che Profilo Giocatore) di effettuare un tentativo
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_ILN* player_ILN: array di giocatori;
 * int tentativoMin: tentativo più basso possibile;
 * int tentativoMax: tentativo più grande possibile.
 */
void faseFaiTentativo(Gioco* game, Player_ILN* player_ILN, int tentativoMin, int tentativoMax);

/*
 * Permette di verificare se il giocatore ha indovinato il numero,
 * nel caso in cui non abbia indovinato stampa se il numero tentato era troppo grande o troppo piccolo,
 * e se necessario si aggiornano il tentativo minimo o il tentativo minimo.
 *
 * Parameters:
 * Player_ILN player_ILN: Giocatore che ha fatto il tentativo;
 * int num: numero da indovinare;
 * int* tentativoMin: tentativo minimo possibile;
 * int* tentativoMax: tentativo massimo possibile
 *
 * Returns:
 * true: il numero è stato indovinato;
 * false: in numero non è stato indovinato.
 */
_Bool checkVittoria_ILN(Player_ILN player_ILN, int num, int* tentativoMin, int* tentativoMax);

#endif //INDOVINAILNUMERO_H
