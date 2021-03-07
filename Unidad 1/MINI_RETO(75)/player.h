#ifndef PLAYER_H
#define PLAYER_H

struct the_player;
struct the_gun;

struct the_player *new_player();

void player_constructor(struct the_player *, const char *);
void player_destructor(struct the_player *);

void player_pickup_gun(struct the_player *, struct the_gun *);
void player_shoot(struct the_player *);
void player_drop_gun(struct the_player *);

#endif /*PLAYER_H*/