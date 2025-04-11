-- a
UPDATE MESSAGE
SET
    SHARED_COUNT = SHARED_COUNT - 1
WHERE
    MID IN (
        SELECT
            MID
        FROM
            SEND
        WHERE
            uid_sender=0
            AND uid_receiver = 1
        UNION
        SELECT
            MID
        FROM
            SEND
        WHERE
            uid_sender=1
            AND uid_receiver = 0
    );

-- b
DELETE FROM MESSAGE
WHERE
    SHARED_COUNT = 0;

-- c
DELETE FROM SEND
WHERE
    (uid_sender = 0
    AND uid_receiver = 1)
    OR (uid_sender = 1
    AND uid_receiver = 0);

-- d
DELETE FROM FRIEND
WHERE
    (UID1 = 0
    AND UID2 = 1)
    OR (UID1 = 1
    AND UID2 = 0);