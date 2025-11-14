
-- Создавайте таблицы напрямую
CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE orders (
    order_id SERIAL PRIMARY KEY,
    order_date DATE NOT NULL
);

CREATE TABLE order_items (
    order_item_id SERIAL PRIMARY KEY,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    total_price DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE, 
    FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE RESTRICT
);

INSERT INTO products (name, price) VALUES --values:VALUES ('Ноутбук ASUS', 75000.00)
('Ноутбук ASUS', 75000.00),
('Мышь беспроводная', 2500.00),
('Клавиатура механическая', 5500.00),
('Монитор 24"', 15000.00),
('Наушники Sony', 8000.00),
('Веб-камера', 3500.00),
('Коврик для мыши', 800.00);

-- Заполнение таблицы orders заказами
INSERT INTO orders (order_date) VALUES
('2024-01-15'),  -- январь 2024
('2024-01-16'),  -- январь 2024  
('2024-01-17'),  -- январь 2024
('2024-01-18'); 

-- Заполнение таблицы order_items позициями заказов
INSERT INTO order_items (order_id, product_id, quantity, total_price) VALUES

(1, 1, 1, 75000.00),  
(1, 2, 1, 2500.00),   
(1, 3, 1, 5500.00),   

(2, 4, 2, 30000.00),  -- 2 x Монитор 
(2, 5, 1, 8000.00),   

(3, 6, 3, 10500.00),  -- 3 x Веб-камера
(3, 7, 5, 4000.00),   
(3, 2, 2, 5000.00),

(4, 1, 1, 75000.00),
(4, 5, 1, 8000.00);

