﻿CREATE TABLE TEST3_08 AS
    SELECT
        *
    FROM
        PUB.STUDENT_COURSE_32;

DROP TABLE TEST3_08;


DELETE FROM TEST3_08
WHERE
    TEST3_08.SID NOT IN (
        SELECT
            PUB.STUDENT.SID
        FROM
            PUB.STUDENT
    )
    OR (TEST3_08.CID, TEST3_08.TID) NOT IN (
        SELECT
            PUB.TEACHER_COURSE.CID,
            PUB.TEACHER_COURSE.TID
        FROM
            PUB.TEACHER_COURSE
    );