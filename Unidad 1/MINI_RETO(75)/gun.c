#include <stdlib.h>
#include <stdio.h>
typedef int bool_t;

typedef struct
{
    int charger;
    int bullets;
    int damage;

} the_gun;

the_gun *new_gun()
{
    return (the_gun *)malloc(sizeof(the_gun));
}

void gun_constructor(the_gun *gun, int init_bullets, int damage, int charger)
{
    gun->bullets = 0;
    gun->charger = 0;
    if (init_bullets > 0)
    {
        gun->bullets = init_bullets;
    }
    if (charger > 0)
    {
        gun->charger = charger;
    }
    if (damage > 0)
    {
        gun->damage = damage;
    }
}
void gun_destructor(the_gun *gun)
{
}
bool_t gun_has_bullets(the_gun *gun)
{
    return gun->bullets > 0;
}
void gun_trigger(the_gun *gun)
{
    if(gun->charger==0){
        printf("No tiene balas en el cargador\n");
    }else{
    gun->bullets--;
    gun->charger--;
    printf("!PUM¡\n");
    }
}
void gun_refill(the_gun *gun, int origin_charger)
{
    if (gun->bullets > 0 && gun->bullets < origin_charger)
    {
        printf("SOLO SE PUDIERON RECARGAR %d balas\n", gun->bullets);
        gun->bullets = 0;
        gun->charger += gun->bullets;
    }
    else if (gun->bullets == 0)
    {
        printf("NO TIENE MÀS BALAS PARA RECARGAR\n");
    }
    else
    {
        gun->bullets -= (origin_charger-gun->charger);
        gun->charger = origin_charger;
        printf("Arma recargada\n");
    }
}
void gun_charger(the_gun *gun)
{

    printf("Cargador: %d\n", gun->charger);
}
void gun_bullets(the_gun *gun)
{

    printf("Balas: %d\n", gun->bullets);
}
