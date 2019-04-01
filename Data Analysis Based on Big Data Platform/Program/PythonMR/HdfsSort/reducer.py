#!/usr/bin/env python
# encoding: utf-8
from operator import itemgetter
import sys
dick1={}
for line in sys.stdin:
    words = line.split("\n")
    if words[0][0]=='\t':
        continue
    else:
        word =words[0].split(" ")
        dick1[word[0]]=int((word[1].split("\t"[0]))[0])
dick2=sorted(dick1.items(), key=lambda d:d[1], reverse = False)
for one in dick2:
    print one

