main: fat.o fat.h
	gcc -g -Wall	gcc -g -Wall -Wextra -o fat fat.o
main.o: fat_etu.c 
	gcc -g -c -Wall -Wextra -o fat.o 
liste_etu.o: 
	gcc -g -c -Wall -Wextra -o liste_etu.c preparation/liste_etu.c
clean :
	rm *.o
	rm fat
