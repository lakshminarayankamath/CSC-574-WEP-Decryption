#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int findKey(int);
void findMax(int);
void swap(int,int);
void initialize();

unsigned char out;
unsigned char lineRead[256];
unsigned char WEPKey[5];
unsigned char counts[256];
unsigned char s[256];
unsigned char a,ch;

int main(int argc,char* argv[])
{
	FILE *inputFile;
	int len = 0;
	int bytesRead;
	int i, tmp;
      
	inputFile = fopen (argv[1],"r");
	if (inputFile == NULL)
	{
		printf ("File doesn't exist \n");
		return 1;
	}

	for(i=0;i<5;i++)
		WEPKey[i]=0;
	
	unsigned char plainText = 'C';
	int byteNum=0;

	while(byteNum<5) 
	{
		//memset(counts, 0, 256);
		for(i=0;i<256;i++)
			counts[i]=0;
		inputFile = fopen (argv[1],"r");
		bytesRead = fread (lineRead, 1, 143, inputFile);
		while ((bytesRead = fread(lineRead, 1, 143, inputFile))!=0)
		{
			//Process read packet and update counts array 
			if (lineRead[24] == byteNum+3)
			{
				out = lineRead[27]^plainText;
				tmp = findKey(byteNum);
				if (tmp >= 0 && tmp<=255)
					counts[tmp]++;
			}
			
		}
		//Process counts array and find WEPKey[byteNum]
		findMax(byteNum);
		byteNum++;
	}

        printf("The WEP Key for %s is : ",argv[1]);
	for(i=0;i<5;i++)
		printf("%c",WEPKey[i]);
        printf("\n");
	fclose (inputFile);
	return 0;
}


void findMax(int byteNum)
{
 int large=0;
 int position=0;
 int i=0;
 
 for (i=0; i<256; i++)
 {
	if(counts[i]<=large)
		continue;
	else if (counts[i] > large)
	{
		position=i;
		large = counts[i];
	}
 }
 WEPKey[byteNum]=(unsigned char)position;
}


void swap(int i,int j)
{
 a = s[i];
 s[i] = s[j];
 s[j] = a;
}


int findKey(int byteNum)
{
	unsigned int k=0;
	unsigned char tmp_key[8];
	int i=0, j=0;

        for(i=0;i<3;i++)
		tmp_key[i]=lineRead[24+i];

	for(i=0;i<5;i++)
		tmp_key[i+3]=WEPKey[i];

        initialize();
	for (i=0; i<byteNum+3; i++)
	{
		j = (unsigned char)(j+i+tmp_key[k]);
		swap(i,j);
		if (8 <= ++k)
			k = 0;
	}
	for (i=0; i<256; i++)
	{
		if (s[i] != out)
		    continue;
		else if(s[i]==out)
		    ch = i;
	}
        //printf("%d %c %d \n",s[0],s[0],byteNum+3);
	if ((s[0] == byteNum + 3))
		return (ch-j-s[byteNum+3]);
	else
		return -1;
}

void initialize()
{
 int i=0;
 for (i=0; i<256; i++)
	s[i] = i;
}



