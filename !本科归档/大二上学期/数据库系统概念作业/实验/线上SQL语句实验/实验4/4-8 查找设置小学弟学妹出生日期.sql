CREATE TABLE TEST4_08 AS
    SELECT
        *
    FROM
        PUB.STUDENT_42
    WHERE
        INSTR(NAME, ' ')=0
        AND INSTR(DNAME, ' ')=0
        AND SEX IN ('男', '女');

DROP TABLE TEST4_08;

ALTER TABLE TEST4_08
    ADD (
        BIRTHDAY1 DATE
    );

UPDATE TEST4_08
SET
    BIRTHDAY1 = (
        SELECT
            TO_DATE(YEAR
                    || '-'
                    || MONTH
                    || '-'
                    || DAY, 'YYYY-MM-DD')
        FROM
            (
                SELECT
                    EXTRACT(MONTH FROM BIRTHDAY)     AS MONTH,
                    EXTRACT(DAY FROM BIRTHDAY)       AS DAY,
                    MAX(EXTRACT(YEAR FROM BIRTHDAY)) AS YEAR
                FROM
                    TEST4_08
                GROUP BY
                    EXTRACT(MONTH FROM BIRTHDAY),
                    EXTRACT(DAY FROM BIRTHDAY)
            )
        WHERE
            MONTH = EXTRACT(MONTH FROM BIRTHDAY)
            AND DAY = EXTRACT(DAY FROM BIRTHDAY)
    );