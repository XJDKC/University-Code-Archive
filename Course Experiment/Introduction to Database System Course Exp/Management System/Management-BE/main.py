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

# Other Function
def Query(sql):
    cur = mysql.connection.cursor()
    cur.execute(sql)
    mysql.connection.commit()
    results = cur.fetchall()
    cur.close()
    return results

def Insert(sql):
    cur = mysql.connection.cursor()
    try:
        cur.execute(sql)
        mysql.connection.commit()
        return True
    except:
        mysql.connection.rollback()
        return False
    finally:
        cur.close()

def Delete(sql):
    cur = mysql.connection.cursor()
    try:
        cur.execute(sql)
        mysql.connection.commit()
        return True
    except:
        mysql.connection.rollback()
        return False
    finally:
        cur.close()

def Update(sql):
    cur = mysql.connection.cursor()
    try:
        cur.execute(sql)
        mysql.connection.commit()
        return True
    except:
        mysql.connection.rollback()
        return False
    finally:
        cur.close()

def Trans(tuple,list):
    ret = []
    for item in tuple:
        dict = {}
        for index, str in enumerate(list):
            dict[str] = item[index]
        print(dict)
        ret.append(dict)
    return ret


# Test
@app.route('/')
def hello_world():
    return 'Hello Flask!'

# login check
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


# Users Table
@app.route('/QueryUsers', methods=["POST","GET"])
def QueryUsers():
    response = []
    if (request.method == 'GET'):
        sql = "SELECT * FROM Users"
    elif (request.method == 'POST'):
        usrtype = request.get_json()['usrtype']
        sql = "SELECT * FROM Users WHERE Usrtype = %d" % usrtype
    results = Query(sql)
    response = Trans(results, ['Username', 'Password', 'Usertype'])
    return jsonify(response)

@app.route('/UpdateUser', methods=["POST"])
def UpdateUser():
    response = {}
    post = request.get_json()
    sql = "Update Users SET Password = '%s', Usrtype = '%s' WHERE Usrname = '%s'" \
          % (post['Password'],post['Usertype'],post['Username'])
    response['State'] = Update(sql)
    return jsonify(response)

@app.route('/InsertUser', methods=["POST"])
def InsertUser():
    response = {}
    post = request.get_json()
    sql = "INSERT INTO Users VALUES('%s','%s',%d);" % (post['Username'],post['Password'],post['Usertype'],)
    response['State'] = Insert(sql)
    return jsonify(response)

@app.route('/DeleteUser', methods=["POST"])
def DeleteUser():
    response = {}
    post = request.get_json()
    sql = "DELETE FROM Users WHERE Usrname = '%s'" % (post['Username'])
    response['State'] = Delete(sql)
    return jsonify(response)



# Teacher Table
@app.route('/QueryTeachers', methods=["GET"])
def QueryTeachers():
    response = []
    sql = "SELECT * FROM Teacher"
    results = Query(sql)
    response = Trans(results, ['TID', 'TName', 'TSex', 'TDept'])
    return jsonify(response)

@app.route('/InsertTeacher', methods=["POST"])
def InsertTeacher():
    response = {}
    post = request.get_json()
    print(post)
    sql = "INSERT INTO Teacher VALUES('%s','%s',%d,'%s');" % (post['TID'],post['TName'],post['SSex'],post['TDept'])
    print(sql)
    response['State'] = Insert(sql)
    return jsonify(response)

@app.route('/DeleteTeacher', methods=["POST"])
def DeleteTeacher():
    response = {}
    post = request.get_json()
    sql = "DELETE FROM Teacher WHERE TID = '%s'" % (post['TID'])
    response['State'] = Delete(sql)
    return jsonify(response)

@app.route('/UpdateTeacher', methods=["POST"])
def UpdateTeacher():
    response = {}
    post = request.get_json()
    print(post)
    sql = "Update Teacher SET TName = '%s', SSex = '%s', TDept = '%s' WHERE TID = '%s'" \
          % (post['TName'],post['SSex'],post['TDept'],post['TID'])
    response['State'] = Update(sql)
    return jsonify(response)



# Student Table
@app.route('/QueryStudents', methods=["GET"])
def QueryStudents():
    response = []
    sql = "SELECT * FROM Student"
    results = Query(sql)
    print(results)
    response = Trans(results, ['SID', 'SName', 'SSex', 'SDept', 'SAdmYear'])
    return jsonify(response)

@app.route('/InsertStudent', methods=["POST"])
def InsertStudent():
    response = {}
    post = request.get_json()
    print(post)
    sql = "INSERT INTO Student VALUES('%s','%s',%d,'%s','%s');" % (post['SID'],post['SName'],post['SSex'],post['SDept'],post['SAdmYear'])
    print(sql)
    response['State'] = Insert(sql)
    return jsonify(response)

