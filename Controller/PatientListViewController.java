package Controller;

import DataBase.RegisterTableAccess;
import Model.PatientList;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.net.URL;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class PatientListViewController extends ViewController {

    @FXML private TableView tbvPatient;
    @FXML private TableColumn colRegisterNo;
    @FXML private TableColumn colPatientName;
    @FXML private TableColumn colRegisterDate;
    @FXML private TableColumn colRegisterType;

    @FXML
    public void miMainInterfaceOnAction(ActionEvent e) {
        sceneController.changeScene("Doctor", true);
    }

    @FXML
    public void miLogoutOnAction(ActionEvent e) {
        sceneController.changeScene("Login", true);
    }

    @FXML
    public void miPatientListOnAction(ActionEvent e) {

    }

    @FXML
    public void miIncomeListOnAction(ActionEvent e) {
        sceneController.changeScene("Income", false);
    }

    @FXML
    public void miRefreshOnAction(ActionEvent e) {
        refreshTable();
    }

    @FXML
    public void miAboutOnAction(ActionEvent e) {
        AlertController.showInfomation("About", "Powered by XJDKC");
    }

    @Override
    public void reset() {
        refreshTable();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        colRegisterNo.setCellValueFactory(new PropertyValueFactory<>("registerNo"));
        colPatientName.setCellValueFactory(new PropertyValueFactory<>("patientName"));
        colRegisterDate.setCellValueFactory(new PropertyValueFactory<>("registerDate"));
        colRegisterType.setCellValueFactory(new PropertyValueFactory<>("registerType"));
        refreshTable();
    }


    private void refreshTable() {
        tbvPatient.setItems(FXCollections.observableArrayList());

        try {
            ArrayList<PatientList> data = RegisterTableAccess.getPatientList(AccountController.getAccountName());
            tbvPatient.setItems(FXCollections.observableArrayList(data));
        } catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
        }
    }
}
