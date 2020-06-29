# 8051-stack
A game disgned for 8051 series single chips where player try to stack flat
platforms as high as possible.

## Wiring

Port | Device | Abbreviation | Remarks
:-: | :-: | :-: | :-:
P0(C), P2(R) | 8 * 8 dot matrix LED display | `dotm` | Common cathode
P1           | Seven-segment display        | `ssd` | Common cathode
P3.4         | Speaker | `sp` |
P3.2         | Main Push button | `btn` |

### Seven-segment display

P1.0 | P1.1 | P1.2 | P1.3 | P1.4 | P1.5 | P1.6 | P1.7
:--: | :--: | :--: | :--: | :--: | :--: | :--: | :--:
  A  |   B  |   C  |   D  |   E  |   F  |   G  |  SEL

* SEL
    L: data is sent to `ssd0`
    H: data is sent to `ssd1`

## 8 * 8 dot matrix LED display

### Usage

To light up a LED in position (x, y):
1. Clear R[y] (=0)
2. Set C[x] (=1)

## Links

* [ _Maybe_ the orignal game on Android](https://www.youtube.com/watch?v=62wMiyt82ng)
* [Similar larger version of the game](https://www.reddit.com/r/nextfuckinglevel/comments/erdvy6/a_neat_small_stacking_game/)

## Project Hierarchy

* `inc/`: where .h files should be.
* `src/`: where .c files should be.
* `tests/`: simple program for testing each device.
* `PowerPoint/`: Used to report on stage
