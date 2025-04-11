SELECT
    *
FROM
    CHAMPION
WHERE
    CID NOT IN(
        SELECT
            DISTINCT CID
        FROM
            PICK
    );