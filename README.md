# Light Light
It's a small PCB game with actually 2 games :

https://www.youtube.com/video/Cth2Q4qN7tQ/

https://www.youtube.com/video/z0U1Xu2ibLQ/

## The game

### How it work
Button 9 disable sound (horrible, i know)
Button 1 & 2 start game 1 or 2
All Button Player 1 & 2 at same time at the beggining reset highscore (little bit hard)

### Configuration
In light_light_func.h duree_jeu change the timeout of game1 2 = 20s
You can also change how many led will light at same time on game 1 with Jeu1_nombre_led_joueur_actif

### Game 1
You will have 4 LED, press button with led on as fast as you can until timeout of the game.

### Game 2
The program will add one led every x secondes, going faster and faster. It end when all the led are on for the two players.

## Game Board

Actually there is only dev board, which don't change so much. You can remove external connector to gain some place and make a smaller PCB.
It use an Attiny1604 & HT16K33A as it was the cheapest price and easy to use. Version with 75HC595 & 74HC595 may be a little bit cheaper but more difficult to make.
For Attiny1604, all reference on how to use it are[here]([https://pages.github.com/](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md)) for UDPI & [here](https://github.com/SpenceKonde/megaTinyCore)
Thanks to [SpenceKonde](https://github.com/SpenceKonde) for his huge great work.

### Get notice
I use v1.1, v1.2 have some change and should work without problem.

### Information about the board
The board have 2 footprint for microphone, you need to get a passive one.
There are 2 foorprint for button + LED. One is cheap with standard 6x6mm tactil switch and 5730 LED, the other one use more expensive set with tactil switch & led in same package. You can take with [cap](https://www.lcsc.com/product-detail/Tactile-Switches_ROCPU-Switches-TPB01-101L1W_C2762125.html) or without and take that type of [cap] (https://www.lcsc.com/product-detail/Switch-Accessories-Caps_Khon-SC804AF1_C45359438.html). Be aware that some button + LED have cathode/anode at different position which will not work.
With 5730 LED, i recommend 5Kohm for R77 to R88 and 330ohm for the others.
You could also change the R for green LED.

### v1.2 :
- Correction Bug with Led J2 6-7-8-9
- Mutualising R for button
- Double footprint for microphone
- Change mounting hole
- Smaller PCB
- Add 5x220Ohm resistor to trick external battery cut off

## Small box

You can find .stl and FreeCad file inside FreeCad dir, as well as the PCB, i didn't try that version.

# Licence
Copyright (c) 2025 Froggy / FroggyCorp.

Do what you want with it until it's not money.