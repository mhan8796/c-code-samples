#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char **word;
int num = 0;
void Read();
void Creat();
void Decode();
void Exit();


int main() //The first part will be to write a menu driven program that prompts the user for the following actions
{	
	int a=0, i = 0;
	int flag = 0;                               //you can ignore the assignment part
	word = (char**)malloc(sizeof(char*)* 5001); //you will use no more than the first 5,000 words in the text
	if (word == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}
	for (i = 0; i < 5001; i++)
	{
		word[i] = (char*)malloc(sizeof(char)* 16); //no more than the first 15 characters in a word
		if (word[i] == NULL)
		{
			printf("Not enough memory\n");
			exit(0);
		}
	}                                              //assignment end
	i = 0;
	while (flag == 0)
	{
		printf("1) Read in the name of a text file to use as a cipher key\n");
		printf("2) Create a cipher using the input text file\n");
		printf("3) Decode an existing cipher\n");
		printf("4) Exit the program\n");
		printf("Please input the number:");
		scanf("%d", &a);
		if (a == 1)
		{
			Read();
			flag = 0;
			i = 1;
		}
		else if (a == 2 && i == 1)
		{
			Creat();
			flag = 0;
		}
		else if (a == 3 && i == 1)
		{
			Decode();
			flag = 0;
		}
		else if (a == 4)
		{
			for (i = 0; i < 5001; i++)
				free(word[i]);
			free(word);
			Exit();
			flag = 1;
		}
		else continue;
	}
	return 0;
}

void Exit() // create a stub function that will be completed in the remaining steps
{
	exit(1);
}

void Read() // create a stub function that will be completed in the remaining steps
{
	FILE *opfile;
	char *filename, *cha, *line;
	int i = 0, j = 0, k = 0;
	line = (char*)malloc(1000 * sizeof(char)); //you can ignore the assignment part
	if (line == NULL)
	{
		printf("Not enough meomry\n");
		exit(0);
	}
	filename = (char*)malloc(50 * sizeof(char));
	if (filename == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}                                              //assignment end
f2:	printf("Please enter the name of the file:\n"); //Prompt the user for the name of a text file
	scanf("%s", filename);
	opfile = fopen(filename, "r"); //need change
	if (opfile == NULL) //check
	{
		printf("Error opening file, Please enter again\n"); 
		goto f2;
	}
	while (fgets(line, 999, opfile) != NULL) //read this text file line by line
	{
		cha = strtok(line, " -',.\n:");
		while (cha != NULL)
		{
			num++;
			strcpy(word[j],cha); //place each word, in order, in an array of char strings
			for (k = 0; k<15; k++)
				word[j][k] = tolower(word[j][k]); //convert the letters of each word to lower case.
			j++; //keep a running count of the number of words in the text file
			cha = strtok(NULL, " -',.\n:");
		}
	}
	fclose(opfile);
	free(filename);
	free(line);
	return;
}

void Creat() // create a stub function that will be completed in the remaining steps
{
	int j = 0, row = 0, column = 0, k = 0,l=0, i=0;
	char *line, *cha2, *name, *token, dust, rowc[150], columnc[150];
	FILE *clfile;
	name = (char*)malloc(50 * sizeof(char)); //you can ignore the assignment part
	if (name == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}
	cha2 = (char*)calloc(5000 , sizeof(char));
	if (cha2 == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}
	line = (char*)malloc(1000 * sizeof(char));
	if (line == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}                                              //assignment end
	printf("Please enter the secret message: \n"); // prompt the user to enter a secret message
	dust=getchar();
	fgets(line,1000,stdin);
		while (line[j] != '\0')
		{
			line[j] = tolower(line[j]); //character by character, converting them to lower case 
			j++;
		}
		token = strtok(line, " "); //find corresponding characters in the words found in the key text word array
		while (token != NULL) //find corresponding characters in the words found in the key text word array
		{

			for (k = 0; k < (int)strlen(token); k++) //find corresponding characters in the words found in the key text word array
			{
				if (token[k] >= 'A' && token[k] <= 'Z' || token[k] >= 'a' && token[k] <= 'z')
				for (row = 0; row < num; row++)
				for (column = 0; column < (int)strlen(word[row]); column++)
				{
					if (token[k] == word[row][column])
					{
						sprintf(rowc, "%d", row);
						sprintf(columnc, "%d", column);
						strcat(cha2, rowc); //you will write the index of the word and the index of the character to a character string
						strcat(cha2, ","); //you will write the index of the word and the index of the character to a character string
						strcat(cha2, columnc); //you will write the index of the word and the index of the character to a character string
						goto f1;
					}
				}
				else strcat(cha2, "#");
f1:				strcat(cha2, ",");
			}
			cha2[strlen(cha2) - 1] = ' '; //Spaces are to be placed into the text as found in the message and will be used to delimit the separate words in the secret message
			token = strtok(NULL, " ");
		}
	printf("Please enter the output file name:\n"); // prompt the user for the name of a file to save the encoded message to, and save it to that file
	scanf("%s", name); // prompt the user for the name of a file to save the encoded message to, and save it to that file
	clfile = fopen(name, "w"); // prompt the user for the name of a file to save the encoded message to, and save it to that file
	if (clfile == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	fputs(cha2, clfile);
	fclose(clfile);
	free(line);
	free(cha2);
	free(name);
	return;
}

void Decode() // create a stub function that will be completed in the remaining steps
{
	FILE *fp;
	char *name, *cha, *msg, **number;
	int i = 0, j = 0, k = 0, l = 0, m = 0, n=0;
	number = (char**)malloc(sizeof(char*)* 10001);        //you can ignore the assignment part
	if (number == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}
	for (i = 0; i < 10001; i++)
	{
		number[i] = (char*)malloc(sizeof(char)* 100);
		if (number[i] == NULL)
		{
			printf("Not enough memory\n");
			exit(0);
		}
	}
	msg = (char*)malloc(1001 * sizeof(char));
	if (msg == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}
	name = (char*)malloc(50 * sizeof(char));
	if (name == NULL)
	{
		printf("Not enough memory\n");
		exit(0);
	}							//assignment end
f3:	printf("Please enter the name of encoded file:\n"); 	//prompt the user for the name of a file containing an encoded text
	scanf("%s", name);
	fp = fopen(name, "r"); 
	if (fp == NULL) //check
	{
		printf("Error opening file, Please enter again\n");
		goto f3;
	}
	i = 0;
	while (fgets(msg, 1000, fp) != NULL) //will read the file
	{
		cha = strtok(msg, " ");
		while (cha != NULL)
		{
			strcpy(number[i],cha);
			i++;
			cha = strtok(NULL, " ");
		}
	}
	for (j = 0; j < i; j++) //decode the the text
	{
		cha = strtok(number[j], ",");
		while (cha != NULL)
		{
			for (n = 0; n < (int)strlen(cha);n++) //judge if it is a number
			if (cha[n]<'0'||cha[n]>'9')
			{	
				printf("%s", cha);
				goto f;
			}
			m++;
			if (m % 2!=0)
			l = atoi(cha);
			if (m % 2 == 0)
			{
				k = atoi(cha);
				printf("%c", word[l][k]); //Once the text is decoded print the message to standard output.
			}
f:			cha = strtok(NULL, ",");
		}
		printf("%c", ' ');
	}
	printf("\n");
	for (i = 0; i < 10001; i++)
		free(number[i]);              
	fclose(fp);
	free(number);
	free(msg);
	free(name);
	return;
}
