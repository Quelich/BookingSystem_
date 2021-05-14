#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
    int Wallet;
};
#pragma endregion Structures

#pragma region Lists of the data
//Stores the information all Customer and saves the information into the Customers list
static struct Customer Customers[150];

//Stores the information all Book and saves the information into the Books list
static struct Book Books[150] = {0};
//Stores the information all Rented and saves the information into RentedBooks list
static struct Rented RentedBooks[150] = {0};
#pragma endregion Lists of the data

#pragma region Enumeraters of ID numbers

//Enumerates Book IDs -> static variable to create unique IDs
static int B_ID_ENUMERATION = 1;
//Enumerates Rented Book IDs -> static variable to create unique IDs
static int R_ID_ENUMERATION = 1;
#pragma endregion Enumeraters of ID numbers

#pragma endregion Booking System functions

#pragma region Functions For Array Operations
static int current = 0;
void addCustomer(struct Customer newCustomer)
{
    if(current <= sizeof Customers)
    {
        Customers[current] = newCustomer;
        current++;
    }
    else
    {
        perror("YOU REACHED THE LIMIT! CANNOT ADD ANY MORE ELEMENTS!");
    }
}
void initializeCIDs()
{
    //Initializing the IDs of all customers
    for(int element = 0; element < sizeof Customers; element++) //sizeof Customers
    {
        Customers[element].C_ID = element;
    }
}
#pragma endregion Functions For Array Operations

#pragma region Booking System functions
//Creates a new customer
int newCustomer(int _customerID, char _name[25], char _surname[25], int _age, int _wallet)
{
    //Creating a new Customer and passing the parameters, taken from the user, into it
    struct Customer newCustomer;
    newCustomer.C_ID = _customerID;
    strcpy(newCustomer.Name, _name);
    strcpy(newCustomer.Surname,_surname);
    newCustomer.Age = _age;
    newCustomer.Wallet = _wallet;
    //Adding the customer created recently to the Customers list
    addCustomer(newCustomer);
    //Appending the Customers.txt to put the Customers information line by line.
    FILE* fp = fopen("Customers.txt", "a");
    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    fprintf(fp, "Customer ID #%d |"
                "Customer Name: %s |"
                "Customer Surname: %s |"
                "Customer Age: %d |"
                "Customer Wallet: %d\n",
            newCustomer.C_ID,
            newCustomer.Name,
            newCustomer.Surname,
            newCustomer.Age,
            newCustomer.Wallet);
    fclose(fp);
}
//Selects the customer by ID and increases its deposit
void depositMoney(int _customerID, double _deposit)
{
    for(int element = 0; element <= sizeof Customers; element++)
    {
       if( Customers[element].C_ID == _customerID)
       {
           Customers[element].Wallet =  Customers[element].Wallet + _deposit;
       }
    }
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
int listCustomers()
{

    //Writing every element of the Customers array into the Customers.txt
    for(int element = 0; element <= sizeof Customers; element++) //sizeof Customers
    {
        printf("Customer ID: #[%d] | "
               "Customer Name: [%s] | "
               "Customer Surname: [%s] | "
               "Customer Age: [%d] | "
               "Customer Wallet: [%lf]\n", Customers[element].C_ID,Customers[element].Name, Customers[element].Surname, Customers[element].Age, Customers[element].Wallet);
    }

}
void listBooks()
{

}

//Enumerates Customer IDs -> static variable to create unique IDs
static int C_ID_ENUMERATION = 1;
int proceedOption1()
{
    //Processing the option
    bool isCustomer = false;
    //A control element, bool, to stop asking for the information from the
    while(!isCustomer)
    {
        //Getting a name from the user
        printf("Enter the customer name:\n");
        char _name[25];
        scanf("%s", _name);
        //Getting a surname from the user
        printf("Enter the customer Surname:\n");
        char _surname[25];
        scanf("%s", _surname);
        printf("Enter the customer Age:\n");
        int _age;
        scanf("%d", &_age);
        printf("Enter the customer Wallet:\n");
        int _wallet;
        scanf("%d", &_wallet);
        //Checking for the name and surname whether they are in the customers list
        for (int i = 0; i < sizeof Customers; i++)
        {
            if (Customers[i].Name == _name || Customers[i].Surname == _surname)
            {
                perror("The customer already exits!");
                return -1;
            } else{
                isCustomer = true;
                //Passing the user input into list by newCustomer method
                newCustomer(C_ID_ENUMERATION,
                            _name,
                            _surname,
                            _age,
                            _wallet);
                C_ID_ENUMERATION++; //! Auto-Increment #C_ID_ENUMERATION
                return -1;
                //The loop, asking for the user information, ends due to the valid information
            }
        }
    }
}
int isExist(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}


int runProgram()
{
    char* fileCustomers = "Customers.txt";
    int customersExist = isExist(fileCustomers);
    FILE* fp = fopen(fileCustomers, "w");
    if(!fp) {
        perror("Customers.txt file opening failed");
        return EXIT_FAILURE;
    }
    else if(customersExist)
    {

    }
    //Looping the program
    bool isExit = false;
    while(!isExit)
    {
        //Showing all the options to the user
        printf("0.\tExit Booking System\n"
               "1.\tCreate New Customer\n"
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
        //Getting an option from the user
        printf("Select one Option:\n");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 0:
                isExit = true;
                printf("You exit Booking System program. See you again");
                return -1;
            case 1:
                proceedOption1();

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
                listCustomers();
                break;
            case 11:
                break;
            default:
                perror("Invalid Input!");
        }

    }

}

//Entry-point of BookingSystem program
int main()
{
    runProgram();
    return 0;
}