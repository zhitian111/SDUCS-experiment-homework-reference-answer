CREATE OR REPLACE VIEW TEST2_03 AS
    SELECT
        DISTINCT PUB.STUDENT.SID,
        PUB.STUDENT.NAME
    FROM
        PUB.STUDENT,
        PUB.STUDENT_COURSE,
        PUB.COURSE
    WHERE
        PUB.STUDENT_COURSE.CID IN (
            SELECT
                CID
            FROM
                PUB.COURSE
            WHERE
                FCID = '300002'
        )
        AND PUB.STUDENT_COURSE.SID = PUB.STUDENT.SID;