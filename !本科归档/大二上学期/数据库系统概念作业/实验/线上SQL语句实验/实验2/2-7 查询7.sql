﻿CREATE OR REPLACE VIEW TEST2_07 AS
    SELECT
        DISTINCT PUB.STUDENT.SID,
        PUB.STUDENT.NAME
    FROM
        PUB.STUDENT,
        PUB.STUDENT_COURSE
    WHERE
        PUB.STUDENT.SID NOT IN(
            SELECT
                PUB.STUDENT_COURSE.SID
            FROM
                PUB.STUDENT_COURSE
        );