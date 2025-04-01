#ifndef POPULATEBILL_H
#define POPULATEBILL_H

#include <vector>
#include <sqlite3.h>
#include "Bill.h"

    std::vector<Bill> loadAllBills(const char* dbPath);


#endif
