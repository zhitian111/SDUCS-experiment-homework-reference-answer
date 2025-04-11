CREATE TABLE TEST7_02 AS
    SELECT
        SID,
        NAME,
        BIRTHDAY
    FROM
        PUB.STUDENT;

UPDATE TEST7_02
SET
    BIRTHDAY=TO_DATE(
        '19881018',
        'yyyymmdd'
    )
WHERE
    SUBSTR(SID, 12, 1)= '0';

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
                    TEST7_02
                WHERE
                    NAME=T1.NAME
                    AND BIRTHDAY=T1.BIRTHDAY
            ) SAMENAMEBIRTHDAY,
            (
                SELECT
                    COUNT(*)
                FROM
                    TEST7_02
                WHERE
                    BIRTHDAY=T1.BIRTHDAY
            ) SAMEBIRTHDAY
        FROM
            PUB.STUDENT_TESTINDEX T1
    )
WHERE
    SAMEBIRTHDAY=403;

CREATE INDEX TEST7_02_INDEX ON TEST7_02 (BIRTHDAY);

DROP INDEX TEST7_02_INDEX;