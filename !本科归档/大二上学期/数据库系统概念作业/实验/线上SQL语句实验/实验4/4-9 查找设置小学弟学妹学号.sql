CREATE TABLE TEST4_09 AS
    SELECT
        *
    FROM
        PUB.STUDENT_42
    WHERE
        SEX IN ('男', '女')
        AND INSTR(NAME, ' ') =0
        AND INSTR(DNAME, ' ') = 0;

DROP TABLE TEST4_09;

ALTER TABLE TEST4_09 ADD SID1 CHAR(
    12
);

UPDATE TEST4_09
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
                            TEST4_09
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
                                            TEST4_09
                                        GROUP BY
                                            EXTRACT(MONTH FROM BIRTHDAY),
                                            EXTRACT(DAY FROM BIRTHDAY)
                                    )        
                            )
                    )
                GROUP BY
                    MONTH,
                    DAY
            )
        WHERE
            MONTH = EXTRACT(MONTH FROM BIRTHDAY)
            AND DAY = EXTRACT(DAY FROM BIRTHDAY)
    );