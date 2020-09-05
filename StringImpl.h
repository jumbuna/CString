#include "String.h"

void newString(struct String *str) {
	str->capacity = 500;
	str->ptr = (char *) malloc(str->capacity);
	str->len = 0;
	str->offSet = 0;
	*(str->ptr) = '\0';
}

void destroyString(struct String *str) {
	/*free array memory*/
	free(str->ptr-str->offSet);
	str->len = 0;
}

int length(struct String *str) {
	return str->len;
}

/*
	dest->has to be set before calling this function
*/
void subStr(struct String *src, struct String *dest, int start, int len) {
	if(start < src->len) {
		/*prevent substr from exceeding the past the terminating character*/
		int min = (start + len) > src->len ? src->len - start : len;
		memcpy(dest->ptr, src->ptr+start, min);
		/*terminating character*/
		*(dest->ptr+min) = '\0';
		dest->len = min;
	}
}

void append(struct String *str, char *other) {
	/*length to be appended*/
	long oLen = strlen(other);
	/*if addition size will cause an overflow then create space to accomodate*/
	if(str->len+str->offSet+ oLen >= str->capacity) {
		/*shift array to the left if unused space is available*/
		if(str->offSet > str->capacity * 0.75 && str->len+oLen < str->capacity) {
			memcpy(str->ptr-str->offSet, str->ptr, str->len+1);
			str->ptr -= str->offSet;
			str->offSet = 0;
		} else {
			/*extend array to exactly fit/bigger size*/
			str->capacity += oLen;
			char *temp = realloc(str->ptr-str->offSet, str->capacity);
			memcpy(temp, str->ptr, str->len);
			str->ptr = temp;
			str->offSet = 0;
		}
	}
	/*include the terminating character also*/
	memcpy(str->ptr+str->len, other, oLen+1);
	/*update length*/
	str->len += oLen;
}

void strip(struct String *str, char *trail) {
	int tLen = strlen(trail);
	int i = 0;
	char *eStart = str->ptr+str->len-tLen;
	for(; i < tLen; i++) {
		/*trail will be removed only when it matched on both ends*/
		if(*(trail+i) != *(str->ptr+i) || *(eStart+i) != *(trail+i)) return;
	}
	str->ptr += tLen;
	str->offSet += tLen;
	/*x2*/
	str->len -= tLen*2;
	/*new termination point*/
	*(str->ptr+str->len) = '\0';
}

void trimChar(struct String *str, char lc) {
	//front
	while(*(str->ptr) == lc && str->len > 0) {
		++(str->offSet);
		++(str->ptr);
		--(str->len);
	}
	//back
	while(*(str->ptr+str->len-1) == lc && str->len > 0) {
		--(str->len);
		*(str->ptr+str->len) = '\0';
	}
}

void clear(struct String *str) {
	str->ptr -= str->offSet;
	str->offSet = 0;
	str->len = 0;
	*(str->ptr) = '\0';
}

void toLowerCase(struct String *str) {
	for(int i = 0; i < str->len; i++) {
		if(*(str->ptr+i) >= 65 && *(str->ptr+i) <= 90) {
			*(str->ptr+i) += 32;
		}
	}
}

void toUpperCase(struct String *str) {
	for(int i = 0; i < str->len; i++) {
		if(*(str->ptr+i) >= 97 && *(str->ptr+i) <= 122) {
			*(str->ptr+i) -= 32;
		}
	}
}

void capitalize(struct String *str) {
	for(int i = 0; i < str->len-1; i++) {
		if(*(str->ptr+i) == ' ') {
			if(*(str->ptr+i+1) >= 97 && *(str->ptr+i+1) <= 122) {
				*(str->ptr+i+1) -= 32;
			}
		}
	}
}

int contains(struct String *str, char *subStr) {
	return kmpSearch(str->ptr, str->len, subStr, strlen(subStr));
}