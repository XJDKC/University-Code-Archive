package Controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class PatientListViewController extends ViewController {

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

    }

    @FXML
    public void miIncomeListOnAction(ActionEvent e){
        sceneController.changeScene("Income",false);
    }

    @FXML
    public void miRefreshOnAction(ActionEvent e){

    }

    @FXML
    public void miAboutOnAction(ActionEvent e){
        AlertController.showInfomation("About","Powered by XJDKC");
    }

    @Override
    public void reset(){

    }
}
