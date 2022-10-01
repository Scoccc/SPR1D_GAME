
#ifndef MORRACINESE_H
#define MORRACINESE_H

#include "../../SPR1D_GAME/spr1dgamelib.h"
#include "MorraCineseTypes.h"

#define NUMPLAYERS_MORRACINESE 2
#define NULL_SCELTA -1
#define ISTRUZIONI_MC "Infos/Istruzioni_MC.txt"

/*
 * Morra cinese (Sasso, carta e forbici)
 * I due giocatori possono scegliere uno tra i seguenti simboli: carta, forbici, o sasso. Si confrontano,
 * quindi, i simboli scelti dai giocatori e si dichiara il vincitore, in base alle seguenti regole:
 * ● carta contro forbici => vince forbici
 * ● carta contro sasso => vince carta
 * ● forbici contro sasso => vince sasso
 * ● se i due simboli sono uguali non vince nessuno e si ripete il gioco finché non c’è un vincitore.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_MorraCinese(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Morra Cinese".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Morra Cinese".
 */
Player_MorraCinese* initPlayers_MorraCinese(Gruppo gruppo);

/*
 * Permette di giocare la fase in cui entrambi i giocatori scelgono:
 * sasso, carta o forbici.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_MorraCinese* players_MorraCinese: array di giocatori
 */
void faseScelta(Gioco* game, Player_MorraCinese* players_MorraCinese);

/*
 *  Riceve le scelte in forma numerica dei due giocatori:
 *  ● 0 = Sasso
 *  ● 1 = Carta
 *  ● 2 = Forbice
 *  Nota: Le scelte sono ordinate in modo che ogni scelta vinca sempre sulla
 *  precedente, e perda sempre rispetto la successiva.
 *  La funzione controlla se:
 *  ● Ha vinto il player1 con la formula (p1_SCF == (p2_SCF + 1) % 3),
 *    ovvero controllando che il player1 abbia fatto la scelta successiva
 *    rispetto a quella del player2;
 *  ● Ha vinto il player2 con la formula (p2_SCF == (p1_SCF + 1) % 3),
 *    ovvero controllando che il player2 abbia fatto la scelta successiva
 *    rispetto a quella del player1;
 *  ● È un pareggio nel caso in cui ambi due i giocatori abbiano effettuato
 *    la stessa scelta.
 *
 *  Parameters:
 * Player_MorraCinese* players_MorraCinese: array di giocatori
 *
 *  Returns:
 *  ●  0: Se ha vinto player1
 *  ●  1: Se ha vinto player2
 *  ● -1: Se è un pareggio
 */
int trovaVincitore_MorraCinese(Player_MorraCinese* players_MorraCinese);

/*
 *  Riceve un valore intero restituendo una stringa:
 *  ● 0 = Carta;
 *  ● 1 = Sasso;
 *  ● 2 = Forbice.
 *  ● ogni altro valore = NULL;
 *
 * Parameters:
 *  SCF: valore da convertire in stringa
 *
 *  Returns:
 *  Una stringa.
 */
char* intToString(Scf SCF);

#endif //MORRACINESE_H
