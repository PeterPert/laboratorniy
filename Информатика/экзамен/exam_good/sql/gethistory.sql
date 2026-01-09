-- 3. Функция получения истории
CREATE OR REPLACE FUNCTION getHistory(p_order_id INTEGER)
RETURNS TABLE(
    old_status VARCHAR,
    new_status VARCHAR,
    changed_at TIMESTAMP,
    changed_by INTEGER
) AS $$
BEGIN
    RETURN QUERY
    SELECT 
        osh.old_status,
        osh.new_status,
        osh.changed_at,
        osh.changed_by
    FROM order_status_history osh
    WHERE osh.order_id = p_order_id
    ORDER BY osh.changed_at DESC;
END;
$$ LANGUAGE plpgsql;