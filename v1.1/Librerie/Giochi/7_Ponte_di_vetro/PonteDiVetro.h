#ifndef PONTEDIVETRO_H
#define PONTEDIVETRO_H
#define NUMPLAYERS_PONTEDIVETRO 4
#define NUM_RIGHE 3
#define NUM_COLONNE 2
#define START -1
#define END 5
#define CADUTO -2
#define SCONOSCIUTO -1
#define ISTRUZIONI_PDV "Infos/Istruzioni_PonteDiVetro.txt"

#include "../../SPR1D_GAME/spr1dgamelib.h"
#include "PonteDiVetroTypes.h"

/*
 * PONTE DI VETRO
 * Il gioco consiste nell’attraversamento di un ponte composto da tre coppie di vetri
 * consecutive, in cui uno dei due vetri della coppia è fragile, e l’altro no.
 * I 4 giocatori sono inizialmente disposti in modo casuale, dopodiché il primo
 * giocatore dovrà iniziare ad attraversare il ponte, e scegliere su quale tra i
 * vetri della prima coppia passare.
 * Se sbaglia, viene eliminato.
 * Se indovina, può cercare d' indovinare il vetro della successiva coppia.
 * Il giocatore dietro di lui può usare l’informazione data dai tentativi del
 * giocatore precedente (fin dove è riuscito ad arrivare).
 * Vince il primo giocatore che riesce ad attraversare il ponte.
 * Se i primi tre giocatori vengono tutti e tre eliminati, il quarto vince
 * automaticamente (anche se non ha attraversato il ponte).
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_PonteDiVetro(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Ponte di vetro".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Ponte di vetro".
 */
Player_PDV* initPlayers_PDV(Gruppo gruppo);

/*
 * Permette d' inizializzare un nuovo ponte, impostando tutte le lastre di vetro come
 * integre, e generando casualmente quali lastre saranno fragili e quali no.
 *
 * Parameters:
 * Vetro ponte[NUM_RIGHE][NUM_COLONNE]: ponte di vetro d ainizializzare
 */
void initPonte(Vetro ponte[NUM_RIGHE][NUM_COLONNE]);

/*
 * Permette di stampare un ponte di vetro.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Vetro ponte[NUM_RIGHE][NUM_COLONNE]: ponte di vetro da attraversare;
 * Player_PDV player: giocatore che sta attraversando il ponte
 */
void printPonte(Gioco* game, Vetro ponte[NUM_RIGHE][NUM_COLONNE], Player_PDV player);

/*
 * Permette a un giocatore di tentare di attraversare il ponte.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_PDV player: giocatore che sta attraversando il ponte;
 * Vetro ponte[NUM_RIGHE][NUM_COLONNE]: ponte di vetro da attraversare;
 * Posizione nonFragili[NUM_RIGHE]: array che memorizza quali posizioni solo sicure.
 *
 * Returns:
 * -true: il giocatore ha superato il ponte;
 * -false: il giocatore non ha superato il ponte.
 */
_Bool attraversaPonte(Gioco* game, Player_PDV player, Vetro ponte[NUM_RIGHE][NUM_COLONNE], Posizione nonFragili[NUM_RIGHE]);

/*
 * Permette di inizializzare l'array che permette alle CPU di ricordare le mosse degli altri giocatori.
 *
 * Parameters:
 * Posizione nonFragili[NUM_RIGHE]: array che memorizza quali posizioni solo sicure.
 */
void initNonFragili(Posizione nonFragili[NUM_RIGHE]);

/*
 * Randomizza l'ordine di attraversamento dei giocatori.
 */
void randOrdinePlayers(Player_PDV* players_PDV);

#endif //PONTEDIVETRO_H
