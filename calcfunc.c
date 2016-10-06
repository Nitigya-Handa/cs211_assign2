#include "calcfunc.h"
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include <math.h>


/**
	@param char * str, char c
	prepends the character c to the string str
	will only work on strings that have been dynamically allocated
*/
char * append(char * str, char c)
{
	int size = strlen(str);
	char * ret = (char *)malloc(size+2);
	ret[size + 2] = '\0';
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		ret[i+1] = str[i];
	}
	ret[0] = c;
	free(str);
	return ret;
}

/**
	@param int num
	converts an integer to its string equivalent
*/
char * BinToDecStr(int num) 
{
	int temp = num;
	if(temp < 0)
	{
		temp = temp *-1;
	}
	char c;
	char * ret =(char *) malloc(sizeof(char));
	ret[0] = '\0';
	if (temp == 0)
	{
		ret = append(ret, '0');
		return ret;
	}
	while (temp != 0)
	{
		int tester = temp % 10;
		temp = temp / 10;
		c = tester + '0';
//		printf("%c\n", c);
		ret = append(ret, c);
	}
	ret = append(ret, 'd');
	if (num < 0)
	{
		ret = append(ret, '-');
	}
	return ret;
}

char * BinToHexStr(int num) 
{
	int temp = num;
	if (temp < 0)
	{
		temp = temp * -1;
	}
	char c;
	char * ret =(char *) malloc(sizeof(char));
	ret[0] = '\0';
	if (temp == 0) 
	{
		ret = append(ret, '0');
		return ret;
	}
	while(temp != 0)
	{
		int tester = temp % 16;
		temp = temp / 16;
		if (tester <= 9)
		{
			c = tester + '0';
		} 
		else
		{
			c = tester + 'A' - 10;
		}
		ret = append(ret, c);
	}
	ret = append(ret, 'x');
	if (num < 0)
	{
		ret = append(ret, '-');
	}
	return ret;
} 

char * BinToOctStr(int num) 
{
	int temp = num;
	if(temp < 0)
	{
		temp = temp *-1;
	}
	char c;
	char * ret =(char *) malloc(sizeof(char));
	ret[0] = '\0';
	if (temp == 0)
	{
		ret = append(ret, '0');
		return ret;
	}
	while (temp != 0)
	{
		int tester = temp % 8;
		temp = temp / 8;
		c = tester + '0';
		ret = append(ret, c);
	}
	ret = append(ret, 'o');
	if (num < 0)
	{
		ret = append(ret, '-');
	}
	return ret;
}

char * BinToBinStr(BinNum * num)
{
	int size = num -> size;
	int i;
	char * ret = (char *)malloc(sizeof(char));
	ret[0] = '\0';
	for(i = 31; i > 31 - size; i--)
	{
		char c = num -> number[i] + '0';
		ret = append(ret, c);
	}
	ret = append(ret, 'b');
	return ret;
}

BinNum * DecToBin(int num) 
{	
	BinNum * ret = makeBinNum();
	int quotient = num;
	int i = 31;
	while(quotient != 0)
	{
		ret -> number[i] = quotient % 2;
		quotient = quotient / 2;
		i = i - 1;
		ret -> size = ret -> size + 1;
	}
	return ret;
}

BinNum * OctToBin(char * num) 
{
	int i = strlen(num) - 1;
	BinNum * ret = makeBinNum();
	int j = 31;
	while (i > 0 && j >= 0) 
	{
		char c = num[i];
		switch(c)
		{
			case '7':
			ret -> number[j] = 1;
			ret -> number[j-1] = 1;
			ret -> number[j-2] = 1;
			break;
			case '6':
			ret -> number[j-1] = 1;
			ret -> number[j-2] = 1;
			break;
			case '5':
			ret -> number[j] = 1;
			ret -> number[j-1] = 1;
			break;
			case '4':
			ret -> number[j-2] = 1;
			break;
			case '3':
			ret -> number[j] = 1;
			ret -> number[j-1] = 1;
			break;
			case '2':
			ret -> number[j-1] = 1;
			break;
			case '1':
			ret -> number[j] = 1;
			break;
			case '0':
			break;	
		}
		j = j - 3;
		i = i - 1;
		ret -> size = ret -> size + 3;
	}
	return ret;
}

