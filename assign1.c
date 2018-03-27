//Regan Fung, z5113254
//Yahtzee Game
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

void getDiceValue(char *inputValue);
void getAction(char *inputValue, int *score, int *dices);
void rerollSomeDices(char *inputValue);
void displayScore(int *score, int *dices);


int main (int argc, char * argv []) {
	char inputValue[100];
	int score = 0, dices[6] = {0,0,0,0,0,0};
   getDiceValue(inputValue);
	getAction(inputValue,&score,dices);
	displayScore(&score, dices);
   return EXIT_SUCCESS;
}


//To get all the dices values from the user

void getDiceValue(char *inputValue) {
	int i; 
	printf("Please enter dice values:\n");
	printf("> ");  
   fgets(inputValue, 100, stdin);
   printf("\n");
	for (i = 0; i < strlen(inputValue) - 1; i++){
	    //only accept digits and spaces
	   if (inputValue[i] != ' ' && !isdigit(inputValue[i])){
			printf("Incorrect Input Format.\n");
			exit(0); //Dice value must be less than 6 and greater than 0 
		} else if ((inputValue[i] - '0' < 1 || inputValue[i] - '0' > 6) &&   
		inputValue[i] != ' '){
			printf("Value Out of Range.\n");
			exit(0);
		}
	} 
	//Total length of the input must include 5 digits
	
	if (strlen(inputValue) != 10){
		printf("Incorrect Number of Values.\n");
		exit(0); 
	} 
    printf("Your dice values are: %s\n", inputValue);
    
}

//Allow user to perform different actions

void getAction(char *inputValue, int *score, int *dices) {
	char input[100];
	int i;
	
	printf("Please choose:\n");  
	printf(" 1 -> Reroll some dice\n");  
	printf(" 2 -> Reroll all dice\n");  
	printf(" 3 -> Keep dice\n"); 
   printf("> ");
	fgets(input, 10, stdin);
	
	if (input[0] - '0' < 1 || input[0]- '0' > 3 || strlen(input) > 2) {
		printf("Invalid Choice.\n");
		exit(0);
	}
	if (input[0] - '0' == 1) { 
	   printf("\n");
      rerollSomeDices(inputValue);
      
            
	} 
	if (input[0] - '0' == 2) {
	   printf("\n");
		getDiceValue(inputValue);
		getAction(inputValue, score, dices);
		
		if (*inputValue == '1') {
		rerollSomeDices(inputValue);
		} else if (*inputValue == '2') {
		   getDiceValue(inputValue);
		} else if (*inputValue == '3') {
		   displayScore(score,dices);
		}
		
   }
	for (i = 0; i < strlen(inputValue)-1; i++) {
	    if (inputValue[i] != ' ') {
			dices[inputValue[i]-'0' - 1] += 1;
			*score += inputValue[i]-'0';
		}
	} 
}

//Reroll some of the dices

void rerollSomeDices(char *inputValue) {
	
	char input[100];
	int i,j, numberOfDiceToReroll = 0,diceToReroll[10]; 
	bool exist = false;
	printf("Please enter dice to reroll (1 - 5):\n");  
	printf("> ");
   fgets(input, 100, stdin);
	for (i = 0; i < strlen(input) - 1; i++) {
	   if (input[i] != ' ' && !isdigit(input[i])) {
			printf("Incorrect Input Format.\n");
			exit(0);
		} else if ((input[i] - '0' < 1 || input[i] - '0' > 5) && input[i] 
		!= ' ') {
			printf("Dice Number Out of Range.\n");
			exit(0);
		} else if (input[i] != ' ') {
		    for (j = 0; j < 10; j++) {
				if (diceToReroll[j] == input[i] - '0') {
					exist = true;
					break;
				}
			}
			if (!exist) {
				diceToReroll[numberOfDiceToReroll] = input[i] - '0';
				numberOfDiceToReroll += 1;
			}
			exist = false;
		}
		
	} 
	if (strlen(input) < 2 || strlen(input) > 10) {
		printf("Incorrect Number of Values.\n");
		exit(0);
	}
	if (numberOfDiceToReroll == '1' || numberOfDiceToReroll == 1) {
	   printf("Please enter one die value:\n");
	} else { 
	   printf("Please enter %d values:\n",numberOfDiceToReroll); 
	}
	printf("> "); 
   fgets(input, 100, stdin);
   printf("\n");
	for (i = 0; i < strlen(input)-1; i++) {
	    if (input[i] != ' ' && !isdigit(input[i])) {
			printf("Incorrect Input Format.\n");
			exit(0);
		} else if ((input[i] - '0' < 1 || input[i] - '0' > 6) && input[i] 
		!= ' ') {
			printf("Value Out of Range.\n");
			exit(0);
		} else if (input[i] != ' ')
		   inputValue[diceToReroll[i/2]*2-2] = input[i];
	} 
	//The value limit is depends on the number of dices
	if (strlen(input) < 2 || strlen(input) > numberOfDiceToReroll*2) {
		printf("Incorrect Number of Values.\n");
		exit(0);
	}
	
   printf("Your dice values are: %s\n", inputValue);
   
}


//Display all the possible scores to the user

void displayScore(int *score, int *dices) {
	int i, option = 1, scores[10];
	bool three = false,two= false, yahtzee = false;
	printf("Your score options are:\n");
	for (i = 0; i < 6; i++) {
		if (dices[i] > 2) {
			printf(" %d -> Three of a Kind (%d points)\n" , option,*score);
			scores[option - 1] = *score;
			option += 1;
			three = true;
		}
		else if (dices[i] > 1) {
			two = true;
			}
		if (dices[i] > 3) {
			printf(" %d -> Four of a Kind (%d points)\n" , option,*score);
			scores[option - 1] = *score;
			option += 1;
		}
		if (dices[i] > 4) {
			yahtzee = true;
			}
	}
	if (three && two) {
		printf(" %d -> Full House (25 points)\n" , option);
		scores[option - 1] = 25;
		option += 1;
	}
	if ((dices[0]>= 1 && dices[1]>= 1 && dices[2]>= 1 && dices[3]>= 1 )||
	    (dices[1]>= 1 && dices[2]>= 1 && dices[3]>= 1 && dices[4]>= 1 )|| 
		 (dices[2]>= 1 && dices[3]>= 1 && dices[4]>= 1 && dices[5]>= 1 )) {
		printf(" %d -> Small Straight(30 points)\n" , option);
		scores[option-1] = 30;
		option += 1;
	}
	if ((dices[0] == 1 && dices[1] == 1 && dices[2] == 1 && dices[3] == 1 && 
	dices[4] == 1)||
      (dices[1] == 1 && dices[2] == 1 && dices[3] == 1 && dices[4] == 1 && 
		dices[5] == 1)) {
		printf(" %d -> Straight(40 points)\n" , option);
		scores[option-1] = 40;
		option += 1;
	}
	if (yahtzee) {
		printf(" %d -> Yahtzee(50 points)\n" , option);
		scores[option-1] = 50;
		option += 1;
	}
	printf(" %d -> Chance (%d points)\n" , option, *score);
	scores[option-1] = *score;
	printf("> ");
	scanf("%d",&option);
	if (option > 4 || option < 1) {
	   printf("Invalid Choice.\n");
	} else {
	printf("Your score is: %d points\n" , scores[option-1]);
   }
}
