public class MyClass {
    public static void main(String args[]) {
      B b = new B();
      C c = new C(b);
      
      b.print();
      c.print();
      
      b.s = "Balls 2";
      
      b.print();
      c.print();
    }
}

class B {
    public String s = "balls";
    public void print() {
        System.out.println(s);
    }
}

class C {
    public B instance;
    public C(B in) {
        instance = in;
    }
    
    void print() {
        instance.print();
    }
}

// This will show that the instance in C c is in fact a reference to the B b
