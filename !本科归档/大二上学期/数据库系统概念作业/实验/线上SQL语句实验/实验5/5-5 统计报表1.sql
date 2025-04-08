CREATE OR REPLACE VIEW TEST5_05 AS
    SELECT
        PUB.STUDENT.DNAME,
        ROUND(AVG(
            CASE
                WHEN PUB.COURSE.NAME='数据结构' THEN
                    SCORE
                ELSE
                    NULL
            END), 0) AS AVG_DS_SCORE,
        ROUND(AVG(
            CASE
                WHEN PUB.COURSE.NAME='操作系统' THEN
                    SCORE
                ELSE
                    NULL
            END), 0) AS AVG_OS_SCORE
    FROM
        (
            SELECT
                PUB.STUDENT_COURSE.SID AS SSID,
                PUB.STUDENT_COURSE.CID AS CCID,
                MAX(PUB.STUDENT_COURSE.SCORE) AS SCORE
            FROM
                PUB.STUDENT_COURSE
            GROUP BY
                PUB.STUDENT_COURSE.SID,
                PUB.STUDENT_COURSE.CID
        )
        JOIN PUB.STUDENT
        ON PUB.STUDENT.SID = SSID
        JOIN PUB.COURSE
        ON CCID = PUB.COURSE.CID
    WHERE
        PUB.STUDENT.DNAME IS NOT NULL
    GROUP BY
        PUB.STUDENT.DNAME           ;
