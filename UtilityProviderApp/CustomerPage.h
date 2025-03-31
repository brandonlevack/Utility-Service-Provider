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

    static QTableWidget* createTable(std::list<Customer> customers);

    // Static method to update customer data in the table
    static void updateCustomerData(QTableWidget* customerTable, int row, int column, const QString& newValue);
};

#endif // CUSTOMERPAGE_H
