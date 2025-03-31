#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>

class DatabasePopulator {
private:
    sqlite3* db;
    std::mt19937 gen{std::random_device{}()};

    const std::vector<std::string> providerNames = {
        "PowerCo", "GasWorks", "WaterCorp", "InternetPlus", "EnergyFirst",
        "UtilityPro", "ConnectAll", "EcoUtilities", "SmartPower", "CityServices"
    };

    const std::vector<std::pair<std::string, std::string>> services = {
        {"Hydro", "Electricity"}, {"Hydro", "Water"}, {"Hydro", "Sewerage"},
        {"Internet", "TV"}, {"Internet", "Cell Phone"}, {"Internet", "Home Phone"}, {"Natural Gas", ""}, {"Internet", ""}
    };

    const std::vector<std::string> customerNames = {
        "John Smith", "Mary Johnson", "James Williams", "Patricia Brown", "Robert Jones",
        "Michael Davis", "Linda Wilson", "David Moore", "Elizabeth Taylor", "Joseph Anderson",
        "Jennifer Thomas", "William Jackson", "Barbara White", "Richard Harris", "Susan Martin",
        "Charles Thompson", "Margaret Garcia", "Thomas Martinez", "Sandra Robinson", "Daniel Clark",
        "Nancy Rodriguez", "Paul Lewis", "Betty Lee", "Mark Walker", "Dorothy Hall",
        "George Allen", "Helen Young", "Kenneth King", "Ruth Wright", "Edward Scott",
        "Sharon Green", "Steven Baker", "Cynthia Nelson", "Kevin Hill", "Carol Adams",
        "Frank Mitchell", "Amy Phillips", "Roger Campbell", "Shirley Evans", "Howard Roberts",
        "Angela Turner", "Lawrence Collins", "Virginia Parker", "Eugene Edwards", "Catherine Stewart",
        "Gerald Morris", "Frances Rogers", "Dennis Reed", "Alice Cook", "Peter Morgan",
        "Joan Bennett", "Harry Murphy", "Ann Ross", "Philip Peterson", "Joyce Gray",
        "Ronald Sanders", "Gloria Long", "Larry Foster", "Rachel Alexander", "Stephen Price",
        "Martha Howard", "Bruce Butler", "Sharon Coleman", "Wayne Brooks", "Louise Jenkins",
        "Arthur Watson", "Lois Washington", "Roger Barnes", "Kelly Bryant", "Ralph Bailey",
        "Christina Griffin", "Terry Fisher", "Diane Russell", "Alan Diaz", "Phyllis Hayes",
        "Randy Ford", "Marilyn Reynolds", "Henry James", "Janice Simpson", "Johnny Hamilton",
        "Cheryl Stevens", "Jeremy Wallace", "Andrea Wells", "Keith Freeman", "Maria Gonzales",
        "Carl Webb", "Beverly Jordan", "Arthur Owens", "Theresa Fuller", "Ralph Woods",
        "Louise Carroll", "Dylan Graham", "Evelyn Sullivan", "Eugene Ellis", "Deborah Perry",
        "Gerald Powell", "Christina Rice", "Victor Robertson", "Pamela Hunt", "Walter Fox"
    };

    void executeSQL(const std::string& sql) {
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    std::string getDate(int monthsAgo) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&time);
        tm->tm_mon -= monthsAgo;
        mktime(tm);

        std::stringstream ss;
        ss << std::put_time(tm, "%Y-%m-%d");
        return ss.str();
    }

