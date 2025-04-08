CREATE OR REPLACE VIEW TEST7_04 AS
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
                        PUB.STUDENT
                    WHERE
                        BIRTHDAY BETWEEN TO_DATE(SUBSTR(TO_CHAR(T1.BIRTHDAY, 'YYYY-MM-DD'), 1, 7)
                                                 ||'-01', 'YYYY-MM-DD') AND ADD_MONTHS(TO_DATE(SUBSTR(TO_CHAR(T1.BIRTHDAY, 'YYYY-MM-DD'), 1, 7)
                                                                                               ||'-01', 'YYYY-MM-DD'), 1)-1
                ) SAMEYEARMONTH,
                (
                    SELECT
                        COUNT(*)
                    FROM
                        PUB.STUDENT
                    WHERE
                        BIRTHDAY BETWEEN TO_DATE(SUBSTR(TO_CHAR(T1.BIRTHDAY, 'YYYY-MM-DD'), 1, 4)
                                                 ||'-01-01', 'YYYY-MM-DD') AND TO_DATE(SUBSTR(TO_CHAR(T1.BIRTHDAY, 'YYYY-MM-DD'), 1, 4)
                                                                                       ||'-12-31', 'YYYY-MM-DD')
                ) SAMEYEAR
            FROM
                PUB.STUDENT_TESTINDEX T1
        )
    WHERE
        SAMEYEARMONTH=35;