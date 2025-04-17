//Copyright (c) 2025 Froggy / FroggyCorp.
//Do what you want with it until it's not money

#include "light_light.func.h"
#include "ascii_led.h"
#include "sound.h"

uint8_t array_led_score[6];
uint16_t array_led_joueur[2];
uint16_t array_led_timer = 0;
uint16_t array_bouton[2];
uint16_t score[2];
bool bool_update_affichage = 0;
#if EEPROM_SAVE_SOUND == 1
bool bool_music_on = EEPROM.read(EEPROM_CONF_SOUND);
#else
bool bool_music_on = 1;
#endif
uint32_t timer_tricking_external_battery = 0;
uint8_t state_tricking_external_battery = LOW;

void animation_lancement_jeu() {
    clear_affichage();
    update_affichage(true);
    noTone(pin_musique);

    uint32_t millis_animation = millis();
    const uint32_t tick = 10;    //definit un tick de la boucle en mS

    uint8_t tick_animation_led_timer = 0;
    uint8_t index_animation_led_timer = 0;

    while (true) {
        if (millis() - millis_animation > tick) {
            millis_animation = millis();
            tick_animation_led_timer ++;
        }

        if (tick_animation_led_timer == 50) {
            tick_animation_led_timer = 0;

            if (index_animation_led_timer == 0) {
                array_led_timer = 0b1111111111;
                if (bool_music_on)
                    tone(pin_musique, 500);
            }
            if (index_animation_led_timer == 2) {
                array_led_timer = 0b11111;
                if (bool_music_on)
                    tone(pin_musique, 500);
            }
            if (index_animation_led_timer == 4) {
                array_led_timer = 0b11;
                if (bool_music_on)
                    tone(pin_musique, 500);
            }
            if ((index_animation_led_timer == 1) || (index_animation_led_timer == 3) || (index_animation_led_timer == 5)) {
                array_led_timer = 0;
                if (bool_music_on)
                    noTone(pin_musique);
            }
            
            if ((index_animation_led_timer == 6) || (index_animation_led_timer == 7))
                if (bool_music_on)
                    tone(pin_musique, 1000);
            index_animation_led_timer++;

            update_affichage(true);
        }

        if (index_animation_led_timer == 8)
            return;

        tricking_external_battery();
    }


}

