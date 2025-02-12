package application;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.util.ArrayList;

import application.ChartGantt.ExtraData;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;


public class FXMLController {
	@FXML
	private Button Valider;
	
	@FXML
	private TextField Instance;
	
	@FXML 
	private TextField Balancement;
	
	@FXML
	private TextField NbMachine;
	
	@FXML
	private TextField Preemption;
	
	@FXML
	private TextField Resultat;
	
	
	@FXML
	public void initialize()
	{
		Valider.setDisable(true);
		
        Instance.setOnKeyTyped(event -> handleTextFieldChanged());
        Balancement.setOnKeyTyped(event -> handleTextFieldChanged());
        NbMachine.setOnKeyTyped(event -> handleTextFieldChanged());
        Preemption.setOnKeyTyped(event -> handleTextFieldChanged());
        Resultat.setOnKeyTyped(event -> handleTextFieldChanged());
	}
	
	
    @FXML
    public void handleTextFieldChanged() {
        boolean champsRemplis = !Instance.getText().isEmpty() && !Balancement.getText().isEmpty()
                && !NbMachine.getText().isEmpty() && !Preemption.getText().isEmpty()
                && !Resultat.getText().isEmpty();

        Valider.setDisable(!champsRemplis);
    }
    
  

	
	
	@FXML
	public void Generate(ActionEvent event) throws IOException, InterruptedException, ParseException
	{
		System.out.println("yoo");
		String Ins = Instance.getText();
		String Res = Resultat.getText();
		String NbM = NbMachine.getText();
		String Preempt = Preemption.getText();
		String Balance = Balancement.getText();
		
		
		ProcessBuilder pb = new ProcessBuilder("bash", "script.sh", Ins, Res, NbM,Preempt,Balance);
        pb.directory(new File("src"));
        Process process = pb.start();
        int exitCode = process.waitFor();
        System.out.println("Bash script executed with exit code: " + exitCode);
        
        String filePath = "src/application/result/" + Res;
        

    	
		File f=new File(filePath);
		FileReader fr=null;
        System.out.println("heeeela");

		try {
			fr = new FileReader(f);
	        System.out.println("heedkfjkjggeela");

		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}		
    	System.out.println("lkjgkjgljg");
        BufferedReader fb=new BufferedReader(fr);
        
        String[] colors=new String[] { "status-red", "status-green", "status-blue","status-yellow","status-pink","status-cyan","status-grey", };

		ArrayList<XYChart.Series> TabSerie=new ArrayList<XYChart.Series>();
		
        ArrayList<String> machinename = new ArrayList<String>();
        
        try {
        	System.out.println("lkjgkjgljg");
        	String line=fb.readLine().trim(); //On lit la 1ère ligne du fichier qui contient le nombre de machine
        	int numMachines=Integer.parseInt(line); //On stock le nombre de machine
        	
        	line = fb.readLine();//On skip la ligne M1
	        System.out.println("heeeela");
	        for(int i =1; i<=numMachines;i++) { // Ici on construit les taches
	        	String mn="M"+i;
	        	machinename.add(mn);

				XYChart.Series<Object, Object> s= new XYChart.Series<>();
	        	
	        	int j=i;
	        	while((line = fb.readLine())!=null && !line.matches("M[0-9]")) {
	        		if (line.isEmpty() || line.matches("M[0-9]")) {
	        	        break;
	        	    }
	        		
	        		String[] token=line.split(" ");
	        		int start= Integer.parseInt(token[0]);
	        		int end= Integer.parseInt(token[1]);
	        		
	        		System.out.println(start+" "+end+" "+j+" "+s);
	        		Data o = new Data<Object, Object>(start,mn, new ExtraData( start+end,colors[j]));
	        		System.out.println(o);
	        		s.getData().add(new Data<Object, Object>(start,mn, new ExtraData( start+end,colors[j])));	
	        		if(j==6) j=0;
	        		j++;
	        		System.out.println(s);
	        	}
	        	TabSerie.add(s);
	        }
	        System.out.println(TabSerie);
	        fb.close();
        }catch(IOException e) {
        	e.printStackTrace();
        }
        
        /*----------------------------------------------Affichage Diagramme de Gantt----------------------------------------------*/
        
        final NumberAxis xAxis = new NumberAxis();
        final CategoryAxis yAxis = new CategoryAxis();
        
        final ChartGantt<Number,String> chart = new ChartGantt<Number,String>(xAxis,yAxis);
        xAxis.setLabel("");
        xAxis.setTickLabelFill(Color.CHOCOLATE);
        xAxis.setMinorTickCount(4);

        yAxis.setLabel("");
        yAxis.setTickLabelFill(Color.CHOCOLATE);
        yAxis.setTickLabelGap(10);
        yAxis.setCategories(FXCollections.<String>observableArrayList(machinename));

        chart.setTitle("Diagramme de Gantt");
        chart.setLegendVisible(false);
        chart.setBlockHeight(50);
        
        for(XYChart.Series s : TabSerie) {
        	chart.getData().add(s); 
        }      
        chart.getStylesheets().add(getClass().getResource("chartgantt.css").toExternalForm());
        
        System.out.println("laaaaaa");
        Main.getStage().setScene(new Scene(chart,620,350));
       
    }

}
	


