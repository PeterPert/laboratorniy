CREATE TABLE students (
	student_id SERIAL PRIMARY KEY,
	full_name VARCHAR NOT NULL,
	group_number INT NOT NULL CHECK (group_number >= 0)
);
CREATE TABLE subjects (
	subject_id SERIAL PRIMARY KEY, 
	subject_name VARCHAR NOT NULL
);
CREATE TABLE grades (
	grade_id SERIAL PRIMARY KEY,
	student_id INT NOT NULL,
	subject_id INT NOT NULL, 
	grade INT,
	FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE,
	FOREIGN KEY (subject_id) REFERENCES subjects(subject_id) ON DELETE CASCADE
);
CREATE TABLE attendance (
	attendance_id SERIAL PRIMARY KEY,
	student_id INT NOT NULL,
	date_attended DATE NOT NULL DEFAULT CURRENT_DATE,
	status VARCHAR NOT NULL,
	FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE
);
CREATE TABLE notes (
	note_id SERIAL PRIMARY KEY,
	student_id INT NOT NULL,
	note_text TEXT NOT NULL,
	FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE
);
CREATE INDEX idx_group_number ON students(group_number);
CREATE INDEX idx_grades_student_id ON grades(student_id);
CREATE INDEX idx_notes_text ON notes USING GIN(to_tsvector('russian', note_text));


CREATE VIEW student_avg_grades AS
SELECT 
    s.student_id,
    s.full_name,
    s.group_number,
    COUNT(g.grade_id) AS total_grades,      
    ROUND(AVG(g.grade)::numeric, 2) AS average_grade  
FROM students s
LEFT JOIN grades g ON s.student_id = g.student_id
GROUP BY s.student_id, s.full_name, s.group_number
ORDER BY average_grade DESC; 
