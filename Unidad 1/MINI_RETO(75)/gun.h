#ifndef GUN_H
#define GUN_H

typedef int bool_t;
struct the_gun;

struct the_gun *new_gun();

void gun_constructor(struct the_gun *, int, int, int);

void gun_destructor(struct the_gun *);

bool_t gun_has_bullets(struct the_gun *);
void gun_trigger(struct the_gun *);
void gun_refill(struct the_gun *,int);
void gun_charger(struct the_gun*);
void gun_charger(struct the_gun *);
void gun_bullets(struct the_gun *);


#endif /*GUN_H*/