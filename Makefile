FLAGS = -Wall -Werror -pedantic

bin/Lab3 : obj/Lab3.o lib/liblab2.a lib/libplugin.so
	mkdir -p bin
	gcc $(FLAGS) -ldl obj/Lab3.o -L./lib -lcjson -llab2 -lplugin -Wl,-rpath,'$(shell pwd)/lib' -o bin/Lab3

obj/Lab2.o : inc/Lab2.h src/Lab2.c
	gcc $(FLAGS) -c src/Lab2.c -o obj/Lab2.o

obj/Lab3.o : inc/Lab3.h src/Lab3.c
	mkdir -p obj
	gcc $(FLAGS) -c src/Lab3.c -o obj/Lab3.o

obj/Plugin.o : inc/Plugin.h src/Plugin.c
	gcc $(FLAGS) -c src/Plugin.c -o obj/Plugin.o

lib/libplugin.so : obj/Plugin.o
	gcc $(FLAGS) obj/Plugin.o -shared -o lib/libplugin.so

lib/liblab2.a : obj/Lab2.o
	ar rs lib/liblab2.a obj/Lab2.o

.PHONY: clean
clean: 
	rm -f -r bin  
	rm -f -r obj
	rm -f -r lib/libplugin.so
	rm -f -r lib/liblab2.a