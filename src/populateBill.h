#ifndef BILLDATALOADER_H
#define BILLDATALOADER_H

#include <vector>
#include <sqlite3.h>
#include "Bill.h"

class BillDataLoader {
public:
    static std::vector<Bill> loadAllBills(const char* dbPath);
};

#endif
