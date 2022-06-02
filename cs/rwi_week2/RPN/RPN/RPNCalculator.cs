using RPN.Interfaces;

namespace RPN;

public class RpnCalculator : ICalculator
{
    private readonly Stack<IToken> _stack = new();
    private readonly Stack<Token<string>> _backlog = new();

    public IList<string> SupportedOperators { get; }
    public IList<string> OperatorHelpText { get; }

    public RpnCalculator()
    {
        SupportedOperators = new List<string>();
        OperatorHelpText = new List<string>();
    }

    public void Calculate(IEnumerable<IToken> list)
    {
        PopulateStack(list);

        while (_stack.Count > 1)
        {
            if (_stack.First().Sign == Signature.Operator)
                _backlog.Push((Token<string>) _stack.Pop());
            else
                ApplyOperator(_backlog.Pop());
        }

        foreach (var item in _stack)
        {
            Console.WriteLine(item);
        }
    }

    private void PopulateStack(IEnumerable<IToken> list)
    {
        foreach (var item in list)
            _stack.Push(item);
        // Can also use constructor but prefer stack to be readonly
        //      var stack = new Stack<IToken>(list);
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
        var result = PopType<int>().Value + PopType<int>().Value;
        _stack.Push(new Token<int>(result));
    }

    private void Subtract()
    {
        var result = PopType<int>().Value - PopType<int>().Value;
        _stack.Push(new Token<int>(result));
    }

    private Token<T> PopType<T>()
    {
        return (Token<T>) _stack.Pop();
    }
}