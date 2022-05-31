using System.Collections;

namespace RPN
{
    internal static class Program
    {
        private static void Main()
        {
            var calculator = new RpnCalculator();
            
            const string test = "5 10 + 10 -";
            var list = Parser.Parse(test);

            calculator.Calculate(list);
        }
    }
}