#include "wave.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>



wave_t  wave_new(uint32_t f, uint16_t p, uint16_t c, uint32_t B) { 
   wave_t  New=malloc(sizeof(wave_tt)); //pr just *p
   New->entete=malloc(sizeof(Wave));
   New->entete->riff[0]='R'; New->entete->riff[1]='I'; New->entete->riff[2]='F'; New->entete->riff[3]='F';
   New->entete->S_tailf=B*(c*p/8)+44-8;
   New->entete->wave[0]='W';New->entete->wave[1]='A';New->entete->wave[2]='V';New->entete->wave[3]='E';

   New->entete->nombre=16;
   New->entete->pcm=1;
   New->entete->C_nbrc=c;

   New->entete->Freq=f;
   New->entete->r_ops=(c*p/8)*f;
    New->entete->b_octparblock=c*p/8;

   New->entete->Precision=p;
   New->entete->data[0]='d';New->entete->data[1]='a';New->entete->data[2]='t';New->entete->data[3]='a';

   New->entete->D_taildonne=B*(c*p/8);
   New->entete->fmt[0]='f';New->entete->fmt[1]='m';New->entete->fmt[2]='t';New->entete->fmt[3]=' ';
   
   
   New->block_canal=malloc(B*(c*p/8));
   
 return New;
}
void wave_delete(wave_t w){
  free(w->block_canal);
  free(w->entete);
  free(w);
}
wave_t wave_scale(wave_t w , float s){
wave_t w2 = wave_new((w->entete->Freq)*s, w->entete->Precision, w->entete->C_nbrc, (w->entete->D_taildonne)/(w->entete->b_octparblock));

w2->block_canal=malloc(w->entete->D_taildonne);
 uint32_t i =0;
uint8_t *copie_nl= malloc(w->entete->D_taildonne);
copie_nl = w->block_canal; 
uint8_t * stok = malloc(w->entete->D_taildonne);

for(i =0; i<=(w->entete->D_taildonne);i++){
*(stok+i)=*(copie_nl+i);
}
w2->block_canal=stok;
return w2;
}

wave_t wave_crop(wave_t w, uint32_t start, uint32_t length){
uint32_t startbloc = (w->entete->r_ops)/(w->entete->b_octparblock)*start;
uint32_t lengthbloc = (w->entete->r_ops)/(w->entete->b_octparblock)*length;

uint32_t startOct = (((w->entete->Precision/8)*(w->entete->C_nbrc))*startbloc);/// l'octet du depart
uint32_t lengthOct=(((w->entete->Precision/8)*(w->entete->C_nbrc))*lengthbloc);/// le nb d'octet a parcourir


if ( (startOct < w->entete->D_taildonne && lengthOct+startOct <= w->entete->D_taildonne)||
(startOct < w->entete->D_taildonne && startOct<=lengthOct && lengthOct+startOct <= w->entete->D_taildonne)||
(startOct < w->entete->D_taildonne && startOct>=lengthOct && lengthOct+startOct <= w->entete->D_taildonne))
{
wave_t w2 = wave_new(w->entete->Freq , w->entete->Precision, w->entete->C_nbrc, lengthbloc);
uint32_t temp = startOct;
uint8_t* new_debut_cop = malloc((w->entete->D_taildonne)-(temp));
new_debut_cop = (w->block_canal + (temp));
uint32_t i =0;
uint8_t * stok = malloc(lengthOct);
for(i =0; i<=(lengthOct);i++){
*(stok+i)=*((new_debut_cop)+i);
}
(w2->block_canal)=(stok);
return w2;
}else {
printf("paramettre invalide\n");
return NULL;
}
}


