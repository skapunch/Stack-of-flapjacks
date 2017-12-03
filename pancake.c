#include <stdio.h>
#define MAXSTACK 10
#undef DEBUG
int tonumber(char *s);
int loop(int *stack, int current, int npancakes);
void flip(int *stack, int maxIndex, int npancakes);
void pancakesort(int *stack, int n);
void printshit(int *s, int n);
void flipat(int index);

int main ( int argc, char *argv[] )											// argv[0]: program name			argc = 1
{	
#ifdef DEBUG
	int stack[] = { 5 , 4 , 3 , 2 , 1};
	int n = 5;
#endif
#ifndef DEBUG	//	argv[1]: number of pancakes	argc = 2																				// argv[2]:	1st pancake				argc = 3
	int stack[MAXSTACK];															// .....	
	int n;					//number of pancakes								// argv[argc-1] : last pancake	argc 
#endif
	if (argc == 2)
	{
		printf("where are the pancakes?");
		return 0;
	}
	else if (argc > 2) 
	{
#ifndef DEBUG
		int i,j;
		n = tonumber(argv[1]);
		for (i = 0, j = 2 ; j < argc  ; i++, j++) 
			stack[i] = tonumber(argv[j]); //readin
		printshit(stack, n);
		pancakesort(stack, n);				//you can cook!!
		
		//print out
		printf("0\n");
#endif
	}
	else 
	{
#ifndef DEBUG
		printf("please say something.\n");
			return 0;
#endif
#ifdef DEBUG
		printshit(stack, n);
		pancakesort(stack, n);				//you can cook!!
		
		//print out
		printf("0\n");
#endif
	}
	return 0;
}

int tonumber(char *s)
{
	int i,c;
	c = 0;
	for (i = 0 ; s[i] != '\0' ;i++)
			c = c*10 + (s[i] - '0');
	return c;
}

int loop(int *stack, int current, int npancakes1)
{
	int maxIndex1 = current;
	int i = current;
	int largest = stack[current];
	
	for (i = current; i < npancakes1; i++) {
		if ( stack[i] >= largest) {					//goes through the stack starting from the lastest largest recorded
			largest = stack[i];						//recorded the largest so far
			maxIndex1 = i;								//record the index 
		}
	}
	return maxIndex1;									//return the recorded index of the largest after walk through
}

void flip(int *stack,int maxIndex2, int npancakes2)
{
	int i,j,temp;
	i = maxIndex2;
	j = npancakes2 - 1;
	for(; i < j; i++, j--) 
	{
		temp = stack[i];
		stack[i] = stack[j];
		stack[j] = temp;
	}
}

void pancakesort(int *stack, int n)
{
	int currentIndex, maxIndex;
	currentIndex = maxIndex = 0;
	while(currentIndex < n)
	{
		maxIndex = loop(stack, currentIndex, n); 		//return the largest index after a walkthrough starting from current
		if (maxIndex < (n-1))		//largest not at top
		{
			if(maxIndex == currentIndex)  // largest is at base (current)
			{
				currentIndex++;						//just advance
				continue;
			}
			else if (maxIndex > currentIndex)						// largest is above current
			{
				flip(stack,maxIndex,n);			//bring it to top
				flipat(maxIndex);
				flip(stack,currentIndex,n);			//bring it to the current
				flipat(currentIndex);
				currentIndex++;						//advance
			}
		}
		else if (maxIndex == (n-1) )		//it is at top  //beware when the current reach the top of the stack
		{
			if(currentIndex == (n-1))
			{
				currentIndex++;
				continue;
			}
			flip(stack, currentIndex, n);			//just a flip will do
			flipat(currentIndex);
			currentIndex++;						//advance
		}
	} 
}

void printshit(int *stack , int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", stack[i]);
	printf("\n");
}

void flipat(int index)
{
	printf("%d ",index+1);
}