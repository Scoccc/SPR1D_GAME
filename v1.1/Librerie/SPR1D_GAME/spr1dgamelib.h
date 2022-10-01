#ifndef SPR1DGAMELIB_H
#define SPR1DGAMELIB_H

#define NAME_SIZE 64 //Grandezza massima per i nomi dei giocatori
#define PATH_SIZE 256 //Grandezza massima per i path dei salvataggi
#define PREFISSO_SAVES "Saves/" //Prefisso dei salvataggi
#define SAVEINFO_LOCATION "saveFilesInfo.txt" //Percorso di SaveFilesInfo
#define ESTENSIONE_SAVES ".bin" //Estensione pr i file di salvataggio
#define NULL_ID -1 //ID nullo
#define NULL_NAME "" //Nome nullo
#define GAMES_SPEED 750000 //Velocità di gioco(tempo impiegato dalle CPU per giocare)
#define MIN_NUM_PLAYERS 16 //Numero minimo di giocatori dello SPR1D GAME
#define MAX_NUM_PLAYERS 100000 //Numero massimo di giocatori dello SPR1D GAME
#define LUNGHEZZA_BARRA 22 //lunghezza delle barre rappresentanti le statistiche dei giocatori
#define NUM_COLORI 12 //Numero di colori disponibili
#define PGfromIndiceGU(I) (game->profiliGiocatore[game->indiciGU[I]]) //Macro che permette di ottenere un Profilo Giocatore, dato un indice dell'array indiciGU

#include <math.h>
#include "../Michele Library/mchlib.h"
#include <limits.h>
#include <unistd.h>
#include "spr1dgameTypes.h"

/*
 * Permette di ricavare il colore di un giocatore in base al suo ID
 *
 * Parameters:
 * int id: id del giocatore
 *
 * Returns:
 * colore corrispondente all'id
 */
Colore getColoreFromID(int id);

/*
 * Trova il numero di gruppi da formare in base al numero di giocatori che parteciperanno allo SPR1D GAME.
 *
 * Parameters:
 * Gioco* game: gioco in corso
 *
 * Returns:
 * esponente intero trovato tramite la funzione trovaPotenzaDi2() - 1;
 */
int getNumGruppiScrematura(int numPlayers);

/*
 * Forma i gruppi che parteciperanno alla scrematura
 *
 * Parameters:
 * Gioco* game: gioco in corso
 * int numGruppi: numero di gruppi da formare
 *
 * Returns:
 * Array di tipo Gruppo, allocato dinamicamente, di dimensione numGruppi.
 */
Gruppo* formaGruppiScrematura(Gioco* game, int numGruppi);

/*
 * Forma i gruppi che parteciperanno allo svolgimento
 *
 * Parameters:
 * Gioco* game: gioco in corso
 * int numGruppi: numero di gruppi da formare
 *
 * Returns:
 * Array di tipo Gruppo, allocato dinamicamente, di dimensione numGruppi.
 */
Gruppo* formaGruppiSvolgimento(Gioco* game, int numPlayerGruppo);

/*
 * Forma i gruppi che parteciperanno alla finale
 *
 * Parameters:
 * Gioco* game: gioco in corso
 * int numGruppi: numero di gruppi da formare
 *
 * Returns:
 * Gruppo formato
 */
Gruppo formaGruppoFinale(Gioco* game);

/*
 * Permette di scoprire se un id è associato a una CPU
 *
 * Parameters:
 * Gioco* game: gioco in corso
 * int id: Id del giocatore
 *
 * Returns:
 * true: L'ID è associato a una CPU
 * false: L'ID è associato a un profilo giocatore
 */
_Bool isCPU(Gioco* game, int id);

/*
 * Dato un nome ne crea un nuovo Profilo Giocatore
 *
 * Parameters:
 * char nome[NAME_SIZE]: stringa di dimensione NAME_SIZE contenente il nome da assegnare al profilo Giocatore
 *
 * Returns:
 * Profilo Giocatore con ID pari a NULL_ID(-1), nome uguale al nome ricevuto come parametro e i restati campi
 * inizializzati a 0.
 */
ProfiloGiocatore createNewPG(char nome[NAME_SIZE]);

