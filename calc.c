#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "calcfunc.h"
#include <math.h>

int main (int argc, char** argv) 
{
	if (argc < 5) 
	{
		printf("ERROR: Not enough input arguements!\n");
		return 0;
	}
	
	// gets the operator and checks if the operator was valid
	// in this implementation the only valid operators are - + *
	
	char * operator = (char*)malloc(strlen(argv[1]) + 1);
	strcpy(operator, argv[1]);
	operator[strlen(argv[1])] = '\0';

	if (operator[1] != '\0' ||( operator[0] != '+' 
		&& operator [0] != '-' && operator[0] != '*')) 
	{
		printf("ERROR: Invalid operator!\n");
		return 0;
	}

	// get the first arg and copy it
	char * input1 = (char*)malloc(strlen(argv[2])+1);
	strcpy(input1, argv[2]);
	// and second
	char * input2 = (char*)malloc(strlen(argv[3])+1);
	strcpy(input2, argv[3]);
	// finally the base that the result will be output in
	char * outBase = (char*)malloc(strlen(argv[4])+1);
	strcpy(outBase, argv[4]);
	
	// flags will deterimine if the inputs are negative 0 for pos 1 for neg
	int flag1 = 0, flag2 = 0;
	
	char * ref1 = input1;	//"reference to full input"
	char * ref2 = input2;	//cleaves part off depending if '-'
	// check if either input is negative to apply the right operation accordingly
	
	if (input1[0] == '-') 
	{
		flag1 = 1;
		input1++;
	}
	if (input2[0] == '-')
	{
		flag2 = 1;
		input2++;
	} 

	// error checking to see if the first arguement is not one of the specified 
	// only d x o b are valid

	if(strlen(outBase) > 1 || 
	(outBase[0] != 'd' && outBase[0] != 'b' && outBase[0] != 'o' && outBase[0] != 'x')) 
	{
		printf("ERROR: Invalid output base!\nThe only valid output bases are: d o b x\n%s was the output base that was detected\n", outBase);

		return 0;
	}

	int check1 = checkValidInput(input1);
	int check2 = checkValidInput(input2);
	
	if (!(check1 == 1 && check2 == 1)) 
	{
		switch(check1)
		{
			case 0:
				printf("ERROR: Input 1: Invalid base!\n");
				break;
			case 1:
				break;
			case 2:
				printf("ERROR: Input 1: Digits mismatched with base!\n");
				break;
				
		}
		switch(check2)
		{
			case 0:
				printf("ERROR: Input 2: Invalid base!\n");
				break;
			case 1:
				break;
			case 2:
				printf("ERROR: Input 2: Digits mismatched with base!\n");
		}
		return 0;
	}

	BinNum * num1;

	switch(input1[0])
	{
		case 'x':
			num1 = HexToBin(input1);
			break;
		case 'o':
			num1 = OctToBin(input1);
			break;
		case 'd':
			{
			int temp = 0;
			int i;
			int count = 0;
			for (i = strlen(input1) - 1; i >= 1; i = i - 1)
			{
				char c = input1[i];
				temp += (c - '0') * (int)pow(10, count);
	  			count = count + 1;
			}
			num1 = DecToBin(temp);
			break;
			}
		case 'b':
			num1 = BinToBin(input1);
			break;
	}

	BinNum * num2;

	switch(input2[0])
	{
		case 'x':
			num2 = HexToBin(input2);
			break;
		case 'o':
			num2 = OctToBin(input2);
			break;
		case 'd':
			{
			int temp = 0;
			int i;
			int count = 0;
			for (i = strlen(input2) - 1; i >= 1; i = i - 1)
			{
				char c = input2[i];
				temp += (c - '0') * (int)pow(10, count);
	  			count = count + 1;
			}
			num2 = DecToBin(temp);
			break;
			}
		case 'b':
			num2 = BinToBin(input2);
			break;
	}
	int convert1 = BinToInt(num1);
	int convert2 = BinToInt(num2);
	if(flag1 == 1)
	{
		convert1 = -1*convert1;
	}
	if(flag2 == 1)
	{
		convert2 = -1*convert2;	
	}
	int final;
	switch(operator[0])
	{
		case '+':
			final = convert1 + convert2;
			break;
		case '-':
			final = convert1 - convert2;
			break;
		case '*':
			final = convert1 * convert2;
			break;
	}
	
	char * output;
	switch(outBase[0])
	{
		case 'd':
		{
			output = BinToDecStr(final);
			printf("%s\n", output);
			break;
		}
		case 'b':
		{
			int tempi = 0;
			BinNum * temp;
			if(final < 0)
			{
				tempi = final *-1;
				temp = DecToBin(tempi);
			}
			else
			{
				temp = DecToBin(final);
			}
			output = BinToBinStr(temp);
			if(tempi != 0)
			{
				output = append(output, '-');
			}
			printf("%s \n", output);
			break;
		}
		case 'x':
			output = BinToHexStr(final);
			printf("%s\n", output);
		break;
		case 'o':
			output = BinToOctStr(final);
			printf("%s\n", output);
		break;	
	}
	free(ref1);
	free(ref2);
	return 0;
}
