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
    int PricePerWeek;
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
static int enumerate_latest_BID = 0;
//Enumerates Rented Book IDs -> static variable to create unique IDs
static int R_ID_ENUMERATION = 1;
static int enumerate_latest_CID = 0; // Storing the last ID executed in the file by counting the line numbers
#pragma endregion Enumeraters of ID numbers



#pragma region Functions For Array Operations


//Counting line in order to indicate the current customer's ID
int lineCounter()
{
    // count the number of lines in the file called filename
    FILE *customersFile = fopen("Customers.txt", "r");
    int ch=0;
    int lines=0;
    lines++;
    while ((ch = fgetc(customersFile)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    fclose(customersFile);
    return lines;
}

#pragma endregion Functions For Array Operations

#pragma region Booking System functions
//Prints the content of given array
void printCustomersArray()
{
    for (int i = 0; i < 5; i++) {
        printf("Array Place:%d CID:%d Name:%s Surname:%s Age:%d Wallet:%d\n", i, Customers[i].C_ID,Customers[i].Name,Customers[i].Surname, Customers[i].Age,Customers[i].Wallet);
    }
}
void printBooksArray()
{
    for (int i = 0; i < 5; i++) {
        printf("Array Place:%d BID:%d Name:%s Author:%s Age Limit:%d Rented:%d\n", i, Books[i].B_ID,Books[i].Name,Books[i].Author, Books[i].AgeLimit,Books[i].Rented);
    }
}
int addCustomerTOCustomers(struct Customer newCustomer)
{
    Customers[enumerate_latest_CID-1].C_ID = newCustomer.C_ID;
    strcpy(Customers[enumerate_latest_CID-1].Name,newCustomer.Name);
    strcpy(Customers[enumerate_latest_CID-1].Surname,newCustomer.Surname);
    Customers[enumerate_latest_CID-1].Age = newCustomer.Age;
    Customers[enumerate_latest_CID-1].Wallet = newCustomer.Wallet;
    if(Customers[enumerate_latest_CID-1].C_ID == newCustomer.C_ID)
    {
        printf("New customer has successfully added into the customers array");
    }
    printf("New customer has NOT added into the customers array");
    return -1;
}
int addBookTOBooks(struct Book newBook)
{
    Customers[enumerate_latest_BID-1].C_ID = newBook.B_ID;
    strcpy(Customers[enumerate_latest_BID-1].Name, newBook.Name);
    strcpy(Customers[enumerate_latest_BID-1].Surname, newBook.Author);
    Customers[enumerate_latest_BID-1].Age = newBook.AgeLimit;
    Customers[enumerate_latest_BID-1].Wallet = newBook.PricePerWeek;
    if(Customers[enumerate_latest_BID-1].C_ID == newBook.B_ID)
    {
        printf("New book has successfully added into the customers array");
    }
    printf("New book has NOT added into the customers array");
    return -1;
}
void setCID(struct Customer newCustomer)
{
    enumerate_latest_CID = lineCounter();
    if(enumerate_latest_CID <= sizeof Customers)
    {
        newCustomer.C_ID = enumerate_latest_CID;
        addCustomerTOCustomers(newCustomer);
    }
    else
    {
        perror("YOU REACHED THE LIMIT! CANNOT ADD MORE THAN 150 CUSTOMERS!");
    }
}
void setBID(struct Book newBook)
{
    enumerate_latest_CID = lineCounter();
    if(enumerate_latest_CID <= sizeof Customers)
    {
        newBook.B_ID = enumerate_latest_CID;
        addBookTOBooks(newBook);
    }
    else
    {
        perror("YOU REACHED THE LIMIT! CANNOT ADD MORE THAN 150 CUSTOMERS!");
    }
}
//Saves the buffer input data of Customers into machine-readable format (line-each-data)
int saveBufferCustomerData(struct Customer newCustomerBufferData)
{
    //Checking whether the file exists for read mode
    FILE* readCustomersBufferDataFile = fopen("CustomersBufferData.txt", "r");
    if(!readCustomersBufferDataFile) {
        //if not, creating CustomersBufferData.txt file
        FILE* writeCustomersBufferDataFile = fopen("CustomersBufferData.txt", "w");
        fclose(writeCustomersBufferDataFile);
    }
    FILE* customersBufferDataFile = fopen("CustomersBufferData.txt", "a");
    if(!customersBufferDataFile) {
        perror("File opening failed");
        fopen("CustomersBufferData.txt", "w");
        return EXIT_FAILURE;
    }
    fprintf(customersBufferDataFile, "%d\n"
                                     "%s\n"
                                     "%s\n"
                                     "%d\n"
                                     "%d\n",
            newCustomerBufferData.C_ID,
            newCustomerBufferData.Name,
            newCustomerBufferData.Surname,
            newCustomerBufferData.Age,
            newCustomerBufferData.Wallet);
    fclose(customersBufferDataFile);
    return 0;
}

//! Filedan arraye koyma işini çözersen bunu kullabilirsin -> şimdilik program tek oturum için istenilen sonucu veriyor.
int toCustomersArray()
{
    FILE* readCustomersBufferDataFile = fopen("CustomersBufferData.txt", "r");
    if(!readCustomersBufferDataFile) {
        //if not, creating CustomersBufferData.txt file
        FILE* writeCustomersBufferDataFile = fopen("CustomersBufferData.txt", "w");
        fclose(writeCustomersBufferDataFile);
    }
    FILE* customersBufferDataFile = fopen("CustomersBufferData.txt", "a");
    fclose(customersBufferDataFile);
    return 0;
}

//Creates a new customer
int newCustomer(char _name[25], char _surname[25], int _age, int _wallet)
{
    //Creating a new Customer and passing the parameters, taken from the user, into it
    int _customerID = lineCounter();
    struct Customer newCustomer;
    newCustomer.C_ID = _customerID;
    strcpy(newCustomer.Name, _name);
    strcpy(newCustomer.Surname,_surname);
    newCustomer.Age = _age;
    newCustomer.Wallet = _wallet;
    //Adding the customer created recently to the Customers list for listing
    setCID(newCustomer);
    //Saving the customer buffer data which will be later saved into a array of structs
    saveBufferCustomerData(newCustomer);
    //Appending the Customers.txt to put the Customers information line by line.
    FILE* customersFile = fopen("Customers.txt", "a");
    if(!customersFile) {
        perror("File opening failed");
        fopen("Customers.txt", "w");
        return EXIT_FAILURE;
    }
    //Writing Customer Data for its listing
    fprintf(customersFile, "Customer ID #%d |"
                "Customer Name: %s |"
                "Customer Surname: %s |"
                "Customer Age: %d |"
                "Customer Wallet: %d\n",
            newCustomer.C_ID,
            newCustomer.Name,
            newCustomer.Surname,
            newCustomer.Age,
            newCustomer.Wallet);
    fclose(customersFile);
    return 0;
}
int lineCounterForBook()
{
    // count the number of lines in the file called filename
    FILE *booksFile = fopen("books.txt", "r");
    int ch=0;
    int lines=0;
    lines++;
    while ((ch = fgetc(booksFile)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    fclose(booksFile);
    return lines;
}
//creating a new book
int newBook(char _name[25], char _authorName[25], int _ageLimit, int _pricePerWeek,bool _isRented)
{
    //Creating a new Customer and passing the parameters, taken from the user, into it
    int _bookID = lineCounterForBook();
    struct Book newBook;
    newBook.B_ID = _bookID;
    strcpy(newBook.Name, _name);
    strcpy(newBook.Author, _authorName);
    newBook.AgeLimit = _ageLimit;
    newBook.PricePerWeek = _pricePerWeek;
    newBook.Rented = _isRented;
    //Adding the customer created recently to the Customers list for listing
    setBID(newBook);
    //Saving the customer buffer data which will be later saved into a array of structs
    //!saveBufferCustomerData(newBook);
    //Appending the Customers.txt to put the Customers information line by line.
    FILE* booksFile = fopen("books.txt", "a");
    if(!booksFile) {
        perror("File opening failed");
        fopen("books.txt", "w");
        return EXIT_FAILURE;
    }
    //Writing Customer Data for its listing
    fprintf(booksFile, "Book ID #%d |"
                           "Book Name: %s |"
                           "Author Name: %s |"
                           "Age Limit: %d |"
                           "Rent: %d\n",
            newBook.B_ID,
            newBook.Name,
            newBook.Author,
            newBook.AgeLimit,
            newBook.PricePerWeek,
            newBook.Rented);
    fclose(booksFile);
    return 0;
}
//Selects the customer by ID and transfers the input deposit into the specified customer's account
int depositMoney()
{
    int _customerID, _deposit;
    printf("Deposit destination Customer ID:\n");
    scanf("%d", &_customerID);
    printf("Quantity of the deposit:\n");
    scanf("%d", &_deposit);

    for(int _cid = 0; _cid < sizeof Customers; _cid++)
    {
       if(Customers[_cid].C_ID == _customerID)
       {
           Customers[_cid].Wallet = Customers[_cid].Wallet + _deposit;
           return 0;
       }
    }
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

void updateBook(char _name[25], char _author[25],  int _ageLimit,  int _pricePerWeek)
{

}

void listCustomersRentedBook()
{

}

int listCustomers()
{
//    printf("List of our precious customers\n");
//    //Writing every element of the Customers array into the Customers.txt
//    FILE* customersFile = fopen("Customers.txt", "r");
//    if(!customersFile) {
//        perror("Customers.txt file opening failed");
//        return EXIT_FAILURE;
//    }
//    char c;
//    c = fgetc(customersFile);
//    while (c != EOF)
//    {
//        printf ("%c", c);
//        c = fgetc(customersFile);
//    }
//    fclose(customersFile);
    toCustomersArray();
    printCustomersArray();
    return 0;
}

void listBooks()
{
    //read later from the book file
    printBooksArray();
}
int getBookInput()
{
    //Processing the option
    bool isBook = false;
    //A control element, bool, to stop asking for the information from the
    while(!isBook)
    {
        //Getting a name from the user
        printf("Enter the book name:\n");
        char _name[25];
        scanf("%s", _name);
        //Getting a surname from the user
        printf("Enter the author name:\n");
        char _authorName[25];
        scanf("%s", _authorName);
        printf("Enter the age limit:\n");
        int _ageLimit;
        scanf("%d", &_ageLimit);
        printf("Enter the price per week:\n");
        int _pricePerWeek;
        scanf("%d", &_pricePerWeek);
        //Books are not rented initially.
        bool _isRented = false;
        //Checking for the name and author name whether they are in the books list
        for (int i = 0; i < sizeof Customers; i++)
        {
            if (Books[i].Name == _name || Books[i].Author == _authorName)
            {
                perror("The book already exits!");
                return -1;
            } else{
                isBook = true;
                //Passing the user input into list by newBook method
                newBook(_name,
                        _authorName,
                        _ageLimit,
                        _pricePerWeek,
                        _isRented);
                return -1;
                //The loop, asking for the user information, ends due to the valid information
            }
        }
    }
}
//Enumerates Customer IDs -> static variable to create unique IDs
static int C_ID_ENUMERATION = 1;
int getCustomerInput()
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
                newCustomer(_name,
                            _surname,
                            _age,
                            _wallet);
                return -1;
                //The loop, asking for the user information, ends due to the valid information
            }
        }
    }
}


int runProgram()
{
    //CREATING REQUIRED FILES AT THE BEGINNING OF THE PROGRAM
    //********************************************************************//
    FILE* readCustomersFile = fopen("Customers.txt", "r");
    //Checking whether the file exists for read mode
    if(!readCustomersFile) {
        //if not, creating Customers.txt file
        FILE* writeCustomersFile = fopen("Customers.txt", "w");
        fclose(writeCustomersFile);
    }
    // Now reading the file created recently
    FILE* customersFile = fopen("Customers.txt", "r");
    //********************************************************************//
    FILE* readBooksFile = fopen("books.txt", "r");
    //Checking whether the file exists for read mode
    if(!readBooksFile) {
        //if not, creating Customers.txt file
        FILE* writeBookssFile = fopen("books.txt", "w");
        fclose(writeBookssFile);
    }
    // Now reading the file created recently
    FILE* booksFile = fopen("books.txt", "r");
    //Looping the program
    //Looping the program
    //********************************************************************//
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
                fclose(customersFile);
                printf("You exit Booking System program. See you again");
                return -1;
            case 1:
                lineCounter();
                getCustomerInput();
                fclose(customersFile);
                break;
            case 2:
                depositMoney();
                fclose(customersFile);
                break;
            case 3:
                getBookInput();
                fclose(booksFile);
                break;
            case 4:
                fclose(customersFile);
                fclose(booksFile);
                break;
            case 5:
                fclose(customersFile);
                fclose(booksFile);
                break;
            case 6:
                fclose(customersFile);
                fclose(booksFile);
                break;
            case 7:
                fclose(customersFile);
                break;
            case 8:
                fclose(customersFile);
                break;
            case 9:
                fclose(customersFile);
                break;
            case 10:
                listCustomers();
                fclose(customersFile);
                break;
            case 11:
                listBooks();
                fclose(booksFile);
                break;
            default:
                perror("Invalid Input!");
                return -1;
        }

    }

}

//Entry-point of Booking System program
int main()
{
    runProgram();
    return 0;
}