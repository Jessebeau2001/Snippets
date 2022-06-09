namespace RPN
{
    // public class Token<T> where T : Enum
    public enum Signature { Number, Operator }
    public interface IToken
    {
        Signature Sign { get; init; }
    }
    
    public readonly struct Token<T>: IToken
    { 
        public Signature Sign { get; init; }
        public T Value { get; }
        
        public Token(T value)
        {
            Value = value;
            Sign = Value is int ? Signature.Number : Signature.Operator;
        }

        public override string ToString()
        {
            return new string($"Token: '{Value}', Signature: '{Sign}'");
        }
    }
}

