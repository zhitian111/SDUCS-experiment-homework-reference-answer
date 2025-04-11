CREATE OR REPLACE VIEW TEST5_07 AS WITH CITE AS (
    SELECT
        SID,
        CID
    FROM
        PUB.STUDENT_COURSE
)
    SELECT
        PUB.STUDENT_COURSE.SID,
        PUB.STUDENT.NAME,
        PUB.STUDENT.DNAME,
        MAX(
            CASE
                WHEN PUB.COURSE.NAME = '数据结构' THEN
                    PUB.STUDENT_COURSE.SCORE
                ELSE
                    NULL
            END) AS DS_SCORE,
        MAX(
            CASE
                WHEN PUB.COURSE.NAME = '操作系统' THEN
                    PUB.STUDENT_COURSE.SCORE
                ELSE
                    NULL
            END) AS OS_SCORE
    FROM
        PUB.STUDENT_COURSE
        JOIN PUB.STUDENT
        ON PUB.STUDENT_COURSE.SID = PUB.STUDENT.SID
        JOIN PUB.COURSE
        ON PUB.STUDENT_COURSE.CID = PUB.COURSE.CID
    WHERE
        ((PUB.STUDENT_COURSE.SID, 300002) IN (
            SELECT
                SID,
                CID
            FROM
                CITE
        )
        OR (PUB.STUDENT_COURSE.SID, 300005) IN (
            SELECT
                SID,
                CID
            FROM
                CITE
        ))
        AND PUB.STUDENT.DNAME = '计算机科学与技术学院'
    GROUP BY
        PUB.STUDENT_COURSE.SID,
        PUB.STUDENT.NAME,
        PUB.STUDENT.DNAME;