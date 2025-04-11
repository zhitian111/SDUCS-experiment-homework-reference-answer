CREATE TABLE TEST3_10 AS
    SELECT
        *
    FROM
        PUB.STUDENT_COURSE_32;


DROP TABLE TEST3_10;


DELETE FROM TEST3_10
WHERE
    (SID NOT IN (
        SELECT
            SID
        FROM
            PUB.STUDENT
    ))
    OR (CID NOT IN (
        SELECT
            CID
        FROM
            PUB.COURSE
    ))
    OR (TID NOT IN (
        SELECT
            TID
        FROM
            PUB.TEACHER
    ))
    OR (SCORE>100
    OR SCORE < 0)
    OR ((CID, TID) NOT IN (
        SELECT
            CID,
            TID
        FROM
            PUB.TEACHER_COURSE
    ));