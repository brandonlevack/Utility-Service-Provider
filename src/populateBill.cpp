#include "populateBill.h"
#include <iostream>

std::vector<Bill> loadAllBills(const char* dbPath) {
    std::vector<Bill> bills;
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return bills;
    }

    std::string sql = "SELECT bill_id, customer_id, service_id, provider_id, "
                     "status, used, issue_date, due_date, payment_date "
                     "FROM bills;";

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        std::vector<Bill>* bills = static_cast<std::vector<Bill>*>(data);
        Bill bill;
        
        bill.setBillId(std::stoi(argv[0]));
        bill.setCustomerId(std::stoi(argv[1]));
        bill.setServiceId(std::stoi(argv[2]));
        bill.setStatus(argv[4]);
        bill.setIssueDate(argv[6]);
        bill.setDueDate(argv[7]);
        
        bills->push_back(bill);
        return 0;
    };

    if (sqlite3_exec(db, sql.c_str(), callback, &bills, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return bills;
}
