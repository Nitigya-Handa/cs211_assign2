#include <malloc.h>
#include <string.h>
#include <math.h>

char * prepend(char * str, char c)
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

char * CreateIntOut(char * bitstream, char sign) 
{
//	printf("dafuq");
	int i;
	char * alt = (char *)malloc(sizeof(char)*33);
	if(sign == '1')
	{
		alt[0] = '2';				//for my own reference
		alt[33] = '\0';
		for(i = 1; i < 33; i++)			//populates alternate string with complimentary characters
		{					//allows for easy int conversion
			if(bitstream[i] == '1')
			{
				alt[i] = '0';
			}
			else
			{
				alt[i] = '1';
			}
		}
	}	
	int convert = 0;
	char * str = (sign == '0') ? bitstream:alt;	//differentiates between pos and neg values
	for (i = 31; i > 0; i--)
	{
		char c = str[i];
	//	printf("%c\n", c);
		if(c == '1')
		{
			convert += (int)pow(2, 31 - i);
		}
	}
	char * ret = (char *) malloc(sizeof(char));
	ret[0] = '\0';
	if (sign == '1')
	{
		convert = convert + 1;
	}
	if (convert == 0)
	{
		ret = prepend(ret, '0');
		return ret;
	}
	while(convert != 0)
	{
		char c = (convert % 10) + '0';
//		printf("%c\n", c);
		ret = prepend(ret, c);
		convert = convert / 10;
	}
	if (sign == '1')
	{
		ret = prepend(ret, '-');
	}
	return ret;
}

char * CreateFltOut (char * bitstream)
{
	char pinf[] = "01111111100000000000000000000000";
	char ninf[] = "11111111100000000000000000000000";
	if(strcmp(pinf, bitstream) == 0)
	{
		return "pinf";
	}
	if(strcmp(ninf, bitstream) == 0)
	{
		return "ninf";
	}
	int i, test = 0;
	for(i = 1; i < 9; i++)
	{
		if(bitstream[i] == '1')
		{
			test++;
		}
	}
	if (test == 8)
	{
		for(i = 9; bitstream[i] != '\0'; i++)
		{
			if (bitstream[i] == '1')
			{
				return "NaN";
			}
		}
	}
	float exponent = 0;
	for (i = 1; i < 9; i++)
	{
		if (bitstream[i] == '1')
		{
			exponent += (float)pow(2, 8 - i);
		}
	}
	exponent = exponent - 127;
	float mantissa = 1;
	for (i = 9; i < 32; i++)
	{
		if (bitstream[i] == '1')
		{
			mantissa += (float)pow(2, 8-i);
		}
	}
	float result = ((bitstream[0] == '1') ? -1 : 1 )*pow(2, exponent)*mantissa;
	int pow10 = 0;
	while (fabsf(result) > 10)
	{
		result = result / 10;
		pow10 = pow10 + 1;
	}
	while (fabsf(result) < 0)
	{
		result = result * 10;
		pow10 = pow10 - 1;
	}
	char * ret = (char *)malloc(50);
	sprintf(ret, "%fe%d\n", result, pow10);
	return ret;
	
	
	
	
	
	
}
