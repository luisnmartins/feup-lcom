# FEUP-LCOM

Here you can find  the laboratory projects and a final project developed for the Computer Laboratory (LCOM) class of the Master in Informatics and Computer Engineering (MIEIC) at the Faculty of Engineering of the University of Porto (FEUP).

This project was developed in C for MINIX OS.

Made in collaboration with [Carlos Freitas](https://github.com/CarlosFr97)

## Labs
--------------------

* Lab 1 - Introduction
* Lab 2 - Timer
* Lab 3 - Keyboard
* Lab 4 - Mouse
* Lab 5 - Graphics (VBE)

## Final Project
--------------------

This final project gets together all the previous labs developed through the course. This is inspired in the traditional game Snake.

The game allows both single and multiplayer.

![main menu](https://github.com/luisnmartins/feup-lcom/blob/master/proj/screenshots/menu.png)


### **Game styling**


In order to make it more editable and fun for the player before playing a user can select the head and body colors of his snake.

![snake styling](https://github.com/luisnmartins/feup-lcom/blob/master/proj/screenshots/styling.png)

### **Singleplayer**

In this mode there's a map where apples and bombs appear and disappear randomly. For each apple the player can "eat" his snake will grow a bit. For each 3 apples eaten the snake's speed will also increase. Besides these features there's also a boost that a user can use for one second which resets also after eating 3 apples. If it colides against a bomb the player will lose.

To control his snake the player can use the arrows and the CRTL key can be used for using the boost.

![singleplayer](https://github.com/luisnmartins/feup-lcom/blob/master/proj/screenshots/singleplayer.png)


### **Multiplayer**

For multiplayer there are 2 different game modes:

* Snake Gladiator
* Snake and Mouse

![multiplayer](https://github.com/luisnmartins/feup-lcom/blob/master/proj/screenshots/multiplayer.png)

#### Snake Gladiator

In this mode 2 players compete directly in the same game.

Following the same idea from the singleplayer mode each player has 5 keyboard inputs to use - 4 to guide the snake and 1 to use the boost when it is available.

![gladiator](https://github.com/luisnmartins/feup-lcom/blob/master/proj/screenshots/gladiator.png)


#### Snake and Mouse

This mode is a bit different since just one player has a snake. The other user should try to make it difficult to his adversary by planting some apples and bombs in the most difficult places using the mouse. In order to make it fair a player have to plant apples in order to be able to plant bombs.

It is based in 2 rounds so players should switch positions between rounds.


![snake and mouse](https://github.com/luisnmartins/feup-lcom/blob/master/proj/screenshots/snakemouse.png)




For a more detailed explanation feel free to read our [report](https://github.com/luisnmartins/feup-lcom/blob/master/proj/doc/relatorio.pdf)

