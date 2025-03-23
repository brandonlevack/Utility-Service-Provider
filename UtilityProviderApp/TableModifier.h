#ifndef TABLEMODIFIER_H
#define TABLEMODIFIER_H

#include <QTableWidget>
#include <vector>
#include <string>

class TableModifier {
public:
    // Function prototypes
    static void initTable(QTableWidget* table, std::vector<std::string> headers);
    static void addRow(QTableWidget* table, std::vector<std::string> items);
    static void addColumn(QTableWidget* table, std::string header);
};

#endif // TABLEMODIFIER_H
