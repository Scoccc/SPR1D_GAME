#ifndef CARTE_CARTE_H
#define CARTE_CARTE_H
#include "carte_types.h"
#include "../../../Michele Library/mchlib.h"
#include "strings.h"

#define NUM_CARTE 52
#define NUM_SEMI 4
#define NUM_CARTEPERSEME (NUM_CARTE / NUM_SEMI)

/*
 * Permette di ricevere un carattere UTF-8 corrispondente al seme ricevuto
 */
char* semeConvertion(Seme seme);

/*
 * Permette di creare una nuova carta creata dall'utente
 */
Carta creaCarta();

/*
 * Permette la creazione di una carta tramite i parametri ricevuti
 */
Carta creaCartaParam(Seme seme, int val);

/*
 * Permette stampare una carta
 */
void printCarta(Carta carta);

/*
 * Alloca lo spazio necessario per creare un nuovo mazzo
 */
Mazzo* allocaMazzo();

/*
 * Permette di creare un nuovo mazzo
 */
Mazzo* creaMazzo();

/*
 * Permette di stampare un mazzo
 */
void printMazzo(Mazzo* mazzo);

/*
 * FUNZIONE DEBUG:
 * permette di stampare un mazzo scrivendo il numero di carte stampate
 */
void printMazzoCounter(Mazzo* mazzo, int i);

/*
 * Stampa un mazzo spostato a destra
 */
void printMazzoDX(Mazzo* mazzo);

/*
 * Stampa due mazzi affiancati
 */
void printDueMazzi(Mazzo* mazzoSX, Mazzo* mazzoDX);

/*
 * Stampa due carte affiancate
 */
void printDueCarte(Carta cartaSX, Carta cartaDX);

/*
 * Stampa la parte superiore di una carta
 */
void printCartaSU(Carta carta);

/*
 * Stampa la parte inferiore di una carta
 */
void printCartaGIU(Carta carta);

/*
 * Azione push sulla lista
 */
void aggiungiCartaInCima(Mazzo** mazzo, Carta carta);

/*
 * Permette di aggiungere una cara in fondo a un mazzo
 */
void aggiungiCartaInfondo(Mazzo** mazzo, Carta carta);

/*
 * Azione pop sulla lista
 */
Carta pescaCarta(Mazzo** mazzo);

/*
 * Permette di creare un mazzo completo, ovvero un mazzo da 52 carte ordinate.
 */
Mazzo* creaMazzoCompleto();

/*
 * permette di creare un mazzo completo ricorsivamente
 */
Mazzo* creaMazzoCompleto_rec(int i);

/*
 * Mischia un mazzo effettuando:
 * - un riffle shuffle sul mazzo;
 * - smezzando il mazzo e ricomponendolo al contrario
 * - facendo un altro riffle shuffle
 * - e rismezzando il mazzo e ricomponendolo
 *
 * questi passi saranno effettuati per un numero di volte pari a loops,
 * maggiore sarà loops e meglio sarà mischiato il mazzo.
 */
void mischiaMazzo(Mazzo** mazzo, int loops);

/*
 * Effettua il Riffle Shuffle sul mazzo.
 * Ovvero smezza il mazzo creando due mazzetti,
 * poi crea un nuovo mazzo prendendo una carta dal primo mazzetto e mettendola in fondo,
 * prendendo una carta dal secondo mazzetto e mettendola in fondo al nuovo mazzo,
 * prendendo di nuovo una carta dal primo mazzetto e mettendola in fondo al nuovo mazzo,
 * e così via.
 */
void riffleShuffle(Mazzo** mazzo);

/*
 * Permette di smezzare un mazzo, generando un nuovo mazzo.
 *
 * Mazzo* mazzo: mazzo da smezzare
 *
 * int numCartePrimoMazzo: numero di carte da lasciare al primo mazzo,
 *                         le restanti carte faranno parte del mazzo generato.
 *
 * returns: il mazzo creato smezzando il mazzo ricevuto come parametro
 */
Mazzo* smezza(Mazzo* mazzo, int numCartePrimoMazzo);

/*
 * Permette di unire 2 mazzi
 */
void unisciMazzi(Mazzo* mazzo, Mazzo* mazzo_aggiunto);

#endif