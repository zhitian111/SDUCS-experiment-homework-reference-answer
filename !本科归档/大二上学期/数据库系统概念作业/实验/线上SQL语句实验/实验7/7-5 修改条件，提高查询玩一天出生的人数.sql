CREATE OR REPLACE VIEW TEST7_05 AS
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
                        BIRTHDAY=T1.BIRTHDAY+1
                ) NEXTBIRTHDAY
            FROM
                PUB.STUDENT_TESTINDEX T1
        )
    WHERE
        NEXTBIRTHDAY=7;