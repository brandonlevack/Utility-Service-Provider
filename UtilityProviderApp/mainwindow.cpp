#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TableModifier.h"
#include "CustomerPage.h"
#include "ProviderPage.h"
#include "../src/Service.h"


#include <QVBoxLayout>
#include <QLabel>
#include <vector>

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

    Customer c;
    c.setFirstName("John");
    c.setLastName("James");
    c.setAccountNumber("123456");
    c.setStreetAddress("123 Main Street");
    c.setCity("Windsor");
    c.setProvince("Ontario");
    c.setPostalCode("A1B2C3");
    c.setCountry("Canada");
    Service s("Hydro", "Water", 15.0, 0.2);
    c.addService(s);
    c.billCustomer();
    Service s2("Hydro", "Gas", 20.0, 0.32);
    s2.setUnitsUsed(10);
    c.addService(s2);
    c.billCustomer();

    QTableWidget* customerTable = CustomerPage::createTable(new std::vector<Customer>{c});


    connect(customerTable, &QTableWidget::cellDoubleClicked, [this, customerTable](int row, int column){
        QString accountNumber = customerTable->item(row, 2)->text();

        //if tab already exists, open it
        for (int i = 0; i < tabWidget->count(); i++){
            if (tabWidget->tabText(i) == accountNumber){
                tabWidget->setCurrentIndex(i);
                return;
            }
        }

        QWidget* newCustomerPage = CustomerPage::createPage(customerTable, row);

        int temp = tabWidget->addTab(newCustomerPage, accountNumber);
        tabWidget->setCurrentIndex(temp);
    });

    //Provider Page
    QVBoxLayout* layout2 = new QVBoxLayout(providerPage);
    layout2->addWidget(new QLabel("This is the provider page"));

    Provider p("Gas Co", "999-999-9999", std::vector<Service>{s});
    p.setCity("Windsor");
    p.setCountry("Canada");
    p.setPostalCode("A1B2C3");
    p.setProvince("Ontario");
    p.setStreetAddress("123 Main Street");

    QTableWidget* providerTable = ProviderPage::createTable(new std::vector<Provider>{p});
    connect(providerTable, &QTableWidget::cellDoubleClicked, [this, providerTable](int row, int column){
        QString companyName = providerTable->item(row, 0)->text();

        //if tab already exists, open it
        for (int i = 0; i < tabWidget->count(); i++){
            if (tabWidget->tabText(i) == companyName){
                tabWidget->setCurrentIndex(i);
                return;
            }
        }

        QWidget* newProviderPage = ProviderPage::createPage(providerTable, row);

        int temp = tabWidget->addTab(newProviderPage, companyName);
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
