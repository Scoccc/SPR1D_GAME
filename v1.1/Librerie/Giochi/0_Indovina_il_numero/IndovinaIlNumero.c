#include "IndovinaIlNumero.h"

int game_IndovinaIlNumero(Gioco* game, Gruppo gruppo)
{
    //Dichiarazione variabili
    int num = randNumInRange(ILN_MIN,ILN_MAX); //Numero da indovinare
    Turno index_turno = indexLowestIDinGruppo(gruppo); //Indice che indic il giocatore corrente all'interno dell'array gi giocatori
    _Bool finita = false;
    int tentativoMin = ILN_MIN, tentativoMax = ILN_MAX; //Range di tentativi sensati
    int id_vincitore;
    Player_ILN* players_ILN = initPlayerILN(gruppo); //Array di giocatori

    font_title("INDOVINA IL NUMERO",FG_CYAN);

    printf("Inizia ");
    printNomefromID(game, gruppo.id_membri[index_turno]);
    printf("\n\n");

    while (!finita)
    {
        faseFaiTentativo(game,&players_ILN[index_turno], tentativoMin, tentativoMax);

        if(checkVittoria_ILN(players_ILN[index_turno],num,&tentativoMin,&tentativoMax))
            finita = true;
        else
            cambiaTurno(&index_turno,gruppo.sizeGruppo);
    }

    id_vincitore = players_ILN[index_turno].id;

    free(players_ILN);

    return id_vincitore;
}

Player_ILN* initPlayerILN(Gruppo gruppo)
{
    Player_ILN* players_ILN = (Player_ILN*) malloc(sizeof(Player_ILN) * gruppo.sizeGruppo);
    int i;

    for (i = 0; i < gruppo.sizeGruppo; ++i)
    {
        players_ILN[i].id = gruppo.id_membri[i];
        players_ILN[i].ultimoTentativo = NULL_TENTATIVO;
    }

    return players_ILN;
}

void faseFaiTentativo(Gioco* game, Player_ILN* player_ILN, int tentativoMin, int tentativoMax)
{
    printNomefromID(game, player_ILN->id);
    printf(" cerca di indovinare il numero\n");

    if(isCPU(game, player_ILN->id))
    {
        player_ILN->ultimoTentativo = randNumInRange(tentativoMin, tentativoMax);
        usleep(GAMES_SPEED);//Simula l'attesa dell'input
        printf("%d\n", player_ILN->ultimoTentativo);
    }
    else
        player_ILN->ultimoTentativo = getIntInRange("Il numero deve essere nel range 0-999",0,999);

}

_Bool checkVittoria_ILN(Player_ILN player_ILN, int num, int* tentativoMin, int* tentativoMax)
{
    if(player_ILN.ultimoTentativo == num) //Il giocatore ha indovinato il numero
    {
        printf("Numero indovinato!\n\n");
        return true;
    }
    else //Il giocatore non ha indovinato il numero
    {
        if(player_ILN.ultimoTentativo > num) //Il numero tentato era troppo grande rispetto al numero da indovinare
        {
            printf("Numero troppo grande!\n\n");
            // Se il giocatore ha tentato un numero più piccolo di tentativoMax,
            // quest'ultimo dovrà assumere il valore dell' ultimo tentativo -1
            *tentativoMax = (int) fmin( player_ILN.ultimoTentativo - 1, *tentativoMax);
        }
        else //Il numero tentato era troppo piccolo rispetto al numero da indovinare
        {
            printf("Numero troppo piccolo!\n\n");
            // Se il giocatore ha tentato un numero più grande di tentativoMin,
            // quest'ultimo dovrà assumere il valore dell' ultimo tentativo +1
            *tentativoMin = (int) fmax(player_ILN.ultimoTentativo + 1, *tentativoMin);
        }
        return false;
    }
}
