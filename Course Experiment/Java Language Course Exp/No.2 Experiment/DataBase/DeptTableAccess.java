package DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class DeptTableAccess {

    public static ArrayList<String> getDeptNames(String deptName) throws SQLException, ClassNotFoundException  {
        //医生姓名 会影响查询结果 医生有归属的科室
        //是否为专家会影响医生查询结果
        //typename会影响医生查询结果

        ArrayList<String> rtn = new ArrayList<>();
        String SQL = "select deptName from Department where (deptName like ? or nameAbbr like ?)";

        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);

        stm.setObject(1, "%" + deptName + "%");
        stm.setObject(2, "%" + deptName.toLowerCase() + "%");

        ResultSet rst = stm.executeQuery();

        while (rst.next()){
            rtn.add(rst.getString(1));
        }

        System.out.println(rtn.size());

        return rtn;
    }

    public static ArrayList<String> getDeptNames(String deptName,String doctorName,String isExpert,String typeName) throws SQLException, ClassNotFoundException  {
        //医生姓名 会影响查询结果 医生有归属的科室
        //是否为专家会影响医生查询结果
        //typename会影响医生查询结果

        ArrayList<String> rtn = new ArrayList<>();
        String SQL = "select deptName from Department where (deptName like ? or nameAbbr like ?) and deptNo in" +
                     "(Select deptBelong from Doctor where doctorName like ? or nameAbbr like ?) and deptNo in" +
                     "(Select deptBelong from RegType where typeName like ? or nameAbbr like ?)";
        Connection conn = DBConnection.getDBConnection().getConnection();
        PreparedStatement stm = conn.prepareStatement(SQL);

        stm.setObject(1, "%" + deptName + "%");
        stm.setObject(2, "%" + deptName.toLowerCase() + "%");
        stm.setObject(3, "%" + doctorName + "%");
        stm.setObject(4, "%" + doctorName.toLowerCase() + "%");
        stm.setObject(5, "%" + typeName + "%");
        stm.setObject(6, "%" + typeName.toLowerCase() + "%");

        ResultSet rst = stm.executeQuery();

        while (rst.next()){
            rtn.add(rst.getString(1));
        }

        //System.out.println(rtn.size());

        return rtn;
    }
}
