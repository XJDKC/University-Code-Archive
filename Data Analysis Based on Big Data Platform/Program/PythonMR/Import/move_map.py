#!/usr/bin/env python
# encoding: utf-8
import sys
import os
import happybase


table_name = os.environ.get('table_name')
num = os.environ.get('num')
connection = happybase.Connection('jz-xrl',9090)
if table_name not in connection.tables():
    connection.create_table(table_name,{"info":dict()})
t = connection.table(table_name)


with t.batch(batch_size=int(num)) as b:
    for line in sys.stdin:
        words = line.split("\n")
        if words[0][0]=='\t':
            continue
        else:
            word = words[0].split(",")
            b.put(word[0].zfill(9),{'info:name':word[1], 'info:score':word[2]})

