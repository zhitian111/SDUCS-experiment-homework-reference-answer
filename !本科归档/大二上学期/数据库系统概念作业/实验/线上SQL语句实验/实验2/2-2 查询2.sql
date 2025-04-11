create
or REPLACE view test2_02 AS
WITH CTE AS (
    SELECT
        CID
    FROM
        PUB.STUDENT_COURSE
    WHERE
        SID = '200900130417'
)
SELECT
    DISTINCT PUB.STUDENT.SID,
    PUB.STUDENT.NAME
FROM
    PUB.STUDENT,
    PUB.STUDENT_COURSE
WHERE
    PUB.STUDENT.SID IN (
        SELECT
            SID
        FROM
            PUB.STUDENT_COURSE
        WHERE
            PUB.STUDENT_COURSE.CID IN (
                SELECT
                    CID
                FROM
                    CTE
            )
    )
    AND PUB.STUDENT.SID != '200900130417';