--запрос 2(Все позиции заказа по определенному заказу)
SELECT 
    oi.order_item_id,
    p.name as product_name,
    oi.quantity,
    p.price as unit_price,
    oi.total_price
FROM order_items oi
JOIN products p ON oi.product_id = p.id
WHERE oi.order_id = 2
ORDER BY oi.order_item_id;