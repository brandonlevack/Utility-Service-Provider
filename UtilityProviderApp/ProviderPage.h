#ifndef PROVIDERPAGE_H
#define PROVIDERPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QString>

class ProviderPage
{
public:

    static std::vector<std::string> providerHeaders;

    // Static method to create and return the customer page as a QWidget
    static QWidget* createPage(QString inputs[], int numColumns);

};

#endif // PROVIDERPAGE_H
