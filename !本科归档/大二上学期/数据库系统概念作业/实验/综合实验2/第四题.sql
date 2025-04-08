SELECT
    VIDEO.[NAME],
    VIDEO.CONTENT,
    T.NUM
FROM
    VIDEO,
    (
        SELECT
            VID,
            COUNT(*) AS NUM
        FROM
            WATCH
        GROUP BY
            VID
    )     AS T
WHERE
    VIDEO.VID = T.VID
ORDER BY
    T.NUM DESC LIMIT 10;