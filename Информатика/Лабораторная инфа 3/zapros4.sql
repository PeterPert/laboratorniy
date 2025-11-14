-- запрос 4(Список всех заказов за определенный период с общей суммой)
SELECT 
    o.order_id,
    o.order_date,
    COUNT(oi.order_item_id) as items_count,
    SUM(oi.quantity) as total_units,
    SUM(oi.total_price) as order_total
FROM orders o
JOIN order_items oi ON o.order_id = oi.order_id
WHERE o.order_date BETWEEN '2024-01-16' AND ('2024-01-17')
GROUP BY o.order_id, o.order_date
ORDER BY o.order_date;