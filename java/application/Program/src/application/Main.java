package application;
	
import java.io.File;



import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import application.FXMLController;

public class Main extends Application implements EventHandler<ActionEvent> {
	
	private static Stage guiStage;
	
	 public static Stage getStage() {
	        return guiStage;
	    }
	 
	@Override
	public void start(Stage primaryStage) {
		try {
			guiStage=primaryStage;
			System.out.println(new File(".").getAbsolutePath());
			System.out.println("yoo");

			
			Button btn = new Button();
			GridPane root = new GridPane();
			root = FXMLLoader.load(getClass().getResource("vue.fxml"));
			//root.getClass().getResource("vue.fxml");
			
			Scene scene = new Scene(root);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.show();
			
			
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void handle(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}

