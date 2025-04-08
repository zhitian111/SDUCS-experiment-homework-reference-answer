CREATE TABLE TEST4_10 AS
    SELECT
        *
    FROM
        PUB.STUDENT_42
    WHERE
        INSTR(NAME, ' ')=0
        AND INSTR(DNAME, ' ')=0
        AND SEX IN ('男', '女');

DROP TABLE TEST4_10;

ALTER TABLE TEST4_10
    ADD SID1 CHAR(
        12
    );

UPDATE TEST4_10
SET
    SID1 = NULL;

UPDATE TEST4_10
SET
    SID1 = (
        SELECT
            SID
        FROM
            (
                SELECT
                    MAX(SID) AS SID,
                    MONTH,
                    DAY
                FROM
                    (
                        SELECT
                            SID,
                            EXTRACT(MONTH FROM BIRTHDAY) AS MONTH,
                            EXTRACT(DAY FROM BIRTHDAY)   AS DAY
                        FROM
                            TEST4_10
                        WHERE
                            BIRTHDAY IN (
                                SELECT
                                    BIRTH
                                FROM
                                    (
                                        SELECT
                                            EXTRACT(MONTH FROM BIRTHDAY) AS MONTH,
                                            EXTRACT(DAY FROM BIRTHDAY)   AS DAY,
                                            MAX(BIRTHDAY)                AS BIRTH
                                        FROM
                                            (
                                                SELECT
                                                    *
                                                FROM
                                                    TEST4_10
                                                WHERE
                                                    SEX = '男'
                                            )
                                        GROUP BY
                                            EXTRACT(MONTH FROM BIRTHDAY),
                                            EXTRACT(DAY FROM BIRTHDAY)
                                    )        
                            )
                            AND SEX = '男'
                    )
                GROUP BY
                    MONTH,
                    DAY
            )
        WHERE
            MONTH = EXTRACT(MONTH FROM BIRTHDAY)
            AND DAY = EXTRACT(DAY FROM BIRTHDAY)
            AND SEX = '女'
    )
WHERE
    SEX = '女';

UPDATE TEST4_10
SET
    SID1 = (
        SELECT
            SID
        FROM
            (
                SELECT
                    MAX(SID) AS SID,
                    MONTH,
                    DAY
                FROM
                    (
                        SELECT
                            SID,
                            EXTRACT(MONTH FROM BIRTHDAY) AS MONTH,
                            EXTRACT(DAY FROM BIRTHDAY)   AS DAY
                        FROM
                            TEST4_10
                        WHERE
                            BIRTHDAY IN (
                                SELECT
                                    BIRTH
                                FROM
                                    (
                                        SELECT
                                            EXTRACT(MONTH FROM BIRTHDAY) AS MONTH,
                                            EXTRACT(DAY FROM BIRTHDAY)   AS DAY,
                                            MAX(BIRTHDAY)                AS BIRTH
                                        FROM
                                            (
                                                SELECT
                                                    *
                                                FROM
                                                    TEST4_10
                                                WHERE
                                                    SEX = '女'
                                            )
                                        GROUP BY
                                            EXTRACT(MONTH FROM BIRTHDAY),
                                            EXTRACT(DAY FROM BIRTHDAY)
                                    )        
                            )
                            AND SEX = '女'
                    )
                GROUP BY
                    MONTH,
                    DAY
            )
        WHERE
            MONTH = EXTRACT(MONTH FROM BIRTHDAY)
            AND DAY = EXTRACT(DAY FROM BIRTHDAY)
            AND SEX = '男'
    )
WHERE
    SEX = '男';