/*
	jumbuna
	©2020
*/
#pragma once

#include <string.h>
#include <stdlib.h>
#include "Kmp.h"

struct String {
	/*Pointer to internal char array*/
	char *ptr;
	/*number of characters currently inarray Excluding '\0'*/
	int len;
	/*current maximum size of array*/
	int capacity;
	/*reduce overhead of shifting array after a trim/strip*/
	int offSet;
};

/*Should be called when initializing a string*/
void newString(struct String *);
/*free memory used by string*/
void destroyString(struct String *);
/*return length of the string*/
int length(struct String *);
/*
get substring starting at param(3) with length of patam(4)
if given length extends past end then only charactes upto end are included
*/
void subStr(struct String *, struct String *, int , int);
/*add given string param(2) to end of string*/
void append(struct String *, char *);
/*
check if given substring param(4) is present in string then return index else -1
*/
int contains(struct String*, char *);
/*remove given substring param(2) if it is present in begining and end of string*/
void strip(struct String*, char *);
/*remove both leading and trailing occurrences of the given character param(2)*/
void trimChar(struct String *, char );
/**/
void clear(struct String *);
/*to uppercase*/
void toUpperCase(struct String *);
/*to lowerCase*/
void toLowerCase(struct String *);
/*capitalize first letter of word*/
void capitalize(struct String *);

#include "StringImpl.h"