public:
    DatabasePopulator(const char* dbPath) {
        std::remove(dbPath);  // Delete existing database
        if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        std::ifstream schemaFile("newfile.sql");
        if (schemaFile) {
            std::string line;
            std::string currentStatement;
            while (std::getline(schemaFile, line)) {
                // Skip empty lines and comments
                if (line.empty() || line.substr(0, 2) == "--") continue;
                
                currentStatement += line + " ";
                
                // If we find a semicolon, execute the statement
                if (line.find(';') != std::string::npos) {
                    executeSQL(currentStatement);
                    currentStatement.clear();
                }
            }
        } else {
            std::cerr << "Could not open newfile.sql" << std::endl;
        }
    }

    void populateAll() {
        // Populate providers
        for (size_t i = 0; i < providerNames.size(); i++) {
            executeSQL("INSERT INTO providers (provider_id, name, phone_number, address) VALUES (" +
                std::to_string(i+1) + ", '" + providerNames[i] + "', '555-" + 
                std::to_string(1000 + i) + "', 'Address " + std::to_string(i) + "');");
        }

        // Populate customers
        for (size_t i = 0; i < customerNames.size(); i++) {
            executeSQL("INSERT INTO customers VALUES (" + std::to_string(i+1) + 
                ", '" + customerNames[i] + "', 'Address " + std::to_string(i) + "');");
        }

        // Populate services
        int serviceId = 1;
        for(const auto& provider : providerNames) {
            for(const auto& [category, subcategory] : services) {
                double flatRate, varRate;
                std::uniform_real_distribution<> flatDist(50.0, 100.0);

                if (category == "Hydro" && subcategory == "Electricity") {
                    std::uniform_real_distribution<> varDist(0.10, 0.15);
                    flatRate = flatDist(gen);
                    varRate = varDist(gen);
                }
                else if (category == "Hydro" && subcategory == "Water") {
                    std::uniform_real_distribution<> varDist(1.0, 2.0);
                    flatRate = flatDist(gen);
                    varRate = varDist(gen);
                }
                else if (category == "Natural Gas" && subcategory.empty()) {
                    std::uniform_real_distribution<> varDist(0.05, 0.15);
                    flatRate = flatDist(gen);
                    varRate = varDist(gen);
                }
                else if (category == "Internet") {
                    flatRate = flatDist(gen);
                    varRate = 0.0;
                }
                else if (category == "Hydro" && subcategory == "Sewerage") {
                    std::uniform_real_distribution<> varDist(0.10, 0.15);
                    flatRate = flatDist(gen);
                    varRate = varDist(gen);
                }

                executeSQL("INSERT INTO services VALUES (" + 
                    std::to_string(serviceId++) + ", '" + provider + "', '" + 
                    category + "', '" + subcategory + "', " + 
                    std::to_string(flatRate) + ", " + 
                    std::to_string(varRate) + ");");
            }
        }

        // Populate bills
        std::uniform_int_distribution<> usage(50, 200);
        std::uniform_int_distribution<> providerDist(1, providerNames.size());
        int billId = 1;

        // Generate dates for 6 months
        std::vector<std::pair<std::string, std::string>> monthlyDates;
        for(int month = 5; month >= 0; month--) {
            std::string issueDate = getDate(month * 30);
            std::string dueDate = getDate((month * 30) - 30);
            monthlyDates.push_back({issueDate, dueDate});
        }

        for (size_t customer = 1; customer <= customerNames.size(); customer++) {
            for (size_t serviceId = 1; serviceId <= services.size(); serviceId++) {
                for (int month = 0; month < 6; month++) {
                    int providerId = providerDist(gen);
                    int usageAmount = usage(gen);

                    // Generate random payment date between issue date + 7 days and issue date + 90 days
                    std::uniform_int_distribution<> paymentDayDist(7, 90);
                    int paymentDays = paymentDayDist(gen);
                    std::string paymentDate = getDate((5 - month) * 30 - paymentDays);

                    // If payment date would be after 6-month period, set to NULL and status to unpaid
                    std::string status = "paid";
                    if (month == 0 && paymentDays > 30) {
                        paymentDate = "NULL";
                        status = "unpaid";
                    }

                    executeSQL("INSERT INTO bills VALUES (" + 
                        std::to_string(billId++) + ", " + 
                        std::to_string(customer) + ", " + 
                        std::to_string(serviceId) + ", " + 
                        std::to_string(providerId) + ", '" + 
                        status + "', " + 
                        std::to_string(usageAmount) + ", '" + 
                        monthlyDates[month].first + "', '" + 
                        monthlyDates[month].second + "', " + 
                        (paymentDate == "NULL" ? "NULL" : ("'" + paymentDate + "'")) + ");");
                }
            }
        }

        std::cout << "Database population complete!" << std::endl;
    }

    static int displayCallback(void* data, int argc, char** argv, char** azColName) {
        for (int i = 0; i < argc; i++) {
            std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
        }
        std::cout << std::endl;
        return 0;
    }

    void executeQueryWithDisplay(const char* sql) {
        char* errMsg = nullptr;
        std::cout << "\n=== Executing: " << sql << " ===\n";
        if (sqlite3_exec(db, sql, displayCallback, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    void display() {
        executeQueryWithDisplay("SELECT * FROM customers;");
        executeQueryWithDisplay("SELECT * FROM providers;");
        executeQueryWithDisplay("SELECT * FROM services;");
        executeQueryWithDisplay("SELECT * FROM bills;");
    }

    ~DatabasePopulator() {
        sqlite3_close(db);
    }
};


int main() {
    DatabasePopulator populator("newfile.db");
    populator.populateAll();
    populator.display();
    return 0;
}
