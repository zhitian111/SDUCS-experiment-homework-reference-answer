CREATE TABLE TEST3_06 AS
    SELECT
        *
    FROM
        PUB.STUDENT_31;


DROP TABLE TEST3_06;

DELETE FROM TEST3_06
WHERE
    (INSTR(NAME, ' ') != 0
    OR LENGTH(NAME)<2)
    OR (SUBSTR(TEST3_06.SID, 1, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 2, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 3, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 4, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 5, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 6, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 7, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 8, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 9, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 10, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 11, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_06.SID, 12, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9'))
    OR (2012 - EXTRACT(YEAR FROM BIRTHDAY) != AGE)
    OR( TEST3_06.SEX IS NOT NULL
    AND TEST3_06.SEX != '男'
    AND TEST3_06.SEX != '女')
    OR ( INSTR(DNAME, ' ') != 0
    OR DNAME IS NULL
    OR LENGTH(DNAME)<3)
    OR(LENGTH(CLASS)>4);