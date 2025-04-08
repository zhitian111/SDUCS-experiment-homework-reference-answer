SELECT
    NICKNAME,
    PROFILE,
    USERLEVEL
FROM
    [USER]
WHERE
    (USER.UID, 15) IN (
        SELECT
            UID_FOLLOWER,
            UID_FOLLOWED
        FROM
            FOLLOW
    )
    AND (15, USER.UID) IN (
        SELECT
            UID_FOLLOWER,
            UID_FOLLOWED
        FROM
            FOLLOW
    );