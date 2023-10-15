
## Linux
```
gcc -c libtouch_nix.c -o libtouch_nix.o
ar -r libtouch.a libtouch_nix.o
gcc touch.c -L. -ltouch -o touch
```

## win

```
gcc -c libtouch_w32.c -o libtouch_w32.o
ar -r libtouch.a libtouch_nix.o
gcc touch.c -L. -ltouch -o touch.exe
```