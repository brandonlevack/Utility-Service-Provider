#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TableModifier.h"
#include "CustomerPage.h"
#include "ProviderPage.h"
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

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    QWidget* customerPage = new QWidget();
    QWidget* providerPage = new QWidget();

    //Customer Page
    QVBoxLayout* layout1 = new QVBoxLayout(customerPage);
    layout1->addWidget(new QLabel("This is the customer page"));


    QTableWidget* customerTable = new QTableWidget(this);

    TableModifier::initTable(customerTable, CustomerPage::customerHeaders);
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
    connect(customerTable, &QTableWidget::cellDoubleClicked, [this, customerTable](int row, int column){
        QString accountNumber = customerTable->item(row, 2)->text();

        //if tab already exists, open it
        for (int i = 0; i < tabWidget->count(); i++){
            if (tabWidget->tabText(i) == accountNumber){
                tabWidget->setCurrentIndex(i);
                return;
            }
        }

        int columnCount = customerTable-> columnCount();

        QString inputs[columnCount];

        for (int i = 0; i < columnCount; i++){
            inputs[i] = customerTable->item(row, i)->text();
        }

        QWidget* newCustomerPage = CustomerPage::createPage(inputs, columnCount);

        int temp = tabWidget->addTab(newCustomerPage, accountNumber);
        tabWidget->setCurrentIndex(temp);
    });



    //Provider Page
    QVBoxLayout* layout2 = new QVBoxLayout(providerPage);
    layout2->addWidget(new QLabel("This is the provider page"));
    QTableWidget* providerTable = new QTableWidget(this);
    TableModifier::initTable(providerTable, ProviderPage::providerHeaders);
    std::vector<std::string> testProvider = {
        "Gas Co",
        "+1 999-999-9999",
        "123456",
        "123 Main Street",
        "Windsor",
        "Ontario",
        "A1B2C3",
        "Canada"
    };
    TableModifier::addRow(providerTable, testProvider);
    connect(providerTable, &QTableWidget::cellDoubleClicked, [this, providerTable](int row, int column){
        QString accountNumber = providerTable->item(row, 2)->text();

        //if tab already exists, open it
        for (int i = 0; i < tabWidget->count(); i++){
            if (tabWidget->tabText(i) == accountNumber){
                tabWidget->setCurrentIndex(i);
                return;
            }
        }

        int columnCount = providerTable-> columnCount();

        QString inputs[columnCount];

        for (int i = 0; i < columnCount; i++){
            inputs[i] = providerTable->item(row, i)->text();
        }

        QWidget* newProviderPage = ProviderPage::createPage(inputs, columnCount);

        int temp = tabWidget->addTab(newProviderPage, accountNumber);
        tabWidget->setCurrentIndex(temp);
    });

    layout1->addWidget(customerTable);
    customerPage->setLayout(layout1);
    layout2->addWidget(providerTable);
    providerPage->setLayout(layout2);


    tabWidget->setTabsClosable(true);

    int temp = tabWidget->addTab(customerPage, "Customers");
    tabWidget->tabBar()->setTabButton(temp, QTabBar::RightSide, nullptr);

    temp = tabWidget->addTab(providerPage, "Providers");
    tabWidget->tabBar()->setTabButton(temp, QTabBar::RightSide, nullptr);

    connect(tabWidget, &QTabWidget::tabCloseRequested, [=](int index) {
        tabWidget->removeTab(index); // Remove the tab when close button is clicked
    });

}
MainWindow::~MainWindow()
{
    delete ui;
}