/*
 * Controlla che un nome sia univoco, ovvero che non esistano altri giocatori con quel nome
 *
 * Parameters:
 * char nome[NAME_SIZE]: nome di cui si deve controllare l'unicità
 * Gioco* game: partita in corso
 *
 * Returns:
 * true: non esiste alcun giocatore con quel nome
 * false: esiste già un giocatore con quel nome
 */
_Bool checkNomeUnivoco(char nome[NAME_SIZE], Gioco* game);


/*
 * Ricevuto un ID scrive il nome del giocatore corrispondente:
 * - Se l'ID corrisponde ad una CPU il nome sarà "CONCORRENTE #<ID>";
 * - Se l'ID corrisponde ad un profilo giocatore il nome verrà scritto il suo
 *   nome colorato del giusto colore.
 *
 * Parameters:
 * Gioco* game: partita in corso
 * int id: ID del giocatore
 */
void printNomefromID(Gioco* game, int id);

/*
 * Permette di visualizzare il menù contenente tutti i
 * Profili Giocatore creati nella partita in corso.
 *
 * Parameters:
 * Gioco* game: partita in corso.
 */
void printMenuPGs(Gioco* game);

/*
 * Permette di visualizzare tutti i campi di un profilo giocatore se la partita non è in corso, altrimenti permette
 * il profilo giocatore solo se è un profilo scelto
 *
 * Parameters:
 * Gioco* game: partita in corso
 * ProfiloGiocatore player: giocatore da visualizzare
 */
void printPG(Gioco* game, ProfiloGiocatore player);

/*
 * Permette di visualizzare tutti i profili giocatore
 *
 * Parameters:
 * Gioco* game: partita in corso
 */
void printAllPGs(Gioco* game);

/*
 * Permette di caricare un salvataggio per aggiornare i campi di una struttura Gioco.
 * Se il file di salvataggio non viene aperto viene riportato un errore e il Gioco sarà
 * pari a NULL e la procedura verrà bloccata.
 * Se in un qualunque tentativo di lettura dal file binario viene letto un numero di elemento
 * diverso da quello aspettato vuol dire che il file è corrotto, quindi il gioco sarà pari a NULL
 * e la procedura verrà bloccata.
 *
 * Parameters:
 * const char saveFilePath[PATH_SIZE]: Percorso del file di salvataggio.
 */
Gioco* loadGame(const char saveFilePath[PATH_SIZE]);

/*
 * Permette di ricevere la locazione estesa di un file di salvataggio, dato il nome del file.
 *
 * Parameters:
 * char* nome: nome del file
 *
 * Returns:
 * "Saves/<nomefile>.bin"
 */
char* getFullPath(char* nome);

/*
 * Permette di visualizzare tutti i salvataggi presenti.
 */
void printSaves();

/*
 * Permette all'utente di selezionare un file di salvataggio da caricare.
 * Prima di visualizzano tutti i file presenti con un numero associato.
 * Poi si chiede all'utente di inserire il numero o il nome corrispondente al file,
 * nel caso in cui l'utente cambi idea e decida di iniziare una nuova partita può premere invio.
 *
 * Returns:
 * nome del file selezionato.
 */
char* selectSaveFile();

/*
 * Funzione di debug per visualizzare i campi di una struttura Gioco.
 *
 * Parameters:
 * Gioco* gioco: partita da stampare.
 */
void printGame(Gioco* gioco);

/*
 * Permette di terminare correttamente un gioco
 * Dealloca la memoria utilizzata dalla struttura Gioco durante lo Spr1d game.
 *
 * Parameters:
 * Gioco* game: partita in corso.
 */
void fineGioco(Gioco* game);

/*
 * Restituisce il numero di salvataggi presenti
 *
 * Returns:
 * numero intero positivo pari al numero di salvataggi.
 */
int NumSaves();

/*
 * Ricevuto un numero, restituisce il nome del file associato a quel numero.
 *
 * Parameters:
 * int num: numero corrispondente al file.
 *
 * Returns:
 * Nome del file corrispondete al numero.
 */
char* getSaveFromNum(int num);

/*
 * Permette di aggiungere il nome di un salvataggio nel file SaveFilesInfo.txt.
 *
 * Parameters:
 * char nome[PATH_SIZE]: nome del file di salvataggio.
 */
void aggiungiSalvataggio(char nome[PATH_SIZE]);

/*
 * Ricevuto il nome di un file di salvataggio, verifica se il nome è già in uso o se è disponibile.
 *
 * Parameters:
 * char saveFileName[NAME_SIZE]: nome del file di salvataggio.
 *
 * Returns:
 * true: il nome non è in uso
 * false: esiste un salvataggio con quel nome
 */
