package Controller;

import javafx.fxml.Initializable;

import java.net.URL;
import java.util.ResourceBundle;

public abstract class ViewController implements Initializable {
    protected SceneController sceneController;

    public ViewController(){}

    public ViewController(SceneController sceneController) {
        this.setSceneController(sceneController);
    }

    public void setSceneController(SceneController sceneController){
        this.sceneController=sceneController;
    }

    @Override
    public void initialize(URL location, ResourceBundle resources)  {

    }
}
