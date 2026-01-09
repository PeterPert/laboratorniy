-- 1. Триггер для продуктов
CREATE FUNCTION log_product() RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log (entity_type, entity_id, operation) 
    VALUES ('product', COALESCE(NEW.product_id, OLD.product_id), TG_OP);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER product_log 
AFTER INSERT OR UPDATE OR DELETE ON products 
FOR EACH ROW EXECUTE FUNCTION log_product();

-- 2. Триггер для заказов
CREATE FUNCTION log_order() RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log (entity_type, entity_id, operation) 
    VALUES ('order', COALESCE(NEW.order_id, OLD.order_id), TG_OP);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER order_log 
AFTER INSERT OR UPDATE OR DELETE ON orders 
FOR EACH ROW EXECUTE FUNCTION log_order();

-- 3. Триггер для пользователей (только удаление)
CREATE FUNCTION log_user() RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log (entity_type, entity_id, operation) 
    VALUES ('user', OLD.user_id, 'delete');
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER user_log 
AFTER DELETE ON users 
FOR EACH ROW EXECUTE FUNCTION log_user();