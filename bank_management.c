#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

int account_count = 0;
FILE *fp;
sqlite3 *db;

struct bank_management
{

    int account_number;
    char account_holder_name[100];
    float balance;
};

void createAccount()
{
    char name[100];
    printf("Enter account holder's name: ");
    scanf(" %[^\n]", name);

    const char *sql = "INSERT INTO accounts (account_holder_name, balance) VALUES (?, 0.0);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        printf("Account created successfully!\n");
    }
    else
    {
        printf("Failed to create account: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

void displayAll()
{
    printf("Displaying all accounts...\n");
    const char *sql = "SELECT * FROM accounts";
    sqlite3_stmt *stmt;
    int done = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int acc_num = sqlite3_column_int(stmt, 0);                // account_number
        const unsigned char *name = sqlite3_column_text(stmt, 1); // name
        double balance = sqlite3_column_double(stmt, 2);          // balance

        printf("Acc No: %d, Name: %s, Balance: %.2f\n", acc_num, name, balance);
    }
    sqlite3_finalize(stmt);
}

void searchAccount()
{

    printf("please enter your account number: ");
    int accountnumber = 0;
    scanf("%d", &accountnumber);

    char sql[200];

    sprintf(sql, "SELECT * FROM accounts WHERE account_number = %d;", accountnumber);

    // printf("SQL Query: %s\n", sql);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Execute and print the result
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int acc_no = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        int balance = sqlite3_column_int(stmt, 2);

        printf("Account Number: %d\n", acc_no);
        printf("Name: %s\n", name);
        printf("Balance: %d\n", balance);
    }
}

void depositAmount()
{

    printf("Enter account number");
    int accountnumber = 0;
    scanf("%d", &accountnumber);
    char sql[200];

    sprintf(sql, "SELECT * FROM accounts WHERE account_number = %d;", accountnumber);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    int acc_no = 0;
    const unsigned char *name;
    int balance = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        acc_no = sqlite3_column_int(stmt, 0);
        name = sqlite3_column_text(stmt, 1);
        balance = sqlite3_column_int(stmt, 2);
    }
    else
    {
        printf("Account not found!\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);

    int depositAmount = 0;
    printf("Enter the ammount you want to deposite");
    scanf("%d", &depositAmount);
    int newBalance = balance + depositAmount;
    sprintf(sql, "UPDATE accounts SET balance = %d WHERE account_number = %d;", newBalance, accountnumber);

    char *errMsg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("Failed to update balance: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    else
    {
        printf("Deposit successful. New balance: %d\n", newBalance);
    }
}

void withdrawAmount()
{

    printf("Withdrawing amount...\n");

    printf("Enter account number");
    int accountnumber = 0;
    scanf("%d", &accountnumber);
    char sql[200];

    sprintf(sql, "SELECT * FROM accounts WHERE account_number = %d;", accountnumber);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    int acc_no = 0;
    const unsigned char *name;
    int balance = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        acc_no = sqlite3_column_int(stmt, 0);
        name = sqlite3_column_text(stmt, 1);
        balance = sqlite3_column_int(stmt, 2);
    }
    else
    {
        printf("Account not found!\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);

    int withdrawAmount = 0;
    printf("Enter the ammount you want to withdraw");
    scanf("%d", &withdrawAmount);

    if (balance < withdrawAmount)
    {

        printf("not enogh money in your account");
    }
    else
    {
        int newBalance = balance - withdrawAmount;
        sprintf(sql, "UPDATE accounts SET balance = %d WHERE account_number = %d;", newBalance, accountnumber);

        char *errMsg = 0;
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK)
        {
            printf("Failed to update balance: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
        else
        {
            printf("withdraw successful. New balance: %d\n", newBalance);
        }
    }
}

void deleteAccount()
{
    printf("Deleting an account...\n");

    printf("enter the account number you want to deleat");
    int accountnumber = 0;
    scanf("%d", &accountnumber);
    char sql[200];

    sprintf(sql, "DELETE FROM accounts WHERE account_number = %d;", accountnumber);
    sqlite3_stmt *stmt;
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("Failed to update balance: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    else
    {
        printf("Your account is sucssesfuly deleted");
    }
}

void updateAccount()
{
    printf("Enter the account number you want to update: ");
    int accountnumber = 0;
    scanf("%d", &accountnumber);

    // Check if account exists
    char selectSQL[200];
    sprintf(selectSQL, "SELECT * FROM accounts WHERE account_number = %d;", accountnumber);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK || sqlite3_step(stmt) != SQLITE_ROW)
    {
        printf("Account not found!\n");
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    // Ask new name
    char newName[100];
    printf("Enter new name for account: ");
    scanf(" %[^\n]", newName); // Read string with spaces

    // Update query
    char updateSQL[300];
    sprintf(updateSQL, "UPDATE accounts SET account_holder_name = '%s' WHERE account_number = %d;", newName, accountnumber);

    char *errMsg = 0;
    rc = sqlite3_exec(db, updateSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("Failed to update account: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    else
    {
        printf("Account updated successfully.\n");
    }
}

int main()
{
    printf("Welcome to the Bank Management System\n");

    if (sqlite3_open("bank.db", &db))
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_query =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "account_number INTEGER PRIMARY KEY AUTOINCREMENT,"
        "account_holder_name TEXT NOT NULL,"
        "balance REAL DEFAULT 0.0);";

    char *errMsg = 0;
    if (sqlite3_exec(db, create_table_query, 0, 0, &errMsg) != SQLITE_OK)
    {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    while (1)
    {

        int choice = 0;
        printf("Enter your choice \n 1 for createAccount \n 2 for displayAll \n 3 for searchAccount \n 4 for depositAmount \n 5 for withdrawAmount\n 6 for deleteAccount\n 7 for updateAccount \n 8 for exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            displayAll();
            break;

        case 3:
            searchAccount();
            break;

        case 4:
            depositAmount();
            break;

        case 5:
            withdrawAmount();
            break;

        case 6:
            deleteAccount();
            break;

        case 7:
            updateAccount();
            break;

        case 8:
            printf("exiting...................\n");
            sqlite3_close(db);
            exit(0);
            break;

        default:

            printf("Invalid choice");
            break;
        }
    }

    return 0;
}