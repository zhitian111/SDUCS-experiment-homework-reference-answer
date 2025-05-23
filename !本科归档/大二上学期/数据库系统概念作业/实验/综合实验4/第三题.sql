﻿SELECT
    GROUPS.GNAME,
    MESSAGE.CONTENT,
    GROUP_SEND.SENT_TIME
FROM
    GROUP_SEND
    JOIN MESSAGE
    ON GROUP_SEND.MID = MESSAGE.MID
    JOIN GROUPS
    ON GROUPS.GID = GROUP_SEND.GID
WHERE
    (1, GROUPS.GID) IN (
        SELECT
            UID,
            GID
        FROM
            JOINGROUP
        WHERE
            UID = 1
    )
ORDER BY
    GROUPS.GNAME,
    GROUP_SEND.SENT_TIME DESC;