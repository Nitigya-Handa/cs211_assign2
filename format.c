#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "formfunc.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("ERROR: Not enough input arguements!\n");
		return 0;
	}
	if (strlen(argv[1]) != 32)
	{
		printf("ERROR: Please enter a sequence of 32 bits!\n");
		return 0;
	}
	char * bitstream = (char *)malloc(sizeof(char)*33);
	strcpy(bitstream, argv[1]);
	
	int i;
	for(i = 0; bitstream[i] != '\0'; i++)
	{
		char c = bitstream[i];
		if(c != '0' && c != '1')
		{
			printf("ERROR: Please enter a valid bitstream! (1's and 0's only)\n");
			return 0;
		}
		
	}
	
	char * outtype = (char *)malloc(sizeof(char)*(strlen(argv[2])+1));
	strcpy(outtype, argv[2]);
//	printf("dafuq");
	char test1[] = "int";
	char test2[] = "float";
	if(strcmp(outtype, test1) != 0 && strcmp(outtype, test2) != 0)
	{
		printf("ERROR: Invalid output type! Use \"int\" or \"float\"\n");
		return 0;
	}
	int flag = 1;		// flag = i if int
	if (strcmp(outtype, test2) == 0)
	{
		flag = 2;	// flag = 2 if float
	}
	switch(flag)
	{
		case 1:		
		{
			char * output = CreateIntOut(bitstream, bitstream[0]);
			printf("%s\n", output);
			break;
		}
		case 2:
		{	
			char * output = CreateFltOut(bitstream);
			printf("%s", output);
			break;
		}
		
	}
	
	
	
	return 0;
}
