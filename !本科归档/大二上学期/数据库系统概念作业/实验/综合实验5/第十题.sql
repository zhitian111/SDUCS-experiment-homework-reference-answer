SELECT
    CHAMPION.NAME,
    BP_CNT
FROM
    (
        SELECT
            CID1,
            PICK_CNT+BAN_CNT AS BP_CNT
        FROM
            (
                SELECT
                    CID AS CID1,
                    COUNT(*) AS PICK_CNT
                FROM
                    PICK
                GROUP BY
                    CID
            ),
            (
                SELECT
                    CID AS CID2,
                    COUNT(*) AS BAN_CNT
                FROM
                    BAN
                GROUP BY
                    CID
            )
        WHERE
            CID1 = CID2
        ORDER BY
            PICK_CNT+BAN_CNT DESC LIMIT 1
    ),
    CHAMPION
WHERE
    CHAMPION.CID = CID1;