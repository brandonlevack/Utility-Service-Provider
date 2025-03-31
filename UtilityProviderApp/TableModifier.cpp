#include "TableModifier.h"
#include <QTableWidgetItem>
#include <QString>

void TableModifier::initTable(QTableWidget* table, std::vector<std::string> headers) {
    for (std::string i : headers) {
        TableModifier::addColumn(table, i);
    }
    TableModifier::addColumn(table, "Object");
    table->hideColumn(table->columnCount()-1);
}

void TableModifier::addColumn(QTableWidget* table, std::string header) {
    int column = table->columnCount();
    table->insertColumn(column);
    table->setHorizontalHeaderItem(column, new QTableWidgetItem(QString::fromStdString(header)));
}
