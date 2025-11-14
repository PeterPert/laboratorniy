BEGIN TRANSACTION;

DELETE FROM orders WHERE order_id = 1;

DELETE FROM order_items WHERE order_id = 1;

SELECT COUNT(*) as orders_remaining FROM orders WHERE order_id = (
    SELECT order_id FROM order_items WHERE order_item_id = 5
);

SELECT COUNT(*) as products_remaining FROM products WHERE id = (
    SELECT product_id FROM order_items WHERE order_item_id = 5
);

COMMIT;
