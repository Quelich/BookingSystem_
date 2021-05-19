#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma region Structures
//Stores the information of Book object
struct Book
{
    int B_ID;
    char Name[25];
    char Author[25];
    int AgeLimit;
    int PricePerWeek;
    int Rented;
};
//Stores the information of Rented object
struct Rented
{
    int R_ID;
    int C_ID;
    int B_ID;
    int Date;
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
static struct Book Books[150];
//Stores the information all Rented and saves the information into RentedBooks list
static struct Rented RentedBooks[150];
#pragma endregion Lists of the data

#pragma region Functions For Array Operations
//Counting line in order to indicate the current customer's ID

//Counting all the lines in the specified file
int countAll(char fileName[25])
{
    FILE *customersFile = fopen(fileName, "r");;
    int countAll = 0;
    char chr;
    chr = getc(customersFile);
    while (chr != EOF)
    {
        if (chr == '\n')
        {
            countAll = countAll + 1;
        }
        chr = getc(customersFile);
    }
    fclose(customersFile);
    return countAll;
}

#pragma endregion Functions For Array Operations

#pragma region Booking System functions
//Prints the content of given array

int toCustomersArray() {
    FILE *customersBufferDataFile = fopen("CustomersBufferData.txt", "r");
    int lineCounter = countAll("CustomersBufferData.txt");
    int counter = 0;
    int end, loop;
    char str[216] = "";
    for (int line = 1; line <= lineCounter + 1; ++line) {
        for (end = loop = 0; loop < line; ++loop) {
            counter++;
            if (0 == fgets(str, sizeof str, customersBufferDataFile)) {
                EXIT_FAILURE;
                break;
            }
            if (!end) {
                char *pch;
                pch = strtok(str, "|");
                int reset = 0;
                while (pch != NULL) {
                    if (reset == 0) {
                        Customers[counter].C_ID = atoi(pch);
                    }
                    if (reset == 1) {

                        strcpy(Customers[counter].Name, pch);

                    }
                    if (reset == 2) {

                        strcpy(Customers[counter].Surname, pch);

                    }
                    if (reset == 3) {

                        Customers[counter].Age = atoi(pch);

                    }
                    if (reset == 4) {

                        Customers[counter].Wallet = atoi(pch);
                    }
                    reset++;
                    pch = strtok(NULL, "|");
                }
            }
        }
    }
    fclose(customersBufferDataFile);
    return 0;
}
int toRentedArray()
{
    FILE *rentedDataFile = fopen("rented.txt", "r");
    int lineCounter = countAll("rented.txt");
    int counter = 0;
    int end, loop;
    char str[216] = "";
    for (int line = 1; line <= lineCounter + 1; ++line) {
        for (end = loop = 0; loop < line; ++loop) {
            counter++;
            if (0 == fgets(str, sizeof str, rentedDataFile)) {
                EXIT_FAILURE;
                break;
            }
            if (!end) {
                char *pch;
                pch = strtok(str, "|");
                int reset = 0;
                while (pch != NULL) {
                    if (reset == 0) {
                        RentedBooks[counter].R_ID = atoi(pch);
                    }
                    if (reset == 1) {
                        RentedBooks[counter].C_ID = atoi(pch);
                    }
                    if (reset == 2) {
                        RentedBooks[counter].B_ID = atoi(pch);
                    }
                    if (reset == 3) {
                        RentedBooks[counter].Date = atoi(pch);
                    }
                    reset++;
                    pch = strtok(NULL, "|");
                }
            }
        }
    }
    fclose(rentedDataFile);
    return 0;
}
int toBooksArray()
{
    FILE *booksBufferDataFile = fopen("BooksBufferData.txt", "r");
    int lineCounter = countAll("BooksBufferData.txt");
    int counter = 0;
    int end, loop;
    char str[216] = "";
    for (int line = 1; line <= lineCounter + 1; ++line) {
        for (end = loop = 0; loop < line; ++loop) {
            counter++;
            if (0 == fgets(str, sizeof str, booksBufferDataFile)) {
                EXIT_FAILURE;
                break;
            }
            if (!end) {
                char *pch;
                pch = strtok(str, "|");
                int reset = 0;
                while (pch != NULL) {
                    //! SWITCH
                    if (reset == 0) {
                        Books[counter].B_ID = atoi(pch);
                    }
                    if (reset == 1) {

                        strcpy(Books[counter].Name, pch);

                    }
                    if (reset == 2) {

                        strcpy(Books[counter].Author, pch);

                    }
                    if (reset == 3) {

                        Books[counter].AgeLimit = atoi(pch);

                    }
                    if (reset == 4) {

                        Books[counter].PricePerWeek = atoi(pch);
                    }
                    if(reset == 5)
                    {
                        Books[counter].Rented = atoi(pch);
                    }
                    reset++;
                    pch = strtok(NULL, "|");
                }
            }
            fclose(booksBufferDataFile);

        }

    }

    return 0;
}

//Selects the customer by ID and transfers the input deposit into the specified customer's account
int modifyCustomers(int _countLines, char _name[25], char _surname[25], int _age, int _wallet)
{
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
    fprintf(customersBufferDataFile, "%d|"
                                     "%s|"
                                     "%s|"
                                     "%d|"
                                     "%d\n",
            _countLines+1,
            _name,
            _surname,
            _age,
            _wallet);
    fclose(customersBufferDataFile);
    //Also saving to Customers.txt in order for listing1
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
            _countLines+1,
            _name,
            _surname,
            _age,
            _wallet);
    fclose(customersFile);
    return -1;
}
//Selects the book by ID and transfers the input deposit into the specified book
int modifyBooks(int _countLines,char _bookName[25], char _author[25], int _ageLimit, int _pricePerWeek, int _isRented)
{
    FILE* readBooksBufferDataFile = fopen("BooksBufferData.txt", "r");
    if(!readBooksBufferDataFile) {
        //if not, creating CustomersBufferData.txt file
        FILE* writeBooksBufferDataFile = fopen("BooksBufferData.txt", "w");
        fclose(writeBooksBufferDataFile);
    }
    FILE* booksBufferDataFile = fopen("BooksBufferData.txt", "a");
    if(!booksBufferDataFile) {
        perror("File opening failed");
        fopen("BooksBufferData.txt", "w");
        return EXIT_FAILURE;
    }
    fprintf(booksBufferDataFile,     "%d|"
                                     "%s|"
                                     "%s|"
                                     "%d|"
                                     "%d|"
                                     "%s\n",
            _countLines+1,
            _bookName,
            _author,
            _ageLimit,
            _pricePerWeek,
            _isRented == 1 ? "true": "false");
    fclose(booksBufferDataFile);FILE* booksFile = fopen("books.txt", "a");
    if(!booksFile) {
        perror("File opening failed");
        fopen("books.txt", "w");
        return EXIT_FAILURE;
    }
    //Writing Customer Data for its listing
    fprintf(booksFile,     "Book ID #%d |"
                           "Book Name: %s |"
                           "Book Author: %s |"
                           "Book Age Limit: %d |"
                           "Book Price per Week: %d|"
                           "Book Rented: %s\n",
            _countLines+1,
            _bookName,
            _author,
            _ageLimit,
            _pricePerWeek,
            _isRented == 1 ? "true" : "false");
    fclose(booksFile);
    return -1;
}
int modifyRentedBooks(int _countLines, int _cid, int _bid, int _rentDate, int _week)
{
    // if rented.txt is not present, a new one is immediately created!
    FILE* readRentedDataFile = fopen("rented.txt", "r");
    if(!readRentedDataFile) {
        //if not, creating CustomersBufferData.txt file
        FILE* writeBooksBufferDataFile = fopen("rented.txt", "w");
        fclose(writeBooksBufferDataFile);
    }
    //saving to rented.txt in order for listing
    FILE* appendRentedBookFile = fopen("rented.txt", "a");
    if(!appendRentedBookFile) {
        perror("File opening failed");
        fopen("rented.txt", "w");
        return EXIT_FAILURE;
    }
    fprintf(appendRentedBookFile,    "%d|"
                                     "%d|"
                                     "%d|"
                                     "%d|"
                                     "%d\n",
            _countLines+1,
            _cid,
            _bid,
            _rentDate,
            _week);
    fclose(appendRentedBookFile);
    return -1;
}
//Creates a new customer -- saves it into the Customers array as Customer struct elements
//also saves into Book struct because I cannot manipulate the string in Customers.txt to obtain data
//Therefore I created another file that gets the same data but saves it by "|" in order to save the data into Customers array
int newCustomer(char _name[25], char _surname[25], int _age, int _wallet)
{
    toCustomersArray(); //Initializing Customers.txt as array
    //Creating a new Customer and passing the parameters, taken from the user, into it
    int countLines = countAll("CustomersBufferData.txt");
    //Saving the customer into the array
    Customers[countLines+1].C_ID = countLines;
    strcpy( Customers[countLines+1].Name,_name);
    strcpy( Customers[countLines+1].Surname,_surname);
    Customers[countLines+1].Age = _age;
    Customers[countLines+1].Wallet = _wallet;
    //Saving the data after the operation
    modifyCustomers(countLines,_name,_surname,_age,_wallet);
    return 0;
}
//Creates a new book -- saves it into the Books array as Book struct elements
//also saves into Book Struct because I cannot manipulate the string in Customers.txt to obtain the required data
int newBook(char _bookName[25], char _author[25], int _ageLimit, int _pricePerWeek)
{
    toBooksArray();//Initializing books.txt array
    int countLines = countAll("BooksBufferData.txt");
    //Saving the book into the array
    Books[countLines+1].B_ID = countLines;
    strcpy( Books[countLines+1].Name,_bookName);
    strcpy( Books[countLines+1].Author,_author);
    Books[countLines+1].AgeLimit = _ageLimit;
    Books[countLines+1].PricePerWeek = _pricePerWeek;
    Books[countLines+1].Rented = 0;
    //Saving the data after the operation
    //Initially the book is not rented
    modifyBooks(countLines,_bookName,_author,_ageLimit,_pricePerWeek,0);
    return 0;
}
int newRented(int _cid, int _bid, int _rentDate, int _week)
{
    toRentedArray(); //Initializing rented.txt as array
    int countLines = countAll("rented.txt");
    //Saving the rented book into the array
    RentedBooks[countLines + 1].R_ID = countLines;
    RentedBooks[countLines + 1].C_ID = _cid;
    RentedBooks[countLines + 1].B_ID = _bid;
    RentedBooks[countLines + 1].Date = _rentDate;
    RentedBooks[countLines + 1].Week = _week;
    modifyRentedBooks(countLines,_cid,_bid,_rentDate,_week);
    return 0;
}
int depositMoney()
{
    toCustomersArray(); //Initializing the array
    int _customerID, _deposit, countLines = countAll("CustomersBufferData.txt"); ;
    printf("Deposit destination Customer ID:\n");
    scanf("%d", &_customerID);
    printf("Quantity of the deposit:\n");
    scanf("%d", &_deposit);
    Customers[_customerID].Wallet = Customers[_customerID].Wallet + _deposit;
    printf("Deposit has successfully transferred!");
    FILE *customersBufferData;
    customersBufferData = fopen("CustomersBufferData.txt", "w");
    for (int i = 1; i < countLines+1; ++i) {
        fprintf(customersBufferData, "%d|%s|%s|%d|%d\n", i, Customers[i].Name, Customers[i].Surname, Customers[i].Age,   Customers[i].Wallet);
    }
    fclose(customersBufferData);
    FILE *customersData;
    customersData = fopen("Customers.txt", "w");
    for (int i = 1; i < countLines+1; ++i) {
        fprintf(customersData, "Customer ID #%d |"
                               "Customer Name: %s |"
                               "Customer Surname: %s |"
                               "Customer Age: %d |"
                               "Customer Wallet: %d\n",
                i,
                Customers[i].Name,
                Customers[i].Surname,
                Customers[i].Age,
                Customers[i].Wallet);
    }
    fclose(customersData);
    return -1;
}
#define TEXTLIMIT 250
int listCustomers()
{
    toCustomersArray(); //Initializing the array
    FILE* readCustomersBufferDataFile = fopen("Customers.txt", "r");
    if(!readCustomersBufferDataFile) {
        perror("File opening failed");
        fopen("Customers.txt", "w");
        return EXIT_FAILURE;
    }
    char text[TEXTLIMIT];
    while (fgets(text, TEXTLIMIT, readCustomersBufferDataFile) != NULL)
        printf("%s", text);
    fclose(readCustomersBufferDataFile);
    return 0;
}
int listBooks()
{
    toBooksArray();
    FILE* readBooksBufferDataFile = fopen("books.txt", "r");
    if(!readBooksBufferDataFile) {
        perror("File opening failed");
        fopen("books.txt", "w");
        return EXIT_FAILURE;
    }
    char text[TEXTLIMIT];
    while (fgets(text, TEXTLIMIT, readBooksBufferDataFile) != NULL)
        printf("%s", text);
    fclose(readBooksBufferDataFile);
    return 0;
}
int listRentedBooks()
{
    toRentedArray();
    FILE* readRentedBooks = fopen("rented.txt", "r");
    if(!readRentedBooks) {
        perror("File opening failed");
        fopen("rented.txt", "w");
        return EXIT_FAILURE;
    }
    char text[TEXTLIMIT];
    while (fgets(text, TEXTLIMIT, readRentedBooks) != NULL)
        printf("%s", text);
    fclose(readRentedBooks);
    return 0;
}
//Enumerates Customer IDs -> static variable to create unique IDs
static int C_ID_ENUMERATION = 1;
int getCustomerInput()
{
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
    // Getting the data of customers from the CustomersBufferData.txt
    toCustomersArray();
    //Checking for the name and surname whether they are in the customers list
    int compareName = 1;
    int compareSurname;
    int customer = 1;
    bool hasInput = false;
    while(compareName == 1)
    {
        //using strcmp to detect whether the given name and surname exist
        compareName = strcmp(Customers[customer].Name,_name);
        compareSurname = strcmp(Customers[customer].Surname, _surname);
        if(compareName == 0)
        {
            hasInput = true;
            break;
        }
        if(compareSurname == 0)
        {
            hasInput = true;
            break;
        }
        customer++;
    }
    if(hasInput)
    {
        printf("[%s %s] already exists\n", _name, _surname);
        return -1;
    }
    else
    {
        newCustomer(_name,
                    _surname,
                    _age,
                    _wallet);
        printf("[%s %s] has been added into the database\n", _name, _surname);
    }
    return -1;
}
int getBookInput()
{
    printf("Enter the book name:\n'Example: journey_to_the_center_of_the_earth'\n");
    char _bookName[25];
    scanf("%s", _bookName);//using regular expressions to get also names with spaces
    //Getting a surname from the user
    printf("Enter the author name:\n'Example: Jules_Verne'\n");
    char _authorName[25];
    scanf("%s", _authorName);
    printf("Enter the Age Limit:\n");
    int _ageLimit;
    scanf("%d", &_ageLimit);
    printf("Enter the price of specified book per week:\n");
    int _pricePerWeek;
    scanf("%d", &_pricePerWeek);

    toBooksArray();
    //Checking for the name and surname whether they are in the customers list
    int compareName = 1;
    int compareAuthor;
    int book = 1;
    bool hasInput = false;
    while(compareName == 1)
    {
        //using strcmp to detect whether the given name and surname exist
        compareName = strcmp(Books[book].Name, _bookName);
        compareAuthor = strcmp(Books[book].Author, _authorName);
        if(compareName == 0)
        {
            hasInput = true;
            break;
        }
        if(compareAuthor == 0)
        {
            hasInput = true;
            break;
        }
        book++;
    }
    if(hasInput)
    {
        printf("[%s written by %s] already exists\n", _bookName, _authorName);
        return -1;
    }
    //Initial _isRented value of books are set to false due to the concerns on optimization
    newBook(_bookName,
            _authorName,
            _ageLimit,
            _pricePerWeek);
    printf("[%s written by %s] has been added into the database\n", _bookName, _authorName);
    return -1;
}
//Getting the current date to be compared with - I just compare the days because the books are rented weekly
//!SO I DO NOT GET WEEK NUMBERS
int getDate()
{
    time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    return current_time->tm_mday;
}
//Gets the information of the book that the customer desires to rent
//And sends to the rent book to process the data and complete the operations
int getRentedInput()
{
    printf("What's your Customer ID:\n");
    int _cid;
    scanf("%d", &_cid);
    printf("Enter the book ID you want to rent:\n");
    int _bid;
    scanf("%d", &_bid);
    printf("Enter the week duration that you will be using?\n");
    int _periodWeek;
    scanf("%d", &_periodWeek);
    //Checking if the restrictions occur for the specified book.
    toBooksArray();
    toCustomersArray();
    toRentedArray();
    if(Books[_bid].Rented == 1)
    {
        perror("The book is already rented!\n");
        return -1;
    }
    if(Customers[_cid].Wallet < Books[_bid].PricePerWeek * _periodWeek)
    {
        perror("You do not have sufficient credits to rent this book!\n");
        return -1;
    }
    if(Books[_bid].AgeLimit >= Customers[_cid].Age)
    {
        perror("You are not allowed to access this book content!\n");
        return -1;
    }
    //If the given information passes the test, the rented book will be saved into the database
    //The customer's wallet will be updated
    //The book's "isRented" value will be updated
    //Getting the current day to compare with the

    /**Updating customers.txt and CustomersBufferData.txt**/
    toCustomersArray();
    Customers[_cid].Wallet =  Customers[_cid].Wallet - (Books[_bid].PricePerWeek * _periodWeek);
    int countLinesCustomerBuffer = countAll("CustomersBufferData.txt");
    FILE *customersBufferData = fopen("CustomersBufferData.txt", "w");
    for (int i = 1; i < countLinesCustomerBuffer+1; ++i) {
        fprintf(customersBufferData, "%d|%s|%s|%d|%d\n", i, Customers[i].Name, Customers[i].Surname, Customers[i].Age,   Customers[i].Wallet);
    }
    fclose(customersBufferData);
    FILE *customersData;
    customersData = fopen("Customers.txt", "w");
    for (int i = 1; i < countLinesCustomerBuffer+1; ++i) {
        fprintf(customersData, "Customer ID #%d |"
                               "Customer Name: %s |"
                               "Customer Surname: %s |"
                               "Customer Age: %d |"
                               "Customer Wallet: %d\n",
                i,
                Customers[i].Name,
                Customers[i].Surname,
                Customers[i].Age,
                Customers[i].Wallet);
    }
    fclose(customersData);
    /**Updating customers.txt and CustomersBufferData.txt**/

    /**Updating books.txt and BooksBufferData.txt**/
    toBooksArray();
    Books[_bid].Rented = 1;
    int countLinesBookBuffer = countAll("BooksBufferData.txt");
    FILE *booksBufferData = fopen("BooksBufferData.txt", "w");
    for (int i = 1; i < countLinesBookBuffer+1; ++i) {
        fprintf(booksBufferData, "%d|%s|%s|%d|%d|%d\n", i, Books[i].Name, Books[i].Author, Books[i].AgeLimit,   Books[i].PricePerWeek,Books[i].Rented);
    }
    fclose(booksBufferData);
    FILE *booksData = fopen("books.txt", "w");

    for (int i = 1; i < countLinesBookBuffer+1; ++i) {

        fprintf(booksData,      "Book ID #%d |"
                                "Book Name: %s |"
                                "Book Author: %s |"
                                "Book Age Limit: %d |"
                                "Book Price per Week: %d|"
                                "Book Rented: %s\n",
                i,
                Books[i].Name,
                Books[i].Author,
                Books[i].AgeLimit,
                Books[i].PricePerWeek,
                Books[i].Rented == 1 ? "true" : "false");
    }
    fclose(booksData);
    /**Updating books.txt and BooksBufferData.txt**/

    /***Updating rented.txt***/
    int _rentedDate = getDate(); //as days
    //Created a new rented book entry
    newRented(_cid,
              _bid,
              _rentedDate,
              _periodWeek);
    printf("The book %s has successfully rented by %s %s\n", Books[_bid].Name,Customers[_cid].Name, Customers[_cid].Surname);
    /***Updating rented.txt***/
    return -1;
}