uint8_t animation_debut() {
    clear_affichage();
    update_affichage(true);
    noTone(pin_musique);

    uint32_t millis_animation = millis();
    const uint32_t tick = 20;    //definit un tick de la boucle en mS

    uint8_t tick_read_bouton = 0;
    uint32_t tick_read_bouton_2 = 0;


    uint8_t tick_animation_led_joueur = 0;
    uint8_t count_animation_led_joueur = 0;

    uint8_t tick_animation_led_timer = 0;
    int8_t part_animation_led_timer = -1;
    int16_t numero_bit_animation_led_timer;
    int8_t direction_animation_led_timer;
    uint16_t tmp_array_led_timer; 

    uint8_t tick_animation_led_score = 0;
    uint8_t index_animation_led_score = 0;

    uint8_t tick_animation_son = 0;
    uint8_t index_animation_son = 0;
    uint32_t timer_changement_bool_musique_on = 0;

    while (true) {  //~3ms / boucle sur UNO
        if (millis() - millis_animation > tick) {
            millis_animation = millis();
            tick_animation_led_joueur ++;
            tick_animation_led_timer ++;
            tick_animation_led_score ++;
            tick_animation_son ++;
            tick_read_bouton ++;
            tick_read_bouton_2 ++;
        }

        //scrolling led score
        if (tick_animation_led_score == 10) {
            tick_animation_led_score = 0;
            index_animation_led_score = affichage_texte(index_animation_led_score, texte_animation_debut, 0);
            array_led_score[3] = array_led_score[0];
            array_led_score[4] = array_led_score[1];
            array_led_score[5] = array_led_score[2];
        }

        //animation led timer
        if (tick_animation_led_timer == 3) {
            tick_animation_led_timer = 0;

            if (part_animation_led_timer == -1) {//initialisation
                numero_bit_animation_led_timer = 0;
                direction_animation_led_timer = 1;
                tmp_array_led_timer = 0b100000000001;   //permet de définir les extremités
                part_animation_led_timer = 0;
                array_led_timer = 0;
            }

            if (part_animation_led_timer == 0) {
                if ((!bitRead(tmp_array_led_timer, numero_bit_animation_led_timer + direction_animation_led_timer)) && (numero_bit_animation_led_timer != 0))
                    bitClear(tmp_array_led_timer, numero_bit_animation_led_timer);

                numero_bit_animation_led_timer = numero_bit_animation_led_timer + direction_animation_led_timer;
                if (bitRead(tmp_array_led_timer, numero_bit_animation_led_timer)) {
                    direction_animation_led_timer = direction_animation_led_timer * -1;
                    numero_bit_animation_led_timer = numero_bit_animation_led_timer + 2*direction_animation_led_timer;
                }
                bitSet(tmp_array_led_timer, numero_bit_animation_led_timer);
                array_led_timer = tmp_array_led_timer >> 1;

                if (array_led_timer == 0b11111111111) {
                    part_animation_led_timer++;
                    direction_animation_led_timer = -1;
                    numero_bit_animation_led_timer = 10;
                }
            }
            else if (part_animation_led_timer == 1) {
                bitClear(array_led_timer, numero_bit_animation_led_timer);
                if (numero_bit_animation_led_timer == 0) {
                    numero_bit_animation_led_timer = 0;
                    part_animation_led_timer = 2;
                }
                else
                    numero_bit_animation_led_timer = numero_bit_animation_led_timer - 1;
            }
            else if (part_animation_led_timer == 2) {
                bitSet(array_led_timer, numero_bit_animation_led_timer);
                if (numero_bit_animation_led_timer == 9) {
                    numero_bit_animation_led_timer = 9;
                    part_animation_led_timer = 3;
                }
                else
                    numero_bit_animation_led_timer = numero_bit_animation_led_timer + 1;
            }
            else if (part_animation_led_timer == 3) {
                bitClear(array_led_timer, numero_bit_animation_led_timer);
                if (numero_bit_animation_led_timer == 0) {
                    part_animation_led_timer = -1;
                }
                else
                    numero_bit_animation_led_timer = numero_bit_animation_led_timer - 1;
            }
        }

        //animation led_joueurs
        if (tick_animation_led_joueur == 12) {
            tick_animation_led_joueur = 0;

            if (count_animation_led_joueur == 0) array_led_joueur[0] = 0b110110001;
            if (count_animation_led_joueur == 1) array_led_joueur[0] = 0;
            if (count_animation_led_joueur == 2) array_led_joueur[0] = 0b1001010;
            if (count_animation_led_joueur == 3) array_led_joueur[0] = 0;
            if (count_animation_led_joueur == 4) array_led_joueur[0] = 0b100;
            if (count_animation_led_joueur == 5) array_led_joueur[0] = 0;

            array_led_joueur[1] = array_led_joueur[0];
            count_animation_led_joueur ++;
            if (count_animation_led_joueur == 6)
                count_animation_led_joueur = 0;
        }

        //musique
        if ((tick_animation_son == 6) && (bool_music_on)) {
            tick_animation_son = 0;
            
            if (music_animation_lancement_jeu[index_animation_son] == 0)
                noTone(pin_musique);
            else
                tone(pin_musique, music_animation_lancement_jeu[index_animation_son]);
            
            index_animation_son ++;            

            if (index_animation_son >= sizeof(music_animation_lancement_jeu) >> 1)
                index_animation_son = 0;
        }

        update_affichage(true);
        if (tick_read_bouton >= 2) {//20ms minimum entre 2 read
            tick_read_bouton = 0;
            read_bouton();
            if ((array_bouton[0] == 0b111111111) || (array_bouton[1] == 0b111111111)) { //all button player 1 & 2 to reset highscore
                write_highscore(0, 1);
                write_highscore(0, 2);
            }
            if (((array_bouton[0] & 0b100000000) > 0 | (array_bouton[1] & 0b100000000) > 0) && (tick_read_bouton_2 - timer_changement_bool_musique_on > 40)) {
                switch_sound();
                timer_changement_bool_musique_on = tick_read_bouton_2;
                index_animation_son = 0;
                tick_animation_son = 5;
                noTone(pin_musique);
            }
            if (tick_read_bouton_2 > 50) {    //on attend 2s pour lancer les jeux
                if (((array_bouton[0] & 0b1) > 0) || ((array_bouton[1] & 0b1) > 0))
                    return 1;
                else if (((array_bouton[0] & 0b10) > 0) || ((array_bouton[1] & 0b10) > 0))
                    return 2;
            }
        }

        tricking_external_battery();

    }
}


