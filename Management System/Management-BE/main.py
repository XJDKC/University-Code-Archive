# encoding: utf-8
import os
import sys
from flask import Flask, render_template,jsonify,request
from flask_cors import CORS
from flask_mysqldb import MySQL



app = Flask(__name__)
app.secret_key = 'development key'

app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = 'xrl520'
app.config['MYSQL_DB'] = 'GMDB'

mysql = MySQL(app)
CORS(app)

@app.route('/')
def hello_world():
    return 'Hello Flask!'

def Query(sql):
    cur = mysql.connection.cursor()
    cur.execute(sql)
    mysql.connection.commit()
    results = cur.fetchall()
    cur.close()
    return results

def Trans(tuple,list):
    ret = []
    for item in tuple:
        dict = {}
        for index, str in enumerate(list):
            dict[str] = item[index]
        print(dict)
        ret.append(dict)
    return ret

@app.route('/loginCheck', methods=["POST"])
def loginCheck():
    response = {}
    usrname = request.get_json()['usrname']
    password = request.get_json()['password']
    sql = "SELECT Password, Usrtype FROM Users WHERE Usrname = '%s'" % usrname
    results = Query(sql)
    if (len(results) == 0):
        response['Success'] = 0
    else:
        if (results[0][0] == password):
            response['Success'] = 1
            response['Usrname'] = usrname
            response['Usrtype'] = results[0][1]
        else:
            response['Success'] = 0
    return jsonify(response)

@app.route('/QueryAccounts', methods=["POST","GET"])
def QueryAccounts():
    response = []
    if (request.method == 'GET'):
        sql = "SELECT * FROM Users"
    elif (request.method == 'POST'):
        usrtype = request.get_json()['usrtype']
        sql = "SELECT * FROM Users WHERE Usrtype = %d" % usrtype
    results = Query(sql)
    response = Trans(results, ['Usrname', 'Password', 'Usrtype'])
    return jsonify(response)

@app.route('/QeuryTeachers', methods=["GET"])
def QueryTeachers():
    response = []
    sql = "SELECT * FROM Teacher"
    results = Query(sql)
    response = Trans(results, ['TID', 'TName', 'TSex', 'TDept'])
    return jsonify(response)

@app.route('/QueryStudents', methods=["GET"])
def QueryStudents():
    response = []
    sql = "SELECT * FROM Student"
    results = Query(sql)
    print(results)
    response = Trans(results, ['SID', 'SName', 'SSex', 'SDept', 'SAdmYear'])
    return jsonify(response)

@app.route('/QueryCourses', methods=["GET"])
def QueryCourses():
    response = []
    sql = "SELECT * FROM Course"
    results = Query(sql)
    print(results)
    response = Trans(results, ['CID', 'CName', 'CCredit', 'CTerm'])
    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)      # 设置debug=True是为了让代码修改实时生效，而不用每次重启加载
