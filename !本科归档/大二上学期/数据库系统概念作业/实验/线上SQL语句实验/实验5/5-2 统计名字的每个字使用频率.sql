CREATE TABLE TEST5_02(
    LETTER VARCHAR(2),
    FREQUENCY NUMERIC(4)
);

INSERT INTO TEST5_02(
    LETTER,
    FREQUENCY
)
    SELECT
        LETTER,
        COUNT(LETTER) AS FREQUENCY
    FROM
        (
            SELECT
                SUBSTR(NAME, 2, 1)AS LETTER
            FROM
                PUB.STUDENT
            UNION
            ALL
            SELECT
                SUBSTR(NAME, 3, 1)AS LETTER
            FROM
                PUB.STUDENT
        )
    GROUP BY
        LETTER
    HAVING
        LETTER != ' '           ;