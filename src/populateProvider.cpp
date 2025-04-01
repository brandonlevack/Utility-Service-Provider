#include "populateProvider.h"
#include <sqlite3.h>
#include <iostream>
  
static int providerCallback(void* data, int argc, char** argv, char** azColName) {
    std::vector<Provider>* providers = static_cast<std::vector<Provider>*>(data);
    Provider provider;
    
    // Set name
    provider.setName(argv[1]);
    
    // Set phone number
    provider.setPhoneNumber(argv[2] ? argv[2] : "");
    
    // Set address
    provider.setStreetAddress(argv[3]);

    //add to vector
    providers->push_back(provider);
    return 0;
}

std::vector<Provider> populateProvider(const char* dbPath) {
    std::vector<Provider> providers;
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return providers;
    }

    const char* sql = "SELECT provider_id, name, phone_number, address FROM providers;";
    int rc = sqlite3_exec(db, sql, providerCallback, &providers, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return providers;
}