wave_t  wave_load(const char* fname){ // charge un wave
   FILE* fp=fopen(fname,"rb+");
   wave_t wav=malloc(sizeof(wave_t));
   wav->entete=malloc(sizeof(Wave));

    if(fp != NULL){
    unsigned char donner4[4];
    unsigned char donner2[2];
   

    fread(wav->entete->riff, 4, 1, fp); //

    fread(donner4, 4, 1, fp);
    wav->entete->S_tailf = donner4[0] | donner4[1]<<8 | donner4[2]<<16 | donner4[3]<<24;
    
    fread(wav->entete->wave, 4, 1, fp); // 
    fread(wav->entete->fmt, 4, 1, fp); //

    fread(donner4, 4, 1, fp); 
    wav->entete->nombre = donner4[0] | donner4[1]<<8 | donner4[2]<<16 | donner4[3]<<24;

    fread(donner2, 2, 1, fp); 
    wav->entete->pcm = donner2[0] | donner2[1]<<8;

    fread(donner2, 2, 1, fp); 
    wav->entete->C_nbrc = donner2[0] | donner2[1]<<8;

    fread(donner4, 4, 1, fp); 
    wav->entete->Freq = donner4[0] | donner4[1]<<8 | donner4[2]<<16 | donner4[3]<<24;

    fread(donner4, 4, 1, fp);  
    wav->entete->r_ops = donner4[0] | donner4[1]<<8 | donner4[2]<<16 | donner4[3]<<24;

    fread(donner2, 2, 1, fp); 
    wav->entete->b_octparblock= donner2[0] | donner2[1]<<8;

    fread(donner2, 2, 1, fp); 
    wav->entete->Precision = donner2[0] | donner2[1]<<8;

    fread(wav->entete->data, 4, 1, fp); 

    fread(donner4, 4, 1, fp); 
    wav->entete->D_taildonne = donner4[0] | donner4[1]<<8 | donner4[2]<<16 | donner4[3]<<24;

    wav->block_canal=malloc(wav->entete->D_taildonne);
      
     fread(wav->block_canal,wav->entete->D_taildonne,1,fp);
      

 fclose(fp);
   
return wav;
} 
 else {return NULL;}
}
bool wave_save(const char* fname, wave_t w){
  
  FILE * fp = fopen(fname,"wb+");
  if (w == NULL){
   // printf("err d'ouverture de ficher %s\n",fname);
    return false;
  }else{
    
    fwrite(w->entete->riff, 4, 1, fp); //
    
    fwrite(& (w->entete->S_tailf), 4, 1, fp); //

    fwrite(w->entete->wave, 4, 1, fp); // 
    fwrite(w->entete->fmt, 4, 1, fp); //

    fwrite(&(w->entete->nombre), 4, 1, fp); 
    

    fwrite(&(w->entete->pcm ), 2, 1, fp); 
    

    fwrite(&(w->entete->C_nbrc), 2, 1, fp); 
    

    fwrite(&(w->entete->Freq), 4, 1, fp); 
    
    fwrite(&(w->entete->r_ops) , 4, 1, fp);  
   
    fwrite(&(w->entete->b_octparblock), 2, 1, fp); 
    
    fwrite(&(w->entete->Precision), 2, 1, fp); 

    fwrite(w->entete->data, 4, 1, fp); // 

    fwrite(&(w->entete->D_taildonne), 4, 1, fp); 

    fwrite(w->block_canal,w->entete->D_taildonne,1,fp);

 fclose(fp);
    wave_delete(w);
     return true;
  }
}


/*void wave_canal(wave_t w, uint16_t c){
if (w->entete->nbC > c){
 w->entete->nbC = 1; 
}else if (w->entete->nbC < c){
 w->entete->nbC = w->entete->nbC * 2 ;
}
}*/


 /*void f4() {
  printf("Inversé: cette requette n'est pas disponible\n");
}*/
void wave_reverse(wave_t w){

int i =0;
uint8_t *renver= malloc(w->entete->D_taildonne);
renver = w->block_canal;
uint8_t * stok = malloc(w->entete->D_taildonne);
for(i = w->entete->D_taildonne;i>0;i--){
*(stok+i)=*(renver+((w->entete->D_taildonne)-i));
}
w->block_canal=stok;
 
}
 
void f5() { 
  printf("découpé : cette fonction n'est pas disponible\n");
}

///////////////////////////////////////////sans options:


wave_t fichier=NULL;
char nomff[20];
//bool enre =false;

void save(){
    if(fichier!=NULL){
printf("Entrez le nom du fichier dans lequel vous voulez enregistrer le son: ");
//char nomff[20];
scanf("%s",nomff);
  if(wave_save(nomff,fichier)){
   printf("Le %s a été crée avec succée !\n",nomff);
   
  }else{
 printf("Echec de creation ! Ouvrez d'abord un fichier.\n");
}
}else{printf("Echec de création ! Ouvrez d'abord un fichier.\n");}
}


void load(){
     if(fichier != NULL){
         printf("Voulez vous déjà enregistrer la source audio courrante ?: 1:oui / 2:non ");
      int c;
      scanf("%d",&c);
      if(c==1){
          if(wave_save(nomff,fichier)){
     
        printf("Le fichier %s a été creer avec succèe!\n",nomff);
}else{ printf("Echec de création !\n");}
  }else if(c==2){
      // wave_delete(fichier);
}
}
       printf("Entrez le nom du fichier que vous voulez ouvrir(wave_load):  ");
      
       scanf("%s",nomff);
       fichier=wave_load(nomff);
       if(fichier != NULL){
       printf("Le fichier %s a été ouvert avec succée!\n",nomff); 
       //enre=true;    
      
}else{
printf("Le fichier entré %s n'existe pas !\n",nomff);
}
}


void f3(const char* fname,float t) {  //information
  
  printf("Le nom du ficher courant est %s\n",fname);
  printf("Sa taille est: %f (s)\n ",t);
  
}

