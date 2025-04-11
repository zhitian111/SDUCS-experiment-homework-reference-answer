CREATE VIEW USER1_FRIEND AS
    SELECT
        FRIEND.UID2   AS UID,
        USER.NICKNAME,
        FRIEND.NOTE,
        FRIEND.TYPE
    FROM
        USER
        JOIN FRIEND
        ON USER.UID = FRIEND.UID2
    WHERE
        (USER.UID, 1) IN (
            SELECT
                UID1,
                UID2
            FROM
                FRIEND
        )
        AND (1, USER.UID) IN (
            SELECT
                UID1,
                UID2
            FROM
                FRIEND
        )
        AND FRIEND.UID1 = 1;