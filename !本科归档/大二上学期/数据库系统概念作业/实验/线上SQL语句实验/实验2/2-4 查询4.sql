CREATE OR REPLACE VIEW TEST2_04 AS
    SELECT
        PUB.STUDENT.SID,
        PUB.STUDENT.NAME
    FROM
        PUB.STUDENT,
        PUB.STUDENT_COURSE
    WHERE
        PUB.STUDENT.SID IN(
            SELECT
                PUB.STUDENT_COURSE.SID
            FROM
                PUB.STUDENT_COURSE
            WHERE
                PUB.STUDENT_COURSE.CID IN(
                    SELECT
                        PUB.COURSE.CID
                    FROM
                        PUB.COURSE
                    WHERE
                        PUB.COURSE.NAME = '操作系统'
                )
        )
        AND PUB.STUDENT.SID IN(
            SELECT
                PUB.STUDENT_COURSE.SID
            FROM
                PUB.STUDENT_COURSE
            WHERE
                PUB.STUDENT_COURSE.CID IN(
                    SELECT
                        PUB.COURSE.CID
                    FROM
                        PUB.COURSE
                    WHERE
                        PUB.COURSE.NAME = '数据结构'
                )
        )
        AND PUB.STUDENT.SID NOT IN(
            SELECT
                PUB.STUDENT_COURSE.SID
            FROM
                PUB.STUDENT_COURSE
            WHERE
                PUB.STUDENT_COURSE.CID IN(
                    SELECT
                        PUB.COURSE.CID
                    FROM
                        PUB.COURSE
                    WHERE
                        PUB.COURSE.NAME = '程序设计语言'
                )
        );
