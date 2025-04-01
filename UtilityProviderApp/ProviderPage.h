#ifndef PROVIDERPAGE_H
#define PROVIDERPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QString>
#include "../src/Provider.h"

class ProviderPage
{
public:

    static std::vector<std::string> providerHeaders;

    static QWidget* createPage(QTableWidget* table, int& row);

    static QTableWidget* createTable(std::vector<Provider>* providers);

};

#endif // PROVIDERPAGE_H
