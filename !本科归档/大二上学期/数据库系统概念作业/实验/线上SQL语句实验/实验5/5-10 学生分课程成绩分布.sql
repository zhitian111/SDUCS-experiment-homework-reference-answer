CREATE OR REPLACE VIEW TEST5_10 AS
    SELECT
        CID,
        CNAME,
        SCORE,
        COUNT1,
        COUNT0,
        ROUND(COUNT1*100/COUNT0, 2) AS PERCENTAGE
    FROM
        (
            SELECT
                CID,
                NAME                                       AS CNAME,
                SCORE,
                COUNT(*)                                   AS COUNT1,
                SUM(COUNT(*)) OVER(PARTITION BY CID, NAME) AS COUNT0
            FROM
                (
                    SELECT
                        PUB.COURSE.CID,
                        PUB.COURSE.NAME,
                        TO_CHAR(TRUNC(PUB.STUDENT_COURSE.SCORE, -1), 'fm000')
                        ||'-'
                        ||TO_CHAR(TRUNC(PUB.STUDENT_COURSE.SCORE, -1)+9, 'fm000') AS SCORE
                    FROM
                        PUB.STUDENT_COURSE,
                        PUB.COURSE
                    WHERE
                        PUB.STUDENT_COURSE.CID = PUB.COURSE.CID
                        AND SCORE>=60
                        AND SCORE<=149
                )
            GROUP BY
                CID,
                NAME,
                SCORE
        );

