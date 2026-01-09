-- 1. Триггер для обновления order_date при изменении статуса заказа
CREATE OR REPLACE FUNCTION update_order_date()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.status != NEW.status THEN
        NEW.order_date = CURRENT_TIMESTAMP;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_order_date_update
BEFORE UPDATE ON orders
FOR EACH ROW
EXECUTE FUNCTION update_order_date();

-- 2. Триггер аудита для записи изменений статуса заказа
CREATE OR REPLACE FUNCTION log_status_change()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.status != NEW.status THEN
        INSERT INTO order_status_history 
        (order_id, old_status, new_status, changed_at, changed_by)
        VALUES 
        (NEW.order_id, OLD.status, NEW.status, CURRENT_TIMESTAMP, NEW.user_id);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_status
AFTER UPDATE ON orders
FOR EACH ROW
EXECUTE FUNCTION log_status_change();

-- 3. Триггер для обновления total_price при изменении цены продукта
CREATE OR REPLACE FUNCTION update_order_totals()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.price != NEW.price THEN
        UPDATE orders o
        SET total_price = (
            SELECT SUM(oi.quantity * 
                CASE 
                    WHEN oi.product_id = NEW.product_id THEN NEW.price 
                    ELSE p.price 
                END)
            FROM order_items oi
            JOIN products p ON oi.product_id = p.product_id
            WHERE oi.order_id = o.order_id
        )
        WHERE EXISTS (
            SELECT 1 
            FROM order_items 
            WHERE order_id = o.order_id 
            AND product_id = NEW.product_id
        );
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_update_totals
AFTER UPDATE ON products
FOR EACH ROW
EXECUTE FUNCTION update_order_totals();