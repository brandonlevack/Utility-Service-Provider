-- Create Natural Gas Usage table
CREATE TABLE naturalGas (
    customer_id INTEGER NOT NULL,
    name VARCHAR(100),
    gas_usage_month1 Integer,
    gas_usage_month2 Integer,
    gas_usage_month3 Integer,
    gas_usage_month4 Integer,
    gas_usage_month5 Integer,
    gas_usage_month6 Integer
);

-- Create Electricity Usage table
CREATE TABLE electricity (
    customer_id INTEGER NOT NULL,
    name VARCHAR(100),
    electricity_usage_month1 Integer,
    electricity_usage_month2 Integer,
    electricity_usage_month3 Integer,
    electricity_usage_month4 Integer,
    electricity_usage_month5 Integer,
    electricity_usage_month6 Integer
);

-- Create Water Usage table
CREATE TABLE water (
    customer_id INTEGER NOT NULL,
    name VARCHAR(100),
    water_usage_month1 Integer,
    water_usage_month2 Integer,
    water_usage_month3 Integer,
    water_usage_month4 Integer,
    water_usage_month5 Integer,
    water_usage_month6 Integer
);

-- Create Customers table
CREATE TABLE customers (
    customer_id INTEGER NOT NULL,
    name VARCHAR(100),
    address VARCHAR(100),
    service VARCHAR(100),
    PRIMARY KEY (customer_id)
);

-- Create Providers table
CREATE TABLE providers (
    provider_id INTEGER NOT NULL,
    name VARCHAR(100),
    phone_number VARCHAR(100),
    address VARCHAR(100),
    PRIMARY KEY (provider_id)
);

-- Create Services table
CREATE TABLE services (
    service_id INTEGER NOT NULL,
    name VARCHAR(100) NOT NULL,
    service_super_category VARCHAR(100),
    service_sub_category VARCHAR(100),
    flat_rate DECIMAL(10,2),
    variable_rate DECIMAL(10,2),
    PRIMARY KEY(service_id),
    FOREIGN KEY (name) REFERENCES providers(name)
);

-- Create Bills table
CREATE TABLE bills (
    bill_id INTEGER NOT NULL,
    customer_id INTEGER NOT NULL,
    service_id INTEGER NOT NULL,
    provider_id INTEGER NOT NULL,
    status VARCHAR(20) DEFAULT 'unpaid', 
    used Integer,
    total DECIMAL(10,2) NOT NULL,
    PRIMARY KEY(bill_id),
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
    FOREIGN KEY (service_id) REFERENCES services(service_id),
    FOREIGN KEY (provider_id) REFERENCES providers(provider_id)
);
