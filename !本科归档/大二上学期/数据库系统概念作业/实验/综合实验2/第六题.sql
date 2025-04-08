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
    ) AS T
WHERE
    VIDEO.VID = T.VID
    AND VIDEO.CHANEL = "美食"
ORDER BY
    T.NUM DESC LIMIT 5;