WITH RANKED AS (
    SELECT
        C.TYPE,
        C.NAME,
        COUNT(ORDERS.OID)                                                       AS CNT,
        ROW_NUMBER() OVER (PARTITION BY C.TYPE ORDER BY COUNT(ORDERS.OID) DESC) AS RANK
    FROM
        ORDERS
        JOIN COMMODITY C
        ON ORDERS.CID = C.CID
    WHERE
        ORDERS.UID = 1
    GROUP BY
        C.TYPE,
        C.NAME
)
SELECT
    TYPE,
    NAME,
    CNT
FROM
    RANKED
WHERE
    RANK = 1;