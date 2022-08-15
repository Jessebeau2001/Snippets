import java.util.*;

public class MyClass {
    public static void main(String args[]) {
      
      BlockEvent be = new BlockEvent();
      ChatEvent ce = new ChatEvent();
      
      EventSequence seq = new EventSequence( new IEvent[] {be, ce} );
      
      System.out.println(be + "\n" + ce);
      System.out.println(seq);
      
    }
}

class EventSequence
{
    Stack<IEvent> stack = new Stack<IEvent>();
    
    public EventSequence() { }
     
    public EventSequence(String JSONEventSequence) {
        // Convert data to array of Events
        // Push onto stack
    }
    
    public EventSequence(IEvent events[]) {
        for (IEvent event : events) {
            stack.push(event);
        }
    }
    
    @Override
    public String toString() {
        String out = "Events left on stack:";
        for (IEvent event : stack) out += "\n > " + event;
        return out;
    }
}

interface IEvent
{
    public void run();
}

class BlockEvent implements IEvent
{
    @Override
    public void run() {
        System.out.println("A block was placed (Simulated block event)");
    }
    
    @Override
    public String toString() {
        return "I'm a block night";
    }
}

class ChatEvent implements IEvent
{
    @Override
    public void run() {
        System.out.println("Hello im a message (Simulated Text Chat Message Event)");
    }
    
    @Override
    public String toString() {
        return "I'm a Chat event";
    }
}