void jeu_2() {
    HT16K33_init();
    noTone(pin_musique);
    score[0] = 0;
    score[1] = 0;
    
    uint32_t millis_jeu = millis();
    const uint32_t tick = 10;    //definit un tick de la boucle en mS
    uint8_t tick_jeu_read_touche = 0;
    uint8_t tick_jeu_temps = 0;

    uint8_t tick_refresh_led_joueur = 0;
    uint8_t tick_max_refresh_led_joueur = 50;

    array_led_timer = 0;

    while(true) {
        if (millis() - millis_jeu > tick) {
            millis_jeu = millis();
            tick_jeu_read_touche ++;
            tick_refresh_led_joueur++;
            tick_jeu_temps ++;
        }

        //recuperation des touches
        if (tick_jeu_read_touche == 2) {//20ms minimum entre 2 read
            tick_jeu_read_touche = 0;
            read_bouton();

            for (uint8_t a=0; a != 2; a++) {
                //on check si correspondance
                score[a] = score[a] + detection_led_bouton(a);
                update_score(score[a], a);
            }
        }

        if (tick_refresh_led_joueur == tick_max_refresh_led_joueur) {
            tick_refresh_led_joueur = 0;
                if ((array_led_joueur[0] == 0b111111111) && (array_led_joueur[1] == 0b111111111))
                {//Les deux joueurs sont full, on ne pourra rien rajouter, on quitte
                    return;
                }

                //on calcul la vitesse
                tick_max_refresh_led_joueur = 50 - ((score[0] + score[1])/5);
/*                if (((score[0] + score[1]) /2) >= 80)
                    tick_max_refresh_led_joueur = 40;
                if (((score[0] + score[1]) /2) >= 100)
                    tick_max_refresh_led_joueur = 40 - ((score[0] + score[1]) /20);
*/
                //on rafraichit les leds joueur
                set_led_joueur_jeu2(0);
                set_led_joueur_jeu2(1);

                if (bool_music_on)
                    tone(pin_musique, 800, 20);
        }

        update_affichage(true);

        tricking_external_battery();

    }
}


void jeu_1() {
    HT16K33_init();
    set_led_joueur(0);
    set_led_joueur(1);
    noTone(pin_musique);
    score[0] = 0;
    score[1] = 0;
    
    uint32_t millis_jeu = millis();
    const uint32_t tick = 10;    //definit un tick de la boucle en mS
    uint8_t tick_jeu_read_touche = 0;
    uint8_t tick_jeu_temps = 0;
    
    array_led_timer = 0b1111111111;

    while(true) {
        if (millis() - millis_jeu > tick) {
            millis_jeu = millis();
            tick_jeu_read_touche ++;
            tick_jeu_temps ++;
        }

        //recuperation des touches
        if (tick_jeu_read_touche == 2) {//20ms minimum entre 2 read
            tick_jeu_read_touche = 0;
            read_bouton();

            for (uint8_t a=0; a != 2; a++) {
                //on check si correspondance
                score[a] = score[a] + detection_led_bouton(a);
                update_score(score[a], a);

                //on rafraichit les leds joueur
                set_led_joueur(a);
            }
        }

        //affiche du temps
        if (tick_jeu_temps == duree_jeu*100) {
            tick_jeu_temps = 0;

            array_led_timer = array_led_timer >> 1;
        }

        update_affichage(true);

        if (array_led_timer == 0)
            return;
    
        tricking_external_battery();
    }
}

