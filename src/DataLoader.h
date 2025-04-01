#ifndef DATALOADER_H
#define DATALOADER_H

#include <vector>
#include "Customer.h"
#include "Provider.h"
#include "Service.h"
#include "Bill.h"
#include <sqlite3.h>

    void loadServicesForAllCustomers(std::vector<Customer>& customers, const char* dbPath);
    void loadBillsForAllCustomers(std::vector<Customer>& customers, const char* dbPath);
    void loadServicesForAllProviders(std::vector<Provider>& providers, const char* dbPath);

#endif
