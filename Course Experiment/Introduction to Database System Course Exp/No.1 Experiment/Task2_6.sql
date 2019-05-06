# 2.6 存储函数、存储过程和触发器
-- 存储函数
-- 定义存储函数
delimiter $$
create function getActInNum(query_actid int,query_year int) returns int
deterministic
begin
	declare num int default 0;
    select count(FID) into num
    from T_ACTIN
    where ACTID = query_actid and FID in (select distinct FID from T_SHOW where YEAR = query_year)
    group by ACTID;
    return (num);
end$$
delimiter ;

-- 使用存储函数
select * from T_ACTOR
where getActInNum(ACTID, 2017) >= 1;


-- 创建表
Create table T_SHOWCOUNT (
	TID int NOT NULL comment 'Theater ID' primary key,
    TNAME char(20) default 'Unknow' NOT NULL comment 'Theater Name',
    MOVIENUM int default 0 not null comment "The number of movie showed on this theater"
);
-- 定义存储过程
delimiter $$
DROP PROCEDURE IF EXISTS updateTableShowCount $$
CREATE PROCEDURE updateTableShowCount()
BEGIN
	declare t_id int;
    declare t_name char(20);
    declare movie_num int;
    declare done boolean default 0;		-- while 结束标志
    declare dev_rs CURSOR FOR 			-- 定义一个游标
		SELECT T_THEATER.TID,T_THEATER.TNAME,COUNT(FID) from T_THEATER left JOIN T_SHOW ON T_THEATER.TID = T_SHOW.TID
        GROUP BY T_THEATER.TID, T_THEATER.TNAME;
    declare CONTINUE HANDLER FOR NOT FOUND SET done = 1; -- 当游标结束时 将done设为1
    open dev_rs;
    while_loop: while done=0 do
		fetch dev_rs into t_id,t_name,movie_num;
        if (done = 1) then
			leave while_loop;
		end if;
        -- 更新列表
        if t_id not in (select TID from T_SHOWCOUNT) then
			insert into T_SHOWCOUNT values(t_id,t_name,movie_num);
        else
			update T_SHOWCOUNT set TNAME = t_name,MOVIENUM=movie_num where T_SHOWCOUNT.TID = t_id;
        end if; 
	end while;
    close dev_rs;
END$$
delimiter ;
-- 使用存储过程
drop table T_SHOWCOUNT;
Insert into T_THEATER values(100,'巨幕影城','光谷','武汉');
delete from T_SHOW where TID = 100;
Insert into T_SHOW values(1,100,10,null,null);
call updateTableShowCount;
select * from T_SHOWCOUNT;

-- 定义触发器
delimiter $$
drop trigger if exists my_trigger $$
create trigger my_trigger before insert
on T_FILM for each row
begin 
  if new.DNAME = '周星驰' then
     set new.FTYPE = '喜剧';
  end if;
end$$
delimiter ;
-- 使用触发器
select * from T_FILM where DNAME = '周星驰';
insert into T_FILM values(20197396, '新喜剧之王', '无厘头', '周星驰', 108, 'N', 90, date '2019-05-06');
insert into T_FILM values(20190506, '功夫', '无厘头', '周星驰', 108, 'N', 90, date '2019-05-06');
