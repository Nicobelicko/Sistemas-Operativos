#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gun.h"

typedef struct 
{
    char *name;
    struct the_gun *gun;
    
} the_player;

the_player *new_player()
{
    return (the_player *)malloc(sizeof(the_player));
}
void player_constructor(the_player *player, const char *name)
{

    
    player->name = (char *)malloc(strlen(name + 1) * sizeof(char));
    strcpy(player->name, name);
    player->gun = NULL;
}

void player_destructor(the_player *player)
{
    free(player->name);
}

void player_pickup_gun(the_player *player, struct the_gun *gun)
{

    player->gun = gun;
}
void player_shoot(the_player *player)
{
    if (player->gun)
    {
        gun_trigger(player->gun);
    }
    else
    {
        printf("El jugador no tiene un arma con el cual disparar");
    }
}
void player_drop_gun(the_player *player)
{
    player->gun = NULL;
}
