--запрос 3(Общая стоимость всех товаров в конкретном заказе)
SELECT 
    o.order_id,
    o.order_date,
    SUM(oi.total_price) as order_total
FROM orders o
JOIN order_items oi ON o.order_id = oi.order_id
WHERE o.order_id = 1
GROUP BY o.order_id, o.order_date;