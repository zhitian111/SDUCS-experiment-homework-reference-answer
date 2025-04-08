CREATE TABLE TEST5_01(
    FIRST_NAME VARCHAR(4),
    FREQUENCY NUMERIC(4)
);

DROP TABLE TEST5_01;


INSERT INTO TEST5_01 (
    FIRST_NAME,
    FREQUENCY
)
    SELECT
        FIRST_NAME,
        FREQUENCY
    FROM
        (
            SELECT
                FIRST_NAME,
                COUNT(FIRST_NAME) AS FREQUENCY
            FROM
                (
                    SELECT
                        SUBSTR(NAME, 2, 3) AS FIRST_NAME
                    FROM
                        PUB.STUDENT
                )
            GROUP BY
                FIRST_NAME
        );
