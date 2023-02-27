using System;
using System.Collections;
using Microsoft.VisualBasic.FileIO;

namespace ConsoleApp
{
    internal static class Program
    {
        private static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }

        private static void ConvertCSVData()
        {
            using (var parser = new TextFieldParser("./files/info.csv"))
            {
                
            }
        }
    }
}

namespace GS1Lib
{
    public class ComponentBase
    {
        public readonly int Ai;
        protected readonly int Size;

        public ComponentBase(int ai, int size)
        {
            Ai = ai;
            Size = size;
        }
    }

    public class ComponentLookup : ILookup<int, ComponentBase>
    {
        private List<ComponentBase> _components = new();

        public ComponentLookup()
        {
            
        }
        
        public IEnumerator<IGrouping<int, ComponentBase>> GetEnumerator()
        {
            return _components.GroupBy(c => c.Ai).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return _components.GetEnumerator();
        }

        public bool Contains(int key) => _components.FindAll(c => c.Ai.Equals(key)).Any();

        public int Count => _components.Count;

        public IEnumerable<ComponentBase> this[int key]
        {
            get => _components.FindAll(c => c.Ai.Equals(key));
            set
            {
                _components.RemoveAll(c => c.Ai.Equals(key));
                _components.AddRange(value);
            }
        }

        public static ComponentLookup BuildFromCSV(string path)
        {
            try
            {
                File.OpenRead(path);

            }
            catch (IOException)
            {
                
            }
            
            return new ComponentLookup();
        }
    }

    public class Component : ComponentBase
    {
        private string _value = "";
        public string Value
        {
            get => _value;
            set
            {
                if (value.Length == Size)
                    _value = value;
                else
                    _value = value.Length < Size ? value.PadLeft(Size - value.Length, '0') : value[..Size];
            }
            
        }
        
        public Component(int ai, int size, string value) : base(ai, size)
        {
            Value = value;
        }

        public override string ToString()
        {
            return Ai + Value;
        }
    }

    public class GS1
    {
        private readonly List<Component> _components;

        public GS1()
        {
            _components = new List<Component>(2);
        }
        
        public GS1(List<Component> components)
        {
            _components = components;
        }

        public override string ToString()
        {
            return _components.Aggregate("", (current, component) => current + component);
        }
    }
}
