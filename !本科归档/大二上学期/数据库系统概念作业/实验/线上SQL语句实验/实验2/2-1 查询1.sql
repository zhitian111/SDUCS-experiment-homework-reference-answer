CREATE OR REPLACE VIEW TEST2_01 AS
    SELECT
        SID,
        NAME,
        SEX,
        AGE
    FROM
        PUB.STUDENT
    WHERE
        SUBSTR(NAME, 1, 1) != '张'
        AND SUBSTR(SEX, 1, 1) = '男'
        AND SUBSTR(NAME, 1, 1) != '李'
        AND AGE = 20
        AND INSTR(NAME, '建') != 0;