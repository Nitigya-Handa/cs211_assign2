#ifndef CALCFUNC_H_
#define CALCFUNC_H_

typedef struct BinNum_ 
{
	int size;
	int number[32];
} BinNum;

char * append(char * str, char c);

char * BinToDecStr(int num);

char * BinToHexStr(int num);

char * BinToOctStr(int num);

char * BinToBinStr(BinNum * num);

BinNum * DecToBin(int num);

BinNum * OctToBin(char * num);

BinNum * HexToBin(char * num);

BinNum * BinToBin(char * num);

int BinToInt(BinNum * num);

BinNum * makeBinNum();

int checkValidInput(char * str);


#endif
