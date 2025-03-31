#ifndef TABLEMODIFIER_H
#define TABLEMODIFIER_H

#include <QTableWidget>
#include <vector>
#include <string>

class TableModifier {
public:
    // Function prototypes
    static void initTable(QTableWidget* table, std::vector<std::string> headers);
    template <typename T>
    static void addRow(QTableWidget* table, const std::vector<std::string>& items, T* object){
        if (!table) {
            qWarning() << "Null table widget provided";
            return;
        }

        const int row = table->rowCount();
        table->insertRow(row);

        // Add visible items
        for (int col = 0; col < items.size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(items[col]));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(row, col, item);
        }

        // Add hidden object storage
        QTableWidgetItem* hiddenItem = new QTableWidgetItem();
        hiddenItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<void*>(object)));
        hiddenItem->setFlags(hiddenItem->flags() & ~Qt::ItemIsEnabled); // Make visibly disabled
        table->setItem(row, items.size(), hiddenItem);
    }
    static void addColumn(QTableWidget* table, std::string header);
};

#endif // TABLEMODIFIER_H
