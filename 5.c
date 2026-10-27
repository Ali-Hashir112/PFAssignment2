#include <stdio.h>
#include <string.h>

void displayMenu()
{
    printf("\nEnter Choice: \n1. Member Registration \n2. Display Available books");
    printf("\n3. Borrow a book \n4. Return a book \n5. Display member record \n6. Exit \nChoice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    int id, type;
    printf("\nEnter Name: ");
    scanf(" %49[^\n]" , name);

    printf("\nEnter Student id: ");
    scanf("%d" , &id);
    
    while(id <= 0)
    {
        printf("Invalid Id input. Retry: ");
        scanf("%d" , &id);
    }
    

    printf("\nEnter Member type Student(1) / Faculty(2): ");
    scanf("%d" , &type);
    
    while(type != 1 && type != 2)
    {
        printf("Invalid Input for member type. Retry: ");
        scanf("%d" , &type);    
    }

    *studentID = id;
    *memberType = type;

}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    printf("\n%-10s%-50s%-10s\n" , "ID" , "Title" , "Copies");
    for(int i = 0 ; i < totalBooks ; i++)
    {
        printf("%-10d%-50s%-10d\n" , bookIDs[i] , bookTitles[i] , availableCopies[i]);
    }

}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) 
{
    int id, i;
    
    int check = -1;
    int copies = 0;

    printf("Enter a valid bookID: ");
    scanf("%d" , &id);

    for(i = 0 ; i < totalBooks ; i++)
    {
        check = 0;
        if(id == bookIDs[i])
        {
            check = 1;
            copies = availableCopies[i];
            break;
        }
    }

    if(*borrowedCount < 3 && copies > 0 && check == 1)
    {
        borrowedBookIDs[*borrowedCount] = id;
        *borrowedCount += 1;
        availableCopies[i] -= 1;

        printf("\nBookID: %d Title: %s has been issued." , id , bookTitles[i]);
    }
    else if(check == 1)
    {
        if(copies < 1)
        {
            printf("\nNot enough copies.");
        }
        else
        {
            printf("\nMember has already borrowed 3 books");
        }
    }
    else
    {
        printf("\nNo book with given ID found.\n");
    }

}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id , days , i;
    char code[8];
    
    int check = 0;
    float fine = 0;

    printf("Enter a valid borrowed bookID: ");
    scanf("%d" , &id);

    for(i = 0 ; i < *borrowedCount ; i++)
    {
        if(id == borrowedBookIDs[i])
        {
            check = 1;
            break;
        }
    }
    
    if(check == 1)
    {
        for(i = 0 ; i < totalBooks ; i++)
        {
            if(id == bookIDs[i])
            {
                break;
            }
        }

        *borrowedCount -= 1;
        availableCopies[i] += 1;

        printf("Enter duration of borrow in days: ");
        scanf("%d" , &days);
        while(days < 0)
        {
            printf("Enter valid duration: ");
            scanf("%d" , &days);
        }
        

        if(memberType == 1)
        {
            days = days - 14;
            if(days > 0)
            {
                fine = days * 20;
            }
        }
        else
        {
            days = days - 30;
            if(days > 0)
            {
                fine = days * 10;
            }
        }

        *totalFine += fine;

        if(fine > 0)
        {
            printf("Enter membership code: ");
            scanf(" %s" , code);

            if(strcmp(code , "LIB2026") == 0)
            {
                fine = fine/2;
            }
            else
            {
                printf("Invalid membership code. No discount on fine\n");
            }
        }

        return fine;
    }
    else
    {
        return -1;
    }
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver)
{
    printf("\n===========MEMBER RECORD===========");
    printf("\nName: %s" , name);
    printf("\nStudent ID: %d" , studentID);
    
    switch(memberType)
    {
    case 1:
        printf("\nMember Type: Students");
        break;
    
    case 2:
        printf("\nMember Type: Faculty");
        break;
    }

    printf("\nBooks Currently Borrowed: %d" , borrowedCount);
    printf("\nBooks Borrowed(ID): ");
    for (int i = 0; i < borrowedCount; i++)
    {
        printf("%20d\n" , borrowedBookIDs[i]);
    }

    printf("Total Fine: %.2f" , totalFine);
    printf("\nFine payable after waiver: %.2f" , fineAfterWaiver);

}

int main()
{
    int choice , studentID , memberType;
    char name[50];
    int bookIDs[4] = {101 , 102 , 103 , 104};
    char bookTitles[4][50] = {{"Programming in C"} , {"Data Structures"} , {"Database Systems"} , {"Computer Networks"}};
    int availableCopies[4] = {5 , 3 , 0 , 4};
    float currentFine;

    int borrowedBookIDs[3] = {0, 0, 0};
    int borrowedCount = 0;
    int totalBooks = 4;
    float totalFine = 0;
    float fineAfterWaiver = 0;
    int registered = 0;

    do
    {
        while(1)
        {
            displayMenu();
            scanf("%d", &choice);

            if(choice < 1 || choice > 6)
            {
                printf("\nInvalid Menu choice. Retry\n");
            }
            else if(registered == 0 && choice != 1 && choice != 6)
            {
                printf("\nCannot access other options until a member is registered\n");
            }
            else
            {
                break;
            }
        }


        switch (choice)
        {
        case 1:
            registerMember(name , &studentID , &memberType);
            registered = 1;
            break;
        case 2:
            displayBooks(bookIDs , bookTitles , availableCopies , totalBooks);
            break;
        case 3:
            borrowBook(bookIDs , bookTitles , availableCopies , totalBooks , borrowedBookIDs , &borrowedCount , memberType);
            break;
        case 4:
            currentFine = returnBook(bookIDs , availableCopies , totalBooks , borrowedBookIDs , &borrowedCount , memberType , &totalFine);
            if(currentFine == -1)
            {
                printf("\nNo borrowed book with given ID found.");
            }
            else
            {
                fineAfterWaiver += currentFine;
            }
            break;
        case 5:
            displayMemberRecord(name , studentID , memberType , borrowedBookIDs , borrowedCount , totalFine , fineAfterWaiver);
            break;
        case 6:
            printf("\nTerminating Session......");
            break;
        }
        
    }while(choice != 6);


}