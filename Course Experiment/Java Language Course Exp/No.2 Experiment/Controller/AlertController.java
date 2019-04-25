package Controller;

import javafx.scene.control.Alert;

public class AlertController {

    public static void showInfomation(String title,String content){
        Alert alert = new Alert(Alert.AlertType.INFORMATION,content);
        alert.setHeaderText(null);
        alert.setTitle(title);
        alert.showAndWait();
    }
}
