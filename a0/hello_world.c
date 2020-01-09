/*
 * CS 5007, Assignment 0
 * Summer 2019
 * Northeastern University, Seattle
 *
 * Author: Adrienne Slaughter
 * 
 * May 9, 2019
 *
 */
#include "hello_world.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
	long a = -889262067;
	long b = 330223330;

    SayHello(a, b); 
    return 0;
}

void SayHello(long foo, long bar){
	printf("The magic word is: %X\n", foo + bar);
}
