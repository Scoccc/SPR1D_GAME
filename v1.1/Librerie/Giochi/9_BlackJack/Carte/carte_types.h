#ifndef CARTE_TYPES_H
#define CARTE_TYPES_H

typedef enum {Cuori, Quadri, Fiori, Picche}Seme;

typedef struct
{
    Seme seme;
    int val;
}Carta;

typedef struct mazzo
{
    Carta carta;
    struct mazzo* next;
}Mazzo;

#endif //CARTE_TYPES_H
