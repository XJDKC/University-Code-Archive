# 2.5 事务特性
-- 查看当前会话隔离级别
select @@transaction_isolation;
-- 查看系统当前隔离级别
select @@global.transaction_isolation; 
-- 设置当前会话隔离级别
set transaction_isolation='REPEATABLE-READ';
-- 设置系统当前隔离级别
set global transaction isolation level repeatable read;

-- 隔离级别
-- 1. read uncommitted：　可以看到未提交的数据(脏读)。
-- 2. read committed: 读取提交的数据。但是多次读取的数据结果不一致(不可重复读，幻读)，即读取的数据可以在读取期间被别人修改掉。
-- 3. repeatable read: MySQL默认隔离级别，可以重复读取，但有幻读，即读取的数据行不可写，但是别的事务可以向表中新增数据，在MySQL中，其他事务新增的数据看不到，不会产生幻读，采用多版本并发控制MVCC机制解决幻读问题。
-- 4. serializable: 可读不可写，类似锁，写数据必须等到另一个对该行访问的事务结束。

CREATE TABLE R (
	A CHAR(10) NOT NULL,
    B CHAR(10) NOT NULL
); 

drop table R;
select * from R;

Insert into R values('C1',40),('C2',50),('C3',60);

-- T1
START TRANSACTION;
UPDATE R SET B=22 WHERE A='C1';
INSERT INTO R VALUES('C4',0);
UPDATE R SET B=38 WHERE A='C1';
COMMIT;

-- T2
BEGIN;
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
SELECT SUM(B) FROM R;
SELECT AVG(B) FROM R;
COMMIT;

-- @@global.transaction_isolation = read uncommitted or read committed or repeatable read
-- result 1: 148,37 (T1提交时在T2两个SELECT之间)
-- result 2: 150,37 (T1提交时在T2两个SELECT之间)
-- result 3: 150,50 (T1提交时在T2两个SLECT之后)

-- @@global.transaction_isolation = serializable
-- result 1: 150,50 (T2 先执行，T1 后执行)
-- result 2: 148,37 (T1 先执行，T2 后执行) 


