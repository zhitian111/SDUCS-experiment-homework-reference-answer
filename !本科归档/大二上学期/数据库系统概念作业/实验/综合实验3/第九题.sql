-- a
INSERT INTO ORDERS(
    UID,
    SID,
    CID,
    SOLD_TIME,
    STATUS
) VALUES(
    1,
    1,
    1,
    1000,
    '待付款'
);

-- b
UPDATE ONSELL
SET
    REM_AMOUNT = REM_AMOUNT - 1
WHERE
    SID = 1
    AND CID = 1;

-- c
UPDATE ONSELL
SET
    STATUS = "缺货"
WHERE
    SID = 1
    AND CID = 1
    AND REM_AMOUNT = 0;

-- d
UPDATE ORDERS
SET
    STATUS = '已完成',
    BUYERRATE = 5
WHERE
    STATUS != '已完成'
    AND (SOLD_TIME + 100) < 1000;

-- a
INSERT INTO ORDERS(
    UID,
    SID,
    CID,
    SOLD_TIME,
    STATUS
) VALUES(
    1,
    10,
    3298,
    1000,
    '待付款'
);

-- b
UPDATE ONSELL
SET
    REM_AMOUNT = REM_AMOUNT - 1
WHERE
    SID = 10
    AND CID = 3298;

-- c
UPDATE ONSELL
SET
    STATUS = "缺货"
WHERE
    SID = 10
    AND CID = 3298
    AND REM_AMOUNT = 0;