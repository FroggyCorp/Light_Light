//Copyright (c) 2025 Froggy / FroggyCorp.
//Do what you want with it until it's not money

uint8_t texte_animation_debut[] = {"   - PRESS BOTTOM BUTTON TO START - PLAYER 1 FOR GAME 1 - PLAYER 2 FOR GAME 2 -   HIGHSCORE GAME 1   ;   ;   ;   ;   ;   ;      HIGHSCORE GAME 2   <   <   <   <   <   <    WINNER DONT USE DRUGS   @"};
uint8_t texte_animation_gagnant_new_highscore[] = {"NEW HIGHSCORE   @"};
uint8_t texte_animation_gagnant_equality[] = {"   SAME SAME   @"};
uint8_t texte_animation_gagnant_winner[] = {"   WIN - WIN - WIN   @"};
uint8_t texte_animation_gagnant_looser[] = {"   LOOSE - LOOSE -   @"};

//table - 48 pour le bon chr
const uint8_t ascii_afficheur[] = {
    0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
    0b11111111, // :  permet de faire clignoter en faisant un saut dans le texte ex : "   :123:   :123:   :123:"
    0b11111111, // ; affichage du highscore jeu 1 ex : "HIGHSCORE   ;   ;   ;   ;   ;   ;   SUITE TEXTE"
    0b11111111, // < affichage du highscore jeu 2 ex : "HIGHSCORE   ;   ;   ;   ;   ;   ;   SUITE TEXTE"
    0b11111111, // =
    0b11111111, // >
    0b11111111, // ?
    0b11111111, // @ fin de la chaine de chr
    0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
	0b00111101, // G
	0b01110110, // H
	0b00110000, // I
	0b00011110, // J
	0b01110101, // K
	0b00111000, // L
	0b00010101, // M
	0b00110111, // N
	0b00111111, // O
	0b01110011, // P
	0b01101011, // Q
	0b00110011, // R
	0b01101101, // S
	0b01111000, // T
	0b00111110, // U
	0b00111110, // V
	0b00101010, // W
	0b01110110, // X
	0b01101110, // Y
    0b01011011 // Z

};