void tricking_external_battery() {
    pinMode(PIN_PA1, OUTPUT);
    pinMode(PIN_PA2, OUTPUT);
    pinMode(PIN_PA5, OUTPUT);
    pinMode(PIN_PA6, OUTPUT);
    pinMode(PIN_PA7, OUTPUT);

    if (((millis() - timer_tricking_external_battery) > TRICKING_EXTERNAL_BATTERY_ON) && (state_tricking_external_battery == HIGH)) {
        digitalWrite(PIN_PA1, LOW);
        digitalWrite(PIN_PA5, LOW);
        digitalWrite(PIN_PA6, LOW);
        digitalWrite(PIN_PA7, LOW);
        state_tricking_external_battery = LOW;
        timer_tricking_external_battery = millis();
    }
    
    if (((millis() - timer_tricking_external_battery) > TRICKING_EXTERNAL_BATTERY_OFF) && (state_tricking_external_battery == LOW)) {
        digitalWrite(PIN_PA1, HIGH);
        digitalWrite(PIN_PA5, HIGH);
        digitalWrite(PIN_PA6, HIGH);
        digitalWrite(PIN_PA7, HIGH);
        state_tricking_external_battery = HIGH;
        timer_tricking_external_battery = millis();
    }
}

void animation_gagnant(uint8_t numero_jeu) {
    clear_affichage();
    update_affichage(true);

    uint32_t millis_animation = millis();
    const uint32_t tick = 20;    //definit un tick de la boucle en mS

    uint8_t tick_animation_led_score = 0;
    uint8_t index_animation_led_score = 0;
    uint8_t part_animation_led_score = 0;

    uint8_t tick_animation_led_joueur = 0;
    uint8_t part_animation_led_joueur = 0;
    
    uint16_t tick_read_bouton = 0;

    uint8_t tick_animation_son = 0;
    uint8_t index_animation_son = 0;
    uint8_t part_animation_son = 0;

    uint16_t tick_end = 0;

    bool new_highscore = false;
    uint8_t gagnant = 0;
    uint8_t perdant = 0;
    bool egalite = false;

    if (score[0] == score[1]) {
        part_animation_led_score = 0;
        egalite = true;
    }
    else if (score[0] < score[1]) {
        part_animation_led_score = 1;
        gagnant = 1;
        perdant = 0;
    }
    else if(score[0] > score[1]) {
        part_animation_led_score = 1;
        gagnant = 0;
        perdant = 1;
    }
    
    if (read_highscore(numero_jeu) < score[gagnant]) {
        write_highscore(score[gagnant], numero_jeu);
        new_highscore = true;
    }

    while (true) {
        if (millis() - millis_animation > tick) {
            millis_animation = millis();
            tick_animation_led_score ++;
            tick_animation_led_joueur ++;
            tick_animation_son ++;
            tick_read_bouton++;
            tick_end++;
        }

        //scrolling led score
        if (tick_animation_led_score == 15) {
            tick_animation_led_score = 0;

            if (part_animation_led_score == 0) {    //egalite
                index_animation_led_score = affichage_texte(index_animation_led_score, texte_animation_gagnant_equality, 0);
                array_led_score[3] = array_led_score[0];
                array_led_score[4] = array_led_score[1];
                array_led_score[5] = array_led_score[2];

                if (index_animation_led_score == 0) {//on affiche une fois
                    if (new_highscore)
                        part_animation_led_score = 2;
                    else
                        part_animation_led_score = 3;
                }
                tick_end = 0;
            }
            if (part_animation_led_score == 1) {    //on a un gagnant
                index_animation_led_score = affichage_texte(index_animation_led_score, texte_animation_gagnant_winner, gagnant);
                affichage_texte(index_animation_led_score, texte_animation_gagnant_looser, perdant);

                if (index_animation_led_score == 0) {
                    if (new_highscore)
                        part_animation_led_score = 2;
                    else
                        part_animation_led_score = 3;
                }
                tick_end = 0;
            }
            if ((part_animation_led_score == 2) && (new_highscore)) {//on affiche le highscore
                index_animation_led_score = affichage_texte(index_animation_led_score, texte_animation_gagnant_new_highscore, gagnant);

                if (egalite) {
                    if (gagnant == 0) {
                        array_led_score[3] = array_led_score[0];
                        array_led_score[4] = array_led_score[1];
                        array_led_score[5] = array_led_score[2];
                    } else {
                        array_led_score[0] = array_led_score[3];
                        array_led_score[1] = array_led_score[4];
                        array_led_score[2] = array_led_score[5];
                    }
                }

                if (index_animation_led_score == 0)
                    part_animation_led_score = 3;
                tick_end = 0;
            }
        }

        if (tick_animation_led_joueur == 5) {
            tick_animation_led_joueur = 0;
            if (part_animation_led_score == 3) {

                if (part_animation_led_joueur == 0) {
                    array_led_joueur[gagnant] = 0b111111111;
                    update_score(score[gagnant], gagnant);
                    update_score(score[perdant], perdant);

                    if (egalite) {   //perdant & gagnant = 0
                        array_led_joueur[1] = array_led_joueur[0];
                        update_score(score[1], 1);
                    }
                }
                else if (part_animation_led_joueur == 1) {
                    array_led_joueur[gagnant] = 0;
                    array_led_score[0 + gagnant * 3] = 0;
                    array_led_score[1 + gagnant * 3] = 0;
                    array_led_score[2 + gagnant * 3] = 0;

                    if (egalite) {    //perdant & gagnant = 0
                        array_led_joueur[1] = 0;
                        array_led_score[0 + 1 * 3] = 0;
                        array_led_score[1 + 1 * 3] = 0;
                        array_led_score[2 + 1 * 3] = 0;
                    }
                }

                part_animation_led_joueur ++;

                if (part_animation_led_joueur == 2)
                    part_animation_led_joueur = 0;
            }
        }

            //musique
            if ((tick_animation_son == 5) && bool_music_on) {
                tick_animation_son = 0;
                
                if (part_animation_son == 0) {
                    if (music_animation_gagnant[index_animation_son] == 0)
                        noTone(pin_musique);
                    else
                        tone(pin_musique, music_animation_gagnant[index_animation_son]);
                    
                    index_animation_son ++;            
        
                    if (index_animation_son >= sizeof(music_animation_gagnant) >> 1)
                        part_animation_son = 1;
                }
            }

        if (tick_read_bouton == 300) {
            tick_read_bouton = 0;
            read_bouton();
            if ((array_bouton[0] | array_bouton[1]) > 1)
                return;
        }

        if (tick_end == 300)
            return;
        update_affichage(true);

        tricking_external_battery();
    }
}

