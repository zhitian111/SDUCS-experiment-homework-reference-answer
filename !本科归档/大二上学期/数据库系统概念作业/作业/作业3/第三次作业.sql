SELECT
    NAME,
    TITLE
FROM
    INSTRUCTOR
    NATURAL JOIN TEACHES
    NATURAL JOIN SECTION
    NATURAL JOIN COURSE
WHERE
    SEMESTER = 'Spring'
    AND YEAR = 2017;

CREATE TABLE EMPLOYEE (
    ID INTEGER,
    PERSON_NAME VARCHAR(50),
    STREET VARCHAR(50),
    CITY VARCHAR(50),
    PRIMARY KEY (ID)
);

CREATE TABLE COMPANY (
    COMPANY_NAME VARCHAR(50),
    CITY VARCHAR(50),
    PRIMARY KEY(COMPANY_NAME)
);

CREATE TABLE WORKS (
    ID INTEGER,
    COMPANY_NAME VARCHAR(50),
    SALARY NUMERIC(10, 2),
    PRIMARY KEY(ID),
    FOREIGN KEY (ID) REFERENCES EMPLOYEE(ID),
    FOREIGN KEY (COMPANY_NAME) REFERENCES COMPANY(COMPANY_NAME)
);

CREATE TABLE MANAGES (
    ID INTEGER,
    MANAGER_ID INTEGER,
    PRIMARY KEY (ID),
    FOREIGN KEY (ID) REFERENCES EMPLOYEE (ID),
    FOREIGN KEY (MANAGER_ID) REFERENCES EMPLOYEE (ID)
);


WITH Q1 AS (
 -- q1 stands for query 1
    SELECT
        *
    FROM
        SECTION
        NATURAL JOIN CLASSROOM
), Q2 AS (
 -- q2 stands for query 2
    SELECT
        C.BUILDING,
        C.ROOM_NUMBER,
        COURSE_ID,
        SEC_ID,
        SEMESTER,
        YEAR,
        TIME_SLOT_ID,
        CAPACITY
    FROM
        SECTION
        INNER JOIN CLASSROOM C
        USING (BUILDING,
        ROOM_NUMBER)
)
 -- we need to check that result of q1 is a subset of q2 and
-- result of q2 is a subset of q1
SELECT
    NOT EXISTS ( (
        SELECT
            *
        FROM
            Q1
    ) EXCEPT (
        SELECT
            *
        FROM
            Q2
    ) )
    AND NOT EXISTS ( (
        SELECT
            *
        FROM
            Q2
    ) EXCEPT (
        SELECT
            *
        FROM
            Q1
    ) );

CREATE VIEW TOT_CREDITS(
    YEAR,
    NUM_CREDITS
) AS (
    SELECT
        YEAR,
        SUM(CREDITS)
    FROM
        TAKES
        NATURAL JOIN COURSE
    GROUP BY
        YEAR
    ORDER BY
        YEAR ASC
);