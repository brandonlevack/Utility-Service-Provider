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

std::vector<std::string> ProviderPage::providerHeaders = {
    "Company",
    "Phone Number",
    "Street Address",
    "City",
    "State/Province",
    "Postal Code",
    "Country"
};

QWidget* ProviderPage::createPage(QString inputs[], int numColumns) {
    // Create the main container widget
    QWidget* pageWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(pageWidget);

    // Create a scroll area to handle many fields
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* scrollContent = new QWidget();
    QFormLayout* formLayout = new QFormLayout(scrollContent);

    // Create and add all the provider information fields
    QVector<QLineEdit*> fieldEdits; // Store references to all line edits
    for (int i = 0; i < numColumns && i < providerHeaders.size(); ++i) {
        QLabel* label = new QLabel(QString::fromStdString(providerHeaders[i] + ":"));
        QLineEdit* lineEdit = new QLineEdit(inputs[i]);
        lineEdit->setReadOnly(true); // Start in read-only mode
        fieldEdits.append(lineEdit);

        formLayout->addRow(label, lineEdit);
    }

    // Add the services list (using QListWidget instead of QComboBox)
    QLabel* servicesLabel = new QLabel("Services Provided:");
    QListWidget* servicesList = new QListWidget();
    servicesList->setEnabled(false); // Disabled in view mode
    servicesList->setSelectionMode(QAbstractItemView::MultiSelection);

    // TODO: Populate the list with actual services data
    // servicesList->clear();
    // foreach (const Service &service, providerServices) {
    //     QListWidgetItem* item = new QListWidgetItem(service.name());
    //     item->setData(Qt::UserRole, service.id());
    //     servicesList->addItem(item);
    // }
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
        servicesList->setEnabled(true);

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
        servicesList->setEnabled(false);

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
