#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXWORDS 20
#define WORDLENGTH 16
#define BOARDSIZE 16

int promptUser(char[MAXWORDS][WORDLENGTH]);
void sort(char[MAXWORDS][WORDLENGTH]);
void arrangeBoard(char[MAXWORDS][WORDLENGTH], int, char[BOARDSIZE][BOARDSIZE]);
void drawBoard(char[BOARDSIZE][BOARDSIZE]);
void printClues(char[MAXWORDS][WORDLENGTH]);

//Main controller function
int main(void){
	char board[BOARDSIZE][BOARDSIZE];
	char words[MAXWORDS][WORDLENGTH];
	int numWords = promptUser(words);
//	sort(words);
//	arrangeBoard(words, numWords, board);
//	drawBoard(board);
	return 0;
	}

//Function to get words from user, returns number of entered words
int promptUser(char words[MAXWORDS][WORDLENGTH]){
	printf( "Please enter a list of up to 20 words no longer than 15 letters:\n" );
	int count = 0;
	while( fgets( words[count], WORDLENGTH, stdin )) {
		if( words[count][0] == '.' ) {
			count--;
			return count;
		}
		count++;
	} 
}

//Function to sort words by length (longest in index 0)
void sort(char words[MAXWORDS][WORDLENGTH]){
//TODO
}

//Function to arrange words into crossword
void arrangeBoard(char words[MAXWORDS][WORDLENGTH], int numWords, char board[BOARDSIZE][BOARDSIZE]){
	//Place longest word in middle of board
//	int i,j,placing,placed;
//	int lenPlacing = strlen(words[0]);
//	int start = BOARDSIZE - ((BOARDSIZE + lenPlacing)/2) - 1;
//	for(i=start; i<start+lenPlacing; i++){
//		board[(BOARDSIZE-1)/2][i] = words[0][i-start];
//	}
					
	//For every remaining unplaced words,compare each placed word and for each letter in placing word, compare for match in placed word. If a match is found, check if the word will fit in the board dimensions
//	for(placing=1;placing<numWords; placing++){
//		lenPlacing = strlen(words[placing]);
//		for(placed=0;placed<placing;placed++){	
//			lenPlaced = strlen[words[placed]];
//			for(i=0;i<lenPlacing;i++){
//				for(j=0;j<lenPlaced;j++){
//					if(words[placing][i] == words[placed][j]){
//	//TODO Figure out how to check if will fit in board dimensions, add if so
//					}
//				}				
//			}
//		}
//	}
}
//Function to draw board (both with and without solutions)
void drawBoard(char board[BOARDSIZE][BOARDSIZE]){
//TODO
}

//Function to print anagrams
void printClues(char words[MAXWORDS][WORDLENGTH]){
//TODO
}
