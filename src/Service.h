#ifndef CLASSSERVICE_H
#define CLASSSERVICE_H

#include <string>
#include <vector>

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
        std::string superCategory;
        std::string subCategory;

        /*
        Say water costs $15 / month plus $0.02/L
        flatRate -> the flat rate ($15)
        variableRate -> rate per unit ($0.02)

        Thus for any pricing model we can calculate monthly price the same way (flat rate + units * variableRate)
        */
        double flatRate;
        double variableRate;

    public:
        Service(std::string super, std::string sub, double flat, double var);       // constructor

        std::string getSuperCategory() const;                           // getters

        std::string getSubCategory() const;

        double getFlatRate() const;

        double getVariableRate() const;

        void setSuperCategory(std::string super);                       // setters

        void setSubCategory(std::string sub);

        void setFlatRate(double rate);

        void setVariableRate(double rate);

        friend std::ostream& operator<<(std::ostream&os, const Service& service);         // print method
};

#endif