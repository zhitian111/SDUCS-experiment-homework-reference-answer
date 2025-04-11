CREATE OR REPLACE VIEW TEST6_05 AS
    SELECT
        SID,
        NAME,
        ROUND(AVG(SCORE), 0) AS AVG_SCORE,
        SUM(SCORE)           AS SUM_SCORE
    FROM
        (
            SELECT
                PUB.STUDENT.SID,
                PUB.STUDENT.NAME,
                PUB.STUDENT_COURSE.CID,
                MAX(PUB.STUDENT_COURSE.SCORE) AS SCORE
            FROM
                PUB.STUDENT,
                PUB.STUDENT_COURSE
            WHERE
                PUB.STUDENT.SID = PUB.STUDENT_COURSE.SID
                AND PUB.STUDENT.AGE = 20
            GROUP BY
                PUB.STUDENT.SID,
                PUB.STUDENT.NAME,
                PUB.STUDENT_COURSE.CID
        )
    GROUP BY
        SID,
        NAME;