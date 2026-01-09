-- Файл sample_data.sql из вашего задания
-- Исправленная версия без конфликтов

-- 1. Процедура изменения статуса (исправленная)
CREATE OR REPLACE PROCEDURE updateOrderStatus(
    p_order_id INTEGER,
    p_new_status VARCHAR,
    p_user_id INTEGER
)
LANGUAGE plpgsql AS $$
BEGIN
    UPDATE orders 
    SET status = p_new_status 
    WHERE order_id = p_order_id;
END;
$$;

-- 2. Функция получения истории статусов
CREATE OR REPLACE FUNCTION getOrderStatusHistory(p_order_id INTEGER)
RETURNS TABLE(
    old_status VARCHAR,
    new_status VARCHAR,
    changed_at TIMESTAMP,
    changed_by INTEGER
) AS $$
BEGIN
    RETURN QUERY
    SELECT 
        old_status,
        new_status,
        changed_at,
        changed_by
    FROM order_status_history 
    WHERE order_id = p_order_id
    ORDER BY changed_at DESC;
END;
$$ LANGUAGE plpgsql;