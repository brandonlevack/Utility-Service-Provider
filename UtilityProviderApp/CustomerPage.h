#ifndef CUSTOMERPAGE_H
#define CUSTOMERPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QString>
#include "../src/Customer.h"

class CustomerPage
{
public:

    static std::vector<std::string> customerHeaders;

    // Static method to create and return the customer page as a QWidget
    static QWidget* createPage(QTableWidget* table, int& row);

    static QTableWidget* createTable(std::vector<Customer>* customers);
};

#endif // CUSTOMERPAGE_H
