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
        lineEdit->setReadOnly(true); // Start in read-only mode
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

        // TODO: Add database save logic here
        // Access field values through fieldEdits vector
        // Access selected services through servicesList

        // Get selected services example:
        // QList<QVariant> selectedServiceIds;
        // for (auto item : servicesList->selectedItems()) {
        //     selectedServiceIds.append(item->data(Qt::UserRole));
        // }
    });

    return pageWidget;
}

QTableWidget* ProviderPage::createTable(std::list<Provider> providers){
    QTableWidget* providerTable = new QTableWidget();

    TableModifier::initTable(providerTable, ProviderPage::providerHeaders);

    for (const auto &p : providers){
        /*
         * create create a vector of strings (items) with following order:
         * Company Name,
         * Phone Number,
         * Street Address,
         * City,
         * State/Province,
         * Postal Code,
         * Country
         *
         * Then call TableModifier::addRow(providerTable, items)
         */
    }
    return providerTable;
}
