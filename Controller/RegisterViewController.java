package Controller;

import DataBase.DeptTableAcess;
import DataBase.DoctorTableAccess;
import DataBase.PatientTableAccess;
import DataBase.RegTypeTableAccess;
import javafx.application.Platform;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;

import java.net.URL;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class RegisterViewController extends ViewController{

    @FXML private ComboBox cboDeptName;
    @FXML private ComboBox cboDoctorName;
    @FXML private ComboBox cboIsExpert;
    @FXML private ComboBox cboTypeName;
    @FXML private TextField tfPaymentAmout;
    @FXML private TextField tfAmountDue;
    @FXML private TextField tfChangeAmout;
    @FXML private TextField tfRegisterNo;

    private String deptName = "";
    private String doctorName = "";
    private String isExpert = "";
    private String typeName = "";

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


    @FXML
    public void cboIsExpertOnAction(ActionEvent e) {
        isExpert = (String)cboIsExpert.getSelectionModel().getSelectedItem();
        if (isExpert.equals("专家号"))
        {
            try {
                if (!DoctorTableAccess.isExpert(doctorName)) {
                    AlertController.showInfomation("Error","该医生不是专家");
                    cboIsExpert.getSelectionModel().select(0);
                }
            } catch (ClassNotFoundException | SQLException ex) {
                ex.printStackTrace();
            }
        }
    }


    @FXML
    public void btOKOnAction(ActionEvent e) {

    }

    @FXML
    public void btClearOnAction(ActionEvent e) {
        reset();
    }

    @FXML
    public void btQuitOnAction(ActionEvent e) {
        sceneController.changeScene("Patient",true);
    }


    @Override
    public void reset(){
        cboDeptName.getEditor().clear();
        cboDoctorName.getEditor().clear();
        cboIsExpert.getSelectionModel().clearSelection();
        cboTypeName.getEditor().clear();
        cboDeptName.getItems().clear();
        cboDoctorName.getItems().clear();
        cboTypeName.getItems().clear();
        tfPaymentAmout.clear();
        tfAmountDue.clear();
        tfChangeAmout.clear();
        tfRegisterNo.clear();
        try {
            cboDeptName.getItems().setAll(DeptTableAcess.getDeptNames(""));
            cboDoctorName.getItems().setAll(DoctorTableAccess.getDoctorNames(""));
            cboTypeName.getItems().setAll(RegTypeTableAccess.getTypeNames(""));
        }catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources)  {
        cboDeptName.getEditor().textProperty().addListener(new DeptNameTextListener());
        cboDoctorName.getEditor().textProperty().addListener(new DoctorNameTextListener());
        cboTypeName.getEditor().textProperty().addListener(new TypeNameTextListener());
        cboIsExpert.getItems().addAll("普通号","专家号");
    }

    class DeptNameTextListener implements InvalidationListener {
        private String oldValue=null;

        @Override
        public void invalidated(Observable observable) {
            deptName = cboDeptName.getEditor().getText();

            Platform.runLater(() -> comboboxUpdate(cboDeptName,deptName,oldValue,1) );

            oldValue = deptName;
        }
    }

    class DoctorNameTextListener implements InvalidationListener {
        private String oldValue="";

        @Override
        public void invalidated(Observable observable) {
            doctorName = cboDoctorName.getEditor().getText();

            Platform.runLater(() -> comboboxUpdate(cboDoctorName,doctorName,oldValue,2) );

            oldValue = doctorName;
        }
    }

    class TypeNameTextListener implements InvalidationListener {
        private String oldValue="";

        @Override
        public void invalidated(Observable observable) {
            typeName = cboTypeName.getEditor().getText();

            Platform.runLater(() -> comboboxUpdate(cboTypeName,typeName,oldValue,3) );

            oldValue = typeName;
        }
    }

    private void comboboxUpdate(ComboBox comboBox,String newValue,String oldValue,int type) {
        ArrayList<String> newList = null;

        System.out.println(comboBox.getEditor().getText()+" " + oldValue + " " + newValue + " " + deptName + " " + doctorName + " " + typeName + comboBox.getItems().size());

        if (newValue.isEmpty())
            comboBox.hide();
        else if (!newValue.equals((String)comboBox.getSelectionModel().getSelectedItem())){
            try {
                switch (type){
                    case 1:newList = DeptTableAcess.getDeptNames(deptName.trim(),doctorName.trim(),isExpert,typeName.trim());break;
                    case 2:newList = DoctorTableAccess.getDoctorNames(deptName.trim(),doctorName.trim(),isExpert,typeName.trim());break;
                    case 3:newList = RegTypeTableAccess.getTypeNames(deptName.trim(),doctorName.trim(),isExpert,typeName.trim());break;
                    default:break;
                }
            } catch (ClassNotFoundException | SQLException ex) {
                ex.printStackTrace();
            }
            comboBox.getItems().setAll(newList);
            comboBox.show();
        }
    }
}
