CREATE OR REPLACE VIEW TEST6_06 AS
    SELECT
        SID,
        NAME
    FROM
        PUB.STUDENT
    WHERE
        PUB.STUDENT.SID IN (
            SELECT
                SID
            FROM
                (
                    SELECT
                        SID,
                        CID,
                        COUNT(SCORE) AS CNT
                    FROM
                        PUB.STUDENT_COURSE
                    WHERE
                        SCORE<60
                    GROUP BY
                        SID,
                        CID
                    HAVING
                        COUNT(SCORE)>=2
                )           
        );