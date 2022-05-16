using System.Collections;

namespace RPN
{
    internal static class Program
    {
        private static void Main()
        {
            var list = new List<IToken>
            {
                new Token<char>('+'),
                new Token<int>(12)
            };
        }
    }
}