#include <stdio.h>

int sum(int a)
{
    int limit = a;
    int sum = 1;
    for(int i = 2 ; i < limit ; i ++)
    {
        if(a % i == 0)
        {
            limit = a/i;
            sum += i;
            if(limit != i)
            {
                sum += limit;
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