void switch_sound() {
    if (bool_music_on == 1)
        bool_music_on = 0;
    else
        bool_music_on = 1;
    #if EEPROM_SAVE_SOUND == 1
        EEPROM.write(EEPROM_CONF_SOUND, bool_music_on);
    #endif
}

uint16_t read_highscore(uint8_t numero_jeu) {
    uint16_t highscore = 0;
    highscore = EEPROM.read(2*numero_jeu);
    highscore = highscore << 8 | EEPROM.read(2*numero_jeu + 1);
    return highscore;
}

void write_highscore(uint16_t score, uint8_t numero_jeu) {
    if (read_highscore(numero_jeu) != score) {
        EEPROM.write(2*numero_jeu, score >> 8);
        score = score & 0xFF;
        EEPROM.write(2*numero_jeu + 1, score);
    }
    return;
}

void clear_affichage() {
//remet tous les valeurs en lien avec l'affichage à 0
    for (uint8_t a = 0; a != 6; a++) {
        array_led_score[a] = 0;
    }
    array_led_joueur[0] = 0;
    array_led_joueur[1] = 0;
    array_led_timer = 0;

    update_affichage(true);
    return;
}

void set_led_joueur_jeu2(uint8_t num_joueur) {
//on remplit le premier emplacement vide aleatoirement
//si le bit est déjà set, on decalle d'un jusqu'à en trouver un.

    //si c'est déjà full, on quitte
    if (array_led_joueur[num_joueur] == 0b111111111)
        return;

    uint16_t tmp = 0;

    bitSet(tmp, random(0,9));
    while(true) {
        if (!(tmp & array_led_joueur[num_joueur])) {
            array_led_joueur[num_joueur] = array_led_joueur[num_joueur] | tmp;
            return;
        }
        else {
            tmp = tmp << 1;
            if (tmp == 0b1000000000)
                tmp = 0b1;
        }
    }
}


