#include "CustomerPage.h"
#include "TableModifier.h"
#include "../src/Customer.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVector>
#include <vector>

std::vector<std::string> CustomerPage::customerHeaders = {
    "First Name",
    "Last Name",
    "Account Number",
    "Street Address",
    "City",
    "State/Province",
    "Postal Code",
    "Country"
};

QWidget* CustomerPage::createPage(QTableWidget* table, int& row){
    // Create the main container widget
    QWidget* pageWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(pageWidget);

    // Create a scroll area to handle many fields
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* scrollContent = new QWidget();
    QFormLayout* formLayout = new QFormLayout(scrollContent);

    int numColumns = table->columnCount();

    QString inputs[numColumns-1];

    for (int i = 0; i < numColumns-1; i++){
        inputs[i] = table->item(row, i)->text();
    }

    // Create and add all the customer information fields
    QVector<QLineEdit*> fieldEdits; // Store references to all line edits
    for (int i = 0; i < numColumns-1 && i < customerHeaders.size(); ++i) {
        QLabel* label = new QLabel(QString::fromStdString(customerHeaders[i] + ":"));
        QLineEdit* lineEdit = new QLineEdit(inputs[i]);
        lineEdit->setReadOnly(true); // Start in read-only mode
        fieldEdits.append(lineEdit);

        formLayout->addRow(label, lineEdit);
    }

    // Add the bills dropdown
    QLabel* billsLabel = new QLabel("Customer Bills:");
    QComboBox* billsComboBox = new QComboBox();
    billsComboBox->addItem("Select a bill...");
    billsComboBox->setEnabled(true);

    Customer* c = static_cast<Customer*>(table->item(row, numColumns-1)->data(Qt::UserRole).value<void*>());

    formLayout->addRow(billsLabel, billsComboBox);

    billsComboBox->clear();
    int loc = 0;
    for (auto b : c->getBills()){
        QString billText = QString("$%1").arg(b.getTotal(), 0, 'f', 2);
        billsComboBox->addItem(billText, loc);
        loc++;
    }

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

        // TODO: Add database save logic here
        // You can access the field values through fieldEdits vector

        // for (int i = 0; i < fieldEdits.size(); i++) {
        //     QString value = fieldEdits[i]->text();
        //     // Save to database using customerHeaders[i] as field name
        // }
    });

    return pageWidget;
}

QTableWidget* CustomerPage::createTable(std::list<Customer> customers){
    QTableWidget* customerTable = new QTableWidget();

    TableModifier::initTable(customerTable, CustomerPage::customerHeaders);

    for ( auto &c : customers){
        std::vector<std::string> items;

        items.push_back(c.getFirstName());
        items.push_back(c.getLastName());
        items.push_back(c.getStreetAddress());
        items.push_back(c.getCity());
        items.push_back(c.getProvince());
        items.push_back(c.getPostalCode());
        items.push_back(c.getCountry());

        TableModifier::addRow(customerTable, items, &c);
    }
    return customerTable;
}
