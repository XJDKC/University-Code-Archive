package Controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class IncomeViewController extends ViewController {
    @FXML
    public void miMainInterfaceOnAction(ActionEvent e){
        sceneController.changeScene("Doctor",true);
    }

    @FXML
    public void miLogoutOnAction(ActionEvent e){
        sceneController.changeScene("Login",true);
    }

    @FXML
    public void miPatientListOnAction(ActionEvent e){
        sceneController.changeScene("PatientList",false);
    }

    @FXML
    public void miIncomeListOnAction(ActionEvent e){

    }

    @FXML
    public void miRefreshOnAction(ActionEvent e){

    }

    @FXML
    public void miAboutOnAction(ActionEvent e){
        AlertController.showInfomation("About","Powered by XJDKC");
    }

    @Override
    public void clear(){

    }
}
