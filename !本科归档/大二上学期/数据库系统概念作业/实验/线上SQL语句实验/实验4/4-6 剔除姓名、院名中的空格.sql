CREATE TABLE TEST4_06 AS
    SELECT
        *
    FROM
        PUB.STUDENT_42;

DROP TABLE TEST4_06;

UPDATE TEST4_06
SET
    NAME = REPLACE(
        NAME,
        ' ',
        ''
    ),
    DNAME = REPLACE(
        DNAME,
        ' ',
        ''
    );