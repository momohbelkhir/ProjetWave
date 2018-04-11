#ifndef WAVE_H
#define WAVE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>


  
 typedef struct{
 char riff[4]; // ="RIFF"   4oct
 uint32_t S_tailf;   // taille du fichier 
 char wave[4]; //= "WAVE";
 char fmt[4];  //="fmt ";
 uint32_t nombre;  // subtaille=16 tjr
 
 uint16_t pcm;    //pcm=1
 uint16_t C_nbrc;      // nombre de caneaux 1 à 6
 uint32_t Freq;      // fréquence 
 uint32_t r_ops;    //nbr d'octets par seconde
 uint16_t b_octparblock;   //nbr d'octets / block
 uint16_t Precision;    //présdision
 char data[4]; //="data";
 
 uint32_t D_taildonne;    //taille des donneés
 

}Wave;


 typedef struct wave_tt{
Wave * entete;
uint8_t* block_canal;
}wave_tt;

typedef struct wave_tt* wave_t; 
// wave.c :
wave_t  wave_new(uint32_t f, uint16_t p, uint16_t c, uint32_t B);
wave_t  wave_load(const char* fname); 
bool wave_save(const char* fname, wave_t w);
void wave_delete(wave_t w);
void f3(const char* fname,float t);
void wave_reverse(wave_t w);
void decouper();
void mono();
void stereo();
void mono_m();
void stereo_r();
void decouper_r(int s,int l);
//void decouper();
//void oui_non();
//wave_t wave_split(wave_t,int* pc);
//void wave_canal(wave_t w, uint16_t c);
wave_t wave_crop(wave_t w, uint32_t start, uint32_t length);
 void redimensionner();
void redimensionner_r(float c);
void f7();
void f8();
void renverser();
void information();
void load();
void save();
void wave_canal(wave_t w,uint16_t c);
void vite();
void information_f();
void load_l(const char* fname);
void renverser_r();
void save_s();
 void vite_v(int c);
wave_t wave_scale(wave_t w , float s);

#endif




