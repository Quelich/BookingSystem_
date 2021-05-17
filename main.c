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
void printCustomersArray()
{
    printf("######Our precious Customers######\n");
    for (int i = 0; i < 5; i++) {
        printf("Array Place:%d CID:%d Name:%s Surname:%s Age:%d Wallet:%d\n", i, Customers[i].C_ID,Customers[i].Name,Customers[i].Surname, Customers[i].Age,Customers[i].Wallet);
    }
}

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
//Creates a new customer -- saves it into the Customers array
//save is into the CustomersBufferData.txt because I cannot manipulate the string in Customers.txt to obtain data
//Therefore I created another file that gets the same data but saves it by "|" in order to save the data into Customers array
int newCustomer(char _name[25], char _surname[25], int _age, int _wallet)
{
    toCustomersArray(); //Initializing Customers.txt array
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
int listCustomers()
{
    toCustomersArray(); //Initializing the array
    printCustomersArray();
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
    //Checking for the name and surname whether they are in the customers list

    newCustomer(_name,
                _surname,
                _age,
                _wallet);
    return -1;
}

int runProgram() {
    //CREATING REQUIRED FILES AT THE BEGINNING OF THE PROGRAM
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
                printf("You exit Booking System program. See you again");
                return -1;
            case 1:
                getCustomerInput();
                break;
            case 2:
                depositMoney();
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