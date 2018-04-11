#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "menu.h"
#include "wave.h"



 menu_t * createMenu (const char * text){
     menu_t * Menu = malloc(sizeof(menu_t));
     Menu->parent=NULL;
     
     Menu->desc = malloc(strlen(text));
     strcpy(Menu->desc,text);
    
     Menu->cpt=0;
     return Menu;
 }
 
 void addMenuAction(menu_t *m, const char * text, void(*f)() ){
     if(m->cpt < 9){
         
     m->action[m->cpt]=malloc(sizeof(action_t));
     
     m->action[m->cpt]->fonc=f;
     
     m->action[m->cpt]->c=malloc(strlen(text));
     strcpy(m->action[m->cpt]->c,text);
     
     (m->cpt)++;
     }
 }
 
  void addSubMenu(menu_t* m, menu_t* sm){
      if(sm->parent==NULL){
          sm->parent =m;
          if((m->cpt)<9){
          m->item[m->cpt]=malloc(sizeof(sm));
          m->item[m->cpt]=sm;
          (m->cpt)++;
          }
      }
      
  }

void deleteMenu(menu_t* m){
     if(m->parent==NULL){
     for( int i=0;i<(m->cpt);i++){
            if(m->item[i] != NULL){

        free(m->item[i]->desc);
         free(m->item[i]);
      } else if( m->action[i] != NULL){
        free(m->action[i]->c);
        
        free(m->action[i]);
         
    }
         
     }
  
 }
free(m);
 
}
 
void launchMenu(menu_t* m){
    printf(" %s:\n",m->desc);
    int i=0;
    int choix;
    for( i=0;i<(m->cpt);i++){
        if(m->item[i] != NULL){ printf("%d- %s\n",i+1,m->item[i]->desc);}
        else if (m->action[i] !=NULL){printf("%d- %s\n",i+1,m->action[i]->c);}
    }
   
   printf("-------------------------\n");
  printf("choice ? ");
  scanf("%d",&choix);
  
  if( choix <9 && choix >0){
      if(m->item[choix-1] != NULL){ 
          launchMenu(m->item[choix-1]);
          printf("\n");
    }
    
      else if(m->action[choix-1] !=NULL){
          m->action[choix-1]->fonc();
          printf("\n");
    }
  }
    
}
/*bool cont=false;
 void quit() {
  cont = false;
}*/

