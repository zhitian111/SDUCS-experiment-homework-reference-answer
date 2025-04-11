UPDATE ONSELL
SET
    STATUS = "下架"
WHERE
    STATUS = "正常"
    AND EXISTS (
        SELECT
            1
        FROM
            COMMODITY
        WHERE
            ONSELL.CID = COMMODITY.CID
            AND (COMMODITY.MAN_DATE + COMMODITY.GUARANTEE_PERIOD) < 1000
    );