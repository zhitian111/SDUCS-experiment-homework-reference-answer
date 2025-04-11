CREATE TABLE TEST9_01 LIKE PUB.STUDENT_11_1;

CREATE TABLE TEST9_01 AS
    SELECT
        *
    FROM
        PUB.STUDENT_11_1
    WHERE
        1=0;

CREATE UNIQUE INDEX TEST9_01_INDEX ON TEST9_01 (SID);

INSERT INTO TEST9_01 (
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
        SEX = '女';

INSERT INTO TEST9_01 (
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
        SEX = '女' AND pub.STUDENT_11_1.SID NOT IN (SELECT SID FROM TEST9_01);

INSERT INTO TEST9_01 (
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
        SEX = '女' AND pub.STUDENT_11_2.SID NOT IN (SELECT SID FROM TEST9_01);