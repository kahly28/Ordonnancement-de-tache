package application;

public class MyMain {
    public static void main(String[] args) {
        new MyClass().runSchedule(args[0],args[1],Integer.parseInt(args[2]),Integer.parseInt(args[3]),Integer.parseInt(args[4]));
    }


    static { 
        System.loadLibrary("mylibrary");
        //System.load("/Users/ahmet/Documents/L2/Projet/project/java/application/Program/src/libmylibrary.dylib");
    }
}
