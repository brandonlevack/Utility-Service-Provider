#ifndef CLASSPROVIDER_H
#define CLASSPROVIDER_H

#include <string>
#include <vector>

#include "Service.h"

class Provider {
    private:
        std::string name;                           // straightforward
        std::string streetAddress;
        std::string city;
        std::string province;
        std::string postalCode;
        std::string country;
        std::string phoneNumber;

        std::vector<Service> services;              // vector of Services stores each providers available services. Service Class will handle subcategories

    public:

        Provider(std::string name);                     // constructors

        Provider(std::string name, std::string phoneNumber, std::vector<Service> services);

        std::string getName() const;                    // getters

        std::string getAddress() const;

        std::string getStreetAddress() const;

        std::string getCity() const;

        std::string getProvince() const;

        std::string getPostalCode() const;

        std::string getCountry() const;

        std::string getPhoneNumber() const;

        std::vector<Service> getServices() const;

        void setName(std::string newName);              // setters

        void setStreetAddress(std::string ad);

        void setCity(std::string c);

        void setProvince(std::string p);

        void setPostalCode(std::string p);

        void setCountry(std::string c);

        void setPhoneNumber(std::string newNumber);

        void addService(Service s);                     // dont really 'set' a vector, but add to vector

        friend std::ostream& operator<<(std::ostream&os, const Provider& provider);         // print method

};

#endif