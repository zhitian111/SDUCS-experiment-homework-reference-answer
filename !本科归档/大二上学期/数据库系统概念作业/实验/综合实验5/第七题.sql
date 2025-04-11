SELECT
    ID1 AS TID,
    (SUM_TIME1 + SUM_TIME2)/(CNT1+CNT2) AS AVG_TIME
FROM
    (
        SELECT
            HOST_TID AS ID1,
            COUNT(*) AS CNT1,
            SUM(
                CASE
                    WHEN DURATION IS NOT NULL THEN
                        DURATION
                    ELSE
                        0
                END) AS SUM_TIME1
        FROM
            MATCH
        GROUP BY
            HOST_TID
    ),
    (
        SELECT
            GUEST_TID AS ID2,
            COUNT(*) AS CNT2,
            SUM(
                CASE
                    WHEN DURATION IS NOT NULL THEN
                        DURATION
                    ELSE
                        0
                END) AS SUM_TIME2
        FROM
            MATCH
        GROUP BY
            GUEST_TID
    )
WHERE
    ID1 = ID2;