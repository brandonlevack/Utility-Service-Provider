#include "populateCustomer.h"
#include <iostream>
#include <sqlite3.h>

int customerCallback(void* data, int argc, char** argv, char** azColName) {
    std::vector<Customer>* customers = static_cast<std::vector<Customer>*>(data); //sets parameter *data to vector pointer
    Customer customer;

    //sets account#
    customer.setAccountNumber(argv[0]);
        
    //sets first and last name
    //splits fullname into first and last name
    std::string fullName = std::string(argv[1]);
    size_t spacePos = fullName.find(" ");
    if (spacePos != std::string::npos) {
        customer.setFirstName(fullName.substr(0, spacePos));
        customer.setLastName(fullName.substr(spacePos + 1));
    }

    //sets address
    customer.setStreetAddress(argv[2]);
    
    //adds customer to vector
    customers->push_back(customer);
    return 0;
}

std::vector<Customer> populateCustomer(const char* dbPath) {
    std::vector<Customer> customers;
    sqlite3* db;
    char* errMsg = nullptr;

    //open database coonection and check for error opening
    if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return customers;
    }

    //sql statement
    const char* sql = "SELECT customer_id, name, address, service FROM customers;";
    int rc = sqlite3_exec(db, sql, customerCallback, &customers, &errMsg);

    //sql statment execution error checking
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return customers;
}
