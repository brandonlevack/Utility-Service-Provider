#ifndef POPULATESERVICE_H
#define POPULATESERVICE_H

#include <vector>
#include <sqlite3.h>
#include "Service.h"

std::vector<Service> loadAllServices(const char* dbPath);

#endif
