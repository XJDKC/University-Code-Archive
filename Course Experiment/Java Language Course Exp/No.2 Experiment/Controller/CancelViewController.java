package Controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class CancelViewController extends ViewController {

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
        sceneController.changeScene("Register",false);
    }

    @FXML
    public void miCancelOnAction(ActionEvent e){

    }

    @FXML
    public void miAboutOnAction(ActionEvent e){
        AlertController.showInfomation("About","Powered by XJDKC");
    }

    @Override
    public void clear(){

    }
}
