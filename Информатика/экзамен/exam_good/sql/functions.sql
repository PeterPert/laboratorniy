-- 1. Функция getOrderStatus: Возвращает статус заказа по его order_id
CREATE OR REPLACE FUNCTION getOrderStatus(order_id INTEGER)
RETURNS VARCHAR AS $$
    SELECT status FROM orders WHERE order_id = $1;
$$ LANGUAGE SQL;

-- 2. Функция getUserOrderCount: Возвращает количество заказов для каждого пользователя
CREATE OR REPLACE FUNCTION getUserOrderCount()
RETURNS TABLE(user_id INTEGER, order_count BIGINT) AS $$
    SELECT user_id, COUNT(*) 
    FROM orders 
    GROUP BY user_id;
$$ LANGUAGE SQL;

-- 3. Функция getTotalSpentByUser: Возвращает общую сумму денег, потраченную пользователем
CREATE OR REPLACE FUNCTION getTotalSpentByUser(user_id INTEGER)
RETURNS DECIMAL AS $$
    SELECT COALESCE(SUM(total_price), 0) 
    FROM orders 
    WHERE user_id = $1;
$$ LANGUAGE SQL;

-- 4. Функция canReturnOrder: Проверяет, возможен ли возврат заказа
CREATE OR REPLACE FUNCTION canReturnOrder(order_id INTEGER)
RETURNS BOOLEAN AS $$
    SELECT 
        status = 'completed' 
        AND order_date >= CURRENT_DATE - INTERVAL '30 days'
    FROM orders 
    WHERE order_id = $1;
$$ LANGUAGE SQL;
-- 5. Логи по пользователю
CREATE FUNCTION getAuditLogByUser(user_id INTEGER)
RETURNS TABLE(
    log_id INTEGER,
    entity_type VARCHAR,
    entity_id INTEGER,
    operation VARCHAR,
    performed_at TIMESTAMP
) AS $$
    SELECT 
        log_id,
        entity_type,
        entity_id,
        operation,
        performed_at
    FROM audit_log 
    WHERE performed_by = user_id
    ORDER BY performed_at DESC;
$$ LANGUAGE SQL;
