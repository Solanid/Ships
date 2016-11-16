/**
* @author: Rastislav Ruscak
* @date: 13.11.2016 
* @description: Main file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void printArray(int array[8][8]);
int checkCode(int );
void checkCodeUsingPtr(int *);

int main() {
	int field[8][8];
	int code1, code2, code3, code4, i, j;
	int position;
	int positionCol, positionRow;
	printf("Welcome, author: Rastislav Ruscak");
	printf("\nEnter code1: ");
	scanf("%d", &code1);
	printf("Enter code2: ");
	scanf("%d", &code2);
	printf("Enter code3: ");
	scanf("%d", &code3);
	printf("Enter code4: ");
	scanf("%d", &code4);
	
	code1=checkCode(code1);
	code2=checkCode(code2);
	checkCodeUsingPtr(&code3);
	checkCodeUsingPtr(&code4);
	printf("%d  %d  %d  %d", code1, code2, code3, code4);
	
	int bit;
	for(j=7; j>=0;j--){
		bit = code1 & 1;
		field[1][j] = bit *(-1);
		bit = code2 & 1;
		field[3][j] = bit *(-1);
		bit = code3 & 1;
		field[5][j] = bit *(-1);
		bit = code4 & 1;
		field[7][j] = bit *(-1);
		code1>>=1;
		code2>>=1;
		code3>>=1;
		code4>>=1;
	}
	for(j=7; j>=0;j--){
		bit = code1 & 1;
		field[0][j] = bit *(-1);
		bit = code2 & 1;
		field[2][j] = bit *(-1);
		bit = code3 & 1;
		field[4][j] = bit *(-1);
		bit = code4 & 1;
		field[6][j] = bit *(-1);
		code1>>=1;
		code2>>=1;
		code3>>=1;
		code4>>=1;
	}
	printArray(field);
	printf("\n Enter position of the ship <0;63>: ");
	scanf("%d", &position);
	if(position < 0 || position > 63){
		printf("Wrong input.");
		return 1;
	}
	positionRow=position/8;
	positionCol=position%8;
	if(field[positionRow][positionCol]==-1){
		printf("\nError. Wrong position, there is an Island");
		return 2;
	}
	field[positionRow][positionCol]=-2;
	
	if(positionCol>0 && field[positionRow][positionCol-1]==0)
		field[positionRow][positionCol-1]=1;
	if(positionCol<7 && field[positionRow][positionCol+1]==0)
		field[positionRow][positionCol+1]=1;
	if(positionCol>0 && field[positionRow-1][positionCol]==0)
		field[positionRow-1][positionCol]=1;
	if(positionCol<7 && field[positionRow+1][positionCol]==0)
		field[positionRow+1][positionCol]=1;
				
	int count=1;
//	bool change=true;
	while(count<39){
//		change=false;
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(field[i][j]==count){
				//	change=true;
					if(j>0 && field[i][j-1]==0)
						field[i][j-1]=count+1;
					if(j<7 && field[i][j+1]==0)
						field[i][j+1]=count+1;
					if(i>0 && field[i-1][j]==0)
						field[i-1][j]=count+1;
					if(i<7 && field[i+1][j]==0)
						field[i+1][j]=count+1;
				}
			}
		}
		count++;
	}
	/*
	field[positionRow][positionCol]=99;
	int poc=99;
	int distance=1;
	while(distance!=5){
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if((field[i][j+1]==poc || field[i+1][j]==poc || field[i-1][j]==poc || field[i][j-1]==poc)&&field[i][j]==-2 && field[i][j]!=-1 && field[i][j]!=poc-1){
					field[i][j]=distance;
				}
			}
		}
		if(poc==99)
			poc=1;
		poc++;
		distance++;
	}*/
	printArray(field);
}

void printArray(int array[8][8]){
	int i, j;
	printf("\n");
	for(i=0; i<8;i++){
		if(i==0)
			printf(" __________________________\n");
		for(j=0; j<8; j++){
			if(j==0)
				printf("| ");
				
			if(array[i][j]==0)
				printf("   ");
			else if(array[i][j]==-1)
				printf("  #");
			else if(array[i][j]==-2)
				printf("  O");
			else
				printf(" %2d", array[i][j]);
			if(j==7)
				printf(" |");
		}
		printf("\n");
		if(i==7)
			printf("|__________________________|");
	}
}

int checkCode(int num){
	if(num >= 0 && num <= pow(2,16)-1) // <0;65535>
		return num;
	else
		return 0;
}

void checkCodeUsingPtr(int *pnum){
	if(*pnum < 0 || *pnum > (pow(2,16)-1)) // <0;65535>
		*pnum=0;
}
