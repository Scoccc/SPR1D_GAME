typedef enum {sinistra, destra} Posizione;

typedef struct
{
    int id;
    int riga;
    Posizione posizione;
}Player_PDV;

typedef struct
{
    _Bool fragile;
    _Bool integro;
}Vetro;
