#ifndef CLASSCUSTOMER_H
#define CLASSCUSTOMER_H

#include <string>
#include <deque>
#include <vector>

#include "Bill.h"
#include "Service.h"

class Customer {
    private:
        std::string firstName;
        std::string lastName;
        std::string accNumber;
        std::string streetAddress;
        std::string city;
        std::string province;
        std::string postalCode;
        std::string country;


        std::vector<Service> services;              // vector of services the customer has
        std::deque<Bill> bills;                     // more effecient then vector for insert and beginning
    public:
        Customer();

        std::string getName() const;                    // getters

        std::string getFirstName() const;

        std::string getLastName() const;

        std::string getAccountNumber() const;
        
        std::string getAddress() const;

        std::string getStreetAddress() const;

        std::string getCity() const;

        std::string getProvince() const;

        std::string getPostalCode() const;

        std::string getCountry() const;

        std::vector<Service> getServices() const;

        std::deque<Bill> getBills() const;

        void setFirstName(std::string name);                 // setters

        void setLastName(std::string name);

        void setAccountNumber(std::string acnum);

        void setStreetAddress(std::string ad);

        void setCity(std::string c);

        void setProvince(std::string p);

        void setPostalCode(std::string p);

        void setCountry(std::string c);

        void addService(Service service);  // add to services

        void addBill(Bill bill);            // add to bills

        Service& changeService(int index);           // return a reference to the services such that the services in Customer can be modified

        Bill& changeBill(int index);

        friend std::ostream& operator<<(std::ostream&os, const Customer& customer);

        void billCustomer();

        int numServices();

};

#endif