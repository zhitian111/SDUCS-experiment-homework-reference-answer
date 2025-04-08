SELECT
    *
FROM
    (
        SELECT
            [NICKNAME],
            COUNT(*) AS NUM
        FROM
            [USER]
            JOIN POST
            ON [USER].UID = POST.UID
        GROUP BY
            [USER].UID
    )
ORDER BY
    NUM DESC LIMIT 5;