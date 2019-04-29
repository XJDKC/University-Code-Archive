package DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class RegTypeTableAccess {

    //根据科室查询号种

    //

    public static ArrayList<String> getTypeNames(String typeName) throws SQLException, ClassNotFoundException  {
        ArrayList<String> rtn = new ArrayList<>();
        String SQL = "select typeName from RegType where (typeName like ? or nameAbbr like ?)";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);

        stm.setObject(1, "%" + typeName + "%");
        stm.setObject(2, "%" + typeName.toLowerCase() + "%");

        ResultSet rst = stm.executeQuery();

        while (rst.next()){
            rtn.add(rst.getString(1));
        }

        return rtn;
    }

    public static ArrayList<String> getTypeNames(String deptName, String doctorName, String isExpert, String typeName) throws SQLException, ClassNotFoundException  {
        ArrayList<String> rtn = new ArrayList<>();
        String SQL =  "Select distinct typeName from RegType where (typeName like ? or nameAbbr like ?) and deptBelong in" +
                      "(select deptNo from Department where deptName like ? or nameAbbr like ?) and deptBelong in " +
                      "(select deptBelong from Doctor where doctorName like ? or nameAbbr like ?)";
        Connection conn = DBConnection.getDBConnection().getConnection();

        if (!isExpert.isEmpty())
            SQL += "and isExpert = ?";

        PreparedStatement stm = conn.prepareStatement(SQL);

        stm.setObject(1, "%" + typeName + "%");
        stm.setObject(2, "%" + typeName.toLowerCase() + "%");
        stm.setObject(3, "%" + deptName + "%");
        stm.setObject(4, "%" + deptName.toLowerCase() + "%");
        stm.setObject(5, "%" + doctorName + "%");
        stm.setObject(6, "%" + doctorName.toLowerCase() + "%");
        if (!isExpert.isEmpty())
            stm.setObject(7,isExpert.equals("专家号")?true:false);

        System.out.println(stm.toString());

        ResultSet rst = stm.executeQuery();

        while (rst.next()){
            rtn.add(rst.getString(1));
        }

        System.out.println(rtn.size());

        return rtn;
    }

}
