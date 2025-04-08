CREATE OR REPLACE VIEW TEST6_07 AS
    SELECT
        PUB.STUDENT.SID,
        PUB.STUDENT.NAME
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
                        COUNT(DISTINCT CID) AS CNT,
                        COUNT(
                            CASE
                                WHEN SCORE<60 THEN
                                    1
                                ELSE
                                    NULL
                            END)            AS SC
                    FROM
                        PUB.STUDENT_COURSE
                    GROUP BY
                        SID
                    HAVING
                        COUNT(DISTINCT CID)=140
                        AND COUNT(
                            CASE
                                WHEN SCORE<60 THEN
                                    1
                                ELSE
                                    NULL
                            END) = 0
                )           
        );


