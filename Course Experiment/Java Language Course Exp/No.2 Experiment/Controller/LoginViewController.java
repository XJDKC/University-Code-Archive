package Controller;

import DataBase.DBConnection;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.PasswordField;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;

import java.net.URL;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ResourceBundle;


public class LoginViewController extends ViewController {
    @FXML private Button btOK;
    @FXML private Button btQuit;
    @FXML private ComboBox usertype;
    @FXML private ComboBox username;
    @FXML private PasswordField password;

    @FXML
    public void btOKOnAction(ActionEvent e){
        Scene scene = this.sceneController.getScene("Patient");
        this.sceneController.getPrimaryStage().setScene(scene);
    }

    @FXML
    public void btQuitOnAction(ActionEvent e){

    }

    @FXML
    public void cbUsernameOnKeyPre(KeyEvent e){

    }

    @FXML void cbUsernameOnMouseEnter(MouseEvent e){

    }

    @FXML void cbUsernameOnMouseExit(MouseEvent e){

    }


    @Override
    public void initialize(URL location, ResourceBundle resources) {
        this.usertype.setItems(FXCollections.observableArrayList("医生", "病人"));
        try {
            String SQL = "SELECT FNAME FROM T_FILM where FID=1";
            Connection conn = DBConnection.getDBConnection().getConnection();
            PreparedStatement stm = conn.prepareStatement(SQL);
            ResultSet rst = stm.executeQuery();

            if (rst.next()){
                this.username.setItems(FXCollections.observableArrayList(rst.getString("FNAME")));
                this.username.getSelectionModel().select(0);
            }
        }
        catch (ClassNotFoundException | SQLException e){
            e.printStackTrace();
        }
    }
}
