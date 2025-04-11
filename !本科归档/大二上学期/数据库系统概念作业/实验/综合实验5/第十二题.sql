SELECT
    PLAYER.NAME,
    RATIO
FROM
    (
        SELECT
            PLAYER_DAMAGE.PID,
            PLAYER_DAMAGE.TID,
            PLAYER_DAMAGE.SUM_DAMAGE/TEAM_DAMAGE.TOTAL_DAMAGE AS RATIO
        FROM
            (
                SELECT
                    PLAYER.TID,
                    SUM(SUM_DAMAGE) AS TOTAL_DAMAGE
                FROM
                    (
                        SELECT
                            PID_HITTER,
                            SUM(AMOUNT) AS SUM_DAMAGE
                        FROM
                            DAMAGE
                        GROUP BY
                            PID_HITTER
                    ) AS DAMAGE_TABLE
                    JOIN PLAYER
                    ON DAMAGE_TABLE.PID_HITTER = PLAYER.PID
                GROUP BY
                    PLAYER.TID
            ) AS TEAM_DAMAGE,
            (
                SELECT
                    PLAYER.TID,
                    PLAYER.PID,
                    SUM_DAMAGE
                FROM
                    (
                        SELECT
                            PID_HITTER,
                            SUM(AMOUNT) AS SUM_DAMAGE
                        FROM
                            DAMAGE
                        GROUP BY
                            PID_HITTER
                    )
                    JOIN PLAYER
                    ON PLAYER.PID = PID_HITTER
            ) AS PLAYER_DAMAGE
        WHERE
            PLAYER_DAMAGE.TID = TEAM_DAMAGE.TID
        ORDER BY
            PLAYER_DAMAGE.SUM_DAMAGE/TEAM_DAMAGE.TOTAL_DAMAGE DESC LIMIT 1
    ) AS BEST_PLAYER
    JOIN PLAYER
    ON BEST_PLAYER.PID = PLAYER.PID;