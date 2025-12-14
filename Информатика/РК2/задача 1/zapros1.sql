WITH target_student AS (
    SELECT student_id, group_number 
    FROM students 
    WHERE student_id = 3
)
SELECT 
    s.student_id,
    s.full_name,
    s.group_number,
    CASE 
        WHEN s.student_id < ts.student_id THEN 'перед'
        WHEN s.student_id > ts.student_id THEN 'после'
    END as position
FROM students s
CROSS JOIN target_student ts
WHERE s.group_number = ts.group_number 
  AND s.student_id != ts.student_id
  AND s.student_id IN (
      -- 2 студента с меньшим ID
      SELECT student_id FROM students 
      WHERE student_id < 3 
        AND group_number = ts.group_number
      ORDER BY student_id DESC 
      LIMIT 2
  ) OR s.student_id IN (
      -- 3 студента с большим ID
      SELECT student_id FROM students 
      WHERE student_id > 3 
        AND group_number = ts.group_number
      ORDER BY student_id ASC 
      LIMIT 3
  )
ORDER BY s.student_id;