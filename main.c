#include <stdio.h>
#include <stdbool.h>
//Stores the information of Book object
struct Book
{
    int B_ID;
    char Name[25];
    char Author[25];
    int AgeLimit;
    double PricePerWeek;
    bool Rented;
};
//Stores the information of Rented objectt
struct Rented
{
    int R_ID;
    int C_ID;
    int B_ID;
    char Date[10];
    int Week;
};

//A structure that stores the generic information of Customer
struct Customer
{
    int C_ID;
    char Name[25];
    char Surname[25];
    int Age;
    double Wallet;
};


int main()
{
    return 0;

}

//Creates a new customer
void newCustomer(char _name[25], char _surname[25], int age, double wallet)
{
    //Open the file
    //Create the customer
    //save it to the list
    //close the file
}
//Selects the customer by ID and increases its deposit
void depositMoney(int _customerID, double wallet)
{
    
}

//adds new book
void addBook()
{

}

//
void rentBook()
{

}
