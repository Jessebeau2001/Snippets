using System.Collections;

namespace RPN
{
    internal static class Program
    {
        private static void Main()
        {
            var sens = new DistanceSensor(7);
            sens.Write();
        }
    }

    internal interface IWriteable
    {
        public void Write();
    }

    internal abstract class Sensor : IWriteable
    {
        private int _pin;
        protected Sensor(int pin)
        {
            _pin = pin;
        }
        
        protected abstract void Update();
        
        public void Write()
        {
            Console.WriteLine($"The pin is {_pin}");
        }
    }

    internal class DistanceSensor : Sensor
    {
        public DistanceSensor(int pin) : base(pin)
        {
            
        }

        protected override void Update()
        {
            throw new NotImplementedException();
        }
    }
}