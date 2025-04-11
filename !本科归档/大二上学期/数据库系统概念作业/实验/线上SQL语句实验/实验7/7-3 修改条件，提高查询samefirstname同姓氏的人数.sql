CREATE OR REPLACE VIEW TEST7_03 AS
    SELECT
        *
    FROM
        (
            SELECT
                SID,
                NAME,
                BIRTHDAY,
                (
                    SELECT
                        COUNT(*)
                    FROM
                        PUB.STUDENT
                    WHERE
                        NAME LIKE SUBSTR(T1.NAME, 1, 1)
                                  ||'%'
                ) SAMEFIRSTNAME
            FROM
                PUB.STUDENT_TESTINDEX T1
        )
    WHERE
        SAMEFIRSTNAME=7;