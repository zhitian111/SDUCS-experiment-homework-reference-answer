CREATE TABLE TEST4_07 AS
    SELECT
        *
    FROM
        PUB.STUDENT_42;

DROP TABLE TEST4_07;

UPDATE TEST4_07
SET
    SEX = REPLACE(
        SEX,
        ' ',
        ''
    ),
    CLASS = REPLACE(
        CLASS,
        ' ',
        ''
    );

UPDATE TEST4_07
SET
    SEX = REPLACE(
        SEX,
        '性',
        ''
    ),
    CLASS = REPLACE(
        CLASS,
        '级',
        ''
    );


UPDATE TEST4_07
SET
    SEX = SUBSTR(
        SEX,
        1,
        1
    ),
    CLASS = SUBSTR(
        CLASS,
        1,
        4
    );


UPDATE TEST4_07
SET
    AGE = (
        2012 - EXTRACT(YEAR FROM BIRTHDAY)
    )
WHERE
    AGE IS NULL;