#include <stdio.h>

int main()
{
    int rows, col, temp, output[2], total, rowtotal, customers, currentRow, currentCol, check;
    output[0] = '_';
    output[1] = 'X';
    total = 0;
    check = 0;

    do{
        printf("Enter number of rows: ");
        scanf("%d" , &rows);

        printf("Enter number of columns: ");
        scanf("%d" , &col);

    }while(rows <= 0 || col <= 0);

    int seats[rows][col], free[rows];
    int middle = rows/2;

    for(int i = 0  ; i < rows ; i++)
    {
        for (int j = 0 ; j < col ; j++)
        {
            do
            {
            
            printf("Enter availibility (1/0) of row %d col %d : " , i+1 , j+1);
            scanf("%d" , &temp);

            }while(!(temp == 0 || temp == 1));

            seats[i][j] = temp;
        }
        
    }
    
    printf("%6s" , "");

    for(int i = 0 ; i < col ; i++)
    {
        printf("%3d" , i);
    }
    
    printf("\n");

    total = rows * col;
    for (int i = 0 ; i < rows ; i++)
    {
        rowtotal = col;
        printf("R%-5d" , i+1);
        for (int j = 0 ; j < col; j++)
        {
            temp = seats[i][j] & 1;
            printf("%3c" , output[temp]);
            rowtotal -= temp;
            total -= temp;

        }
        free[i] = rowtotal;
        printf("\n");
        
    }

    printf("Seats free per row: ");
    for (int i = 0; i < rows; i++)
    {
        printf("%d " , free[i]);
    }
    
    printf("\nTotal Available Seats: %d" , total);
    
    printf("\nEnter number of seats to be booked: ");
    scanf("%d" , &customers);

    for(int i = 0; i < col; i++)
    {
        temp = 0;
        currentRow = (middle - i) - 1;
        if((currentRow < 0 && (currentRow + (2 * i)) < 0 )|| currentRow >= rows)
        {
            continue;
        }
        if(currentRow != 0)
        {
            for(currentCol = 0 ; currentCol < col ; currentCol++)
            {
                if(seats[currentRow][currentCol] == 0)
                {
                    temp += 1;
                }
                else
                {
                    temp = 0;
                }

                if(temp == customers)
                {
                    check = 1;
                    currentCol = (currentCol - customers) + 1;
                    break;
                }
            }
        }

        if(i != 0)
        {
            temp = 0;
            currentRow += (2 * i);
            if(currentRow < 0 || currentRow >= rows)
            {
                continue;
            }
            for(currentCol = 0 ; currentCol < col ; currentCol++)
            {
                if(seats[currentRow][currentCol] == 0)
                {
                    temp += 1;
                }
                else
                {
                    temp = 0;
                }
                if(temp == customers)
                {
                    
                    check = 1;
                    currentCol = (currentCol - customers) + 1;
                    break;
                }
            }
        }
        if(check)
        {
            break;
        }
        

    }
    if(check)
    {
        for(int i = 0 ; i < customers ; i++)
        {
            seats[currentRow][currentCol + i] = 1;
        }
        
        printf("%6s" , "");

        for(int i = 0 ; i < col ; i++)
        {
            printf("%3d" , i);
        }
        printf("\n");

        total = rows * col;

        for (int i = 0 ; i < rows ; i++)
        {
            rowtotal = col;
            printf("R%-5d" , i+1);

            for (int j = 0 ; j < col; j++)
            {
                temp = seats[i][j] & 1;
                printf("%3c" , output[temp]);
                rowtotal -= temp;
                total -= temp;

            }
            free[i] = rowtotal;
            printf("\n");
        
        }

        printf("Seats free per row: ");
        for (int i = 0; i < rows; i++)
        {
            printf("%d " , free[i]);
        }
    
        printf("\nTotal Available Seats: %d" , total);
    }
    else
    {
        printf("Not enough seats available in a block.");
    }
    
    
}