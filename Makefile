perceptron: dataset.o perceptron.o main.o
	gcc -g -Wall -Wextra -o perceptron main.o perceptron.o dataset.o -lm
test: dataset.o perceptron.o test.o
	gcc -g -Wall -Wextra -o test test.o perceptron.o dataset.o -lm
perceptron.o: src/perceptron.c include/perceptron.h
	gcc -g -c -Wall -Wextra -o perceptron.o src/perceptron.c 
dataset.o: include/dataset.h src/dataset.c
	gcc -g -c -Wall -Wextra -o dataset.o src/dataset.c
main.o: src/main.c 
	gcc -g -c -Wall -Wextra -o main.o src/main.c 
test.o: src/test.c include/dataset.h include/perceptron.h
	gcc -g -c -Wall -Wextra -o test.o src/test.c
clean : 
	rm -f *.o perceptron test
valgrind : 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
