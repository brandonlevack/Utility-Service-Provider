#ifndef CLASSCUSTOMER_H
#define CLASSCUSTOMER_H

#include <string>
#include <deque>
#include <vector>

#include "Bill.h"
#include "Service.h"

class Customer {
    private:
        std::string name;
        std::string address;


        std::vector<Service> services;              // vector of services the customer has
        std::deque<Bill> bills;                     // more effecient then vector for insert and beginning
    public:
        Customer(std::string name, std::string address);

        std::string getName() const;                    // getters
        
        std::string getAddress() const;

        std::vector<Service> getServices() const;

        std::deque<Bill> getBills() const;

        void setName(std::string name);                 // setters

        void setAddress(std::string address);

        void addService(Service service);  // add to services

        void addBill(Bill bill);            // add to bills

        friend std::ostream& operator<<(std::ostream&os, const Customer& customer);

        void billCustomer();

};

#endif