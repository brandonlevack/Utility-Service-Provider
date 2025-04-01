#include <iostream>
#include "src/Service.h"
#include "src/Customer.h"
#include "src/Provider.h"
#include "src/Bill.h"
#include "src/populateProvider.h"
#include "src/populateCustomer.h"
#include "src/DataLoader.h"

int main() {

    std::vector<Provider> providers = populateProvider("src/newfile.db");
    std::vector<Customer> customers = populateCustomer("src/newfile.db");

    loadServicesForAllProviders(providers, "newfile.db");
    loadServicesForAllCustomers(customers, "newfile.db");
    loadBillsForAllCustomers(customers, "newfile.db");

    std::cout << providers[1];
    std::cout << customers[1];


}