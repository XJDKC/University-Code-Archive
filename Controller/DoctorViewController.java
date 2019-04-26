package Controller;


import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;


public class DoctorViewController extends ViewController {

    @FXML private Button btPatientList;
    @FXML private Button btIncomeList;
    @FXML private Button btLogout;


    @FXML
    public void btPatientListOnAction(ActionEvent e){
        sceneController.changeScene("PatientList",true);
    }

    @FXML
    public void btIncomeListOnAction(ActionEvent e){
        sceneController.changeScene("Income",true);
    }

    @FXML
    public void btLogoutOnAction(ActionEvent e){
        sceneController.changeScene("Login",true);
    }

    @Override
    public void clear(){

    }
}
