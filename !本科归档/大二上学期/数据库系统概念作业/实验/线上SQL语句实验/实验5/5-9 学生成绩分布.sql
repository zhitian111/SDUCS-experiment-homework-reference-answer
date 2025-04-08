CREATE OR REPLACE VIEW TEST5_09 AS
    SELECT
        SCORE,
        COUNT1,
        COUNT0,
        ROUND(COUNT1/COUNT0*100, 2) AS PERCENTAGE
    FROM
        (
            SELECT
                SCORE,
                COUNT1,
                SUM(COUNT1) OVER () AS COUNT0
            FROM
                (
                    SELECT
                        SCORE,
                        COUNT(ALL SID) AS COUNT1
                    FROM
                        PUB.STUDENT_COURSE
                    WHERE
                        SCORE>=60
                    GROUP BY
                        SCORE
                )
        );