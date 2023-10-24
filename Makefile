all: clean
	gcc -c libtouch_nix.c -o libtouch_nix.o
	ar -r libtouch.a libtouch_nix.o
	gcc -c libmessage.c -o libmessage.o
	ar -r libmessage.a libmessage.o
	gcc -DLANG_UA -c liblang.c -o liblang_ua.o -Wno-macro-redefined
	gcc -c liblang.c -o liblang_en.o -Wno-macro-redefined
	gcc -shared -o liblang_ua.so liblang_ua.o
	gcc -shared -o liblang_en.so liblang_en.o
	gcc touch.c -L. -ltouch -lmessage  -o touch
	rm -f *.o

clean:
	rm -f touch *.so *.o *.a