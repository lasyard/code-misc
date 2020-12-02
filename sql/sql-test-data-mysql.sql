DROP TABLE IF EXISTS tbl_course;
CREATE TABLE tbl_course (
    c_id int NOT NULL AUTO_INCREMENT,
    c_name varchar(60) DEFAULT NULL,
    PRIMARY KEY (c_id)
);

INSERT INTO tbl_course VALUES (1,'English'),(2,'Chinese'),(3,'Maths'),(4,'Physics'),(5,'Chemistry'),(6,'History');

DROP TABLE IF EXISTS tbl_score;
CREATE TABLE tbl_score (
    s_id int NOT NULL,
    c_id int NOT NULL,
    score int DEFAULT NULL,
    PRIMARY KEY (s_id, c_id)
);

INSERT INTO tbl_score VALUES (1,1,98),(1,2,75),(1,3,80),(1,4,82),(1,5,73),(1,6,88),(2,1,99),(2,2,76),(2,3,68),(2,4,71),(2,5,75),(3,1,75),(3,2,87),(3,3,65),(3,4,77),(3,5,82),(4,1,82),(4,2,83),(4,3,56),(4,4,68),(4,5,79),(4,6,88),(5,1,76),(5,2,73),(5,3,55),(5,4,61),(5,5,76),(5,6,59),(6,1,95),(6,2,63),(6,3,48),(6,4,77),(6,5,79),(6,6,81);

DROP TABLE IF EXISTS tbl_student;
CREATE TABLE tbl_student (
    s_id int NOT NULL AUTO_INCREMENT,
    s_name varchar(50) DEFAULT NULL,
    PRIMARY KEY (s_id)
);

INSERT INTO tbl_student VALUES (1,'Alice'),(2,'TOM'),(3,'Bob'),(4,'Kate'),(5,'Mike'),(6,'Betty');
