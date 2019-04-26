package Controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import java.net.URL;
import java.util.ResourceBundle;

public class RegisterViewController extends ViewController{


    @FXML
    public void miMainInterfaceOnAction(ActionEvent e){
        sceneController.changeScene("Patient",true);
    }

    @FXML
    public void miLogoutOnAction(ActionEvent e){
        sceneController.changeScene("Login",true);
    }

    @FXML
    public void miRegisterOnAction(ActionEvent e){

    }

    @FXML
    public void miCancelOnAction(ActionEvent e){
        sceneController.changeScene("Cancel",false);
    }

    @FXML
    public void miAboutOnAction(ActionEvent e){
        AlertController.showInfomation("About","Powered by XJDKC");
    }


    @Override
    public void clear(){

    }

    @Override
    public void initialize(URL location, ResourceBundle resources)  {

    }
}