void information(){
if(fichier != NULL && nomff !=NULL){
   fichier=wave_load(nomff);
   float taill=(fichier->entete->D_taildonne)/(fichier->entete->r_ops);
  f3(nomff,taill);
  
}else{
  printf("Aucun fichier existant(0 informations) !\n");
}

}

void renverser(){
       if(fichier!=NULL){
          wave_reverse(fichier);
           
          printf("Le fichier courant %s bien été inversé !pour l'enregistrer allez vers (Enregistrer)\n",nomff);
         }else{printf("Echec de l'invertioin ! il faut d'abord ouvrir un fichier\n");
}

   }   
void mono(){
 if(fichier!=NULL){
          fichier =wave_new(11025,8,1,(fichier->entete->D_taildonne)/(fichier->entete->b_octparblock));
           printf("Comment voullez vous enregistrer 1:spécifier un nom / 2: nom d'origine ");
           int c;
           scanf("%d",&c);
           if(c==1){
            printf("Entrez le nom du fichier pour enregistrer ");
            scanf("%s",nomff);
           if(wave_save(nomff,fichier)){
          printf("Le fichier courant %s a bien été enregistrer \n",nomff);
         }else{printf("Echec !\n");
}
}else{ if(wave_save(nomff,fichier)){
 printf("Le fichier courant %s a bien été enregistrer \n",nomff);
      }
}
}else{printf("Echec ouvrez d'abord un fichier !\n");
}
}
void stereo(){
 if(fichier!=NULL){
          fichier =wave_new(44100,16,2,(fichier->entete->D_taildonne)/(fichier->entete->b_octparblock));
           
           printf("Comment voullez vous enregistrer 1:spécifier un nom / 2: nom d'origine ");
           int c;
           scanf("%d",&c);
           if(c==1){
            printf("Entrez le nom du fichier pour enregistrer ");
            scanf("%s",nomff);
           if(wave_save(nomff,fichier)){
          printf("Le fichier courant %s a bien été enregistrer \n",nomff);
         }else{printf("Echec !\n");
}
}else{ if(wave_save(nomff,fichier)){
 printf("Le fichier courant %s a bien été enregistrer \n",nomff);
      }
}
}else{printf("Echec ouvrez d'abord un fichier !\n");
}
}

void wave_canal(wave_t w, uint16_t c){

if (w->entete->C_nbrc > c){
 
 
wave_t w2= wave_new ((w->entete->Freq),(w->entete->Precision),1, (w->entete->D_taildonne)/(w->entete->b_octparblock)); 
 w2->block_canal = w->block_canal;
 *w=*w2;
}else{

wave_t w2= wave_new ((w->entete->Freq),(w->entete->Precision),(w->entete->C_nbrc)*2, (w->entete->D_taildonne)/(w->entete->b_octparblock)); 
 w2->block_canal = w->block_canal;
 *w=*w2;
}
}

void vite(){

  if(fichier != NULL){
    printf("Entrez le nombre de canaux : ");
      int c;
      scanf("%d",&c);
        wave_canal(fichier,c);
       
       printf("Pour enregitrer le fichier avec les nouveaux canaux allez vers (Enregitrer)\n");
}else{
 printf("Echec pas de source courrante! il faut ouvrir d'abord un fichier!\n");
  
}
}
 void redimensionner(){
  if(fichier != NULL){
    printf("Entrez un ratio pour redimensionner la source courrante : ");
      float c;
      scanf("%f",&c);
        fichier=wave_scale(fichier,c);
  
       printf("Pour enregitrer le fichier redimensionné allez vers (Enregitrer)\n");
}else{
 printf("Echec pas de source courrante! il faut ouvrir d'abord un fichier!\n");
  
}

}
 void decouper(){
   if(fichier != NULL){
      uint32_t s;
      uint32_t l;
    printf("Entrez un point de départ en seconde : ");
      scanf("%u",&s);
       printf("Entrez une durée en seconde : ");
      scanf("%u",&l);
        fichier = wave_crop(fichier,s,l);
  
       printf("Pour enregitrer le fichier redimensionné allez vers (Enregitrer)\n");
}else{
 printf("Echec pas de source courrante! il faut ouvrir d'abord un fichier!\n");
  
}
}
//////////////////////////////////////////////////avec options:
wave_t w=NULL;
 char nom1[20];

 

