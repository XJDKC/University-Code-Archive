package DataBase;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * @author XJDKC on 4/23/2019
 *
 */
public class DBConnection {
    private Connection conn;
    private static DBConnection dbConnection;

    private DBConnection()throws ClassNotFoundException, SQLException {
        //Class.forName("com.mysql.jdbc.Driver");
        conn= DriverManager.getConnection("jdbc:mysql://localhost/JavaExp","root","xrl520");
    }
    public Connection getConnection(){
        return conn;
    }
    public static DBConnection getDBConnection()throws ClassNotFoundException,SQLException{
        if(dbConnection==null){
            dbConnection=new DBConnection();
        }
        return dbConnection;
    }

    //返回一个连接
}
