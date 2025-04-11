SELECT
    HOST_TID,
    CNT1 + CNT2 AS CNT
FROM
    (
        SELECT
            HOST_TID,
            COUNT(*) AS CNT1
        FROM
            MATCH
        WHERE
            HOST_WIN = "是"
        GROUP BY
            HOST_TID
    ),
    (
        SELECT
            GUEST_TID,
            COUNT(*)  AS CNT2
        FROM
            MATCH
        WHERE
            HOST_WIN = "否"
        GROUP BY
            GUEST_TID
    )
WHERE
    HOST_TID = GUEST_TID;