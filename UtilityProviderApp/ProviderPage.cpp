#include "ProviderPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVector>
#include <QListWidget>
#include <sstream>
#include <vector>

#include "TableModifier.h"

std::vector<std::string> ProviderPage::providerHeaders = {
    "Company",
    "Phone Number",
    "Street Address",
    "City",
    "State/Province",
    "Postal Code",
    "Country"
};

QWidget* ProviderPage::createPage(QTableWidget* table, int& row) {
    // Create the main container widget
    QWidget* pageWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(pageWidget);

    // Create a scroll area to handle many fields
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* scrollContent = new QWidget();
    QFormLayout* formLayout = new QFormLayout(scrollContent);

    int numColumns = table-> columnCount();

    QString inputs[numColumns];

    for (int i = 0; i < numColumns; i++){
        inputs[i] = table->item(row, i)->text();
    }

    // Create and add all the provider information fields
    QVector<QLineEdit*> fieldEdits; // Store references to all line edits
    for (int i = 0; i < numColumns && i < providerHeaders.size(); ++i) {
        QLabel* label = new QLabel(QString::fromStdString(providerHeaders[i] + ":"));
        QLineEdit* lineEdit = new QLineEdit(inputs[i]);
        if (providerHeaders[i] == "Company") {
            lineEdit->setEnabled(false);
            lineEdit->setStyleSheet(
                "QLineEdit {"
                "   background: #606060;"  // Dark gray
                "   color: #ffffff;"       // White text
                "   border: 1px solid #404040;"
                "}"
                );
        } else {
            lineEdit->setReadOnly(true);
        }
        fieldEdits.append(lineEdit);

        formLayout->addRow(label, lineEdit);
    }

    QLabel* servicesLabel = new QLabel("Services Provided:");
    QListWidget* servicesList = new QListWidget();

    Provider *p = static_cast<Provider*>(table->item(row, numColumns-1)->data(Qt::UserRole).value<void*>());

    int loc = 0;
    for (auto s : p->getServices()){
        std::ostringstream oss;
        oss << s;

        // Add to list with index storage
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(oss.str()));
        item->setData(Qt::UserRole, QVariant(static_cast<int>(loc)));  // Store index as int
        servicesList->addItem(item);
        loc++;
    }

    formLayout->addRow(servicesLabel, servicesList);

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    // Add edit and save buttons at the bottom
    QPushButton* editButton = new QPushButton("Edit");
    QPushButton* saveButton = new QPushButton("Save");
    saveButton->setEnabled(false); // Disabled initially

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(saveButton);
    mainLayout->addLayout(buttonLayout);

    // Connect edit button to enable edit mode
    QObject::connect(editButton, &QPushButton::clicked, [=]() {
        // Enable editing for all fields
        for (auto lineEdit : fieldEdits) {
            lineEdit->setReadOnly(false);
        }

        // Update button states
        editButton->setEnabled(false);
        saveButton->setEnabled(true);
    });

    // Connect save button to disable edit mode
    QObject::connect(saveButton, &QPushButton::clicked, [=]() {
        // Disable editing for all fields
        for (auto lineEdit : fieldEdits) {
            lineEdit->setReadOnly(true);
        }

        // Update button states
        editButton->setEnabled(true);
        saveButton->setEnabled(false);

        p->setName(fieldEdits[0]->text().trimmed().toStdString());
        p->setPhoneNumber(fieldEdits[1]->text().trimmed().toStdString());
        p->setStreetAddress(fieldEdits[2]->text().trimmed().toStdString());
        p->setCity(fieldEdits[3]->text().trimmed().toStdString());
        p->setProvince(fieldEdits[4]->text().trimmed().toStdString());
        p->setPostalCode(fieldEdits[5]->text().trimmed().toStdString());
        p->setCountry(fieldEdits[6]->text().trimmed().toStdString());

        table->item(row, 0)->setText(QString::fromStdString(p->getName()));
        table->item(row, 1)->setText(QString::fromStdString(p->getPhoneNumber()));
        table->item(row, 2)->setText(QString::fromStdString(p->getStreetAddress()));
        table->item(row, 3)->setText(QString::fromStdString(p->getCity()));
        table->item(row, 4)->setText(QString::fromStdString(p->getProvince()));
        table->item(row, 5)->setText(QString::fromStdString(p->getPostalCode()));
        table->item(row, 6)->setText(QString::fromStdString(p->getCountry()));

    });

    return pageWidget;
}

QTableWidget* ProviderPage::createTable(std::list<Provider> providers){
    QTableWidget* providerTable = new QTableWidget();

    TableModifier::initTable(providerTable, ProviderPage::providerHeaders);

    for (auto &p : providers){

        std::vector<std::string> items;

        items.push_back(p.getName());
        items.push_back(p.getPhoneNumber());
        items.push_back(p.getStreetAddress());
        items.push_back(p.getCity());
        items.push_back(p.getProvince());
        items.push_back(p.getPostalCode());
        items.push_back(p.getCountry());

        TableModifier::addRow(providerTable, items, &p);
    }
    return providerTable;
}
