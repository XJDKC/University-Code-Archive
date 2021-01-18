package DataBase;


import Model.IncomeList;
import Model.Patient;
import Model.PatientList;
import Model.RegType;

import java.math.BigDecimal;
import java.sql.*;
import java.util.ArrayList;


public class RegisterTableAccess {

    //根据病人选择挂号信息

    //根据医生选择挂号信息

    //根据

    public static int register(String patientName, String doctorName, String typeName, boolean isExpert, double amountDue) throws SQLException, ClassNotFoundException {

        int maxNum, curNum;
        String SQL;
        String patientNo, doctorNo, typeNo, registerNo;
        PreparedStatement stm;
        ResultSet rst;
        Connection conn = DBConnection.getDBConnection().getConnection();

        //Step 1: Disable auto commit.
        conn.setAutoCommit(false);

        //Step 2: Get all the No.
        patientNo = PatientTableAccess.getPatientNo(patientName);
        doctorNo = DoctorTableAccess.getDoctorNo(doctorName);
        typeNo = RegTypeTableAccess.getTypeNo(typeName, isExpert);
        maxNum = RegTypeTableAccess.getMaxNum(typeNo);
        registerNo = String.format("%06d",RegisterTableAccess.getTotalNum() + 1);

        //Step 3: Get the current number of registrations named typeName.
        curNum = RegisterTableAccess.getCurrentNum(typeNo);

        //Step 4: Judge whether patient can register.
        if (curNum >= maxNum) {
            conn.rollback();
            conn.setAutoCommit(true);
            return 0;
        }

        //Step 5: Registering.
        SQL = "Insert into Register VALUES (?,?,?,?,?,?,?,current_timestamp,NULL)";
        stm = conn.prepareStatement(SQL);
        stm.setObject(1, registerNo);
        stm.setObject(2, typeNo);
        stm.setObject(3, doctorNo);
        stm.setObject(4, patientNo);
        stm.setObject(5, curNum+1);
        stm.setObject(6, 0);
        stm.setObject(7, BigDecimal.valueOf(amountDue));
        stm.executeUpdate();
        conn.commit();

        //Step 6: Update Patient Account Balance
        PatientTableAccess.updateBalance(patientNo,amountDue);

        //Step 7: Enable auto commit.
        conn.setAutoCommit(true);

        return Integer.parseInt(registerNo);
    }

    public static int getTotalNum() throws SQLException, ClassNotFoundException {
        String SQL = "SELECT count(*) FROM Register";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        ResultSet rst = stm.executeQuery();

        if (rst.next())
            return rst.getInt(1);
        return 0;
    }

    public static int getCurrentNum(String typeNo) throws SQLException, ClassNotFoundException {
        String SQL = "SELECT count(*) from Register where typeNo = ? and unregister = 0";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1, typeNo);
        ResultSet rst = stm.executeQuery();

        if (rst.next())
            return rst.getInt(1);
        return 0;
    }

    public static ArrayList<PatientList> getPatientList(String doctorName) throws SQLException,ClassNotFoundException {
        ArrayList<PatientList> rtn = new ArrayList<>();
        String doctorNo = DoctorTableAccess.getDoctorNo(doctorName);
        String SQL = "SELECT registerNo,patientName,registerDate,typeName " +
                     "FROM Register join RegType on Register.typeNo = RegType.typeNo " +
                     "join Patient on Register.patientNo = Patient.patientNo " +
                     "WHERE doctorNo = ? and unregister = 0";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1,doctorNo);
        ResultSet rst = stm.executeQuery();

        while (rst.next()) {
            PatientList data = new PatientList();
            data.setRegisterNo(rst.getString(1));
            data.setPatientName(rst.getString(2));
            data.setRegisterDate(rst.getTimestamp(3));
            data.setRegisterType(rst.getString(4));
            rtn.add(data);
        }

        return rtn;
    }

    public static ArrayList<IncomeList> getIncomeList(Timestamp startTime,Timestamp endTime) throws SQLException,ClassNotFoundException {
        ArrayList<IncomeList> rtn = new ArrayList<>();
        String SQL = "SELECT deptName,Register.doctorNo,doctorName,RegType.isExpert,count(*),sum(realCost) " +
                     "from Register join RegType on Register.typeNo = RegType.typeNo " +
                     "join Doctor on Register.doctorNo = Doctor.doctorNo " +
                     "join Department on Doctor.deptBelong = Department.deptNo " +
                     "where unregister=0 and registerDate between ? and ? " +
                     "group by deptName,Register.doctorNo,doctorName,RegType.isExpert";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1,startTime);
        stm.setObject(2,endTime);
        ResultSet rst = stm.executeQuery();

        System.out.println(stm.toString());

        while (rst.next()) {
            IncomeList data = new IncomeList();
            data.setDeptName(rst.getString(1));
            data.setDoctorNo(rst.getString(2));
            data.setDoctorName(rst.getString(3));
            data.setRegisterType(rst.getBoolean(4)?"专家号":"普通号");
            data.setRegisterNum(rst.getInt(5));
            data.setTotalIncome(rst.getBigDecimal(6).doubleValue());

            rtn.add(data);
        }

        return rtn;
    }
}
