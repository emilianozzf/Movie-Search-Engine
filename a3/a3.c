#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "a3.h"


// YOUR CODE GOES HERE

// Print the string <first> <middle> <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle", then print:
//  "Ben Ivan Bitdiddle".
//
//  If the middle name is NULL, then print:
//  "Ben Bitdiddle"
//
//  name: a pointer to a Name
void Big(Name *name) {
    if (name->middle == NULL) {
    	printf("%s %s", name->first, name->last);
    } else {
        printf("%s %s %s", name->first, name->middle, name->last);
    }
}

// Print the string <last>, <first>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle", then print:
//  "Bitdiddle, Ben".
//
// name: a pointer to a Name
void Last(Name *name) {
    printf("%s, %s", name->last, name->first);
}

// Print the string <first> <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle", then print:
//  "Ben Bitdiddle".
//
// name: a pointer to a Name
void Reg(Name *name) {
    printf("%s %s", name->first, name->last);
}

// Print the string <first> <middle-initial>. <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle", then print:
//  "Ben I. Bitdiddle".
//
// If middle name is NULL, print:
// "Ben Bitdiddle"
//
// name: a pointer to a Name
void Mid(Name *name) {
    if (name->middle == NULL) {
        printf("%s %s", name->first, name->last);
    } else {
        printf("%s %c. %s", name->first, name->middle[0], name->last);
    }
}

// Print the first name only.
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle", then print:
//  "Ben".
//
// name: a pointer to a Name
void Small(Name *name){
    printf("%s", name->first);
}

// Given a format char, print the given
// name in the format specified by char.
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
void FormatName(Name *name, char format){
    if (format == 'B') {
        Big(name);
    } else if (format == 'L') {
        Last(name);
    } else if (format == 'R') {
        Reg(name);
    } else if (format == 'M') {
        Mid(name);
    } else {
        Small(name);
    }
}

// Given a name, a format and a destination array,
// put the properly formatted name in the destination
// array, not printing anything on the screen.
//
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
// dest: a pointer to an array that is guaranteed to be big enough
// to hold the formatted name
void FillName(Name *name, char format, char *dest) {
    if (format == 'B') {
        if (name->middle == NULL) {
	    strcpy(dest, name->first);
	    strcat(dest, " ");
	    strcat(dest, name->last);
	} else {
	    strcpy(dest, name->first);
            strcat(dest, " ");
            strcat(dest, name->middle);
	    strcat(dest, " ");
	    strcat(dest, name->last);
	}
    } else if (format == 'L') {
        strcpy(dest, name->last);
	strcat(dest, ", ");
	strcat(dest, name->first);
    } else if (format == 'R') {
        strcpy(dest, name->first);
        strcat(dest, " ");
        strcat(dest, name->last);
    } else if (format == 'M') {
        if (name->middle == NULL) {
            strcpy(dest, name->first);
            strcat(dest, " ");
            strcat(dest, name->last);
        } else {
            strcpy(dest, name->first);
            strcat(dest, " ");

	    char middle_initial[2];
	    middle_initial[0] = name->middle[0];
	    middle_initial[1] = '\0';

            strcat(dest, middle_initial);
            strcat(dest, ". ");

            strcat(dest, name->last);
        }
    } else {
        strcpy(dest, name->first);
    }
}
