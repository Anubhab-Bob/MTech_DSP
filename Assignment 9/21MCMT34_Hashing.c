#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define MAX_ID_SIZE 320     // maximum length of valid email address is 320 characters
#define PRIME_VALUE 2       // considered prime value for hash value computation

/** Function: getStringLength
 * ----------------------
 *  Gives the length of a given string
 * 
 * string: The string whose length to be found
 * 
 * returns: Length of string
 */
int getStringLength(char *string) {
	int i = 0;
	for(i = 0; string[i] != '\0'; i++);
	
	return i;
}

/** Function: power
 * ----------------------
 *  Gives the result of an exponentiation
 * 
 * x: The number to be raised to some power
 * y: The power to which to raise x
 * 
 * returns: x raised to the power of y
 */
int power(int x, int y) {
	int f = 1;
	while(y) {
		f *= x;
		y--;	
	}
	
	return f;
}

/** Function: getHashValue
 * ----------------------
 *  Gives the hash value of a given string
 * 
 * string: The string whose hash value to be found
 * len: The length of the passed string
 * 
 * returns: Length of string
 */
int getHashValue(char *string, int len) {
	int sum = 0;
	for(int i = 0; i < len; i++)
		sum += string[i] * power(PRIME_VALUE, i);
	
	return (sum % MAX_SIZE);
}

/** Function: insertIntoTable
 * ----------------------
 *  Inserts a string into a given hash table
 * 
 * string: The string to insert
 * table: The hash table in which to insert
 * pos: The position where to insert
 */
void insertIntoTable(char *string, char *table[MAX_ID_SIZE], int pos) {
	int i, j = 0;
	// copy characters of the string into hash table entry
	for(i = 0, j = 0; i < getStringLength(string); i++, j++)
		table[pos][j] = string[i];
		
	table[pos][j] = '\0';	// end the string
}

/** Function: compare
 * ----------------------
 *  Compares 2 strings for equality
 * 
 * s1: The first string
 * s2: The second string
 * 
 * returns: 1 if s1 and s2 are same, 0 otherwise
 */
int compare(char *s1, char *s2) {
	int l1 = getStringLength(s1), l2 = getStringLength(s2);
	if(l1 != l2)	// strings of unequal length cannot be same
		return 0;
	for(int i = 0, j = 0; i < l1; i++, j++) {	// comparing character-wise
		if(s1[i] != s2[j])
			return 0;
	}
	
	return 1;	// strings are same
}

/** Function: removeDuplicates
 * ----------------------
 *  Performs hashing with linear probing to remove duplicate entries
 * 
 * inputFile: The file containg the input
 * outputFile: The file containg the output
 */
void removeDuplicates(char *inputFile, char *outputFile) {
	FILE *fInput = fopen(inputFile, "r");
	if(fInput == NULL){
		printf("File cannot be accessed!\n");
		return;
	}
	FILE *fOutput = fopen(outputFile, "w");
	if(fOutput == NULL) {
		fclose(fInput);
		printf("File cannot be accessed!\n");
		return;
	}
	
	char *hashTable[MAX_SIZE];	// declare hash table
	int counter = 0;	// counts the number of unique entries
	char newID[MAX_ID_SIZE];
	for(int i = 0; i < MAX_SIZE; i++) {
		// allocate memory for each entry of hash table and initialise
		hashTable[i] = (char*)malloc(sizeof(char) * MAX_ID_SIZE);
		hashTable[i][0] = '\0';
	}
	while(!feof(fInput)) {	// read input file
		fgets(newID, MAX_ID_SIZE, fInput);
		
		// modify tha value read as fgets() includes last newline character
		if(newID[getStringLength(newID) - 1] == '\n')
			newID[getStringLength(newID) - 1] = '\0';
			
		// generate hash value
		int hValue = getHashValue(newID, getStringLength(newID));
		
		int present = 0;	// flag variable to mark if entry already exists in table
		while(hashTable[hValue][0] != '\0') {	// collision
			
			if(compare(hashTable[hValue], newID)) {	// collided value is same as entry
				present = 1;
				break;
			}
			hValue = (hValue + 1) % MAX_SIZE;	// linear probing
		}
		if(!present) {	// entry not present in hash table ultimately
			insertIntoTable(newID, hashTable, hValue);
			counter++;
		}
	}
	fclose(fInput);	// close input file after reading
	
	for(int i = 0; i < MAX_SIZE; i++) {	// write hash table entries into output file
		if(hashTable[i][0] != '\0') {
			fputs(hashTable[i], fOutput);
			fputs("\n", fOutput);
		}
	}
	printf("%d values found finally\n", counter);	
	fclose(fOutput);	// close output file after writing
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Wrong number of arguments!\n");
		exit(0);
	}
	removeDuplicates(argv[1], argv[2]);
}