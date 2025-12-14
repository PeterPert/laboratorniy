
DO $$
BEGIN
    IF EXISTS (
        SELECT 1 FROM attendance  
        WHERE student_id = 3  
        AND date_attended = '2024-01-15'
    ) THEN
        UPDATE attendance  
        SET status = 'excused'  
        WHERE student_id = 3  
        AND date_attended = '2024-01-15';  
        RAISE NOTICE 'Запись обновлена';
    ELSE
        INSERT INTO attendance (student_id, date_attended, status)  
        VALUES (3, '2024-01-15', 'excused');  
        RAISE NOTICE 'Новая запись создана';
    END IF;
END $$;

SELECT * FROM attendance WHERE student_id = 3;