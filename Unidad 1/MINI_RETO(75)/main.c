#include <stdio.h>
#include <stdlib.h>

#include "gun.h"
#include "player.h"

int main(int argc, char const *argv[])
{
    int origin_charger=0;
    struct the_gun* weapon = new_gun();
    char nombre[30];
    int aux = 0;
    int op = 0;
    printf("BIENVENIDO A GTA SAN ANDREAS\n");
    printf("Cual va a ser el nombre de su personaje\n");
    scanf("%s", nombre);
    struct the_player *player = new_player();
    player_constructor(player, nombre);

    printf("ESCOJE TU PRIMER ARMA, ELIGE LA QUE QUIERAS\n");
    printf("1. 9mm\n2. Escopeta\n3. Micro Uzi\n4. M4\n5. Francotirador\n6. Minigun\n7. Lanzacohetes\n");
    scanf("%d", &op);
    while (aux == 0)
    {

        switch (op)
        {
        case 1:
            gun_constructor(weapon, 100, 15, 12);
            origin_charger=12;
            aux = 1;
            break;
        case 2:
            gun_constructor(weapon, 30, 80, 2);
            origin_charger=2;
            aux = 1;
            break;
        case 3:
            gun_constructor(weapon, 300, 10, 30);
            origin_charger=30;
            aux = 1;
            break;
        case 4:
            gun_constructor(weapon, 300, 20, 30);
            origin_charger=30;
            aux = 1;
            break;
        case 5:
            gun_constructor(weapon, 20, 90, 1);
            origin_charger=1;
            aux = 1;
            break;
        case 6:
            gun_constructor(weapon, 1000, 10, 100);
            origin_charger=100;
            aux = 1;
            break;
        case 7:
            gun_constructor(weapon, 10, 95, 1);
            origin_charger=1;
            aux = 1;
            break;

        default:
            printf("Elija una opcion valida");
            break;
        }
    }
    player_pickup_gun(player,weapon);

    printf("Controles:\nPulse p para disparar\nPulse r para recargar\nPulse x para dejar el arma y terminar\nPulse s para las estadisticas\n");
    char c;
    do
    {
        c=getchar();
        if(c=='p'){
            player_shoot(player);
        }
        if(c=='r'){
            gun_refill(weapon,origin_charger);
        }
        if(c=='x'){
            player_drop_gun(player);
            break;
        }if(c=='s'){
            printf("Nombre %s\n",nombre);
            gun_charger(weapon);
            gun_bullets(weapon);   
        }
        
    } while (1);
    printf("|--------------------------------|\n");
    printf("|-----------GAME OVER------------|\n");
    printf("|Creador: JUAN NICOLAS RUIZ MUÑOZ|\n");
    printf("|-------Gracias por jugar--------|\n");
    printf("|--------------------------------|\n");

    player_destructor(player);
    free(player);

   
    gun_destructor(weapon);
    free(weapon);

    return 0;
}
