#include <iostream>
#include "src/Service.h"
#include "src/Customer.h"
#include "src/Provider.h"
#include "src/Bill.h"
#include "src/populateProvider.h"
#include "src/populateCustomer.h"
#include "src/DataLoader.h"

int main() {

    std::vector<Provider> providers = populateProvider("newfile.db");
    std::vector<Customer> customers = populateCustomer("newfile.db");

    loadServicesForAllProviders(providers, "newfile.db");
    loadServicesForAllCustomers(customers, "newfile.db");
    loadBillsForAllCustomers(customers, "newfile.db");

    for (Provider p : providers){
        std::cout << p;
    }

    std::cout << "\n\n\n";

    for (Customer c : customers){
        std::cout << c;
    }


}