@app.route('/DeleteStudent', methods=["POST"])
def DeleteStudent():
    response = {}
    post = request.get_json()
    sql = "DELETE FROM Student WHERE SID = '%s'" % (post['SID'])
    response['State'] = Delete(sql)
    return jsonify(response)

@app.route('/UpdateStudent', methods=["POST"])
def UpdateStudent():
    response = {}
    post = request.get_json()
    print(post)
    sql = "Update Student SET SName = '%s', SSex = '%s', Sdept = '%s',SAdmYear = '%s' WHERE SID = '%s'" \
          % (post['SName'],post['SSex'],post['SDept'],post['SAdmYear'],post['SID'])
    response['State'] = Update(sql)
    return jsonify(response)


# Course Table
@app.route('/QueryCourses', methods=["GET"])
def QueryCourses():
    response = []
    sql = "SELECT * FROM Course"
    results = Query(sql)
    print(results)
    response = Trans(results, ['CID', 'CName', 'CCredit', 'CTerm'])
    return jsonify(response)

@app.route('/InsertCourse', methods=["POST"])
def InsertCourse():
    response = {}
    post = request.get_json()
    print(post)
    sql = "INSERT INTO Course VALUES(%d,'%s',%f,%d);" % (post['CID'],post['CName'],post['CCredit'],post['CTerm'])
    print(sql)
    response['State'] = Insert(sql)
    return jsonify(response)

@app.route('/DeleteCourse', methods=["POST"])
def DeleteCourse():
    response = {}
    post = request.get_json()
    sql = "DELETE FROM Course WHERE CID = %d" % (post['CID'])
    response['State'] = Delete(sql)
    return jsonify(response)

@app.route('/UpdateCourse', methods=["POST"])
def UpdateCourse():
    response = {}
    post = request.get_json()
    print(post)
    sql = "Update Course SET CName = '%s', CCredit = %f, CTerm = '%s' WHERE CID = %d" \
          % (post['CName'],post['CCredit'],post['CTerm'],post['CID'])
    response['State'] = Update(sql)
    return jsonify(response)


# Class Table
@app.route('/QueryClasses', methods=["GET", "POST"])
def QueryClasses():
    response = []
    post = request.get_json()
    print(post)
    if request.method == 'GET':
        sql = 'SELECT ClassID ,Class.CID,CName,Class.TID,Tname ' \
              'FROM Class,Course,Teacher ' \
              'WHERE Class.CID = Course.CID and Class.TID = Teacher.TID'
    elif request.method == 'POST':
        if ('TID' in post):
            sql = 'SELECT ClassID ,Class.CID,CName,Class.TID,Tname ' \
                  'FROM Class,Course,Teacher ' \
                  'WHERE Class.CID = Course.CID and Class.TID = Teacher.TID and Teacher.TID = \'%s\'' % post['TID']
            results = Query(sql)
            response = Trans(results, ['ClassID', 'CID', 'CName', 'TID', 'TName'])
        elif 'SID' in post:
            sql = 'SELECT Class.ClassID ,Class.CID,CName,Student.SID,SName ' \
                  'FROM Class,SC,Course,Student ' \
                  'WHERE Class.CID = Course.CID and Class.ClassID = SC.ClassID and SC.SID = Student.SID and Student.SID = \'%s\'' % post['SID']
            results = Query(sql)
            response = Trans(results, ['ClassID', 'CID', 'CName', 'SID','SName'])
    return jsonify(response)


@app.route('/InsertClass', methods=["POST"])
def InsertClass():
    response = {}
    post = request.get_json()
    print(post)
    sql = "INSERT INTO Class VALUES(%d, %d,'%s');" % (post['ClassID'],post['CID'],post['TID'])
    print(sql)
    response['State'] = Insert(sql)
    return jsonify(response)

@app.route('/DeleteClass', methods=["POST"])
def DeleteClass():
    response = {}
    post = request.get_json()
    sql = "DELETE FROM Class WHERE ClassID = %d" % (post['ClassID'])
    response['State'] = Delete(sql)
    return jsonify(response)

@app.route('/UpdateClass', methods=["POST"])
def UpdateClass():
    response = {}
    post = request.get_json()
    print(post)
    sql = "Update Class SET CID = %d, TID = '%s' WHERE ClassID = %d" \
          % (post['CID'],post['TID'],post['ClassID'])
    response['State'] = Update(sql)
    return jsonify(response)


# Task Table
@app.route('/QueryTasks', methods=["GET","POST"])
def QueryTasks():
    response = []
    post = request.get_json()

    sql = "SELECT TaskID,Task.ClassID,TaskName,Weight,Type " \
          "FROM Task, Class " \
          "WHERE Task.ClassID = Class.ClassID and Class.ClassID = %d and Class.TID = '%s'" % (post['ClassID'],post['TID'])
    print(sql)
    results = Query(sql)
    print(results)
    response = Trans(results, ['TaskID','ClassID','TaskName', 'Weight','Type'])
    return jsonify(response)

