#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXQ 80		// maximum size of a question
#define MAXA 7		// maximum size of an answer

/** Structure: reply
 * ----------------------
 *  Structure to store a question and corresponding given and 
 *  correct answers
 */
struct reply {
	char question[MAXQ];	// stores the question
	char answer[MAXA];		// stores the correct answer
	char reply[MAXA];		// stores the answer given by user
};

typedef struct reply wrongReply;

/** Function: displayMistakes
 * ----------------------
 *  Displays the questions anwered incorrectly
 * 
 * mistakes: Array of mistakes
 * numberOfMistakes: Size of mistakes
 */
void displayMistakes(wrongReply mistakes[], int numberOfMistakes) {
	int i;
	for(i = 0; i < numberOfMistakes; i++) {
		printf("\nQuestion : %s\n", mistakes[i].question);
		printf("Your Answer : %s\n", mistakes[i].reply);
		printf("Correct Answer : %s\n", mistakes[i].answer);
	}
}

/** Function: playQuiz
 * ----------------------
 *  Conducts the Computer Based Quiz
 * 
 * fileName: The name of the file containing the questions and answers
 * 
 * returs: The final score
 */
int playQuiz(char fileName[]) {
	FILE *fp = fopen(fileName, "r");	// open file in read mode
	if(fp == NULL) {	// ensure file is properly accessed
		printf("File could not be accessed!");
		exit(0);
	}
	int n = 0;	// number of questions in the quiz
	int score = 0;	// stores the score on correct answer
	int wrong = 0;	// stores the number of wring answers given
	fscanf(fp, "%d\n", &n);
	wrongReply mistakes[n]; // at most all answers can be wrong
	
	while (!feof(fp)) {
		if(!n) {	// file should not contain more questions than n
			printf("Extra questions present!");
			exit(0);
		}
		// fgets includes the \n character at the end so size of the 
		// string receiving the answer has to be 2 more than the size
		// of the largest answer (False) to hold the \n and \0 at the end
		char question[MAXQ] = "", answer[MAXA] = "", reply[MAXA] = "";	
		fgets(question, MAXQ, fp);		// read the question
		// remove \n from question
		if(question[strlen(question) - 1] == '\n')
			question[strlen(question) - 1] = '\0';
		fgets(answer, MAXA, fp);		// read the correct answer
		// remove \n from answer
		if(answer[strlen(answer) - 1] == '\n')
			answer[strlen(answer) - 1] = '\0';
		printf("Question : %s\nYour Answer (True/False): ", question);
		scanf("%s", reply);
		if(!strcmpi(reply, answer))		// check correctness
			score++;
		else {		// save incorrect answers
			strcpy(mistakes[wrong].question, question);
			strcpy(mistakes[wrong].answer, answer);
			strcpy(mistakes[wrong].reply, reply);
			wrong++;
		}
		n--;
	}
	if(n) {	// file should not contain less questions than n
		printf("Less questions present!");
		exit(0);
	}
	if(wrong) {
		printf("\nIncorrect Replies - \n");
		displayMistakes(mistakes, wrong);	// display incorrect answers
	}
	fclose(fp);
	return score;	// return final score
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("Wrong number of arguments!");
		return 1;
	}
	printf("\nYour Score is = %d", playQuiz(argv[1]));
}
