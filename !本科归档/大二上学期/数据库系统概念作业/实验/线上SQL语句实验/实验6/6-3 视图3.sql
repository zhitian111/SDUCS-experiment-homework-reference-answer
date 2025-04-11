CREATE OR REPLACE VIEW TEST6_03 AS
    SELECT
        CID,
        NAME,
        MAX_SCORE,
        COUNT(DISTINCT SID) AS MAX_SCORE_COUNT
    FROM
        (
            SELECT
                CCID      AS CID,
                CNAME     AS NAME,
                MAX_SCORE,
                PUB.STUDENT_COURSE.SID
            FROM
                (
                    SELECT
                        PUB.STUDENT_COURSE.CID AS CCID,
                        PUB.COURSE.NAME AS CNAME,
                        MAX(PUB.STUDENT_COURSE.SCORE) AS MAX_SCORE
                    FROM
                        PUB.STUDENT_COURSE,
                        PUB.COURSE
                    WHERE
                        PUB.STUDENT_COURSE.CID = PUB.COURSE.CID
                    GROUP BY
                        PUB.STUDENT_COURSE.CID,
                        PUB.COURSE.NAME
                ),
                PUB.STUDENT_COURSE
            WHERE
                PUB.STUDENT_COURSE.CID = CCID
                AND PUB.STUDENT_COURSE.SCORE = MAX_SCORE
        )
    GROUP BY
        CID,
        NAME,
        MAX_SCORE;