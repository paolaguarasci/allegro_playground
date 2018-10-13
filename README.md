# Allegro Primer
---
On MAC (and Debian-like distro) compile with:

```bash
g++ main.cpp -L/usr/local/lib -lallegro -lallegro_main
```
---
The main() needs as like this:
```cpp
int main(int argc, char **argv) {}
```
---
With cmake installed:
```bash
$ cd build
$ cmake .
$ make
$ ./allegroPrimer
```



- Inizializzo l'app
- Installo la tastiera
- Creo il display
- Creo la coda di eventi
- Per gestire l'input da tastiera devo
  - avere la coda di eventi
  - registrare la tastiera come input per la cosa
  - in un loop (il game loop) decido cosa fare con questi tasti che premo
    - verifico il tipo di evento, se è del tipo "tasto premuto" allora
      - verifico, se mi serve, quale tasto ho premuto e mi comporto di conseguenza (switch???)
- Fuori dal loop, distruggo gli oggetti che ho creato
- Esco

----
inizializzo il modulo delle immagini
creo l'oggetto ALLEGRO_BITMAP (e lo assegno ad un puntatore) e gli carico dentro l'img (al_load_bitmap([path]))
Disegno l'img

Se voglio far vedere che l'img si muove
  creo e faccio partire un timer che emette un evento ogni x secondi (glielo indico io) (I miei FPS)
  Ogni volta che si verifica l'evento timer
    cancello tutto
    disegno l'img nella nuova posizione
    flippo il display

