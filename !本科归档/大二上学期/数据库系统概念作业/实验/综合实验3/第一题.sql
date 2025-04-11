SELECT
    COMMODITY.NAME,
    ONSELL.STATUS,
    ONSELL.REM_AMOUNT,
    CNT,
    AV
FROM
    ONSELL,
    (
        SELECT
            COUNT(*)       AS CNT,
            AVG(BUYERRATE) AS AV
        FROM
            ORDERS
        WHERE
            SID = 251
            AND CID = 669
    )
    JOIN COMMODITY
    ON ONSELL.CID = COMMODITY.CID
WHERE
    ONSELL.SID = 251
    AND ONSELL.CID = 669;
