package DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class DoctorTableAccess {

    //根据医生查询科室


    public static boolean doctorLogin(String username,String password) throws SQLException, ClassNotFoundException {

        String SQL = "SELECT * FROM Doctor WHERE doctorName=? AND password=?";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1, username);
        stm.setObject(2, password);
        ResultSet rst = stm.executeQuery();

        if (rst.next()) {
            if(!rst.getString(3).equals(username)){
                return false;
            }
            String pwd = rst.getString(5);
            if (pwd.equals(password)) {
                return true;
            }
        }
        return false;
    }

    public static ArrayList<String> getDoctorNames(String filter) throws SQLException, ClassNotFoundException {
        String SQL = "SELECT doctorName FROM Doctor WHERE doctorName like ?";
        ArrayList<String> rtn = new ArrayList<>();

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1, "'%"+filter+"%'");
        ResultSet rst = stm.executeQuery();

        while (rst.next()){
            rtn.add(rst.getString(1));
        }

        return rtn;
    }
}
