#pragma once

typedef int* KmpTable;

void constructKmpTable(KmpTable table, char *subStr, int sLen) {
	table[0] = 0;
	int i = 0;
	for(int j = 1; j < sLen; j++) {
		if(subStr[j] == subStr[i]) {
			table[j] = i++;
		} else {
			table[j] = 0;
			i = i > 0 ? i-1 : 0;
			while(i > 0) {
				if(subStr[i] == subStr[j]) {
					table[j] = table[i++];
					break;
				}
				i = table[i];
			}
		}
	}
}

/*allow for reusability of a Kmptable*/
int KmpSearchWithTable(char *str, int sLen, char *subStr, int ssLen, KmpTable table) {
	int p = 0;
	for(int i = 0; i < sLen; i++) {
		if(str[i] == subStr[p]) {
			++p;
			if(p == ssLen) {
				return (i-p)+1;
			}
		} else {
			p = table[p];
			/*get rid of unnecessary comparisons*/
			if(ssLen-p > sLen-i) {
				break;
			}
		}
	}
	return -1;
}

int kmpSearch(char *str, int sLen, char *subStr, int ssLen) {
	int array[ssLen];
	constructKmpTable(array, subStr, ssLen);
	return KmpSearchWithTable(str, sLen, subStr, ssLen, array);
}
