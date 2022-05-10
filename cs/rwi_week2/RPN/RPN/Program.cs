using System.Collections;

namespace RPN
{
    internal static class Program
    {
        private static void Main()
        {
            var aToken = new Token<char>('+');
            var bToken = new Token<int>(12);
            
            Console.WriteLine(aToken);
            Console.WriteLine(bToken);

            var list = new List<Token<IToken>>();
        }
    }
}