_Bool isSaveFileValid(char saveFileName[NAME_SIZE]);

/*
 * Permette di scegliere il nome del file in cui salvare la partita.
 * Nel caso in cui si voglia creare un nuovo salvataggio permette di inserire un nuovo nome, eliminando
 * eventuali estensioni se inserite dall'utente.
 * Nel caso in cui invece si vuole sovrascrivere un salvataggio si può inserire il numero associato oppure
 * il nome del salvataggio.
 *
 * Parameters:
 * Gioco* game: gioco in corso
 */
void getSaveName(Gioco* game);

/*
 * Inizializza un nuovo gioco con tutti i parametri azzerati
 *
 * Returns:
 * Partita inizializzata.
 */
Gioco* initGame();

/*
 * Permette di salare la partita corrente con il nome ricevuto tramite parametro.
 *
 * Parameters:
 * Gioco* game: gioco in corso;
 * char nomeFile[NAME_SIZE]: nome del file di salvataggio
 */
void saveGame(Gioco* game, char nomeFile[NAME_SIZE]);

/*
 * Permette d' inserire Profili Giocatore alla partita in corso, e di decidere
 * se salvarli o no.
 *
 * Parameters:
 * Gioco* game: gioco in corso
 *
 * Returns:
 * -true: sono stati aggiunti Profili Giocatore
 * -false non sono stati aggiunti Profili Giocatore
 */
_Bool inserimentoPG(Gioco* game);

/*
 * Permette di scegliere i Profili Giocatore che parteciperanno allo SPR1D GAME
 *
 * Parameters:
 * Gioco* game: gioco in corso
 */
void sceltaPG(Gioco* game);

/*
 * Permette l'inserimento dei valori di N (numero di giocatori totali dello SPR1D GAME)
 * e di M (numero di giocatori controllati dall'utente).
 * Alloca dinamicamente i vettori inGioco e indiciGU, e ne inizializza i valori.
 *
 * Parameters:
 * Gioco* game: gioco in corso
 */
void inserimentoMeN(Gioco* game);

/*
 * Restituisce in ID da assegnare a un Profilo Giocatore
 *
 * Parameters:
 * Gioco* game: gioco in corso
 *
 * Returns:
 * ID da assegnare.
 */
int getIdPg(Gioco* game);

/*
 * Controlla se un ID è già in uso
 *
 * Parameters:
 * Gioco* game: gioco in corso
 * int id: ID da controllare
 *
 * Returns:
 * - true: L'ID non è in uso
 * - false: L'ID è già in uso
 */
_Bool checkIDunivoco(Gioco* game, int id);

/*
 * Controlla se il profilo è già in uso
 *
 * Parameters:
 * Gioco* game: gioco in corso
 * int id: indice del profilo da controllare
 *
 * Returns:
 * - true: il profilo è libero
 * - false: il profilo è già in uso
 */
_Bool checkProfiloScelto(Gioco* game, int id);

/*
 * Permette di ricevere il Profilo Giocatore corrispondente a un ID ricevuto come parametro.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * int id: ID del Profilo Giocatore.
 */
ProfiloGiocatore getPGfromID(Gioco* game, int id);

/*
 * Cerca se all'interno del gruppo esista un giocatore con l'ID ricevuto tramite parametro.
 *
 * Parameters:
 * int id: ID da cercare;
 * Gruppo gruppo: gruppo in cui cercare.
 *
 * Returns:
 * true: l'ID è contenuto nel gruppo.
 * false: l'ID non è contenuto nel gruppo.
 */
_Bool isInGruppo(int id, Gruppo gruppo);

/*
 * Permette di trovare un ID estratto casualmente da quello di uno dei giocatori
 * presente all'interno di un Gruppo.
 *
 * Parameters:
 *Gruppo gruppo: gruppo da cui estrarre l'ID.
 *
 * Returns:
 * ID estratto.
 */
int randIDfromGruppo(Gruppo gruppo);

/*
 * Permette di sapere se un gruppo è formato da sole CPU
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che partecipa al gioco.
 *
 * Returns:
 * true: il gruppo è formato da sole CPU;
 * false: all'interno dl gruppo c'é almeno un Profilo Giocatore.
 */
