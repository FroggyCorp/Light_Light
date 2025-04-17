//Copyright (c) 2025 Froggy / FroggyCorp.
//Do what you want with it until it's not money

#include "main.h"

void setup()
{
  Wire.begin();
  Serial.begin(115200); 
  while (!Serial);

  randomSeed(analogRead(0));
  HT16K33_init();

  //on efface les scores lors du premier lancement
  if (EEPROM.read(100) != 123) {
    EEPROM.write(100, 123);
    write_highscore(0, 1);
    write_highscore(0, 2);
  }
}


void loop()
{
    uint8_t numero_jeu = 0;
    numero_jeu = animation_debut();
    animation_lancement_jeu();
    if (numero_jeu == 1)
      jeu_1();
    else if(numero_jeu == 2)
      jeu_2();
    animation_gagnant(numero_jeu);

    clear_affichage();
    delay(2000);
}