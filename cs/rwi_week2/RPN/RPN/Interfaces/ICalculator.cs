namespace RPN.Interfaces;

public interface ICalculator
{
    public void Calculate(IEnumerable<IToken> list);
    public IList<string> SupportedOperators { get; }
    public IList<string> OperatorHelpText { get; }
}