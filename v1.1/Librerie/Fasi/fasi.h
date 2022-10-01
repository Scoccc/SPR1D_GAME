#ifndef FASI_H
#define FASI_H

#define INFO_SPR1DGAME "Infos/InformazioniUtili.txt"
#define NUM_DEFAULT_PLAYERS 16
#define NUM_DEFAULT_GU 4
#define FIRST_DEFAULD_ID 11

#include "../Giochi/giochi.h"
#include "fasiTypes.h"

/*
 * Permette di trovare in quale fase si trova il gioco attualmente in base al
 * numero di giocatori ancora in gioco, trovati tramite la funzione numInGioco().
 *
 * Fase        | num giocatori in gioco
 * scrematura  | num = num giocatori totali
 * svolgimento | 2 < num < num giocatori totali
 * finale      | num = 2
 * conclusa    | num = 1
 *
 * Parameters:
 * Gioco* game: gioco in corso.
 *
 * Returns:
 * Fase: fase attuale.
 */
Fase trovaFase(Gioco* game);

 /*
  * Permette di visualizzare i messaggi iniziali e di scegliere da un menu cosa fare prima
  * d' iniziare il gioco effettivo.
  */
Gioco* Fase0_pregame();

/*
 * Permette di giocare la fase di scrematura, in cui tutti i giocatori verranno divisi
 * in gruppi tramite la funzione formaGruppiScrematura().
 * A tutti i giocatori utente che parteciperanno alla scrematura verrà incrementato di uno
 * il numero di SPR1D GAME giocati.
 * Per i gruppi che non contengono alcun profilo utente verrà generato un vincitore casuale
 * tra i membri del gruppo, invece i gruppi che contengono almeno un profilo giocatore
 * participeranno al gioco "Indovina il numero", tramite il quale si troverà un vincitore.
 * Poi verrà eseguito il cheat FrontmanDelloSPR1DGAME.
 * In fine si aggiornano le statistiche dei giocatori del gruppo e si eliminano i giocatori
 * che non hanno vinto tramite la funzione UpdateStats().
 * In fine viene stampato il nome del vincitore e viene chiesto se si vuole salvare la partita.
 *
 * Parameters:
 * Gioco* game: gioco in corso.
 */
void Fase1_Scrematura(Gioco* game);

/*
 * Permette di giocare la fase di svolgimento, in cui verranno formati casualmente dei gruppi da
 * che giocheranno agli otto giochi, finché non resteranno solo due giocatori in gara.
 * Se il numero di giocatori ancora in gioco è strettamente maggiore di 4 si estrae uno tra
 * i seguenti giochi:
 * - Pari o Dispari,
 * - Dadi,
 * - MorraCinese,
 * - Murra,
 * - Tris,
 * - Biglie,
 * - PonteDiVetro,
 * - Impiccato;
 * Se il numero è minore o uguale a 4 si escluderanno i giochi da 4 player (PonteDiVetro e Impiccato),
 * dato che ci si deve assicurare che dalla fase di svolgimento si esca con almeno 2 player ancora in
 * gioco.
 * Si genera un gruppo in base al numero di giocatori richiesti dal gioco, formando un gruppo da due
 * o da quattro giocatori usando la funzione generaGruppo();
 * Se il gruppo è composto solo da CPU si genera un vincitore, altrimenti i giocatori del gruppo si
 * sfideranno nel gioco estratto in precedenza.
 * Una volta trovato il vincitore di esegue il cheat FrontmanDelloSPR1DGAME.
 * Poi si aggiornano le statistiche e si eliminano i player che non hanno vinto tramite la funzione
 * UpdateStats().
 * In fine si scrive il nome del vincitore e si chiede se si vuole salvare la partita.
 *
 * Parameters:
 * Gioco* game: gioco in corso.
 */
void Fase2_Svolgimento(Gioco* game);

/*
 * Permette di giocare la fase finale, in cui gli ultimi due giocatori rimasti si sfideranno al gioco
 * BlackJack.
 * Questa fase di gioco sarà sempre mostrata anche se i giocatori saranno due CPU.
 *
 * Parameters:
 * Gioco* game: gioco in corso.
 */
void Fase3_Finale(Gioco* game);

/*
 * Permette di aggiornare le statistiche dei giocatori di un gruppo dopo che hanno partecipato ad un gioco,
 * ed elimina i giocatori del gruppo i quali non hanno vinto il gioco precedente.
 *
 * Parameters:
 * Gioco* game: gioco in corso;
 * int id_vincitore: id del giocatore che ha vinto il gioco precedente
 * Gruppo gruppo: gruppo di giocatori che hanno partecipato al gioco precedente di cui si vogliono aggiornare
 *                le statistiche;
 * Fase fase: fase di gioco attuale.
 */
void updateStats(Gioco* game, int id_vincitore, Gruppo gruppo, Fase fase);

/*
 * Permette di provare liberamente un minigioco
 */
void Fase0_1_provaMinigioco();

/*
 * Permette di caricare una partita di default per far provare un minigioco
 */
Gioco* loadDefaultGame();

#endif //FASI_H
