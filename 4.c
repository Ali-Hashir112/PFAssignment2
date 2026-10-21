#include <stdio.h>

int getValidDays()
{
    int days;
    
    printf("Enter Festival length (1-7) : ");
    scanf("%d" , &days);

    while(days < 1 || days > 7)
    {
        printf("Invalid input. Try again: ");
        scanf("%d" , &days);
    }

    return days;
}

float calculateDailySales(int dayNumber)
{
    float total, highest , temp;
    int customerOrder;

    printf("\nEnter number of customer orders for day %d: " , dayNumber);
    scanf("%d" , &customerOrder);

    total = 0;
    highest = 0;

    for(int j = 0 ; j < customerOrder ; j++)
    {
        printf("Enter amount for order %d: " , j+1);
        scanf("%f" , &temp);
        while(temp <= 0)
        {
            printf("Amount must be greater than 0. Try again: ");
            scanf("%f" , &temp);
        }
        total += temp;
    }

    if(temp > highest)
    {
        highest = temp;
    }
    
    printf("Total sales : Rs. %.2f\n" , total);
    printf("Average order : Rs. %.2f\n" , total/customerOrder);
    printf("Highest order : Rs. %.2f\n" , highest);

    return total;
}

int findHighestSalesDay(float dailySales[] , int numberOfDays)
{
    int highest = 0;
    for(int i = 0 ; i < numberOfDays ; i++)
    {
        if(dailySales[highest] < dailySales[i])
        {
            highest = i;
        }
    }

    return highest+1;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int current = 0;
    for(int i = 0 ; i < numberOfDays ; i++)
    {
        printf("\nDay 1: ");

        current = dailySales[i];
        while(current >= 100)
        {
            printf("*");
            current -= 100;
            
        }
        
        printf(" (Rs. %.2f)" , dailySales[i]);
    }
}

int main()
{
    int days , customerOrder, highest;
    float total = 0;

    days = getValidDays();

    float sales[days];
    
    for(int i = 0 ; i < days ; i++)
    {
        sales[i] = calculateDailySales(i+1);
        total += sales[i];
    }

    highest = findHighestSalesDay(sales , days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n" , total);
    printf("Day with highest sales: Day %d\n" , highest);
    printf("Highest daily sales: Rs. %.2f\n" , sales[highest-1]);
    
    printf("\n");

    printf("===== DAILY SALES BAR CHART =====");
    displayBarChart(sales , days);

}