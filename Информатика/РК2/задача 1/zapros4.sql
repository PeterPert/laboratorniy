SELECT 
    n.note_id,
    s.full_name,
    s.group_number,
    n.note_text
FROM notes n
JOIN students s ON n.student_id = s.student_id
WHERE to_tsvector('russian', n.note_text) @@ to_tsquery('russian', 'Информатика')
ORDER BY n.note_id ASC;