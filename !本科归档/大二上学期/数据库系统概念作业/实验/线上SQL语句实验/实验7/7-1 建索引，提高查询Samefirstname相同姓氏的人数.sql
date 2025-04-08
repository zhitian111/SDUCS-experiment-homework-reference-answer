CREATE TABLE TEST7_01 AS
    SELECT
        SID,
        NAME,
        BIRTHDAY
    FROM
        PUB.STUDENT;

DROP TABLE TEST7_01;

SELECT
    *
FROM
    (
        SELECT
            SID,
            NAME,
            BIRTHDAY,
            (
                SELECT
                    COUNT(*)
                FROM
                    TEST7_01
                WHERE
                    SUBSTR(NAME, 2)=SUBSTR(T1.NAME, 2)
            ) SAMEFIRSTNAME
        FROM
            PUB.STUDENT_TESTINDEX T1
    )
WHERE
    SAMEFIRSTNAME=10;


CREATE INDEX TEST7_01_INDEX ON TEST7_01 (SUBSTR(NAME, 2));