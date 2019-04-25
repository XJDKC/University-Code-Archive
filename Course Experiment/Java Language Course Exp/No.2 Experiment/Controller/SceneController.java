package Controller;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.HashMap;

public class SceneController {
    private Stage primaryStage = null;
    private HashMap<String, Scene> scenes = new HashMap<>();
    private static final String[] viewID={"Login","Patient","Doctor","Register","Cancel","PatientList","Income"};
    private static final String[] viewResources={"/View/LoginView.fxml",
                                                 "/View/PatientView.fxml",
                                                 "/View/DoctorView.fxml",
                                                 "/View/RegisterView.fxml",
                                                 "/View/CancelView.fxml",
                                                 "/View/PatientListView.fxml",
                                                 "/View/IncomeView.fxml"};


    public void setPrimaryStage(Stage primaryStage){
        this.primaryStage = primaryStage;
    }

    public Stage getPrimaryStage() {
        return this.primaryStage;
    }

    public void addScene(String sceneID,Scene scene) {
        this.scenes.put(sceneID,scene);
    }

    public void removeScene(String sceneID) {
        this.scenes.remove(sceneID);
    }

    public Scene getScene(String sceneID) {
        Scene scene = scenes.get(sceneID);
        if (scene == null)
            System.out.println("No corresponding scene");
        return scene;
    }

    public Scene getScene(int index) {
        if ( 0 <= index && index < viewID.length)
            return scenes.get(viewID[index]);
        else
            return null;
    }

    public void setScenes(){
        try {
            FXMLLoader loader;
            Parent parent;
            Scene scene;
            ViewController viewController;
            for (int i=0;i<viewID.length;i++){
                loader = new FXMLLoader(getClass().getResource(viewResources[i]));
                parent = loader.load();
                scene = new Scene(parent);
                addScene(viewID[i],scene);

                viewController = loader.getController();
                viewController.setSceneController(this);
            }
        }
        catch (IOException e){
            System.out.println("No target FXML file");
            e.printStackTrace();
        }
        catch (NullPointerException e){
            System.out.println("sceneController is null");
            e.printStackTrace();
        }
    }
}
