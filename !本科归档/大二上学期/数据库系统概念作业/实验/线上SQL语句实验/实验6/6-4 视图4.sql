CREATE OR REPLACE VIEW TEST6_04 AS
    SELECT
        SID,
        NAME
    FROM
        PUB.STUDENT
    WHERE
        SEX = '男'
        AND (PUB.STUDENT.SID IN (
            SELECT
                SID
            FROM
                (
                    SELECT
                        *
                    FROM
                        PUB.STUDENT_COURSE
                    WHERE
                        CID = '300005'
                        AND SCORE >= 60
                )           
        )
        OR PUB.STUDENT.SID IN (
            SELECT
                SID
            FROM
                (
                    SELECT
                        *
                    FROM
                        PUB.STUDENT_COURSE
                    WHERE
                        CID = '300002'
                        AND SCORE >= 60
                )           
        ))
        AND PUB.STUDENT.SID NOT IN (
            SELECT
                SID
            FROM
                (
                    SELECT
                        *
                    FROM
                        PUB.STUDENT_COURSE
                    WHERE
                        CID = '300001'
                        AND SCORE >= 60
                )           
        );