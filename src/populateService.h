#ifndef POPULATESERVICE_H
#define POPULATESERVICE_H

#include <vector>
#include <sqlite3.h>
#include "Service.h"

    static std::vector<Service> loadAllServices(const char* dbPath);


#endif
