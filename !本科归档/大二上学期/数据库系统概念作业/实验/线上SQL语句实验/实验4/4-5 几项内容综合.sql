CREATE TABLE TEST4_05 AS
    SELECT
        *
    FROM
        PUB.STUDENT_41;

DROP TABLE TEST4_05;


ALTER TABLE TEST4_05
    ADD SUM_SCORE NUMBER(
        6,
        1
    );

UPDATE TEST4_05
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
            TEST4_05.SID = SID
    );


ALTER TABLE TEST4_05
    ADD AVG_SCORE NUMBER(
        5,
        1
    );


UPDATE TEST4_05
SET
    AVG_SCORE = (
        SELECT
            AVG_SCORE
        FROM
            (
                SELECT
                    PUB.STUDENT_COURSE.SID,
                    ROUND(AVG(PUB.STUDENT_COURSE.SCORE), 1) AS AVG_SCORE
                FROM
                    PUB.STUDENT_COURSE
                GROUP BY
                    PUB.STUDENT_COURSE.SID
            )
        WHERE
            SID = TEST4_05.SID
    );

ALTER TABLE TEST4_05
    ADD SUM_CREDIT NUMBER(
        4,
        1
    );
    
UPDATE TEST4_05
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
            SIDED = TEST4_05.SID
    );

ALTER TABLE TEST4_05
    ADD DID VARCHAR(
        2
    );


UPDATE TEST4_05
SET
    TEST4_05.DID = (
        SELECT
            PUB.DEPARTMENT.DID
        FROM
            PUB.DEPARTMENT
        WHERE
            PUB.DEPARTMENT.DNAME = TEST4_05.DNAME
    )
WHERE
    TEST4_05.DNAME IN (
        SELECT
            DNAME
        FROM
            PUB.DEPARTMENT
    );

UPDATE TEST4_05
SET
    TEST4_05.DID = (
        SELECT
            PUB.DEPARTMENT_41.DID
        FROM
            PUB.DEPARTMENT_41
        WHERE
            PUB.DEPARTMENT_41.DNAME = TEST4_05.DNAME
    )
WHERE
    TEST4_05.DNAME IN (
        SELECT
            DNAME
        FROM
            PUB.DEPARTMENT_41
    );



UPDATE TEST4_05
SET
    TEST4_05.DID = (
        '00'
    )
WHERE
    (TEST4_05.DNAME NOT IN (
        SELECT
            DNAME
        FROM
            PUB.DEPARTMENT
    )
    OR TEST4_05.DNAME IS NULL)
    AND (TEST4_05.DNAME NOT IN (
        SELECT
            DNAME
        FROM
            PUB.DEPARTMENT_41
    )
    OR TEST4_05.DNAME IS NULL);