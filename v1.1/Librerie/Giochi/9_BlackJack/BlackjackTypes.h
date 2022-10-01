typedef struct
{
    int id;
    Mazzo* carte;
    int somma; //Somma dei valori delle carte possedute
    _Bool stop;
}Player_Blackjack;

typedef enum{inGioco,ventuno,sbancato,fermo}Status;