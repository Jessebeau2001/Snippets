namespace RPN;

public class RpnCalculator
{
    private readonly Stack<IToken> _stack = new Stack<IToken>();
    
    public void Calculate(List<IToken> list)
    {
        foreach (var token in list)
        {
            if (token.Sign == Signature.Number)
                _stack.Push(token);
            else
                ApplyOperator((Token<string>) token);
        }

        foreach (var item in _stack)
        {
            Console.WriteLine(item);
        }
    }

    private void ApplyOperator(Token<string> op)
    {
        switch (op.Value)
        {
            case "+":
                Sum();
                break;
            case "-":
                Subtract();
                break;
        }
    }
    
    private void Sum()
    {
        var result = 0;
        while (_stack.Any())
            result += ((Token<int>) _stack.Pop()).Value; // TODO: Look at aggregating a list cuz Stack is a list extension
        
        _stack.Push(new Token<int>(result));
    }

    private void Subtract()
    {
        var result = 0;
        while (_stack.Any())
            result -= ((Token<int>) _stack.Pop()).Value;
        
        _stack.Push(new Token<int>(result));
    }
}