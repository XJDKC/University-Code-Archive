package Controller;

import DataBase.RegisterTableAccess;
import Model.IncomeList;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.net.URL;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class IncomeViewController extends ViewController {

    @FXML private TableView tbvIncome;
    @FXML private TableColumn colDeptName;
    @FXML private TableColumn colDoctorNo;
    @FXML private TableColumn colDoctorName;
    @FXML private TableColumn colRegisterType;
    @FXML private TableColumn colRegisterNum;
    @FXML private TableColumn colTotalIncome;
    @FXML private ComboBox cboStartYear;
    @FXML private ComboBox cboStartMonth;
    @FXML private ComboBox cboStartDay;
    @FXML private ComboBox cboEndYear;
    @FXML private ComboBox cboEndMonth;
    @FXML private ComboBox cboEndDay;

    private Timestamp startTime = Timestamp.valueOf("2000-01-01 00:00:00.0");
    private Timestamp endTime = Timestamp.valueOf("2050-12-31 23:59:59.9");

    private final int[] monthDays = {31,28,31,30,31,30,31,31,30,31,30,31};

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
        sceneController.changeScene("PatientList",true);
    }

    @FXML
    public void miIncomeListOnAction(ActionEvent e) {

    }

    @FXML
    public void miRefreshOnAction(ActionEvent e){
        refreshTable();
    }

    @FXML
    public void miAboutOnAction(ActionEvent e){
        AlertController.showInfomation("About","Powered by XJDKC");
    }

    @FXML
    public void cbStartYearOnHidden(Event e) {
        updateStartDay();
        updateStartTime();
    }

    @FXML
    public void cbStartMonthOnHidden(Event e) {
        updateStartDay();
        updateStartTime();
    }

    @FXML
    public void cbStartDayOnHidden(Event e) {
        updateStartTime();
    }

    @FXML
    public void cbEndYearOnHidden(Event e) {
        updateEndDay();
        updateEndTime();
    }

    @FXML
    public void cbEndMonthOnHidden(Event e) {
        updateEndDay();
        updateEndTime();
    }

    @FXML
    public void cbEndDayOnHidden(Event e) {
        updateEndTime();
    }

    @Override
    public void reset(){
        setComboboxItems(cboStartYear,2000,2050);
        setComboboxItems(cboStartMonth,1,12);
        setComboboxItems(cboStartDay,1,31);
        setComboboxItems(cboEndYear,2000,2050);
        setComboboxItems(cboEndMonth,1,12);
        setComboboxItems(cboEndDay,1,31);
        startTime = Timestamp.valueOf("2000-01-01 00:00:00.0");
        endTime = Timestamp.valueOf("2050-12-31 23:59:59.9");
        refreshTable();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {

        setComboboxItems(cboStartYear,2000,2050);
        setComboboxItems(cboStartMonth,1,12);
        setComboboxItems(cboStartDay,1,31);
        setComboboxItems(cboEndYear,2000,2050);
        setComboboxItems(cboEndMonth,1,12);
        setComboboxItems(cboEndDay,1,31);

        colDeptName.setCellValueFactory(new PropertyValueFactory<>("deptName"));
        colDoctorNo.setCellValueFactory(new PropertyValueFactory<>("doctorNo"));
        colDoctorName.setCellValueFactory(new PropertyValueFactory<>("doctorName"));
        colRegisterType.setCellValueFactory(new PropertyValueFactory<>("registerType"));
        colRegisterNum.setCellValueFactory(new PropertyValueFactory<>("registerNum"));
        colTotalIncome.setCellValueFactory(new PropertyValueFactory<>("totalIncome"));

        refreshTable();
    }

    private void refreshTable(){
        tbvIncome.setItems(FXCollections.observableArrayList());

        try {
            ArrayList<IncomeList> data = RegisterTableAccess.getIncomeList(startTime,endTime);
            tbvIncome.setItems(FXCollections.observableArrayList(data));
        } catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void updateStartDay() {
        if (!cboStartYear.getSelectionModel().isEmpty()&&!cboStartMonth.getSelectionModel().isEmpty()) {
            int year = ((Integer)cboStartYear.getValue()).intValue();
            int month = ((Integer)cboStartMonth.getValue()).intValue();
            if ((year%4==0&&year%100!=0||year%400==0)&&month==2)
                setComboboxItems(cboStartDay,1,29);
            else
                setComboboxItems(cboStartDay,1,monthDays[month-1]);
        }
    }

    private void updateEndDay() {
        if (!cboEndYear.getSelectionModel().isEmpty()&&!cboEndMonth.getSelectionModel().isEmpty()) {
            int year = ((Integer)cboEndYear.getValue()).intValue();
            int month = ((Integer)cboEndMonth.getValue()).intValue();
            if ((year%4==0&&year%100!=0||year%400==0)&&month==2)
                setComboboxItems(cboEndDay,1,29);
            else
                setComboboxItems(cboEndDay,1,monthDays[month-1]);
        }
    }

    private void updateStartTime() {
        if (!cboStartYear.getSelectionModel().isEmpty() &&
            !cboStartMonth.getSelectionModel().isEmpty() &&
            !cboStartDay.getSelectionModel().isEmpty()) {

            int year = ((Integer)cboStartYear.getValue()).intValue();
            int month = ((Integer)cboStartMonth.getValue()).intValue();
            int day = ((Integer)cboStartDay.getValue()).intValue();
            //startTime = Timestamp.valueOf(String.format("%04d-%02d-%02d 00:00:00.0",year,month,day));
            startTime = new Timestamp(year-1900,month-1,day,0,0,0,0);

            refreshTable();
        }
    }

    private void updateEndTime() {
        if (!cboEndYear.getSelectionModel().isEmpty() &&
            !cboEndMonth.getSelectionModel().isEmpty() &&
            !cboEndDay.getSelectionModel().isEmpty()) {

            int year = ((Integer)cboEndYear.getValue()).intValue();
            int month = ((Integer)cboEndMonth.getValue()).intValue();
            int day = ((Integer)cboEndDay.getValue()).intValue();
            //endTime = Timestamp.valueOf(String.format("%04d-%02d-%02d 23:59:59.9",year,month,day));
            endTime = new Timestamp(year-1900,month-1,day,23,59,59,9);

            refreshTable();
        }
    }

    private void setComboboxItems(ComboBox comboBox,int begin,int end) {
        comboBox.getItems().clear();
        for (int i=begin;i<=end;i++) {
            comboBox.getItems().add(Integer.valueOf(i));
        }
    }
}
