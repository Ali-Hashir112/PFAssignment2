#include <stdio.h>

void inputReadings(int sensors , int hours ,int readings[sensors][hours])
{
    for(int i = 0 ; i < sensors ; i++)
    {
        for(int j = 0 ; j < hours ; j++)
        {
            printf("Enter reading for sensor %d hour %d : " , i+1 , j+1);
            scanf("%d" , &readings[i][j]);
        }
    }
}

void analyze( int sensors , int hours , float analysis[sensors][7] , int readings[sensors][hours])
{
    int warning , critical , lowest , highest , streak, longestStreak;
    float average, total;

    for(int i = 0 ; i < sensors ; i++)
    {
        total = 0;
        average = 0;
        highest = 0;
        lowest = 0;
        critical = 0;
        warning = 0;
        streak = 0;
        longestStreak = 0;

        for(int j = 0 ; j < hours ; j++)
        {
            total += readings[i][j];
            if(readings[i][j] >= 35)
            {
                streak += 1;

                if(readings[i][j] <= 39)
                {
                    warning += 1;
                }
                else
                {
                    critical += 1;
                }
            }
            else
            {
                if(streak > longestStreak)
                {
                    longestStreak = streak;
                }
                streak = 0;
            }

            if(j == 0)
            {
                highest = 0;
                lowest = 0;
            }
            else
            {
                if(readings[i][highest] < readings[i][j])
                {
                    highest = j;
                }
                if(readings[i][lowest] > readings[i][j])
                {
                    lowest = j;
                }
                
            }
            
        }
        if(streak > longestStreak)
        {
            longestStreak = streak;
        }

        average = total/hours;

        analysis[i][0] = total;
        analysis[i][1] = average;
        analysis[i][2] = highest;
        analysis[i][3] = lowest;
        analysis[i][4] = critical;
        analysis[i][5] = warning;
        analysis[i][6] = longestStreak;
    }
}

int highest(int sensors , float analysis[sensors][7])
{
    int highest = 0;
    for(int i = 1 ; i < sensors ; i++)
    {
        if(analysis[highest][1] < analysis[i][1])
        {
            highest = i;
        }
    }
    return highest;
}

int main()
{
    int sensors, hours, highestAve;

    printf("Enter number of sensors: ");
    scanf("%d" , &sensors);

    printf("Enter number of readings: ");
    scanf("%d" , &hours);

    int readings[sensors][hours];
    float analysis[sensors][7];

    inputReadings(sensors , hours , readings );
    analyze(sensors, hours , analysis , readings );
    highestAve = highest(sensors , analysis);

    for(int i = 0 ; i < sensors ; i++)
    {
        int highest = (int)analysis[i][2];
        int lowest  = (int)analysis[i][3];

        printf("Sensor %d: Total=%g  Avg=%.2f  Max=%d  Min=%d\n" , i+1 ,
           analysis[i][0] ,
           analysis[i][1] ,
           readings[i][(int)highest] ,
           readings[i][(int)lowest]);

        printf("          Critical=%d  Warning=%d  Longest hot streak=%d\n" ,
           (int)analysis[i][4] ,
           (int)analysis[i][5] ,
           (int)analysis[i][6]);
    }

    printf("\n");
    printf("Highest average: Sensor %d (%.2f)" , highestAve , analysis[highestAve][1]);

}