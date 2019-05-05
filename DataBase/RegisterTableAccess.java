package DataBase;


import Model.Patient;
import Model.PatientList;
import Model.RegType;

import java.math.BigDecimal;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
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
}
