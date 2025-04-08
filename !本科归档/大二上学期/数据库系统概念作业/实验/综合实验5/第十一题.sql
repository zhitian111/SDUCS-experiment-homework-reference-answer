SELECT
    MATCH.TIME,
    MATCH.LOCATION,
    PLAYER.NAME,
    RATIO
FROM
    (
        SELECT
            SUM_DAMAGE.MID,
            SUM_DAMAGE.PID_HITTER AS PID,
            SUM_DAMAGE.SUM_DAMAGE/SUM_MONEY.SUM_MONEY AS RATIO
        FROM
            (
                SELECT
                    MID,
                    PID_HITTER,
                    SUM(AMOUNT) AS SUM_DAMAGE
                FROM
                    DAMAGE
                GROUP BY
                    MID,
                    PID_HITTER
            ) AS SUM_DAMAGE,
            (
                SELECT
                    MID,
                    PID,
                    SUM(AMOUNT) AS SUM_MONEY
                FROM
                    GOLD
                GROUP BY
                    MID,
                    PID
            ) AS SUM_MONEY
        WHERE
            SUM_DAMAGE.MID=SUM_MONEY.MID
            AND SUM_DAMAGE.PID_HITTER=SUM_MONEY.PID
        ORDER BY
            SUM_DAMAGE.SUM_DAMAGE/SUM_MONEY.SUM_MONEY DESC LIMIT 1
    ) AS BEST_HITTER
    JOIN MATCH
    ON BEST_HITTER.MID=MATCH.MID
    JOIN PLAYER
    ON BEST_HITTER.PID=PLAYER.PID;