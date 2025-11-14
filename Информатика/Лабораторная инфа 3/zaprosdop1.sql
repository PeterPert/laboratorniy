SELECT 
    p.name,
	o.order_date,
    SUM(oi.quantity) as total_quantity_sold,
    COUNT(oi.order_item_id) as times_ordered,
    SUM(oi.total_price) as total_revenue
FROM products p
JOIN order_items oi ON p.id = oi.product_id
JOIN orders o ON oi.order_id = o.order_id
WHERE o.order_date BETWEEN '2024-01-16' AND ('2024-01-17')
GROUP BY p.id, p.name, o.order_date
ORDER BY total_quantity_sold DESC, times_ordered DESC;