void set_led_joueur(uint8_t num_joueur) {
    while(true) {    
        uint16_t mask = 1;
        uint8_t compteur_bit = 0;
        //on compte le nombre de led allumée
        for (uint8_t a = 0; a != 9; a++) {
            if (mask & array_led_joueur[num_joueur])    //la led est up
                compteur_bit++;
            mask = mask << 1 ;
        }

        //on rallume une led. Si le premier emplacement alétoire est vide, on quitte. Sinon on décalle de 1 jusqu'à un emplacement vide
        if (compteur_bit < Jeu1_nombre_led_joueur_actif) {
            bool set_bit = false;
            uint16_t tmp = 0;
            bitSet(tmp, random(0,9));
            while(!set_bit) {
                if (!(tmp & array_led_joueur[num_joueur]) && !(tmp & array_bouton[num_joueur])) {
                    array_led_joueur[num_joueur] = array_led_joueur[num_joueur] | tmp;
                    set_bit = true;
                }
                else {
                    tmp = tmp << 1;
                    if (tmp == 0b1000000000) //on est en dehors, on repart à 0
                        tmp = 0b1;
                }
            }
        }
        else {
            bool_update_affichage = true;
            return;
        }
    }
}

void update_score(uint16_t score, uint8_t joueur) {
    //conversion du score en afficheur 7 segments
    array_led_score[2 + joueur * 3] = ascii_afficheur[score / 100];
    score = score - (score/100) * 100;
    array_led_score[1 + joueur * 3] = ascii_afficheur[score / 10];
    score = score - (score / 10 ) * 10;
    array_led_score[0 + joueur * 3] = ascii_afficheur[score];
    bool_update_affichage = true;
}

uint8_t detection_led_bouton(uint8_t num_joueur) {
    //renvoit le nombre de correspondance bouton + led allumé
    //eteint la led
    uint16_t mask = 1;
    uint16_t tmp = array_led_joueur[num_joueur] & array_bouton[num_joueur];
    uint8_t compteur_bit = 0;
    for (uint8_t a = 0; a != 9; a++) {
        if (mask & tmp)    //la led est up
        {
            compteur_bit++;
            bitClear(array_led_joueur[num_joueur], a);
        }
        mask = mask << 1 ;
    }
    return compteur_bit;
}

uint8_t affichage_texte(uint8_t index, uint8_t *texte, uint8_t joueur) {
    //affiche le *texte sur la position index sur l'afficheur du joueur
    //decale l'index en fonction
    uint8_t b = 0;
    for (int8_t a = 2; a != -1; a--) {
        if (texte[index + a] == ' ')   //espace (non géré par la table de correspondance)
            array_led_score[b + joueur * 3] = 0;
        else if(texte[index + a] == '-') //- (non géré par la table de correspondance)
            array_led_score[b + joueur * 3] = 0b1000000;
        else if(texte[index + a] == '@')   //fin de la chaine, on repart au debut
            return 0;
        else if(texte[index + a ] == ';' ) {    //on affiche le hightscore jeu 1. On saute
            update_score(read_highscore(1), 0);
            index = index + 2;
            break;
        }
        else if(texte[index + a ] == '<' ) {      //on affiche le hightscore jeu 2. On saute
            update_score(read_highscore(2), 0);
            index = index + 2;
            break;
        }
        else {
            array_led_score[b + joueur * 3] = ascii_afficheur[texte[index + a] - 48];   //affichage d'un chr de la table
        }

        b++;
    }

    if (texte[index + 3] == ':') {//cas du saut pour faire un clignotement
        index = index + 3;
    }

    index++;
    return index;
}


