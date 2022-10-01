#ifndef MCHLIB_H
#define MCHLIB_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFSZ 100
#define OFFSET ('a' - 'A') //Offset tra lettere maiuscole e lettere minuscole in ASCII
#define NUMBUFF 10
#define pari(N) (N % 2 == 0) //true: il numero è pari, false: il numero è dispari

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#elif __linux__
#include <ctype.h>
#include <limits.h>
#include <curses.h>
#endif

//NUMERI COLORI FOREGROUND
#define FG_BLACK 30
#define FG_RED 31
#define FG_GREEN 32
#define FG_YELLOW 33
#define FG_BLUE 34
#define FG_MAGENTA 35
#define FG_CYAN 36
#define FG_WHITE 37
#define FG_BRIGHT_BLACK 90
#define FG_BRIGHT_RED 91
#define FG_BRIGHT_GREEN 92
#define FG_BRIGHT_YELLOW 93
#define FG_BRIGHT_BLUE 94
#define FG_BRIGHT_MAGENTA 95
#define FG_BRIGHT_CYAN 96
#define FG_BRIGHT_WHITE 97

//NUMERI COLORI BACKGROUND
#define BG_BLACK 40
#define BG_RED 41
#define BG_GREEN 42
#define BG_YELLOW 43
#define BG_BLUE 44
#define BG_MAGENTA 45
#define BG_CYAN 46
#define BG_WHITE 47
#define BG_BRIGHT_BLACK 100
#define BG_BRIGHT_RED 101
#define BG_BRIGHT_GREEN 102
#define BG_BRIGHT_YELLOW 103
#define BG_BRIGHT_BLUE 104
#define BG_BRIGHT_MAGENTA 105
#define BG_BRIGHT_CYAN 106
#define BG_BRIGHT_WHITE 107

#define P_RESET "\033[m"

//STRINGA COLORI FOREGROUND
#define P_FG_BLACK "\033[30m"
#define P_FG_RED "\033[31m"
#define P_FG_GREEN "\033[32m"
#define P_FG_YELLOW "\033[33m"
#define P_FG_BLUE "\033[34m"
#define P_FG_MAGENTA "\033[35m"
#define P_FG_CYAN "\033[36m"
#define P_FG_WHITE "\033[37m"
#define P_FG_BRIGHT_BLACK "\033[90m"
#define P_FG_BRIGHT_RED "\033[91m"
#define P_FG_BRIGHT_GREEN "\033[92m"
#define P_FG_BRIGHT_YELLOW "\033[93m"
#define P_FG_BRIGHT_BLUE "\033[94m"
#define P_FG_BRIGHT_MAGENTA "\033[95m"
#define P_FG_BRIGHT_CYAN "\033[96m"
#define P_FG_BRIGHT_WHITE "\033[97m"

//STRINGA COLORI BACKGROUND
#define P_BG_BLACK "\033[40m"
#define P_BG_RED "\033[41m"
#define P_BG_GREEN "\033[42m"
#define P_BG_YELLOW "\033[43m"
#define P_BG_BLUE "\033[44m"
#define P_BG_MAGENTA "\033[45m"
#define P_BG_CYAN "\033[46m"
#define P_BG_WHITE "\033[47m"
#define P_BG_BRIGHT_BLACK "\033[100m"
#define P_BG_BRIGHT_RED "\033[101m"
#define P_BG_BRIGHT_GREEN "\033[102m"
#define P_BG_BRIGHT_YELLOW "\033[103m"
#define P_BG_BRIGHT_BLUE "\033[104m"
#define P_BG_BRIGHT_MAGENTA "\033[105m"
#define P_BG_BRIGHT_CYAN "\033[106m"
#define P_BG_BRIGHT_WHITE "\033[107m"

typedef unsigned int Colore;

/*
 * Permette di usare i caratteri UTF-8 e le espace codes ANSI correttamente su tutti i sistemi operativi e sul temrinale di Clion
 */
void initMultiPiattaforma();

/*
 * Permette di stampare un titolo
 */
void font_title(char* title, Colore color);

/*
 * Permette di scrivere in grassetto
 */
void font_Bold();

/*
 * Permette di cambiare il colore dle font
 */
void font_changeFGColor(Colore color);

/*
 * Permette di cambiar eil colore di sfondo
 */
void font_changeBGColor(Colore color);

/*
 * Resetta il font in utilizzo
 */
void font_reset();

/*
 * Una funzione che ricevuti due estremi di un range, restituisce
 * un numero randomico compreso nel range[min, max].
 */
int randNumInRange(int min, int max);

/*
 * Dice se un numero intero è compreso nel range inserito, estremi inclusi.
 *
 * n: numero di cui si vuole verificare se è compreso nel range
 *
 * min: numero minimo del range
 *
 * max: numero massimo del range
 *
 * returns: un valore _Booleano true se il numero è compreso, e false se non è compreso
 */
int isInRange(int n, int min, int max);

/*
 *
 */
int getIntInRange(const char* message,int min, int max);

/*
 * Pulisce lo schermo (Funziona correttamente solo su terminale)
 */
void clearScreen();

/*
 * Blocca il programma, chiedendo all'utente di premere invio per continuare nell'esecuzione
 */
void premereInvio();

/*
 * Restituisce un valore _Booleano sulla base di un'affermazione.
 *
 * returns:
 * true: se è stata inserita una stringa che inizi con 's' o 'y' (case insensitive).
 * false: se è stata inserita una stringa che inizi con 'n' (case insensitive).
 */
_Bool getYesNo();

/*
 * Dado un file ne restituisce il numero di righe da cui è composto
 */
int numRigheFile(char* filePath);

/*
 * Restiutusce il carattere c in maiuscolo, se c è una lettere minuscola
 */
char toUpper(char c);

/*
 * Restiutusce il carattere c in minuscolo, se c è una lettere maiuscola
 */
char toLower(char c);

/*
 * Controlla se un carattere "lettera" è contenuto nella stringa "stringa"
 *
 * Returs:
 * -true: lettera è presente in stringa
 * -false: lettera non è presente in stringa
 */
_Bool IsCharInString(const char* stringa, char lettera);

#endif //MCHLIB_H
