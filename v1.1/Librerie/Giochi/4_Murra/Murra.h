#ifndef MURRA_H
#define MURRA_H

#define NUMPLAYERS_MURRA 2
#define NULLPLAYER -1

#include "../../SPR1D_GAME/spr1dgamelib.h"
#include "MurraTypes.h"
#define ISTRUZIONI_MURRA "Infos/Istruzioni_Murra.txt"

/*
 * I due giocatori generano due numeri:
 * ● un numero compreso tra 1 e 5, estremi inclusi, rappresentante il numero scelto;
 * ● un numero compreso tra 2 e 10, estremi inclusi, rappresentante la somma dei due numeri scelti
 * dai giocatori.
 * Vince il giocatore che riesce a indovinare la somma. In caso di parità, si procede a oltranza finché non
 * c’è un solo vincitore.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_Murra(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Murra".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Murra".
 */
Player_Murra* initPlayers_Murra(Gruppo gruppo);

/*
 * Permette a un player o a una CPU di scegliere il numero da giocare
 *
 * Player_Murra* player_Murra: puntatore al giocatore
 */
void sceltaNumero(Gioco* game, Player_Murra* player_Murra);

/*
 * Permette a un player o a una CPU di fare la previsione sulla somma
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Murra* player_Murra: array di giocatori
 */
void sceltaPrevisione(Gioco* game, Player_Murra* player_Murra);

/*
 * Permette ai giocatori di giocare la fase in cui giocano un numero e fanno una previsione.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Murra* player_Murra: array di giocatori
 */
void faseMurra(Gioco* game, Player_Murra* players_Murra);

/*
 * Controlla se qualcuno tra i giocatori ha indovinato la somma
 *
 * Returns:
 * - il turno corrispondente al giocatore che ha indovinato
 * - NULLPLAYER in caso di pareggio o se nessuno ha indovinato;
 */
Turno checkVincitore(Gioco* game, Player_Murra* players_Murra);

#endif //MURRA_H
