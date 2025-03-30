#ifndef CUSTOMERPAGE_H
#define CUSTOMERPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QString>

class CustomerPage
{
public:

    static std::vector<std::string> customerHeaders;

    // Static method to create and return the customer page as a QWidget
    static QWidget* createPage(QString inputs[], int numColumns);

    // Static method to update customer data in the table
    static void updateCustomerData(QTableWidget* customerTable, int row, int column, const QString& newValue);
};

#endif // CUSTOMERPAGE_H
