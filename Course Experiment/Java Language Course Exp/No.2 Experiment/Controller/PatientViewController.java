package Controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;

import java.awt.*;
import java.net.URL;
import java.util.ResourceBundle;

public class PatientViewController extends ViewController {
    @FXML private Button btRegister;
    @FXML private Button btCancel;
    @FXML private Button btLogout;

    @FXML
    public void btRegisterOnAction(ActionEvent e){
        sceneController.changeScene("Register",true);
    }

    @FXML
    public void btCancelOnAction(ActionEvent e){
        sceneController.changeScene("Cancel",true);
    }

    @FXML
    public void btLogoutOnAction(ActionEvent e){
        sceneController.changeScene("Login",true);
    }

    @Override
    public void reset(){

    }
}