_Bool isCPUvsCPU(Gioco* game,Gruppo gruppo);

/*
 * Permette di cambiare il turno in corrente, passando al prossimo giocatore.
 *
 * Parameters:
 * Turno *indexTurno: turno corrente;
 * int numPlayers: numero di giocatori che partecipano al gioco
 */
void cambiaTurno(Turno *indexTurno, int numPlayers);

/*
 * Restituisce l'indice all'intendo dell'array id_membri nel gruppo,
 * corrispondente a quello del giocatore con ID più basso.
 *
 * Parameters:
 * Gruppo gruppo: gruppo in cui cercare il giocatore.
 *
 * Returns:
 * intero positivo corrispondente all'indice del giocatore.
 */
unsigned int indexLowestIDinGruppo(Gruppo gruppo);

/*
 * Controlla se esiste un Profilo Giocatore chiamato "Riccardo Scateni" che partecipa
 * allo SPR1D GAME.
 *
 * Returns:
 * -true: "Riccardo Scateni" è in gioco;
 * -false: "Riccardo Scateni" non è in gioco;
 */
_Bool RiccardoScateniInGioco(Gioco* game);

/*
 * CHEAT CODE
 * Questo cheat farà sempre vincere il giocatore "Riccardo Scateni".
 * Se presente nel gruppo, "Riccardo Scateni" sostituirà l'effettivo vincitore dle gruppo.
 *
 * Parameters:
 *
 * Returns:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che sta partecipando al gioco;
 * int* id_vincitore: id del vincitore del gioco.
 *
 */
void FrontmanDelloSPR1DGAME(Gioco* game, Gruppo gruppo, int* id_vincitore);

/*
 * CHEAT CODE
 * Questo cheat farà sempre perdere il giocatore "Michele Cocco".
 * Se "Michele Cocco" vince un gioco, questo sarà sostituito da un giocatore a caso dello stesso gruppo.
 *
 * Parameters:
 * Gioco* game: partita in corso;
 * Gruppo gruppo: gruppo che sta partecipando al gioco;
 * int* id_vincitore: id del vincitore del gioco.
 */
void FallitoDelloSPR1DGAME(Gioco* game, Gruppo gruppo, int* id_vincitore);

/*
 * Permette di sapere il numero di giocatori ancora in gioco, ovvero il numero di giocatori che
 * non sono stati ancora eliminati.
 *
 * Parameters:
 * Gioco* game: partita in corso.
 *
 * Returns:
 * numero intero positivo pari al numero di giocatori non eliminati.
 */
int numInGioco(Gioco* game);

/*
 * Permette di leggere le informazioni relative un gioco o relative lo SPR1D GAME.
 *
 * Parameters:
 * char* info: percorso in cui si trovano le info da leggere
 */
void printInfo(char* info);

/*
 * Permette di sapere se tutti i Giocatori Utente sono stati eliminati
 *
 * Parameters:
 * Gioco* game: partita in corso
 *
 * Returns:
 * true: tutti i giocatori utente sono stati eliminati
 * false: ci sono ancora giocatori utente in gioco
 */
_Bool giocatoriUtenteEliminati(Gioco* game);

/*
 * Permette di visualizzare le statistiche riguardanti gli SPR1D GAME giocati da un player:
 * verranno visualizzati in verde gli SPR1D GAME vinti, in ciano quelli in cui
 * è arrivato in finale, e in grigio quelli persi.
 *
 * Parameters:
 * ProfiloGiocatore profilo: Profilo Giocatore di cui si vogliono visualizzare le statistiche
 */
void printSPR1DGAMEtotali(ProfiloGiocatore profilo);

/*
 * Permette di visualizzare le statistiche riguardanti i giochi giocati da un player:
 * verranno visualizzati in verde i giochi vinti, e in grigio quelli persi.
 *
 * Parameters:
 *ProfiloGiocatore profilo: Profilo Giocatore di cui si vogliono visualizzare le statistiche
 */
void printGiochiTotali(ProfiloGiocatore profilo);

/*
 * Trova se un numero è o no una potenza di 2
 *
 * Parameters:
 * int num: numero di cui si vuole verificare se è una potenza di 2
 *
 * Returns:
 * true: il numero è potenza di 2
 * false: il numero non è potenza di 2
 */
_Bool potenzaDiDue(int num);

#endif //SPR1DGAMELIB_H