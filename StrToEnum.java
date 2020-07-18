import java.util.*; 

enum Color {
    RED,
    GREEN,
    BLUE
}

public class HelloWorld{
     public static void main(String []args){
        String strColor = "blUe";
        Color enumColor = null;
        
        Map<String, Color> hm = new HashMap<String, Color>();
        hm.put("red", Color.valueOf("RED"));
        //Map stuff is unused in this example
         
        try {
            enumColor = Color.valueOf(strColor.toUpperCase());
        } catch (IllegalArgumentException e) {
            System.out.println("Could not convert the color, setting to red");
            enumColor = Color.RED;
        }
        System.out.println("The color is " + enumColor);
     }
}
