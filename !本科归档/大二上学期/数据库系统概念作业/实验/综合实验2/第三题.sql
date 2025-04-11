SELECT
    NICKNAME,
    PROFILE,
    [USERLEVEL],
    NUM
FROM
    (
        SELECT
            UID_FOLLOWED,
            COUNT(*) AS NUM
        FROM
            FOLLOW
        GROUP BY
            UID_FOLLOWED
    ),
    [USER]
WHERE
    UID_FOLLOWED = USER.UID
ORDER BY
    NUM DESC LIMIT 10;