#include "DataLoader.h"
#include "populateService.h"
#include "populateBill.h"
#include <vector>
#include <iostream>
#include <random>

int getRandomNumber(int min, int max) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<int> distr(min, max); // Define the range

    return distr(gen); // Generate a random number
}

void loadServicesForAllCustomers(std::vector<Customer>& customers, const char* dbPath) {  // must call before adding bills
    
    std::vector<Service> services = loadAllServices("newfile.db");
    std::size_t size = services.size();
    for (Customer& customer : customers) {
        int i = getRandomNumber(1,4);
        for (int j = 0; j < i; j++){
            int k = getRandomNumber(0,size-1);
            customer.addService(services[k]);
        }
    }
}

void loadBillsForAllCustomers(std::vector<Customer>& customers, const char* dbPath) {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    for (Customer& customer : customers) {
        std::string sql = "SELECT b.bill_id, b.service_id, b.provider_id, b.status, "
                         "b.used, b.issue_date, b.due_date, b.payment_date "
                         "FROM bills b "
                         "WHERE b.customer_id = " + customer.getAccountNumber() + ";";

        auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
            Customer* customer = static_cast<Customer*>(data);
            int size = customer->numServices();
            ///////////////// working here rn

            for (int i = 0; i < size; i++){
                if (customer->changeService(i).getServiceId() == std::stoi(argv[1])){
                    customer->changeService(i).setUnitsUsed(std::stoi(argv[4]));
                    Bill bill(customer->getServicesByReference());
                    bill.setServiceId(std::stoi(argv[1]));
                    bill.setStatus(argv[3]);
                    customer->addBill(bill);
                    break;
                }
            }

            /*
            Bill bill;

            bill.setBillId(std::stoi(argv[0]));
            bill.setServiceId(std::stoi(argv[1]));
            //bill.setProviderId(std::stoi(argv[2]));
            bill.setStatus(argv[3]);
            //bill.setUnitsUsed(std::stoi(argv[4]));    //change to altering the Service Item
            bill.setIssueDate(argv[5]);
            bill.setDueDate(argv[6]);
            if (argv[7]) { // payment_date might be NULL
                bill.setPaymentDate(argv[7]);
            }
            for (int i =0; i < customer->numServices(); i++){                // adds units used to service objects
                if (customer->changeService(i).getServiceId == std::stoi(argv[1])){
                    customer->changeService(i).setUnitsUsed(std::stoi(argv[4]));
                }
            }
            */
            return 0;
        };

        if (sqlite3_exec(db, sql.c_str(), callback, &customer, &errMsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(db);
}

void loadServicesForAllProviders(std::vector<Provider>& providers, const char* dbPath) {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    for (Provider& provider : providers) {
        std::string sql = "SELECT service_id, service_super_category, service_sub_category, "
                         "flat_rate, variable_rate FROM services WHERE name = '" + 
                         provider.getName() + "';";

        auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
            Provider* provider = static_cast<Provider*>(data);
            Service service(argv[1], argv[2], std::stod(argv[3]), std::stod(argv[4]));

            service.setServiceId(std::stoi(argv[0]));
            service.setProviderName(provider->getName());

            provider->addService(service);
            return 0;
        };

        if (sqlite3_exec(db, sql.c_str(), callback, &provider, &errMsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(db);
}
