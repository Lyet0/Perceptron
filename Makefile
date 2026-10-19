main: dataset.o perceptron.o main.o
	gcc -g -Wall -Wextra -o main main.o perceptron.o dataset.o
perceptron.o: src/perceptron.c include/perceptron.h
	gcc -g -c -Wall -Wextra -o perceptron.o src/perceptron.c
dataset.o: include/dataset.h src/dataset.c
	gcc -g -c -Wall -Wextra -o dataset.o src/dataset.c
main.o: src/main.c 
	gcc -g -c -Wall -Wextra -o main.o src/main.c 
clean :
	rm main
	rm *.o
