package DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class PatientTableAccess {

    //查询登录用户名密码

    //更新预存金额

    //更新最后一次登录时间以及日期

    //根据

    public static boolean patientLogin(String username,String password) throws SQLException, ClassNotFoundException {

        String SQL = "SELECT * FROM Patient WHERE patientName=? AND password=?";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1, username);
        stm.setObject(2, password);
        ResultSet rst = stm.executeQuery();

        if (rst.next()) {
            if(!rst.getString(2).equals(username)){
                return false;
            }
            String pwd = rst.getString(3);
            if (pwd.equals(password)) {
                return true;
            }
        }
        return false;
    }

    public static ArrayList<String> getPatientNames(String filter) throws SQLException, ClassNotFoundException {
        String SQL = "SELECT patientName FROM Patient WHERE patientName like ?";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1, "%"+filter+"%");

        System.out.println(stm.toString());

        ResultSet rst = stm.executeQuery();
        ArrayList<String> rtn = new ArrayList<>();

        while (rst.next()){
            rtn.add(rst.getString(1));
        }

        System.out.println(rtn.size());

        return rtn;
    }
}
