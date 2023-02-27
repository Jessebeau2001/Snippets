import java.lang.*;
import java.io.*;
import java.util.Scanner;

public class MyClass {
    public static void main(String args[]) {
        measure(50);
    }
    
    static void measure(int amount) {
        long[] timepoints = new long[amount];
        
        for (int i = 0; i < amount; i++) {
            long startTime = System.nanoTime();
            myFunc(); 
            long stopTime = System.nanoTime();
            timepoints[i] = stopTime - startTime;
        }
        
        long total = 0;
        long min = timepoints[0];
        long max = 0;
        
        for (int i = 0; i < amount; i++) {
            total += timepoints[i];
            if (min > timepoints[i]) min = timepoints[i];
            if (max < timepoints[i]) max = timepoints[i];
            System.out.println((i + 1) + "\t| " + timepoints[i] + " ns");
        }
        
        float av = total / amount;
        
        System.out.println("\nTotal: " + total);
        System.out.println("\nAverage: " + av);
        System.out.println("Min:\t" + min);
        System.out.println("Max:\t" + max);
    }
    
    static void myFunc() {
        File file = new File("myFile.txt");
        Scanner reader;
        
        try {
            reader = new Scanner(file);
        } catch (FileNotFoundException e) {
            return;
        }
        
        while(reader.hasNextLine()) {
            String data = reader.nextLine();
        }
        
        reader.close();
    }
}
