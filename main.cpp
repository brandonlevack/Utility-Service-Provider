#include <iostream>
#include "src/Service.h"
#include "src/Customer.h"
#include "src/Provider.h"
#include "src/Bill.h"

int main() {

    Service s();
    std::cout << s;

    Customer c();
    std::cout << c;

    Provider p();
    std::cout << p;

    Bill b();
    std::cout << b;

}