void update_affichage(bool force = false) {
//converti les données en affichage HT16K33 sur une seule matrice pour tout envoyer en une fois

    if (!force) //on force, on test pas si nécessité de rafraichir
        if (!bool_update_affichage)  //si pas de modification d'affichage, ne refresh pas
            return;

    uint8_t array_update_affichage[16] = {0};

    //score J1
    array_update_affichage[0] = array_led_score[0];
    array_update_affichage[1] = 0;
    array_update_affichage[2] = array_led_score[1];
    array_update_affichage[3] = 0;
    array_update_affichage[4] = array_led_score[2];
    array_update_affichage[5] = 0;

    //score J2
    array_update_affichage[6] = array_led_score[3];
    array_update_affichage[7] = 0;
    array_update_affichage[8] = array_led_score[4];
    array_update_affichage[9] = 0;
    array_update_affichage[10] = array_led_score[5];
    array_update_affichage[11] = 0;

    //led joueur1
    array_update_affichage[14] = array_led_joueur[0] ;
    array_update_affichage[15] = array_led_joueur[0] >> 8;
 
    //led joueur2
    //Les 5 premières leds sont connectés sur COM3/ROW[7-11] 4 dernières sur COM4/ROW[7-10] sur 2e octets
    array_update_affichage[6] = array_update_affichage[6] | ((array_led_joueur[1] & 0b1) << 7);
    array_update_affichage[7] = ((array_led_joueur[1] & 0b11111) >> 1 );
    array_update_affichage[8] = array_update_affichage[8] | ((array_led_joueur[1] & 0b100000) << 2);
    array_update_affichage[9] = ((array_led_joueur[1] & 0b111100000) >> 6);

    //led timer
    array_update_affichage[12] = array_led_timer;
    array_update_affichage[13] = array_led_timer >> 8;
    
    //on balance dans l'HT16K33
    I2C_write(0x00, array_update_affichage, sizeof(array_update_affichage));

    //on reinit l'affichage (facultatif ?)
    I2C_write(HT16K33_Display_setup | 0b1);

    bool_update_affichage = 0;
}


void I2C_write(uint8_t data) {
    //Ecriture 8b sur I2C
    Wire.beginTransmission(HT16K33_addr);
    Wire.write(data);
    Wire.endTransmission();
}

void I2C_write(uint8_t addr, uint8_t *data, uint8_t lenght) {
    //ecriture à la volée
    Wire.beginTransmission(HT16K33_addr);
    Wire.write(addr);
    for (uint8_t a = 0; a != lenght; a++)
        Wire.write(data[a]);
    Wire.endTransmission();
}

void read_bouton() {
//récupération des touches
    uint16_t a;

    I2C_write(HT16K33_Key_data);
    Wire.requestFrom(HT16K33_addr,4);
    a = Wire.read();  
    array_bouton [0] = a | (Wire.read() << 8);
    a = Wire.read();  
    array_bouton [1] = a | (Wire.read() << 8);
}

void test_affichage(uint8_t mode = 0) {
//test des leds
//mode == 0 défilement
//mode == 1 affichage de toutes les LEDs
    if (mode == 0) {
        array_led_joueur[0] = 1;
        for (uint8_t a = 0; a!=9; a++) {
            update_affichage(true);
            delay(200);
            array_led_joueur[0] <<= 1;
        }

        array_led_joueur[1] = 1;
        for (uint8_t a = 0; a!=9; a++) {
            update_affichage(true);
            delay(200);
            array_led_joueur[1] <<= 1;
        }

        array_led_score[0] = 1;
        array_led_score[1] = 1;
        array_led_score[2] = 1;
        for (uint8_t a = 0; a!=7; a++) {
            update_affichage(true);
            delay(200);
            array_led_score[0] <<= 1;
            array_led_score[1] <<= 1;
            array_led_score[2] <<= 1;
        }

        array_led_score[3] = 1;
        array_led_score[4] = 1;
        array_led_score[5] = 1;
        for (uint8_t a = 0; a!=7; a++) {
            update_affichage(true);
            delay(200);
            array_led_score[3] <<= 1;
            array_led_score[4] <<= 1;
            array_led_score[5] <<= 1;
        }
        array_led_score[3] = 0; //pour eviter que led1_J2 reste allumé
        array_led_score[4] = 0; //pour eviter que led6_J2 reste allumé

        array_led_timer = 1;
        for (uint8_t a = 0; a!=12; a++) {
            update_affichage(true);
            delay(200);
            array_led_timer <<= 1;
        }
    }
    else if (mode == 1) {
        array_led_joueur[0] = 0xFFFF;
        array_led_joueur[1] = 0xFFFF;
        array_led_score[0] = 0xFF;
        array_led_score[1] = 0xFF;
        array_led_score[2] = 0xFF;
        array_led_score[3] = 0xFF;
        array_led_score[4] = 0xFF;
        array_led_score[5] = 0xFF;
        array_led_timer = 0xFFFF;
        update_affichage(true);
    }
}

void HT16K33_init() {
//démarrage de HT16K33
    I2C_write(HT16K33_System_setup | 0b1);
    I2C_write(HT16K33_Row_int | 0);
    I2C_write(HT16K33_Dimming_set | 0xF);
    clear_affichage();
}
