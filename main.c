#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "menu.h"
#include "wave.h"
#include "args.h"


bool cont = true;

 void quit() {
   
  cont = false;
  
}


int main(int argc, char** argv){
    int i;
   printf("Programme '%s' lancé avec %d option(s) :\n", argv[0], argc-1);
  for(i = 1; i < argc; i++)
    printf("Option %d : %s\n", i, argv[i]);
  option_t* opt = NULL;
 
 opt =opt_string (opt,"-l",load_l); // load (const char);
 opt =opt_void (opt,"-s",save_s);   
 opt =opt_void (opt,"-f",information_f);
 opt=opt_void(opt,"-q",quit);
 opt =opt_void (opt,"-r",renverser_r);
 opt =opt_int(opt,"-c",vite_v);
 opt =opt_float(opt,"-v",redimensionner_r);
  opt =opt_void (opt,"-m",mono_m);
  opt =opt_void (opt,"-t",stereo_r);
  opt=opt_2int(opt,"-d",decouper_r);
 process_arguments(opt,argc,argv);

     
if( (argc-1)==0){
 
  
  menu_t* m;
  menu_t *m1,*m2,*m3, *m4;

  m = createMenu("Main menu");

  m1=createMenu("Fichier");
  addMenuAction(m1,"Ouvrir",load);
  m4=createMenu("Enregistrer");
  addMenuAction(m4,"enregistrer",save);
  addMenuAction(m4,"Mono 8bit 11.025khz",mono);
  addMenuAction(m4,"Stéréo 16bit 44.1khz",stereo);
  addSubMenu(m1,m4);
  
  addMenuAction(m1,"Informations",information);
  addMenuAction(m1,"Quitter",quit);
  addSubMenu(m,m1);
  
  m2=createMenu("Durée et tempo");
  addMenuAction(m2,"Inverser",renverser);
  addMenuAction(m2,"Découper",decouper); //decouper
  addMenuAction(m2,"Redimensionner",redimensionner); //
  addSubMenu(m,m2);
 
  m3=createMenu("Canaux");
  addMenuAction(m3,"canal",vite);  
  addSubMenu(m,m3);

  
  addMenuAction(m,"Quitter",quit);
  
  
 
  while(cont) launchMenu(m);
               printf("Merci, à bien tot !\n"); 
  deleteMenu(m);
}
opt_delete(opt);

return 0;
}
