import java.util.*;

public class MyClass {
    public static void main(String args[]) {
        Player player = new Player("Jessebeau2001");
        player.addItem("stone");
        player.addItem("wood");
        
        
        var step = new Step();
        step.addCondition(new ItemCondition("stone"));
        
        System.out.println(player);
        
        if(step.canComplete(player)) step.complete(player);
        
        System.out.println(player);
    }
}

class Quest {
    // Dequeue steps
    
}

class Step {
    private final List<Precondition> preconditions = new ArrayList<>();
    
    boolean canComplete(final Player player) {
        for (var condition : preconditions) {
            if (!condition.met(player)) return false;
        }
        return true;
    }
    
    void complete(final Player player) {
        preconditions.stream().forEach(c -> c.complete(player));
    }
    
    public void addCondition(final Precondition condition) {
        preconditions.add(condition);
    }
}

class Player {
    private final String name;
    private final List<String> inventory = new ArrayList<>();

    
    public Player(final String name) {
        this.name = name;
    }
    
    public void addItem(final String item) {
        inventory.add(item);
    }
    
    public void removeItem(final String item) {
        inventory.remove(item);
    }
    
    public boolean hasItem(final String item) {
        return inventory.contains(item);
    }
    
    @Override
    public String toString() {
        return "Inventory: " + inventory.toString();
    }
}

interface Precondition {
    boolean met(final Player player);
    void complete(final Player player);
}

class ItemCondition implements Precondition {
    private final String item;
    
    public ItemCondition(final String item) {
        this.item = item;
    }
    
    @Override
    public boolean met(final Player player) {
        return player.hasItem(item);
    }
    
    @Override
    public void complete(final Player player) {
        player.removeItem(item);
    }
}
