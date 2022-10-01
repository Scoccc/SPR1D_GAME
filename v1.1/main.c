/* * * * * * * * * * * * *
 *      SPR1D_GAME       *
 * Autore: Michele Cocco *
 * Matricola: 66123      *
 *                       *
 * Ver. 1.1   24/05/2022 *
 * * * * * * * * * * * * */

#include "Librerie/Fasi/fasi.h"

int main()
{
    //DICHIARZIONE VARIABILI
    Gioco* game;       //Partita in corso
    Fase fase_attuale; //fase in cui si trova la partita attualmente

    srand(time(NULL));

    //Funzione necessaria per far funzionare correttamente il programma su Windows.
    initMultiPiattaforma();

    do
    {
        clearScreen();

        game = Fase0_pregame();

        if(game == NULL)
            return 0;

        fase_attuale = trovaFase(game);

        while (fase_attuale != conclusa)
        {
            if (fase_attuale == scrematura)
                Fase1_Scrematura(game);
            else if (fase_attuale == svolgimento)
                Fase2_Svolgimento(game);
            else if (fase_attuale == finale)
                Fase3_Finale(game);

            fase_attuale = trovaFase(game);
        }

        fineGioco(game); //Si termina il gioco

        printf("Vorresti rigiocare una partita a SPR1D GAME? [s/n]\n");
    }
    while (getYesNo());

    return 0;
}