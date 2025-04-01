#ifndef SERVICEDATALOADER_H
#define SERVICEDATALOADER_H

#include <vector>
#include <sqlite3.h>
#include "Service.h"

class ServiceDataLoader {
public:
    static std::vector<Service> loadAllServices(const char* dbPath);
};

#endif
