//Name: Maryum Shabazz
//Date: 10/30/2019
//Description: Week 5 assignment for random testing and code coverage
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int maxNumber=126;
    int minNumber=32;
    
    //code for random generator with range referenced from 
    //https://www.geeksforgeeks.org/generating-random-number-range-c/
    int num = (rand() % (maxNumber - minNumber + 1)) + minNumber; 

    while(num>=65 && num<=90)
    {
      num = (rand() % (maxNumber - minNumber + 1)) + minNumber;
    }
    char returnChar=num;
    // TODO: rewrite this function
    
    return returnChar; 
    
}

char *inputString()
{
    // TODO: rewrite this function
    char *charArray = malloc(sizeof(char) * 6);
    
    int i;
    for(i=0; i<6; i++)
    {
        if(i!=5)
        {
            char b=inputChar();
 	    while(b!= 'r' && b!='e' && b!='s' && b!='t')
	    {
	    	b=inputChar();
	    }
	    charArray[i]=b;
        }
        else
        {
            charArray[5]='\0';
        }
    }
    return charArray;
}

void testme()
{
  
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
