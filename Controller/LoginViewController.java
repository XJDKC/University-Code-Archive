package Controller;

import DataBase.DBConnection;
import DataBase.DoctorTableAccess;
import DataBase.PatientTableAccess;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.stage.Window;

import java.net.URL;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.ResourceBundle;


public class LoginViewController extends ViewController {
    @FXML private ComboBox username;
    @FXML private PasswordField password;
    @FXML private RadioButton rbtPatient;
    @FXML private RadioButton rbtDoctor;
    @FXML private Button btOK;
    @FXML private Button btQuit;

    @FXML
    public void btOKOnAction(ActionEvent e){
        String name = (String)username.getValue();
        String pwd = password.getText();

        if (name == null || pwd == null){
            AlertController.showInfomation("Login","Please complete the info");
        }

        if (rbtDoctor.isSelected()) {
            try {
                if (DoctorTableAccess.doctorLogin(name, pwd)) {
                    AlertController.showInfomation("Login", "登陆成功!");
                    sceneController.changeScene("Doctor");
                } else {
                    AlertController.showInfomation("Login", "登录失败,请输入正确的用户名和密码!");
                }
            } catch (ClassNotFoundException | SQLException e1) {
                e1.printStackTrace();
            }
        }
        else if (rbtPatient.isSelected()) {
            try {
                if (PatientTableAccess.patientLogin(name, pwd)) {
                    AlertController.showInfomation("Login", "登陆成功!");
                    sceneController.changeScene("Patient");
                } else {
                    AlertController.showInfomation("Login", "登录失败,请输入正确的用户名和密码!");
                }
            } catch (ClassNotFoundException | SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    @FXML
    public void btQuitOnAction(ActionEvent e){
        sceneController.close();
    }

    @FXML
    public void cbUsernameOnKeyPre(KeyEvent e){
        //username.show();
    }

    @FXML void cbUsernameOnMouseEnter(MouseEvent e){
        //username.show();
    }

    @FXML void cbUsernameOnMouseExit(MouseEvent e){
        //username.hide();
    }

    @FXML
    void cbUsernameOnMousePress(MouseEvent e){

    }


    @Override
    public void initialize(URL location, ResourceBundle resources) {

        this.username.getEditor().textProperty().addListener(new InvalidationListener() {
            private String last = null;
            @Override
            public void invalidated(Observable observable) {
                String filter = username.getEditor().getText();
                ArrayList<String> usernames = null;

                if (filter.isEmpty() || filter == null)
                    username.hide();
                else if (last == null || !filter.equals(last)){
                    try {
                        if (rbtPatient.isSelected()){
                            usernames = PatientTableAccess.getPatientNames(filter);
                        }
                        else if (rbtDoctor.isSelected()){
                            usernames = DoctorTableAccess.getDoctorNames(filter);
                        }
                        else
                            usernames = new ArrayList<>();
                    }catch (ClassNotFoundException | SQLException ex) {
                        ex.printStackTrace();
                    }

                    username.getItems().setAll(usernames);

                    System.out.println(usernames.size());

                    username.show();

                    last = filter;
                }
            }
        });
    }

    @Override
    public void clear(){
        username.getEditor().clear();
        username.getItems().clear();
        password.clear();
    }
}
