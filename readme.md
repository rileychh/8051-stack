# 8051-stack
A game disgned for 8051 series single chips where player try to stack flat
platforms as high as possible.

## Wiring

Port | Device
:-: | :-:
P0, P2 | 8 * 8 dot matrix LED display
P1     | Array of 8 LEDs
P3.4   | Speaker
P3.2   | Main Push button

## Seven-segment display (7LED)

* 7LED port

| 8051 | P1.0 | P1.1 | P1.2 | P1.3 | P1.4 | P1.5 | P1.6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 7LED | A   | B   | C   | D   | E   | F   | G   |

* How to light a 7LED

Ten digits 7LED <= P1.7 get Low

Digits 7LED <= P1.7 get Hi


## LED dot (dotm)

* How to light a LED dot :

R <= HI 

C <= Low

* LED dot's port 

HI port

8051|P2.0|P2.1|P2.2|P2.3|P2.4|P2.5|P2.6|P2.7
--|--|--|--|--|--|--|--|--
dotm|R1|R2|R3|R4|R5|R6|R7|R8

Low port

8051|P0.0|P0.1|P0.2|P0.3|P0.4|P0.5|P0.6|P0.7
--|--|--|--|--|--|--|--|--
dotm|C1|C2|C3|C4|C5|C6|C7|C8



## Links

* [ _Maybe_ the orignal game on Android](https://www.youtube.com/watch?v=62wMiyt82ng)
* [Similar larger version of the game](https://www.reddit.com/r/nextfuckinglevel/comments/erdvy6/a_neat_small_stacking_game/)

## Project Hierarchy

* `inc/`: where .h files should be.
* `src/`: where .c files should be.
* `tests/`: simple program for testing each device.
