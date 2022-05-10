namespace RPN
{
    /*public class Token<T> where T : Enum
    {
        public Token(T input)
        {
            
        }
    }*/

    public struct Token<T>
    {
        public T Value { get; set; }
    }
}

