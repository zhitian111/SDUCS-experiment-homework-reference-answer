CREATE TABLE TEST4_04 AS
    SELECT
        *
    FROM
        PUB.STUDENT_41;

DROP TABLE TEST4_04;

UPDATE TEST4_04
SET
    TEST4_04.DNAME = (
        SELECT
            DID
        FROM
            PUB.DEPARTMENT
        WHERE
            PUB.DEPARTMENT.DNAME = TEST4_04.DNAME
    )
WHERE
    TEST4_04.DNAME IN (
        SELECT
            DNAME
        FROM
            PUB.DEPARTMENT
    );