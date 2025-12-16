
CREATE TABLE products_dim (
    product_id SERIAL PRIMARY KEY, 
    product_name VARCHAR(255) NOT NULL,
    category VARCHAR(100),
    price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE customers_dim (
    customer_id SERIAL PRIMARY KEY,  
    customer_name VARCHAR(255) NOT NULL,
    region VARCHAR(100)
);

CREATE TABLE time_dim (
    time_id SERIAL PRIMARY KEY,  
    year INTEGER NOT NULL,
    quarter INTEGER CHECK (quarter BETWEEN 1 AND 4),
    month INTEGER CHECK (month BETWEEN 1 AND 12),
    day INTEGER CHECK (day BETWEEN 1 AND 31),
    day_of_week VARCHAR(20)
);

CREATE TABLE sales_fact (
    sale_id SERIAL PRIMARY KEY, 
    sale_date DATE NOT NULL,
    product_id INTEGER NOT NULL,
    customer_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    amount DECIMAL(10, 2) NOT NULL CHECK (amount >= 0),
    

    CONSTRAINT fk_product 
        FOREIGN KEY (product_id) 
        REFERENCES products_dim(product_id)
        ON DELETE RESTRICT,
    
    CONSTRAINT fk_customer 
        FOREIGN KEY (customer_id) 
        REFERENCES customers_dim(customer_id)
        ON DELETE RESTRICT
);

-- Индексы для таблицы фактов (sales_fact)
CREATE INDEX idx_sales_fact_product ON sales_fact(product_id);
CREATE INDEX idx_sales_fact_customer ON sales_fact(customer_id);
CREATE INDEX idx_sales_fact_date ON sales_fact(sale_date);
-- Индексы для таблиц измерений (dimensions)
CREATE INDEX idx_products_dim_category ON products_dim(category);
CREATE INDEX idx_customers_dim_region ON customers_dim(region);