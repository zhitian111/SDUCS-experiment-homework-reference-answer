CREATE TABLE TEST9_02 AS
    SELECT
        *
    FROM
        PUB.STUDENT_11_1
    WHERE
        1=0;

CREATE UNIQUE INDEX TEST9_02_INDEX ON TEST9_02 (SID);

INSERT INTO TEST9_02 (
    SID,
    NAME,
    SEX,
    AGE,
    BIRTHDAY,
    DNAME,
    CLASS
)
    SELECT
        SID,
        NAME,
        SEX,
        AGE,
        BIRTHDAY,
        DNAME,
        CLASS
    FROM
        PUB.STUDENT
    WHERE
        SEX='女'
        AND SID IN (
            SELECT
                SID
            FROM
                PUB.STUDENT_COURSE
            WHERE
                SCORE<60
        )
        AND SID NOT IN (
            SELECT
                SID
            FROM
                TEST9_02
        );

INSERT INTO TEST9_02 (
    SID,
    NAME,
    SEX,
    AGE,
    BIRTHDAY,
    DNAME,
    CLASS
)
    SELECT
        SID,
        NAME,
        SEX,
        AGE,
        BIRTHDAY,
        DNAME,
        CLASS
    FROM
        PUB.STUDENT_11_1
    WHERE
        SEX='女'
        AND SID IN (
            SELECT
                SID
            FROM
                PUB.STUDENT_COURSE
            WHERE
                SCORE<60
        )
        AND SID NOT IN (
            SELECT
                SID
            FROM
                TEST9_02
        );

INSERT INTO TEST9_02 (
    SID,
    NAME,
    SEX,
    AGE,
    BIRTHDAY,
    DNAME,
    CLASS
)
    SELECT
        SID,
        NAME,
        SEX,
        AGE,
        BIRTHDAY,
        DNAME,
        CLASS
    FROM
        PUB.STUDENT_11_2
    WHERE
        SEX='女'
        AND SID IN (
            SELECT
                SID
            FROM
                PUB.STUDENT_COURSE
            WHERE
                SCORE<60
        )
        AND SID NOT IN (
            SELECT
                SID
            FROM
                TEST9_02
        );