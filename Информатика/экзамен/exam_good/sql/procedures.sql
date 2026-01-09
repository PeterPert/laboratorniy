CREATE PROCEDURE createOrder(
    user_id INTEGER,
    product_id INTEGER,
    quantity INTEGER
)
LANGUAGE SQL
AS $$
    -- Начало транзакции
    BEGIN;
    
    -- Создаём заказ
    INSERT INTO orders (user_id, status, total_price, order_date)
    VALUES (
        user_id,
        'pending',
        (SELECT price FROM products WHERE product_id = product_id) * quantity,
        NOW()
    );
    
    -- Добавляем товар в заказ
    INSERT INTO order_items (order_id, product_id, quantity, price)
    VALUES (
        (SELECT MAX(order_id) FROM orders),
        product_id,
        quantity,
        (SELECT price FROM products WHERE product_id = product_id)
    );
    
    -- Уменьшаем остаток
    UPDATE products 
    SET stock_quantity = stock_quantity - quantity
    WHERE product_id = product_id;
    
    -- Конец транзакции
    COMMIT;
$$;