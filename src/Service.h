#ifndef CLASSSERVICE_H
#define CLASSSERVICE_H

#include <string>
#include <vector>
#include <deque>

/*
Each individual service has its own service element
Eg Superclass Hydro
    - category Water

This constitutes one Service Object

If a Provider sells gas, water, and electric, it will have a list of service objects like the following
    -Natural gas: Gas
    -Hydro: Electric
    -Hydro: Water
*/

class Service {
    private:
        int serviceId;

        std::string providerName;

        std::string superCategory;                  // ie Hydro
        std::string subCategory;                    // ie Water

        /*
        Say water costs $15 / month plus $0.02/L
        flatRate -> the flat rate ($15)
        variableRate -> rate per unit ($0.02)

        Thus for any pricing model we can calculate monthly price the same way (flat rate + units * variableRate)
        */
        double flatRate;
        double variableRate;

        double unitsUsed;

        std::deque<Service> history;

    public:
        Service(std::string super, std::string sub, double flat, double var);       // constructor

        std::string getSuperCategory() const;                           // getters

        std::string getSubCategory() const;

        std::string getProviderName() const;

        double getFlatRate() const;

        double getVariableRate() const;

        double getUnitsUsed() const;

        int getServiceId();

        void setSuperCategory(std::string super);                       // setters

        void setSubCategory(std::string sub);

        void setProviderName(std::string name);

        void setFlatRate(double rate);

        void setVariableRate(double rate);

        void setUnitsUsed(double val);

        void setServiceId(int id);

        void reset();

        friend std::ostream& operator<<(std::ostream&os, const Service& service);         // print method
};

#endif