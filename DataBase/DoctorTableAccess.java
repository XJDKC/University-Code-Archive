package DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class DoctorTableAccess {

    //根据医生查询科室


    public static boolean doctorLogin(String username, String password) throws SQLException, ClassNotFoundException {

        String SQL = "SELECT * FROM Doctor WHERE doctorName=? AND password=?";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1, username);
        stm.setObject(2, password);
        ResultSet rst = stm.executeQuery();

        if (rst.next()) {
            if (!rst.getString(3).equals(username)) {
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
        String SQL = "SELECT doctorName FROM Doctor WHERE doctorName like ? or nameAbbr like ?";
        ArrayList<String> rtn = new ArrayList<>();

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);
        stm.setObject(1, "%" + filter + "%");
        stm.setObject(2, "%" + filter.toLowerCase() + "%");

        ResultSet rst = stm.executeQuery();

        while (rst.next()) {
            rtn.add(rst.getString(1));
        }

        return rtn;
    }

    public static ArrayList<String> getDoctorNames(String deptName, String doctorName, String isExpert, String typeName) throws SQLException, ClassNotFoundException {
        ArrayList<String> rtn = new ArrayList<>();
        String SQL = "select doctorName from Doctor where (doctorName like ? or nameAbbr like ?) and deptBelong in" +
                     "(select deptNo from Department where deptName like ? or nameAbbr like ?) and deptBelong in " +
                     "(Select deptBelong from RegType where typeName like ? or nameAbbr like ?)";
        Connection conn = DBConnection.getDBConnection().getConnection();

        if (!isExpert.isEmpty())
            SQL += "and isExpert = ?";

        PreparedStatement stm = conn.prepareStatement(SQL);

        stm.setObject(1, "%" + doctorName + "%");
        stm.setObject(2, "%" + doctorName.toLowerCase() + "%");
        stm.setObject(3, "%" + deptName + "%");
        stm.setObject(4, "%" + deptName.toLowerCase() + "%");
        stm.setObject(5, "%" + typeName + "%");
        stm.setObject(6, "%" + typeName.toLowerCase() + "%");
        if (!isExpert.isEmpty())
            stm.setObject(7, isExpert.equals("专家号") ? true : false);

        System.out.println(stm.toString());

        ResultSet rst = stm.executeQuery();

        while (rst.next()) {
            rtn.add(rst.getString(1));
        }

        System.out.println(rtn.size());

        return rtn;
    }

    public static boolean isExpert(String doctorName) throws SQLException, ClassNotFoundException {
        String SQL = "select isExpert from Doctor where (doctorName like ? or nameAbbr like ?) and isExpert=1";
        Connection conn = DBConnection.getDBConnection().getConnection();

        PreparedStatement stm = conn.prepareStatement(SQL);

        stm.setObject(1, "%" + doctorName + "%");
        stm.setObject(2, "%" + doctorName.toLowerCase() + "%");

        ResultSet rst = stm.executeQuery();

        if (rst.next())
            return true;
        return false;
    }
}
