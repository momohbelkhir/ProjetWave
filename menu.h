#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
 






typedef struct menu menu_t;

typedef struct{
    char  *c ;
    void (*fonc)();
    
} action_t;


 struct menu {
    menu_t * parent;
    char  *desc ;
    action_t *action[9];
    menu_t *item[9];
    int cpt;
    
} ;

menu_t * createMenu (const char * text);
void addMenuAction(menu_t *m, const char * text, void(*f)() );
void addSubMenu(menu_t* m, menu_t* sm);
void deleteMenu(menu_t* m);
void launchMenu(menu_t* m);
void quit();


#endif
