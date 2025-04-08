CREATE TABLE TEST5_04(
    DNAME VARCHAR(30),
    CLASS VARCHAR(10),
    P_COUNT1 INT,
    P_COUNT2 INT,
    P_COUNT INT
);

DROP TABLE TEST5_04;

INSERT INTO TEST5_04(
    DNAME,
    CLASS,
    P_COUNT1
)
    SELECT
        DNAME,
        CLASS,
        SUM(
            CASE
                WHEN SUM_SCORE >= 10 AND CLASS > 2008 THEN
                    1
                WHEN SUM_SCORE >= 8 AND CLASS <= 2008 THEN
                    1
                ELSE
                    0
            END) AS P_COUNT
    FROM
        (
            SELECT
                DNAME,
                CLASS,
                SNAME,
                SUM(CREDIT) AS SUM_SCORE
            FROM
                (
                    SELECT
                        PUB.STUDENT.DNAME,
                        PUB.STUDENT.CLASS,
                        PUB.STUDENT.SID AS SNAME,
                        PUB.COURSE.CID AS CNAME,
                        CASE
                            WHEN PUB.STUDENT_COURSE.SCORE >= 60 THEN
                                PUB.COURSE.CREDIT
                            ELSE
                                0
                        END AS CREDIT,
                        MAX(PUB.STUDENT_COURSE.SCORE) AS SCORE
                    FROM
                        PUB.STUDENT,
                        PUB.COURSE,
                        PUB.STUDENT_COURSE
                    WHERE
                        PUB.STUDENT.SID = PUB.STUDENT_COURSE.SID
                        AND PUB.COURSE.CID = PUB.STUDENT_COURSE.CID
                        AND PUB.STUDENT.DNAME IS NOT NULL
                    GROUP BY
                        PUB.STUDENT.DNAME,
                        PUB.STUDENT.CLASS,
                        PUB.STUDENT.SID,
                        PUB.COURSE.CID,
                        CASE
                            WHEN PUB.STUDENT_COURSE.SCORE >= 60 THEN
                                PUB.COURSE.CREDIT
                            ELSE
                                0
                        END
                )
            GROUP BY
                DNAME,
                CLASS,
                SNAME
        )
    GROUP BY
        DNAME,
        CLASS;

UPDATE TEST5_04
SET
    P_COUNT = (
        SELECT
            COUNT(*)
        FROM
            PUB.STUDENT
        WHERE
            DNAME = TEST5_04.DNAME
            AND CLASS = TEST5_04.CLASS
    );



UPDATE TEST5_04
SET
    P_COUNT2 = P_COUNT-P_COUNT1;