int runProgram() {
    /**CREATING REQUIRED FILES AT THE BEGINNING OF THE PROGRAM**/
    //********************************************************************//
    FILE *readCustomersFile = fopen("Customers.txt", "r");
    //Checking whether the file exists for read mode
    if (!readCustomersFile) {
        //if not, creating Customers.txt file
        FILE *writeCustomersFile = fopen("Customers.txt", "w");
        fclose(writeCustomersFile);
    }
    // Now reading the file created recently
    FILE *customersFile = fopen("Customers.txt", "r");
    //********************************************************************//
    FILE *readBooksFile = fopen("books.txt", "r");
    //Checking whether the file exists for read mode
    if (!readBooksFile) {
        //if not, creating Customers.txt file
        FILE *writeCustomersFile = fopen("books.txt", "w");
        fclose(writeCustomersFile);
    }
    // Now reading the file created recently
    FILE *booksFile = fopen("books.txt", "r");
    //********************************************************************//
    FILE *readRentedFile = fopen("rented.txt", "r");
    //Checking whether the file exists for read mode
    if (!readRentedFile) {
        //if not, creating Customers.txt file
        FILE *writeRentedFile = fopen("rented.txt", "w");
        fclose(writeRentedFile);
    }
    // Now reading the file created recently
    //********************************************************************//
    /**CREATING REQUIRED FILES AT THE BEGINNING OF THE PROGRAM**/
    bool isExit = false;
    while (!isExit) {
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
                fclose(booksFile);
                printf("You exit Booking System program. See you again\n");
                return -1;
            case 1:
                getCustomerInput();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                getBookInput();
                break;
            case 4:
                getRentedInput();
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
                listRentedBooks();
                break;
            case 10:
                listCustomers();
                break;
            case 11:
                listBooks();
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