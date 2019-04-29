package Controller;

import DataBase.DBConnection;
import DataBase.DoctorTableAccess;
import DataBase.PatientTableAccess;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableStringValue;
import javafx.beans.value.ObservableValue;
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
    @FXML
    private ComboBox username;
    @FXML
    private PasswordField password;
    @FXML
    private RadioButton rbtPatient;
    @FXML
    private RadioButton rbtDoctor;
    @FXML
    private Button btOK;
    @FXML
    private Button btQuit;

    @FXML
    public void btOKOnAction(ActionEvent e) {
        String name = (String) username.getValue();
        String pwd = password.getText();

        if (name == null || pwd == null) {
            AlertController.showInfomation("Login", "Please complete the info");
        }

        if (rbtDoctor.isSelected()) {
            try {
                if (DoctorTableAccess.doctorLogin(name, pwd)) {
                    AlertController.showInfomation("Login", "登陆成功!");
                    sceneController.changeScene("Doctor", true);
                } else {
                    AlertController.showInfomation("Login", "登录失败,请输入正确的用户名和密码!");
                }
            } catch (ClassNotFoundException | SQLException e1) {
                e1.printStackTrace();
            }
        } else if (rbtPatient.isSelected()) {
            try {
                if (PatientTableAccess.patientLogin(name, pwd)) {
                    AlertController.showInfomation("Login", "登陆成功!");
                    sceneController.changeScene("Patient", true);
                } else {
                    AlertController.showInfomation("Login", "登录失败,请输入正确的用户名和密码!");
                }
            } catch (ClassNotFoundException | SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    @FXML
    public void btQuitOnAction(ActionEvent e) {
        sceneController.close();
    }

    @FXML
    public void cbUsernameOnKeyPre(KeyEvent e) {
        //username.show();
    }

    @FXML
    public void cbUsernameOnMouseEnter(MouseEvent e) {
        //username.show();
    }

    @FXML
    public void cbUsernameOnMouseExit(MouseEvent e) {
        //username.hide();
    }





    @FXML
    public void rbtDoctorOnAction(ActionEvent e) {
        try {
            username.getItems().setAll(DoctorTableAccess.getDoctorNames(""));
        } catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
        }
    }

    @FXML
    public void rbtPatientOnAction(ActionEvent e) {
        try {
            username.getItems().setAll(PatientTableAccess.getPatientNames(""));
        } catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
        }
    }

    @FXML


    @Override
    public void reset() {
        username.getEditor().clear();
        username.getItems().clear();
        password.clear();
        try {
            username.getItems().setAll(PatientTableAccess.getPatientNames(""));
        } catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        username.getEditor().textProperty().addListener(new UsernameTextListener());
    }

    class UsernameTextListener implements InvalidationListener {

        private String oldValue=null;

        @Override
        public void invalidated(Observable observable) {
            String newValue = username.getEditor().getText();
            ArrayList<String> usernames = null;

            System.out.println(oldValue+" "+newValue);


            if (newValue == null || newValue.isEmpty()) {
                //username.getItems().setAll(PatientTableAccess.getPatientNames(""));
                username.hide();
            } else if (oldValue == null || !newValue.equals(oldValue)) {
                try {
                    if (rbtPatient.isSelected())
                        usernames = PatientTableAccess.getPatientNames(newValue.trim());
                    else if (rbtDoctor.isSelected())
                        usernames = DoctorTableAccess.getDoctorNames(newValue.trim());
                    else
                        usernames = new ArrayList<>();
                } catch (ClassNotFoundException | SQLException ex) {
                    ex.printStackTrace();
                }
                username.getItems().setAll(usernames);
                username.show();
                oldValue = newValue;
            }
        }
    }
}
