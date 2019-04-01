# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html

import codecs
import chardet
import MySQLdb
class DouBanPipeline(object):
    
    def __init__(self):
        self.db = MySQLdb.connect("localhost", "root", "123456", "bigdata", charset='utf8')
        self.cursor = self.db.cursor()       
#self.file = codecs.open("data.txt","w",encoding='utf-8')


    def trans(self, str):
        cs = chardet.detect(str)
        return str.decode(cs.get("encoding","utf-8")).encode('utf-8')

    def process_item(self, item, spider):
        print "111111111111111111111111111111"
        sql1 = "create table `douban2`(`id` int (11) not null auto_increment, `name` varchar(20) not null, `stars` varchar(20) not null, `date` varchar(20) not null, primary key(`id`), key `index_id` (`name`) using hash) engine=memory auto_increment=1 default charset=utf8"
        sql2 = "insert into douban2(name, stars, date) values('%s', '%s', '%s') %(item['name'], item['stars'], item['date'])"
        self.cursor.execute(sql1)
        self.db.commit()
        self.cursor.execute(sql2)
        self.db.commit()    
        print "222222222222222222222222222222"   
     #   temp=item['name']+','+item['stars']+','+item['date']+'\n'
     #   self.file.write(temp.encode('utf-8'))
        return item

    def close_spider(self,spider):
        self.db.close()
        self.cursor.close()
        print('close file')
