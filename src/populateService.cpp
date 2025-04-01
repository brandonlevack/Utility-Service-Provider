#include "ServiceDataLoader.h"
#include <iostream>

std::vector<Service> ServiceDataLoader::loadAllServices(const char* dbPath) {
    std::vector<Service> services;
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return services;
    }

    std::string sql = "SELECT service_id, provider_name, service_super_category, "
                     "service_sub_category, flat_rate, variable_rate FROM services;";

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        std::vector<Service>* services = static_cast<std::vector<Service>*>(data);
        Service service;
        
        service.setServiceId(std::stoi(argv[0]));
        service.setProviderName(argv[1]);
        service.setServiceCategory(argv[2]);
        service.setServiceSubCategory(argv[3]);
        service.setFlatRate(std::stod(argv[4]));
        service.setVariableRate(std::stod(argv[5]));
        
        services->push_back(service);
        return 0;
    };

    if (sqlite3_exec(db, sql.c_str(), callback, &services, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return services;
}
