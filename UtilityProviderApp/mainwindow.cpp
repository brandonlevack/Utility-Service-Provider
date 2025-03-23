#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TableModifier.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Utility Provider");

    QTabWidget* tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    QWidget* customerPage = new QWidget();
    QWidget* providerPage = new QWidget();

    //Customer Page
    QVBoxLayout* layout1 = new QVBoxLayout(customerPage);
    layout1->addWidget(new QLabel("This is the customer page"));


    QTableWidget* customerTable = new QTableWidget(this);
    std::vector<std::string> customerHeaders = {
        "First Name",
        "Last Name",
        "Account Number",
        "Street Address",
        "City",
        "State/Province",
        "Postal Code",
        "Country"
    };
    TableModifier::initTable(customerTable, customerHeaders);
    std::vector<std::string> testCustomer = {
        "John",
        "Doe",
        "123456",
        "123 Main Street",
        "Windsor",
        "Ontario",
        "A1B2C3",
        "Canada"
    };
    TableModifier::addRow(customerTable, testCustomer);
    connect(customerTable, &QTableWidget::cellDoubleClicked, [customerTable](int row, int column){
        QMessageBox::information(nullptr, "Row Double-Clicked",
                                 QString("You double-clicked row with account number %1").arg(customerTable->item(row,2)->text()));
    });

    layout1->addWidget(customerTable);
    customerPage->setLayout(layout1);

    //Provider Page
    QVBoxLayout* layout2 = new QVBoxLayout(providerPage);
    layout2->addWidget(new QLabel("This is the provider page"));
    QTableWidget* providerTable = new QTableWidget(this);
    std::vector<std::string> providerHeaders = {
        "Company",
        "Phone Number",
        "Account Number",
        "Street Address",
        "City",
        "State/Province",
        "Postal Code",
        "Country"
    };
    TableModifier::initTable(providerTable, providerHeaders);
    layout2->addWidget(providerTable);
    providerPage->setLayout(layout2);

    tabWidget->addTab(customerPage, "Customers");
    tabWidget->addTab(providerPage, "Providers");

    // ui->CustomerList->setColumnCount(3);
    // ui->CustomerList->setHorizontalHeaderLabels({"First Name", "Last Name", "Account Number"});




}

MainWindow::~MainWindow()
{
    delete ui;
}