@app.route('/ModifyTasks', methods=["POST"])
def ModifyTasks():
    response = {}
    post = request.get_json()
    print(post)
    sql1 = "DELETE FROM Task WHERE ClassID = %d" % post['ClassID']
    sql2 = 'INSERT INTO Task VALUES'
    for index,item in enumerate(post['Weights']):
        print(item)
        if index > 0:
            sql2 += ','
        sql2 = sql2 + "(null,%d,'%s',%d,%d)"%(item['ClassID'],item['TaskName'],item['Weight'],item['Type'])
    print(sql1)
    print(sql2)
    flag = Delete(sql1)
    response = { 'State': flag and Insert(sql2) }
    print(response)
    return jsonify(response)

# Score Table
@app.route('/QueryScores', methods=["GET","POST"])
def QueryScores():
    response = []
    post = request.get_json()
    if 'TID' in post:
        sql = "SELECT Task.TaskID,TaskName,Weight,SC.SID,SName,Score " \
              "FROM (SC JOIN Task ON SC.ClassID = Task.ClassID) LEFT JOIN ST ON (SC.SID = ST.SID and Task.TaskID = ST.TaskID) "\
              "JOIN Student ON SC.SID = Student.SID " \
              "WHERE Task.TaskID = %d " % (post['TaskID'])
    elif 'SID' in post:
        sql = "SELECT Task.TaskID,TaskName,Weight,SC.SID,SName,Score " \
              "FROM (SC JOIN Task ON SC.ClassID = Task.ClassID) LEFT JOIN ST ON (SC.SID = ST.SID and Task.TaskID = ST.TaskID) " \
              "JOIN Student ON SC.SID = Student.SID " \
              "WHERE SC.ClassID = %d and SC.SID = '%s'" % (post['ClassID'],post['SID'])
    print(sql)
    results = Query(sql)
    print(results)
    response = Trans(results, ['TaskID','TaskName','Weight','SID', 'SName','Score'])
    return jsonify(response)

@app.route('/QueryTotalScores', methods=["GET","POST"])
def QueryTotalScores():
    response = []
    post = request.get_json()
    if 'TID' in post:
        sql = "SELECT Course1.CID,CName,SC1.SID,SName, (SELECT SUM(Score * Weight / 100.0) FROM (SC JOIN Task ON SC.ClassID = Task.ClassID) LEFT JOIN ST ON (SC.SID = ST.SID and Task.TaskID = ST.TaskID) JOIN Student ON SC.SID = Student.SID WHERE SC.ClassID = SC1.ClassID and ST.SID = SC1.SID) TotalScore " \
              "FROM SC SC1,Class Class1,Course Course1,Student Student1 " \
              "WHERE SC1.ClassID = Class1.ClassID and Class1.CID = Course1.CID and Student1.SID = SC1.SID AND SC1.ClassID = %d; " % (post['ClassID'])
    elif 'SID' in post:
        sql = "SELECT SC1.ClassID,CName,SC1.SID,SName, (SELECT SUM(Score * Weight / 100.0) FROM (SC JOIN Task ON SC.ClassID = Task.ClassID) LEFT JOIN ST ON (SC.SID = ST.SID and Task.TaskID = ST.TaskID) JOIN Student ON SC.SID = Student.SID WHERE SC.ClassID = SC1.ClassID and ST.SID = SC1.SID) TotalScore " \
              "FROM SC SC1,Class Class1,Course Course1,Student Student1 " \
              "WHERE SC1.ClassID = Class1.ClassID and Class1.CID = Course1.CID and Student1.SID = SC1.SID AND SC1.SID = '%s';" % (post['SID'])
    print(sql)
    results = Query(sql)
    print(results)
    response = Trans(results, ['CID','CName','SID','SName', 'TotalScore'])
    return jsonify(response)



# Score Table
@app.route('/InsertScore', methods=["GET","POST"])
def InsertScore():
    response = {}
    post = request.get_json()
    print(post)
    sql = "INSERT INTO ST VALUES('%s', %d,%.1f);" % (post['SID'],post['TaskID'],post['Score'])
    print(sql)
    response = { 'State': Insert(sql) }
    print(response['State'])
    print(jsonify(response))
    return jsonify(response)

@app.route('/UpdateScore', methods=["GET","POST"])
def UpdateScore():
    response = {}
    post = request.get_json()
    print(post)
    sql = "UPDATE ST SET Score = %f WHERE SID = '%s' and TaskID = %d" % (post['Score'],post['SID'],post['TaskID'])
    print(sql)
    response = { 'State': Update(sql) }
    print(response['State'])
    print(jsonify(response))
    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)      # 设置debug=True是为了让代码修改实时生效，而不用每次重启加载
