# 2.2 数据更新
-- 数据导入导出
LOAD DATA INFILE '/var/lib/mysql-files/电影表.txt' INTO TABLE DB_Exp.T_FILM 
 FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n'
 IGNORE 1 ROWS;
 
LOAD DATA INFILE '/var/lib/mysql-files/演员表.txt' INTO TABLE DB_Exp.T_ACTOR 
 FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n'
 IGNORE 1 ROWS;
 
LOAD DATA INFILE '/var/lib/mysql-files/影院表.txt' INTO TABLE DB_Exp.T_THEATER 
 FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n'
 IGNORE 1 ROWS;

LOAD DATA INFILE '/var/lib/mysql-files/参演表.txt' INTO TABLE DB_Exp.T_ACTIN 
 FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n'
 IGNORE 1 ROWS;

LOAD DATA INFILE '/var/lib/mysql-files/放映表.txt' INTO TABLE DB_Exp.T_SHOW
 FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n'
 IGNORE 1 ROWS;
 
Insert into T_FILM values (20197396,'新喜剧之王','爱情','周星驰',93,'N',73);

Update T_FILM SET FTYPE='喜剧' where DNAME='周星驰';

Delete from T_FILM where FNAME='新喜剧之王';

Create table T_YOUNG_ACTOR &#x0A; as (Select * From T_ACTOR where BYEAR&gt;=1990);

Create view ACTIN_80s (ACTID,ANAME,BYEAR,LEADING_NUM,MAX_GRADE) as 
 Select T_ACTOR.ACTID,T_ACTOR.ANAME,BYEAR,COUNT(ISLEADING),MAX(GRADE)
 from T_ACTOR left join T_ACTIN on T_ACTOR.ACTID=T_ACTIN.ACTID and ISLEADING='Y'
 where BYEAR>=1980 and BYEAR<1990
 group by T_ACTOR.ACTID;


Create table T_TEST (
    SID int NOT NULL,
    SNAME CHAR(10) NOT NULL
);
Insert into T_TEST values(1,'cxk');
select * from T_TEST;
Delete from T_TEST where SID=1;
Insert into T_TEST values(1,'cxk');


