typedef struct
{
    int id;
    int numTentativi;
}Player_Impiccato;

typedef struct
{
    char completa[BUFFSIZE];
    char offuscata[BUFFSIZE];
}Parola;

typedef struct tentativo
{
    char c;
    struct tentativo* next;
}Tentativo;

typedef enum {testa = 'O', corpo = '|', artoDX = '\\' , artoSX = '/'} PartiOmino;