void load_l(const char* fname){ // wave_t  wave_load(const char* fname)
    if(w!=NULL){
      printf("Voulez vous déjà enregistrer la source audio courrante ?: 1:oui / 2:non ");
      int c;
      scanf("%d",&c);
      if(c==1){
          if(wave_save(nom1,w)){
     printf("Le fichier %s a été creer avec succèe!\n",nom1);
        // wave_delete(w);
}else{ printf("Echec de création !\n");}
  }else if(c==2){
       //wave_delete(w);
}
}   
    strcpy(nom1,fname);
    w= wave_load(fname);
    if(w==NULL){printf("Erreur le fichier %s n'as pas été ouvert !\n",fname);}
    else{printf("Le fichier %s à été ouvert avec succès!\n",fname);}
     
}
void information_f(){
if(w!=NULL && nom1!=NULL){
 w=wave_load(nom1);
   float tail_f=(w->entete->D_taildonne)/(w->entete->r_ops);
  f3(nom1,tail_f);
  
}else{
  printf("Aucun fichier existant(0 informations) !\n");
}
}
void renverser_r(){
  if(w!=NULL){
      wave_reverse(w);
     
     printf("Le fichier ouvert est inversé.\n");
}else{
  printf("Echec de l'invertion ! Veuillez d'abord ouvrir un fichier.\n");
}
}
void save_s(){
   
  if(w!=NULL){
printf("Comment souhaitez vous enregitrer la source courante? 1:spécifié un nom / 2:Cas échéant ");
      int c;
      scanf("%d",&c);
      if(c==1){
       printf("Entrez le nom du fichier pour enregistrer: ");
       scanf("%s",nom1);
          if(wave_save(nom1,w)){
     printf("Le fichier %s a été creer avec succèe!\n",nom1);
       // enre=true;

        // wave_delete(w);
}else{ printf("Echec de création !\n");}
  }else if(c==2){
       if(wave_save(nom1,w)){printf("Cas échéant.\n");}
}
} else{printf("Echec d'enregistrement veuillez d'abord ouvrir un fichier!\n");}
}
 void vite_v(int c){

  if(w != NULL){
    
        wave_canal(w,c);
       printf("Le Fichier ouvert a été modifié \n");
      
}else{
 printf("Echec pas de source courrante! il faut ouvrir d'abord un fichier!\n");
  
}
}
   void redimensionner_r(float c){
if(w != NULL){
    
        w= wave_scale(w,c);
        
       printf("Le Fichier ouvert est redimensionné ! \n");
}else{
 printf("Echec pas de source courrante! il faut ouvrir d'abord un fichier!\n");
  
}
}
 
    

void stereo_r(){
 if(w!=NULL){
          w =wave_new(44100,16,2,(w->entete->D_taildonne)/(w->entete->b_octparblock));
           
           printf("Comment voullez vous enregistrer 1:spécifier un nom / 2: nom d'origine ");
           int c;
           scanf("%d",&c);
           if(c==1){
            printf("Entrez le nom du fichier pour enregistrer ");
            scanf("%s",nom1);
           if(wave_save(nom1,w)){
          printf("Le fichier courant %s a bien été enregistrer \n",nom1);
         }else{printf("Echec de l'invertioin ! il faut d'abord ouvrir un fichier\n");
}
}else{ if(wave_save(nom1,w)){
 printf("Le fichier courant %s a bien été enregistrer \n",nom1);
      }
}
}else{printf("Echec ouvrez d'abord un fichier !\n");
}
}

void mono_m(){

 if(w!=NULL){
         w =wave_new(11025,8,1,(w->entete->D_taildonne)/(w->entete->b_octparblock));
           printf("Comment voullez vous enregistrer 1:spécifier un nom / 2: nom d'origine ");
           int c;
           scanf("%d",&c);
           if(c==1){
            printf("Entrez le nom du fichier pour enregistrer ");
            scanf("%s",nom1);
           if(wave_save(nom1,w)){
          printf("Le fichier courant %s a bien été enregistrer \n",nom1);
         }else{printf("Echec de l'invertioin ! il faut d'abord ouvrir un fichier\n");
}
}else{ if(wave_save(nom1,w)){
 printf("Le fichier courant %s a bien été enregistrer \n",nom1);
      }
}
}else{printf("Echec ouvrez d'abord un fichier !\n");
}
}

void decouper_r(int s,int l){
   if(w != NULL){
      
        w = wave_crop(w,s,l);
  
       printf("Le fichier à été découpé avec succès\n");
}else{
 printf("Echec pas de source courrante! il faut ouvrir d'abord un fichier!\n");
  
}
}

/*  fonctions prétes pour l'utilisation:

   int64_t wave_get(wave_t w , uint32_t i ,uint16_t j){
int64_t entier =(int8_t)(*(w->donne_wave+(i+((w->entete->Presi)/8)+(j-1))));
return entier;
}
///////////////////////////////////////////////////////////////////////////////////////
void wave_set(wave_t w , uint32_t i ,uint16_t j,int64_t a){
*(w->donne_wave+(i+((w->entete->Presi)/8)+(j-1)))=(int8_t)a;
}
*/






