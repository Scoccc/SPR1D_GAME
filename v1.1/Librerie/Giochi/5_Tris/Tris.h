#ifndef TRIS_H
#define TRIS_H

#include "../../SPR1D_GAME/spr1dgamelib.h"

#define SIZE 3
#define NUMPLAYERS_TRIS 2
#define BLANK_SPACE -1
#define ISTRUZIONI_TRIS "Infos/Istruzioni_Tris.txt"

/*
 * TRIS
 * I due giocatori dovranno mettere, a turno, un proprio segnaposto in una cella non ancora occupata di
 * una matrice 3x3. Vince chi ottiene per primo una riga, una colonna o una diagonale interamente
 * occupata dal proprio segnaposto. In caso di pareggio, si inizia una nuova partita finché non ci sarà un
 * vincitore. Il primo giocatore a iniziare sarà quello con numero identificativo minore; nelle eventuali
 * partite successive si inizierà a turno.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che parteciperà al gioco.
 *
 * Returns:
 * ID del vincitore del gioco
 */
int game_Tris(Gioco* game, Gruppo gruppo);

/*
 * Disegna la griglia di gioco, colorando i caratteri 'X' e 'O'
 * con i colori dei rispettivi giocatori.
 *
 * Parameters:
 * griglia[SIZE][SIZE]: griglia di gioco;
 * Gruppo gruppo: gruppo che partecipa al gioco.
 */
void printGriglia(int griglia[SIZE][SIZE], Gruppo gruppo);

/*
 * Ripulisce la griglia inserendo il valore
 * -1 in tutte le celle della matrice
 *
 * Parameters:
 * griglia[SIZE][SIZE]: griglia di gioco;
 */
void clearGriglia(int griglia[SIZE][SIZE]);

/*
 * Controlla se sono stati disegnati tre caratteri adiacenti verticalmente nella
 * colonna "last_col".
 */
_Bool ceckVittoriaVerticale(int griglia[SIZE][SIZE], int last_col, Turno turno);

/*
 * Controlla se sono stati disegnati tre caratteri adiacenti orizzontalmente nella
 * riga "last_row".
 */
_Bool ceckVittoriaOrizzontale(int griglia[SIZE][SIZE], int last_row, Turno turno);

/*
 * Controlla se sono stati disegnati tre caratteri adiacenti nella diagonale
 * crescente.
 */
_Bool ceckVittoriaDiagonaleDecrescente(int griglia[SIZE][SIZE], Turno turno);

/*
 * Controlla se sono stati disegnati tre caratteri adiacenti nella diagonale
 * decrescente.
 */
_Bool ceckVittoriaDiagonaleCrescente(int griglia[SIZE][SIZE], Turno turno);

/*
 * Controlla se è stata completata una fila da tre in una qualsiasi direzione.
 */
_Bool ceckVittoria(int griglia[SIZE][SIZE], Turno turno, int row, int col);

/*
 * Controlla se la griglia ha ancora spazi liberi o no.
 */
_Bool isGrigliaPiena(int griglia[SIZE][SIZE]);

/*
 * Permette di far giocare un turno al player
 */
void turnoPlayer_tris(int griglia[SIZE][SIZE], int *col, int *row);

/*
 * Permette di far giocare un turno alla CPU
 */
void turnoCPU_tris(int griglia[SIZE][SIZE], int *col, int *row);

#endif //TRIS_H