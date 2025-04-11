SELECT
    NAME
FROM
    (
        SELECT
            CHAMPION.NAME,
            COUNT(
                CASE RANK
                    WHEN 1 THEN
                        1
                    ELSE
                        NULL
                END) AS TIMES
        FROM
            PICK
            JOIN CHAMPION
            ON PICK.CID = CHAMPION.CID
        GROUP BY
            PICK.CID
        ORDER BY
            COUNT(
                CASE RANK
                    WHEN 1 THEN
                        1
                    ELSE
                        NULL
                END) DESC LIMIT 1
    );