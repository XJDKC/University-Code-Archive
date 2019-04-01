import MySQLdb
import time
from pyhdfs import HdfsClient     
db = MySQLdb.connect("localhost", "root", "123456", "bigdata", charset='utf8' )
client = HdfsClient(hosts='jz-xrl:50070', user_name='root')  
cursor = db.cursor()

sql2 = "CREATE TABLE `data_1qw`(`id` INT (11) NOT NULL AUTO_INCREMENT, `name` VARCHAR (20) NOT NULL, `score` INT (11) NOT NULL,PRIMARY KEY (`id`),KEY `index_id` (`name`) USING HASH) ENGINE = MEMORY AUTO_INCREMENT = 1 DEFAULT CHARSET = utf8"

sql3 = "CREATE FUNCTION `rand_s`(n INT) RETURNS varchar(255) CHARSET latin1 BEGIN DECLARE chars_str varchar(100) DEFAULT 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'; DECLARE return_str varchar(255) DEFAULT '' ; DECLARE i INT DEFAULT 0; WHILE i < n DO SET return_str = concat(return_str,substring(chars_str , FLOOR(1 + RAND()*62 ),1)); SET i = i +1; END WHILE; RETURN return_str; END"

sql4 = "CREATE PROCEDURE `add_data_1qw`(IN n int) BEGIN DECLARE i INT DEFAULT 1; WHILE (i <= n ) DO INSERT into data_1qw (name, score) VALUEs (rand_s(20),FLOOR(RAND() * 10000)); set i=i+1; END WHILE; END"

sql5 = "CALL add_data_1qw(10000000)"

sql6 = "select * from data_1kw"

sql7 = """select * from data_1qw into outfile '/tmp/data_1qw.txt' fields terminated by ','"""
try:
    starttime = time.asctime( time.localtime(time.time()) )
    print "Data size: 10^7"
    print "Start time: ", starttime
    cursor.execute(sql2)
    db.commit()
    #cursor.execute(sql3)
    #db.commit()
    
    cursor.execute(sql4)
    db.commit()
    
    cursor.execute(sql5)
    db.commit()
    #cursor.execute(sql6)
    #db.commit()
    
    
    mysql_time = time.asctime(time.localtime(time.time()))
    print "Data into Mysql: ", mysql_time
    cursor.execute(sql7)
    db.commit()

    client.copy_from_local('/tmp/data_1qw.txt', '/data_1qw.txt')
    
    #results = cursor.fetchall()
    #client.create('/data_1000.txt', '\0')
    #for row in results:
    #    f = row[0]
    #    name = row[1]
    #    score = row[2]
    #    s = str(f) + ',' + name + ',' + str(score) + '\n'
    #    client.append('/data_1000.txt', s)
    endtime = time.asctime( time.localtime(time.time()) )
    print "Data into hdfs: ", endtime
except:
    print "Error!"
db.close()



