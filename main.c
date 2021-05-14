#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#pragma region Structures
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
#pragma endregion Structures

#pragma region Lists of the data
//Stores the information all Customer and saves the information into the Customers list
static struct Customer Customers[150] = {0};
//Stores the information all Book and saves the information into the Book list
static struct Book Books[150] = {0};
//Stores the information all Rented and saves the information into RentedBooks list
static struct Rented RentedBooks[150] = {0};
#pragma endregion Lists of the data

#pragma region Enumeraters of ID numbers
//Enumerates Customer IDs -> static variable to create unique IDs
static int C_ID_ENUMERATION = 0;
//Enumerates Book IDs -> static variable to create unique IDs
static int B_ID_ENUMERATION = 0;
//Enumerates Rented Book IDs -> static variable to create unique IDs
static int R_ID_ENUMERATION = 0;
#pragma endregion Enumeraters of ID numbers

#pragma endregion Booking System functions

#pragma region Functions For Array Operations
void addCustomer(struct Customer)
{


}
#pragma region Booking System functions
//Creates a new customer
int newCustomer(int _customerID, char _name[25], char _surname[25], int _age, double _wallet)
{
    //Creating a new Customer and passing the parameters, taken from the user, into it
    struct Customer newCustomer;
    newCustomer.C_ID = _customerID;
    strcpy(newCustomer.Name,_name);
    strcpy(newCustomer.Surname,_surname);
    newCustomer.Age = _age;
    newCustomer.Wallet = _wallet;
    //Adding the customer created recently to the Customers list
    size_t new_Customers_count = sizeof(Customers) +1;

    //Opening the Customers.txt to put the Customers information into it.
    FILE* fp = fopen("Customers.txt", "w+");
    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    int c; // note: int, not char, required to handle EOF
    while ((c = fgetc(fp)) != EOF) { // standard C I/O file reading loop
        putchar(c);
    }

    if (ferror(fp))
        puts("I/O error when reading");
    else if (feof(fp))
        puts("End of file reached successfully");


    fclose(fp);
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
    //! Auto-Increment #B_ID_ENUMERATION
    //Open the Books.txt
    //add a new book within the limitations
    //save it to the list
    //close the file
}


void rentBook(int _customerID, int _bookID, char _date[15], int _week)
{
    //! Auto-Increment #R_ID_ENUMERATION
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

#pragma endregion Functions For Array Operations
//Entry-point of BookingSystem program
int main()
{

    printf("1.\tCreate New Customer\n"
           "2.\tDeposit Money to the Customer\n"
           "3.\tAdd new Book\n"
           "4.\tRent A Book\n"
           "5.\tDelivery A Book\n"
           "6.\tBurn Book\n"
           "7.\tUpdate Customer Information\n"
           "8.\tUpdate Book Information\n"
           "9.\tList of Customers Who Rent a Book\n"
           "10.\tList of Customers\n"
           "11.\tList of Books\n");
    printf("Select one Option:\n");
    short option;
    scanf("%d", &option);
    bool isCustomer = false;
    switch (option) {
        case 1:
            //A control element, bool, to stop asking for the information from the
            while(!isCustomer)
            {
                //Getting a name from the user
                printf("Enter the customer name:\n");
                char _name[25];
                gets(_name);
                //Getting a surname from the user
                printf("Enter the customer Surname:\n");
                char _surname[25];
                gets(_surname);
                printf("Enter the customer Age:\n");
                int _age;
                scanf("%d", &_age);
                printf("Enter the customer Wallet:\n");
                double _wallet;
                scanf("%lf", &_wallet);
                //Checking for the name and surname whether they are in the customers list
                for (int i = 0; i < sizeof Customers; i++)
                {
                    if (Customers[i].Name != _name || Customers[i].Surname != _surname)
                    {
                        //Passing the user input into list by newCustomer method
                        int delegate_newCustomer = newCustomer(C_ID_ENUMERATION,
                                                               _name,
                                                               _surname,
                                                               _age,
                                                               _wallet);
                        //The loop, asking for the user information, ends due to the valid information
                        isCustomer = true;
                        //The loop, searching for the user information to confirm, ends
                        break;
                    }
                }
            }
            C_ID_ENUMERATION++; //! Auto-Increment #C_ID_ENUMERATION
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        default:
            perror("Invalid Input!"); //throw an error
    }
    return 0;

}