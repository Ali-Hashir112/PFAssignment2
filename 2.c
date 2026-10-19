#include <stdio.h>

int sum(int a)
{
    int sum = 1;
    for(int i = 2 ; i * i <= a ; i ++)
    {
        if(a % i == 0)
        {
            sum += i;
            if(i != a/i)
            {
                sum += a/i;
            }
        }
    }
    return sum;
}

int main()
{
    int pair;
    int end;

    printf("Enter endpoint: ");
    scanf("%d" , &end);

    for(int i = 2 ; i < end ; i ++)
    {
        pair = sum(i);

        if((i < pair) && sum(pair) == i)
        {
            printf("(%d , %d)\n" , i , pair);
        }
    }
}