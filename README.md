# Allegro Primer
---
On MAC compile with:

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
$ ./AllegroPrimer
```