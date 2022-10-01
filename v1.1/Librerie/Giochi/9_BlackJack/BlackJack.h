#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../SPR1D_GAME/spr1dgamelib.h"
#include "Carte/carte.h"
#include "BlackjackTypes.h"

#define SOGLIA 21
#define LOOPS 40 //numero di volte che si mischia il mazzo
#define NUMPLAYERS_BLACKJACK 2
#define ISTRUZIONI_BLACKJACK "Infos/Istruzioni_BlackJack.txt"

/*
 * BLACKJACK
 * Il gioco si avvale di un singolo mazzo di carte, composto da 52 carte distribuite in 4 semi (cuori, quadri,
 * picche, fiori) e, ogni seme possiede le seguenti carte: 1 (asso), 2, 3, 4, 5, 6, 7, 8, 9, 10, fante (J), regina
 * (Q), re (K). Il valore delle carte è quello nominale presente sulla carta, tranne l’asso, che può valere 1 o
 * 11 a scelta dell’utente, e J, Q, e K che valgono 10 punti ciascuna. I semi non hanno alcuna influenza, o
 * valore particolare.
 * I 2 giocatori si sfidano uno contro l’altro, con l’obiettivo di avere in mano delle carte la cui somma sia il
 * più possibile vicina a 21, ma senza superarlo. Il gioco si svolge mediante le seguenti fasi: per ogni
 * giocatore:
 * 1. entrambi i giocatori ricevono due carte;
 * 2. in base alla somma delle carte ricevute, a turno, i giocatori possono decidere se chiedere
 * un’altra carta o fermarsi, accontentandosi del punteggio ottenuto (questa fase si ripete finché il
 * giocatore non decide di fermarsi, oppure la somma delle sue carte è >21. In quest’ultimo caso,
 * ha già perso). Questa fase si ripete finché uno dei due giocatori non perde, oppure entrambi si
 * sono fermati;
 * 3. il gioco termina se uno dei due giocatori ha perso perché ha superato 21 oppure, se entrambi si
 * sono fermati, si confrontano le somme ottenute. Chi ha la somma maggiore, vince.
 * 4. In caso di pareggio, si ripete la partita riconsiderando l’intero mazzo, finché non si ottiene un
 * vincitore.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_Blackjack(Gioco* game, Gruppo gruppo);

/*
 * Permette d' inizializzare i giocatori di "BlackJack".
 *
 * Parameters:
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * Array allocato dinamicamente di giocatori di "BlackJack".
 */
Player_Blackjack* initPlayerBlackjack(Gruppo gruppo);

/*
 * Permette di calcolare la somma delle carte di un player, scegliendo il valore
 * degli assi automaticamente in modo che il player abbia il valore più alto possibile
 * senza sbancare.
 *
 * Player_Blackjack* player: player di cui si vuole ricalcolare la somma complessiva delle carte
 */
void calcolaSommaCarte(Player_Blackjack* player);

/*
 * Fase in cui si danno sue carte a ogni giocatore
 *
 * Player_Blackjack players[NUMPLAYERS_BLACKJACK]: array contenenti i giocatori
 *
 * Mazzo** mazzo: puntatore al mazzo da cui bisognerà pescare le carte
 */
void fasePrimeDueCarte(Player_Blackjack players[NUMPLAYERS_BLACKJACK], Mazzo** mazzo);

/*
 * Permette di stampare le carte di entrambi i giocatori, mostrando in due colonne:
 * - nome dei giocatori;
 * - carte dei giocatori, mettendo in fondo le ultime carte ricevute;
 * - somme dei giocatori utilizzando la funzione printSommaPlayer.
 */
void printCartePlayers(Gioco* game, Player_Blackjack* players_BlackJack);

/*
 * Permette di stampare la somma dei valori delle carte di un player.
 * La somma sarà:
 * - scritta in blu se il giocatore si è fermato;
 * - scritta in rosso se il giocatore ha sbancato;
 * - scritta in verde se è fermo con 21;
 * - scritta in ciano se è ancora in gioco.
 */
void printSommaPlayer(Player_Blackjack player);

/*
 * Fase in cui un giocatore decide se restare o se ricevere un'altra carta
 *
 * Player_Blackjack players[NUMPLAYERS_BLACKJACK]: array contenenti i giocatori
 *
 * Mazzo** mazzo: puntatore al mazzo da cui bisognerà pescare le carte
 */
void faseCartaOFermarsi(Gioco* game, Player_Blackjack *player_BlackJack, Mazzo **mazzo);

/*
 * Permette di dare una carta a un player pescandola dal mazzo.
 * Aggiorna la somma attuale del player.
 */
void daiCarta(Player_Blackjack *players_BlackJack, Mazzo** mazzo);

/*
 * Controlla in che stato si trova un giocatore
 */
Status checkStatusPlayer (Player_Blackjack player);

#endif //BLACKJACK_H

