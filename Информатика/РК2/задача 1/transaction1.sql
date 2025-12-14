BEGIN; 
INSERT INTO students (full_name, group_number) 
VALUES ('Александр', 1)
RETURNING student_id; 
INSERT INTO grades (student_id, subject_id, grade) VALUES
((SELECT student_id FROM students WHERE full_name = 'Александр' AND group_number = 1 ORDER BY student_id DESC LIMIT 1),1, 4),
((SELECT student_id FROM students WHERE full_name = 'Александр' AND group_number = 1 ORDER BY student_id DESC LIMIT 1),2, 5),
((SELECT student_id FROM students WHERE full_name = 'Александр' AND group_number = 1 ORDER BY student_id DESC LIMIT 1),3, 4);
COMMIT;