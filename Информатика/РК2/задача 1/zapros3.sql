SELECT 
    s.full_name,
    s.group_number,
    g.grade as informatics_grade
FROM grades g
JOIN subjects sub ON g.subject_id = sub.subject_id
JOIN students s ON g.student_id = s.student_id
WHERE sub.subject_name = 'Информатика'
ORDER BY g.grade DESC;