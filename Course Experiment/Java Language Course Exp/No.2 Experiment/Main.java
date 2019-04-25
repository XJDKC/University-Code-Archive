import Controller.SceneController;
import Controller.ViewController;
import DataBase.DBConnection;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{

        SceneController sceneController;

        sceneController = new SceneController();
        sceneController.setPrimaryStage(primaryStage);
        sceneController.setScenes();

        DBConnection.getDBConnection();

        primaryStage.setTitle("Registration Management System");
        primaryStage.setScene(sceneController.getScene(0));
        primaryStage.show();
    }
}
