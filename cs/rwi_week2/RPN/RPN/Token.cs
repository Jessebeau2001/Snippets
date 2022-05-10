namespace RPN
{
    // public class Token<T> where T : Enum
    
    public interface IToken {}
    public readonly struct Token<T> : IToken
    {
        private enum Signature { Number, Operator }
        private T Value { get; }
        private Signature Sig { get; }
        
        public Token(T value)
        {
            Value = value;
            Sig = Value is int ? Signature.Number : Signature.Operator;
        }

        public override string ToString()
        {
            return new string($"(Token: '{Value}', Signature: '{Sig}')");
        }
    }
}

