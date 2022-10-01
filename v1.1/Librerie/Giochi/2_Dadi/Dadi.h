#ifndef DADI_H
#define DADI_H

#include "../../SPR1D_GAME/spr1dgamelib.h"
#include <stdio.h>

#define N_ULTIME_MOSSE 2
#define NUMPLAYERS_DADI 2
#define ISTRUZIONI_DADI "Infos/Istruzioni_Dadi.txt"

#include "DadiTypes.h"

/*
 * Dadi
 * I due giocatori hanno in mano 2 dadi. A turno, i giocatori tirano i dadi. Il primo giocatore che fa un tiro la
 * cui somma è minore del tiro precedente, perde. Il giocatore che inizia a tirare è scelto a caso.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_Dadi(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Dadi".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Dadi".
 */
Player_Dadi* initPlayerDadi(Gruppo gruppo);

/*
 * Fase di gioco in cui un giocatore lancia i dadi, e salva
 * le somme ottenute.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Dadi *player_Dadi: array di giocatori
 */
void faseLancioDadi(Gioco* game, Player_Dadi *player_Dadi);

/*
 * Permette di far lanciare 2 dadi a un Profilo Giocatore
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Dadi *player_Dadi: giocatore.
 *
 * Returns:
 * Somma ottenuta lanciando i dadi
 */
int lanciaDueDadi_Player(Gioco* game, Player_Dadi player);

/*
 * Permette di far lanciare 2 dadi ad una CPU
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Dadi *player_Dadi: CPU.
 *
 * Returns:
 * Somma ottenuta lanciando i dadi
 */
int lanciaDueDadi_CPU(Gioco* game, Player_Dadi cpu);

/*
 * Lancia un dado a 6 facce, restituendo un valore nel range 1-6.
 * Stampa su schermo il dado lanciato.
 */
int rollD6();

/*
 * Controlla se il giocatore ha perso, ovvero se la sua ultima somma è minore
 * della penultima.
 *
 * Parameters:
 * Player_Dadi player_Dadi: giocatore
 *
 * Returns:
 * - true: il giocatore ha perso
 * -false: il giocatore non ha perso
 */
_Bool haPerso(Player_Dadi player_Dadi);

#endif //DADI_H

