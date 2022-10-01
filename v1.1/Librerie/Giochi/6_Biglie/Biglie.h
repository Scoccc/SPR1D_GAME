#ifndef BIGLIE_H
#define BIGLIE_H

#include "../../SPR1D_GAME/spr1dgamelib.h"
#include "BiglieTypes.h"

#define NUMBIGLIEINIZIO 10
#define NUMPLAYERS_BIGLIE 2
#define ISTRUZIONI_BIGLIE "Infos/Istruzioni_Biglie.txt"

/*
 * Biglie
 * Ogni giocatore ha in mano un numero di biglie pari a 10. A ogni turno, entrambi i giocatori decidono
 * quante biglie scommettere (tra quelle che hanno a disposizione), e il turno consiste in uno dei due
 * giocatori che prova a indovinare se il giocatore avversario ha scommesso un numero di biglie pari o
 * dispari. Se il giocatore indovina, riceverà dall’avversario un numero di biglie pari a quelle scommesse
 * dall’avversario. Se non indovina, sarà l’avversario a ricevere un numero di biglie pari al numero
 * scommesso dal giocatore. Il gioco termina quando uno dei due giocatori rimane con zero biglie in mano
 * (quest’ultimo perde e viene eliminato).
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_Biglie(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "Biglie".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "Biglie".
 */
Player_Biglie* initPlayerBiglie(Gruppo gruppo);

/*
 * Controlla se c'è almeno un giocatore con 0 biglie, quindi che ha perso.
 * Nel caso in cui un giocatore abbia perso viene scritto un messaggio in
 * cui si annuncia quale giocatore abbia vinto.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Biglie* players_Biglie: array di giocatori
 *
 * Returns:
 * - true: qualcuno ha perso
 * - false: nessuno ha ancora perso
 */
_Bool checkPerdita(Gioco* game, Player_Biglie* players_Biglie);

/*
 * Permette di giocare il turno in cui entrambi i giocatori fanno le
 * loro scommesse.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Biglie* players_Biglie: array di giocatori
 */
void turnoScommessa(Gioco* game, Player_Biglie* players_Biglie);

/*
 * Permette di giocare il turno in cui si cerca di indovinare se
 * l'avversario ha scommesso un numero di biglie pari o dispari.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Player_Biglie* players_Biglie: array di giocatori
 * index_turno: indice che nell'array indica il giocatore che deve indovinare.
 */
void turnoIndovinare(Gioco* game, Player_Biglie* players_Biglie, Turno index_turno);

#endif //BIGLIE_H
