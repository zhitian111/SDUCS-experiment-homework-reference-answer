CREATE OR REPLACE VIEW TEST5_08 AS
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
        PUB.STUDENT.DNAME = '计算机科学与技术学院'
        OR PUB.STUDENT.SID NOT IN (
            SELECT
                SID
            FROM
                PUB.STUDENT_COURSE
        )
    GROUP BY
        PUB.STUDENT_COURSE.SID,
        PUB.STUDENT.NAME,
        PUB.STUDENT.DNAME
    UNION
    ALL
    SELECT
        DISTINCT
        PUB.STUDENT.SID,
        PUB.STUDENT.NAME,
        PUB.STUDENT.DNAME,
        NULL     AS DS_SCORE,
        NULL     AS OS_SCORE
    FROM
        PUB.STUDENT_COURSE,
        PUB.STUDENT
    WHERE
        PUB.STUDENT.DNAME = '计算机科学与技术学院'
        AND PUB.STUDENT.SID NOT IN (
            SELECT
                SID
            FROM
                PUB.STUDENT_COURSE
        );
