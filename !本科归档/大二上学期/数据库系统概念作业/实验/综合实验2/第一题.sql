-- a
SELECT
    *
FROM
    VIDEO
WHERE
    VID = 35;

-- b
SELECT
    [USER].*
FROM [USER]
JOIN POST ON [USER].UID = POST.UID
JOIN VIDEO ON POST.VID = VIDEO.VID
WHERE VIDEO.VID = 35;

-- c
SELECT
    COUNT(*) AS "Number of Watching Videos"
FROM
    WATCH
WHERE
    WATCH.VID = 35;

-- d
SELECT
    COUNT(*) AS "Number of Liked Videos"
FROM
    [LIKE]
WHERE
    [LIKE].VID = 35;

-- e
SELECT
    COUNT(*) AS "Number of Collect on Videos"
FROM
    [COLLECT]
WHERE
    [COLLECT].VID = 35;

-- f
SELECT
    COALESCE(SUM(COIN.AMOUNT),0) AS "Number of Coins the Videos"
FROM
    COIN
WHERE
    COIN.VID = 35;

-- g
SELECT
    *
FROM
    [COMMENT]
WHERE
    [COMMENT].VID = 35
ORDER BY VIDEO_TIME;