BinNum * HexToBin(char * num) 
{
	int i = strlen(num) - 1;
	BinNum * ret = makeBinNum();
	int j = 31;
	while(i > 0 && j >= 0)
	{
		char c = num[i];
		switch(c)
		{
			case '0':
			break;
			case '1':
			ret -> number[j] = 1;
			break;
			case '2':
			ret -> number[j-1] = 1;
			break;
			case '3':
			ret -> number[j] = 1;
			ret -> number[j-1] = 1;
			break;
			case '4':
			ret -> number[j-2] = 1;
			break;
			case '5':
			ret -> number[j] = 1;
			ret -> number[j-2] = 1;
			break;
			case '6':
			ret -> number[j-1] = 1;
			ret -> number[j-2] = 1;
			break;
			case '7':
			ret -> number[j] = 1;
			ret -> number[j-1] = 1;
			ret -> number[j-2] = 1;
			break;
			case '8':
			ret -> number[j-3] = 1;
			break;
			case '9':
			ret -> number[j] = 1;
			ret -> number[j-3] = 1;
			break;
			case 'a':
			case 'A':
			ret -> number[j-3] = 1;
			ret -> number[j-1] = 1;
			break;
			case 'b':
			case 'B':
			ret -> number[j] = 1;
			ret -> number[j-1] = 1;
			ret -> number[j-3] = 1;
			break;
			case 'c':
			case 'C':
			ret -> number[j-2] = 1;
			ret -> number[j-3] = 1;
			break;
			case 'd':
			case 'D':
			ret -> number[j] = 1;
			ret -> number[j-2] = 1;
			ret -> number[j-3] = 1;
			break;
			case 'e':
			case 'E':
			ret -> number[j-1] = 1;
			ret -> number[j-2] = 1;
			ret -> number[j-3] = 1;
			break;
			case 'f':
			case 'F':
			ret -> number[j] = 1;
			ret -> number[j-1] = 1;
			ret -> number[j-2] = 1;
			ret -> number[j-3] = 1;
			break;
		}
		i = i - 1;
		j = j - 4;
		ret -> size = ret -> size + 4;
	}
	return ret;
}

BinNum * BinToBin(char * num)
{
	BinNum * ret = makeBinNum();
	int i = strlen(num) - 1;
	int j = 31;
	while(i > 0 && j >= 0)
	{
		char c = num[i];
		switch(c)
		{
			case '1':
			ret -> number[j] = 1;
			break;
			case '0':
			break;
		}
		j = j - 1;
		ret -> size = ret -> size + 1;
		i = i - 1;
	}
	return ret;
}

int BinToInt(BinNum * num)
{
	int ret = 0;
	int i;
	for(i = 31; i >=0; i--)
	{
		ret += (num -> number[i])*(int)pow(2, 31 - i);
	}
	return ret;
}

BinNum * makeBinNum()
{
	BinNum * ret = (BinNum *)malloc(sizeof(BinNum));
	ret -> size = 0;
	int i;
	for(i = 0; i < 32; i++)
	{
		ret -> number[i] = 0;
	}
	return ret;	
}

int checkValidInput(char * str)
{ 
/*	
 *	Returns:
 *	0 iff the base is invalid
 *	1 iff the number is valid format for given base
 *	2 iff the number has different digits for given base
 *		ie:
 *		8-f in octal returns 2
 *		a-f in decimal returns 2
 *		2-f in binary returns 2
 *		etc
 *	Makes use of the ctype.h library functions
 */ 
	char base = str[0];
	if (base != 'b' && base != 'o' && base != 'x' && base != 'd') 
	{
		return 0;
	}
	int i;
	switch(base)
	{
		case 'b':
			for(i = 1; str[i] != '\0'; i++)
			{
				if(str[i] != '1' && str[i] != '0') 
				{
					return 2;
				}
			}
			return 1;
		case 'd':
			for(i = 1; str[i] != '\0'; i++)
			{
				if(!isdigit(str[i]))
				{
					return 2;
				}
			}
			return 1;
		case 'x':
			for(i = 1; str[i] != '\0'; i++)
			{
				if(!isxdigit(str[i]))
				{
					return 2;
				}
			}
			return 1;
		case 'o':
			for(i = 1; str[i] != '\0'; i++)
			{
				if(!isdigit(str[i]) || str[i] == '8' || str[i] == '9')
				{
					return 2;
				}
			}
			return 1;
	}
	return 0;
}
