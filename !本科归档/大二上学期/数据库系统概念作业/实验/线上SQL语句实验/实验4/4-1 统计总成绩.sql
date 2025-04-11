CREATE TABLE TEST4_01 AS
    SELECT
        *
    FROM
        PUB.STUDENT_41;

ALTER TABLE TEST4_01
    ADD SUM_SCORE NUMBERIC(
        6,
        1
    );


DROP TABLE TEST4_01;

UPDATE TEST4_01
SET
    SUM_SCORE = (
        SELECT
            SUM
        FROM
            (
                SELECT
                    PUB.STUDENT_COURSE.SID,
                    SUM(SCORE) AS SUM
                FROM
                    PUB.STUDENT_COURSE
                GROUP BY
                    PUB.STUDENT_COURSE.SID
            )
        WHERE
            TEST4_01.SID = SID
    );