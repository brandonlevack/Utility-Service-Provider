#include "TableModifier.h"
#include <QTableWidgetItem>
#include <QString>

void TableModifier::initTable(QTableWidget* table, std::vector<std::string> headers) {
    for (std::string i : headers) {
        TableModifier::addColumn(table, i);
    }
}

void TableModifier::addRow(QTableWidget* table, std::vector<std::string> items) {
    int row = table->rowCount();
    table->insertRow(row);
    int count = 0;
    for (std::string i : items) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(i));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, count, item);
        count++;
    }
}

void TableModifier::addColumn(QTableWidget* table, std::string header) {
    int column = table->columnCount();
    table->insertColumn(column);
    table->setHorizontalHeaderItem(column, new QTableWidgetItem(QString::fromStdString(header)));
}
