#ifndef DATALOADER_H
#define DATALOADER_H

#include <vector>
#include "Customer.h"
#include "Provider.h"
#include "Service.h"
#include "Bill.h"
#include <sqlite3.h>

    static void loadServicesForAll(std::vector<Customer>& customers, const char* dbPath);
    static void loadBillsForAll(std::vector<Customer>& customers, const char* dbPath);
    static void loadServicesForAllProviders(std::vector<Provider>& providers, const char* dbPath);

#endif
