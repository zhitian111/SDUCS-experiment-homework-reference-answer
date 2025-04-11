CREATE TABLE TEST4_02 AS
    SELECT
        *
    FROM
        PUB.STUDENT_41;


ALTER TABLE TEST4_02
    ADD AVG_SCORE NUMBER(
        5,
        1
    );

UPDATE TEST4_02
SET
    AVG_SCORE = (
        SELECT
            AVG_SCORE
        FROM
            (
                SELECT
                    PUB.STUDENT_COURSE.SID,
                    AVG(PUB.STUDENT_COURSE.SCORE) AS AVG_SCORE
                FROM
                    PUB.STUDENT_COURSE
                GROUP BY
                    PUB.STUDENT_COURSE.SID
            )
        WHERE
            SID = TEST4_02.SID
    );
    