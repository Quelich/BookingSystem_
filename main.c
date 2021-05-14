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
//Stores the information of Rented object
struct Rented
{
    int R_ID;
    int C_ID;
    int B_ID;
    char Date[15];
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

static int C_ID_ENUMARATION = 0;
static int B_ID_ENUMARATION = 0;
static int R_ID_ENUMARATION = 0;

int main()
{
    return 0;

}

//Creates a new customer
void newCustomer(char _name[25], char _surname[25], int age, double wallet)
{
    //! Auto-Increment #C_ID_ENUMARATION
    //Open the Customers.txt
    //Create the customer
    //save it to the list
    //close the file
}
//Selects the customer by ID and increases its deposit
void depositMoney(int _customerID, double wallet)
{

}

//adds new book
void addBook(char _name[25], char _author[25],  int _ageLimit,  double _pricePerWeek, bool _rented)
{
    //! Auto-Increment #B_ID_ENUMARATION
    //Open the Books.txt
    //add a new book within the limitations
    //save it to the list
    //close the file
}


void rentBook(int _customerID, int _bookID, char _date[15], int _week)
{
    //! Auto-Increment #R_ID_ENUMARATION
    //Open the Rented.txt
    //add a new book within the limitations
    //save it to the list
    //close the file
}
//Removes the book from Books list
void burnBook(int _bookID, bool _rented)
{

}
//Updates the information of the user
void updateCustomer(char _name[25], char _surname[25], int age)
{

}

void updateBook(char _name[25], char _author[25],  int _ageLimit,  double _pricePerWeek)
{

}

void listCustomersRentedBook()
{

}
void listCustomers()
{

}
void listBooks()
{

}