CREATE TABLE TEST4_03 AS
    SELECT
        *
    FROM
        PUB.STUDENT_41;

DROP TABLE TEST4_03;

ALTER TABLE TEST4_03
    ADD SUM_CREDIT NUMBER(
        4,
        1
    );
    

UPDATE TEST4_03
SET
    SUM_CREDIT = (
        SELECT
            SUM(CREDIT)
        FROM
            (
                SELECT
                    DISTINCT SID SIDED,
                    CID CIDED
                FROM
                    PUB.STUDENT_COURSE
                WHERE
                    SCORE>=60
            )          
            JOIN PUB.COURSE
            ON CIDED = PUB.COURSE.CID
        WHERE
            SIDED = TEST4_03.SID
    );