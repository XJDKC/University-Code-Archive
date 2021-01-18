# 2.1 数据定义
Create database if not exists DB_Exp;

Create table T_FILM (
	FID int NOT NULL comment 'Film ID',
    FNAME char(30) NOT NULL comment 'Film Name',
    FTYPE char(10) default 'Unknow' NOT NULL comment 'Film Type',
    DNAME char(30) default 'Unknow' NOT NULL comment 'Director Name',
    LENGTH int default '0' NOT NULL comment 'Film length in minutes',
    IS3D enum('Y','N') default 'N' comment 'Is 3D Film? Y-3D, N-Not 3D',
    GRADE int comment 'User Rating',
    primary key (FID),
    check (GRADE>=0 and GRADE<=100 and (IS3D='Y' or IS3D='N'))
);

Create table T_ACTOR(
	ACTID int NOT NULL comment 'Actor ID',
    ANAME char(30) NOT NULL comment 'Actor Name',
    SEX char(2) default '男' NOT NULL comment 'Actor Sex',
    BYEAR int comment 'Actor\'s birth year',
    primary key (ACTID)
);

Create table T_ACTIN(
	ACTID int NOT NULL comment 'Actor ID',
    FID int NOT NULL comment 'Film ID',
    ISLEADING enum('Y','N') comment 'Y-Is the leading, N-Not the leading',
    GRADE int comment 'User rating for the actor in the film',
    foreign key (ACTID) references T_ACTOR(ACTID),
    foreign key (FID) references T_FILM(FID)
);

Create table T_THEATER(
	TID int NOT NULL comment 'Theater ID',
    TNAME char(20) default 'Unknow' NOT NULL comment 'Theater Name',
    TAREA char(20) default 'Unknow' NOT NULL comment 'Theater Area',
    ADDRESS char (20) default 'Unkonw' NOT NULL comment 'Theater Address',
    primary key (TID)
);

Create table T_SHOW(
	FID int NOT NULL comment 'Film ID',
    TID int NOT NULL comment 'Theater ID',
    PRICE int NOT NULL comment 'Ticket Price',
    YEAR int comment 'Release Year',
    MONTH int comment 'Release Month',
    foreign key(FID) references T_FILM(FID),
    foreign key(TID) references T_THEATER(TID)
);


Insert into T_ACTIN VALUES (1,1,'Y',0);
Insert into T_ACTOR VALUES (1,'CXK','男',1998);
Insert into T_ACTIN VALUES (1,1,'Y',0);
Insert into T_SHOW VALUES (1,1,100,NULL,NULL);
Insert into T_FILM VALUES (1,'JI NI TAI MEI','Sing','CXK',10,'N',100);
Insert into T_ACTIN VALUES (1,1,'Y',0);
Insert into T_SHOW VALUES (1,1,100,NULL,NULL);
Insert into T_THEATER VALUES (1,1,'Unkonw','Unknow');
Insert into T_SHOW VALUES (1,1,100,NULL,NULL);


