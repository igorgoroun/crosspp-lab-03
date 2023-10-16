
## Linux
```
gcc -c libtouch_nix.c -o libtouch_nix.o
ar -r libtouch.a libtouch_nix.o
gcc -DLANG_UA -c message.c -o libmessage_ua.o
gcc -c message.c -o libmessage_en.o
gcc -shared -o libmessage_ua.so libmessage_ua.o
gcc -shared -o libmessage_en.so libmessage_en.o
gcc touch.c -L. -ltouch -o touch
```

## RUN

```
export LANGUAGE=ua && ./touch
```

## win

```
gcc -c libtouch_w32.c -o libtouch_w32.o
ar -r libtouch.a libtouch_nix.o
gcc touch.c -L. -ltouch -o touch.exe
```