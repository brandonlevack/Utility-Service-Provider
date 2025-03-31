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
    QVector<QLineEdit*> fieldEdits;
    for (int i = 0; i < numColumns-1 && i < customerHeaders.size(); ++i) {
        QLabel* label = new QLabel(QString::fromStdString(customerHeaders[i] + ":"));
        QLineEdit* lineEdit = new QLineEdit(inputs[i]);

        if (customerHeaders[i] == "Account Number") {
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

    // Add the bills dropdown
    QLabel* billsLabel = new QLabel("Customer Bills:");
    QComboBox* billsComboBox = new QComboBox();
    billsComboBox->addItem("Select a bill...");
    billsComboBox->setEnabled(true);

    Customer* c = static_cast<Customer*>(table->item(row, numColumns-1)->data(Qt::UserRole).value<void*>());

    formLayout->addRow(billsLabel, billsComboBox);

    billsComboBox->clear();
    billsComboBox->addItem("Please Select a Bill"); // Index 0
    int billSize = c->getBills().size();
    for (const Bill& b : c->getBills()) {
        QString billText = QString("Bill #%1: $%2").arg(billSize - billsComboBox->count() + 1)
        .arg(b.getTotal(), 0, 'f', 2);
        billsComboBox->addItem(billText);
    }

    // Create a container for bill details (initially empty)
    QWidget* billDetailsWidget = new QWidget();
    QVBoxLayout* billDetailsLayout = new QVBoxLayout(billDetailsWidget);
    formLayout->addRow(billDetailsWidget); // Add to main form

    QObject::connect(billsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
     [=](int index) {

         // Clear previous details
         QLayoutItem* child;
         while ((child = billDetailsLayout->takeAt(0))) {
             delete child->widget();
             delete child;
         }

         // Handle the default selection
         if (index <= 0 || index > c->getBills().size()) {
             return;
         }

        // Get selected bill (index 0 is default, so subtract 1)
        Bill currentBill = c->getBills()[index - 1];
        auto test = currentBill.getServices();

        // Add service details
         for (auto s : currentBill.getServices()) {
             QWidget* serviceWidget = new QWidget();
             QHBoxLayout* serviceLayout = new QHBoxLayout(serviceWidget);

             // Service name
            QLabel* serviceName = new QLabel(
            QString("%1: %2")
                .arg(QString::fromStdString(s.getSuperCategory()))
                .arg(QString::fromStdString(s.getSubCategory()))
            );

            //Service calculation
            double serviceTotal = s.getFlatRate() + (s.getVariableRate() * s.getUnitsUsed());
            QLabel* serviceCalc = new QLabel(
                QString("%1 + %2 * %3 = %4")
                    .arg(s.getFlatRate(), 0, 'f', 2)
                    .arg(s.getVariableRate(), 0, 'f', 2)
                    .arg(s.getUnitsUsed(), 0, 'f', 2)
                    .arg(serviceTotal, 0, 'f', 2)
                );

            serviceLayout->addWidget(serviceName);
            serviceLayout->addStretch();
            serviceLayout->addWidget(serviceCalc);
            billDetailsLayout->addWidget(serviceWidget);
        }

        QLabel* billTotalLabel = new QLabel(
            QString("\nTotal: $%1").arg(currentBill.getTotal(), 0, 'f', 2)
            );

        billTotalLabel->setStyleSheet("font-weight: bold;");
        billDetailsLayout->addWidget(billTotalLabel);

        QLabel* statusLabel = new QLabel(
            QString("\nStatus: <span style='color:%1;'>%2</span>")
                .arg(currentBill.getStatus() == "Unpaid" ? "#F00" : "#0F0")
                .arg(QString::fromStdString(currentBill.getStatus()))
            );
        statusLabel->setStyleSheet("font-weight: bold;");
        billDetailsLayout->addWidget(statusLabel);

    });

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

        // Update customer object with edited values
        c->setFirstName(fieldEdits[0]->text().toStdString());
        c->setLastName(fieldEdits[1]->text().toStdString());
        c->setStreetAddress(fieldEdits[3]->text().toStdString());
        c->setCity(fieldEdits[4]->text().toStdString());
        c->setProvince(fieldEdits[5]->text().toStdString());
        c->setPostalCode(fieldEdits[6]->text().toStdString());
        c->setCountry(fieldEdits[7]->text().toStdString());

        table->item(row, 0)->setText(QString::fromStdString(c->getFirstName()));
        table->item(row, 1)->setText(QString::fromStdString(c->getLastName()));
        table->item(row, 3)->setText(QString::fromStdString(c->getStreetAddress()));
        table->item(row, 4)->setText(QString::fromStdString(c->getCity()));
        table->item(row, 5)->setText(QString::fromStdString(c->getProvince()));
        table->item(row, 6)->setText(QString::fromStdString(c->getPostalCode()));
        table->item(row, 7)->setText(QString::fromStdString(c->getCountry()));


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
