//Copyright (c) 2025 Froggy / FroggyCorp.
//Do what you want with it until it's not money

#ifndef LIGH_LIGHT_FUNC_H
#define LIGH_LIGHT_FUNC_H

//*****************
//* configuration *
//*****************
#define Jeu1_nombre_led_joueur_actif 4   //nombre de led active jeu 1
#define duree_jeu 2                      // (en seconde par LED -> 2 = 2x10s)
#define EEPROM_SAVE_SOUND   1           //set to 1 to save sound configuration on/off


#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

#define HT16K33_addr 0x70
#define HT16K33_Display_data 0x00
#define HT16K33_System_setup 0x20
#define HT16K33_Key_data 0x40
#define HT16K33_INT_flag 0x60
#define HT16K33_Display_setup 0x80
#define HT16K33_Row_int 0xA0
#define HT16K33_Dimming_set 0xE0

//pin conf
#define pin_musique PIN_A4

//tricking external battery timer
#define TRICKING_EXTERNAL_BATTERY_ON    2000//en millis
#define TRICKING_EXTERNAL_BATTERY_OFF   8000//en millis

//EEPROM conf
#define EEPROM_CONF_SOUND 102


void read_bouton();
void HT16K33_init();
void clear_affichage();
void update_affichage(bool force = false);
void update_score(uint16_t score, uint8_t joueur);
void test_affichage(uint8_t mode = 0);
void I2C_write(uint8_t data);
void I2C_write(uint8_t addr, uint8_t *data, uint8_t lenght);
void animation_gagnant(uint8_t numero_jeu);
uint16_t read_highscore(uint8_t numero_jeu);
void write_highscore(uint16_t score, uint8_t numero_jeu);
uint8_t affichage_texte(uint8_t index, uint8_t *texte, uint8_t joueur);
uint8_t detection_led_bouton(uint8_t num_joueur);
void set_led_joueur(uint8_t num_joueur);
void set_led_joueur_jeu2(uint8_t num_joueur);
void jeu_1();
void jeu_2();
uint8_t animation_debut();
void animation_lancement_jeu();
void switch_sound();
void tricking_external_battery();

#endif