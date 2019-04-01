@echo off
:: appname 程序名
:: inputname 输入文件名
:: outputname 输出文件名
:: resultname 程序控制台输出重定向文件名

set appname="ReliableTrans.exe"
set inputname="input.txt"
set outputname="output.txt"
set resultname="result.txt"

for /l %%j in (0,1,2) do (
	if %%j==0 echo GBN
		if %%j==1 echo SR
			if %%j==2 echo TCP
	for /l %%i in (1,1,10) do (
		echo Test %appname% %%i:
		%appname% %%j > %resultname% 2>&1
		fc /N %inputname% %outputname%
	)
)

pause