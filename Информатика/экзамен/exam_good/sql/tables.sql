-- 1. Таблица пользователей (users)
CREATE TABLE users (
    user_id INTEGER PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    role VARCHAR(20) NOT NULL CHECK (role IN ('admin', 'manager', 'customer')),
    password_hash VARCHAR(255) NOT NULL,
    loyalty_level INTEGER NOT NULL CHECK (loyalty_level IN (0, 1))
);

-- 2. Таблица продуктов (products)
CREATE TABLE products (
    product_id INTEGER PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    stock_quantity INTEGER NOT NULL,
    CONSTRAINT price_check CHECK (price > 0),
    CONSTRAINT stock_check CHECK (stock_quantity >= 0)
);

-- 3. Таблица заказов (orders)
CREATE TABLE orders (
    order_id INTEGER PRIMARY KEY,
    user_id INTEGER NOT NULL,
    status VARCHAR(20) NOT NULL CHECK (status IN ('pending', 'completed', 'canceled', 'returned')),
    total_price DECIMAL(10, 2) NOT NULL,
    order_date TIMESTAMP NOT NULL,
    CONSTRAINT fk_user
        FOREIGN KEY (user_id) 
        REFERENCES users(user_id)
);

-- 4. Таблица элементов заказов (order_items)
CREATE TABLE order_items (
    order_item_id SERIAL PRIMARY KEY,
    order_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    CONSTRAINT fk_order
        FOREIGN KEY (order_id) 
        REFERENCES orders(order_id),
    CONSTRAINT fk_product
        FOREIGN KEY (product_id) 
        REFERENCES products(product_id)
);
-- 5. Таблица истории статусов заказов (order_status_history)
CREATE TABLE order_status_history (
    history_id SERIAL PRIMARY KEY,
    order_id INTEGER NOT NULL,
    old_status VARCHAR(20),
    new_status VARCHAR(20) NOT NULL,
    changed_at TIMESTAMP NOT NULL,
    changed_by INTEGER NOT NULL,
    CONSTRAINT fk_history_order
        FOREIGN KEY (order_id) 
        REFERENCES orders(order_id),
    CONSTRAINT fk_history_user
        FOREIGN KEY (changed_by) 
        REFERENCES users(user_id)
);

-- 6. Таблица логирования операций (audit_log)
CREATE TABLE audit_log (
    log_id SERIAL PRIMARY KEY,  
    entity_type VARCHAR(20) NOT NULL CHECK (entity_type IN ('order', 'product', 'user')),
    entity_id INTEGER NOT NULL,
    operation VARCHAR(20) NOT NULL CHECK (operation IN ('insert', 'update', 'delete')),
    performed_by INTEGER NOT NULL,
    performed_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_audit_user
        FOREIGN KEY (performed_by) 
        REFERENCES users(user_id)
);