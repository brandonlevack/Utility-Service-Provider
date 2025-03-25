-- Create Customers table
CREATE TABLE customers (
    customer_id INTEGER NOT NULL,
    name VARCHAR(100),
    address VARCHAR(100),
    PRIMARY KEY (customer_id);
);

-- Create Providers table
CREATE TABLE providers (
    provider_id INTEGER NOT NULL,
    name VARCHAR(100),
    phone_number VARCHAR(100),
    address VARCHAR(100),
    PRIMARY KEY (provider_id);
);

-- Create Services table
CREATE TABLE services (
    service_id INTEGER NOT NULL,
    provider_id INTEGER NOT NULL,
    service_super_category VARCHAR(100),
    service_sub_category VARCHAR(100),
    flat_rate DECIMAL(10,2),
    variable_rate DECIMAL(10,2),
    PRIMARY KEY(service_id),
    FOREIGN KEY (provider_id) REFERENCES providers(provider_id)
);

-- Create Bills table
CREATE TABLE bills (
    bill_id INTEGER NOT NULL,
    customer_id INTEGER NOT NULL,
    service_id INTEGER NOT NULL,
    provider_id INTEGER NOT NULL,
    status VARCHAR(20) DEFAULT 'unpaid', 
    total DECIMAL(10,2) NOT NULL,
    issue_date DATE NOT NULL,
    due_date DATE NOT NULL,
    payment_date DATE,
    PRIMARY KEY(bill_id),
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
    FOREIGN KEY (service_id) REFERENCES services(service_id),
    FOREIGN KEY (provider_id) REFERENCES providers(provider_id)
);
