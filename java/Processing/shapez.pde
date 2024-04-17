ArrayList<Node> nodes = new ArrayList<Node>();

void setup()
{
  size(800, 800);
  background(250, 255, 240);
  textSize(32);
  textAlign(CENTER, CENTER);
}

void draw() { }

Node selected = null;

void mouseClicked()
{
  Node clicked = null;
  
  for (var node : nodes)
  {
     var distX = mouseX - node.Pos.x;
     var distY = mouseY - node.Pos.y;
     var dist = sqrt(pow(distX, 2) + pow(distY, 2));
     var radius = node.Size / 2;
     
     if (dist < radius)
     {
       clicked = node;
     }
  }
  
  if (clicked == null)
  {
     if (selected == null)
     { // New single node
       selected = new Node(mouseX, mouseY, GetLetter());
       selected.Draw(165, 252, 3);
       nodes.add(selected);
       println("Added new loosse node");
     } else { // New connected node
       var node = new Node(mouseX, mouseY, GetLetter());
       node.AddConnection(selected, int(random(1, 15)));
       node.DrawCons();
       node.Draw();
       nodes.add(node);
       selected = null;
       println("Connected new node and unselected");
     }
  } else {
    if (selected == null)
    { // Select node
      clicked.Draw(165, 252, 3);
      selected = clicked;
      println("selected node");
    } else {
      if (selected == clicked)
      { // Unselect
         selected.Draw();
         selected = null;
         println("Deselected node");
      } else { // Connect Nodes
        selected.AddConnection(clicked, int(random(1, 15)));
        selected.DrawCons();
        selected.Draw();
        selected = null;
        println("Connected 2 existing nodes");
      }
    }
  }
}

void keyPressed() {
  if (keyCode == DELETE && selected != null) {
    nodes.remove(selected);
    
    for (var con : selected.Cons)
    {
      var toRemove = new ArrayList<Connection>();
      for (var farCon : con.Dest.Cons)
      {
        if (farCon.Dest == selected)
        {
           toRemove.add(farCon);
        }
      }
      
      for (var farCon : toRemove)
        con.Source.Cons.remove(farCon);
    }
    
    selected = null;
    background(250, 255, 240);
    for (var node : nodes)
    {
      node.DrawCons();
      node.Draw();
    }
    
    println("Deleted node");
  }
}

String GetLetter()
{ // Char alphabet ranges form 97 to 122
  return "" + (char)(nodes.size() + 97);
}

class Node
{
  public float Size = 80;
  public PVector Pos;
  public String Name;
  public ArrayList<Connection> Cons = new ArrayList<Connection>();
  
  public Node(float x, float y, String name)
  {
    Pos = new PVector(x, y);
    Name = name;
  }
  
  public void AddConnection(Node dest, int length)
  {
    var con = new Connection(this, dest, length);
    Cons.add(con);
  }
  
  public void Draw()
  {
    Draw(204, 204, 255);
  }
  
  public void Draw(int r, int g, int b)
  {
    fill(r, g, b);
    ellipse(Pos.x , Pos.y, 80, 80);
    fill(0, 0, 0);
    text(Name, Pos.x, Pos.y - 5);
  }
  
  public void DrawCons()
  {
    fill(0, 0, 0);
    for (Connection n : Cons)
    {
      line(Pos.x, Pos.y, n.Dest.Pos.x, n.Dest.Pos.y);
      n.Dest.Draw();
      
      var textX = Pos.x + ((n.Dest.Pos.x - Pos.x) / 2);
      var textY = Pos.y + ((n.Dest.Pos.y - Pos.y) / 2);
      
      text(n.Length, textX, textY - 5);
    }
  }
}

class Connection
{
  public int Length;
  public Node Source;
  public Node Dest;
  
  public Connection(Node source, Node dest, int length)
  {
    Source = source;
    Dest = dest;
    Length = length;
  }
}
