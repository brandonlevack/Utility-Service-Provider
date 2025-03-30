#include "CustomerPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVector>

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

QWidget* CustomerPage::createPage(QString inputs[], int numColumns){
    // Create the main container widget
    QWidget* pageWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(pageWidget);

    // Create a scroll area to handle many fields
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* scrollContent = new QWidget();
    QFormLayout* formLayout = new QFormLayout(scrollContent);

    // Create and add all the customer information fields
    QVector<QLineEdit*> fieldEdits; // Store references to all line edits
    for (int i = 0; i < numColumns && i < customerHeaders.size(); ++i) {
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
    billsComboBox->setEnabled(false); // Disabled in view mode

    // TODO: Populate the combo box with actual bills data
    // billsComboBox->clear();
    // foreach (const Bill &bill, customerBills) {
    //     billsComboBox->addItem(bill.displayString(), bill.id());
    // }
    formLayout->addRow(billsLabel, billsComboBox);

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
        billsComboBox->setEnabled(true);

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
        billsComboBox->setEnabled(false);

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
