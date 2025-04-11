CREATE TABLE TEST3_01 AS
    SELECT
        *
    FROM
        PUB.STUDENT_31;


DROP TABLE TEST3_01;

DELETE FROM TEST3_01
WHERE
    SUBSTR(TEST3_01.SID, 1, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 2, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 3, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 4, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 5, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 6, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 7, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 8, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 9, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 10, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 11, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    OR SUBSTR(TEST3_01.SID, 12, 1) NOT IN ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9');