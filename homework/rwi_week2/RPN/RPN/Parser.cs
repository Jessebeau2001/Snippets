namespace RPN;

public static class Parser
{
    public static List<IToken> Parse(string input)
    {
        var array = input.Split(" ");
        return array.Select(str => (IToken) (int.TryParse(str, out var value) ? new Token<int>(value) : new Token<string>(str))).ToList();
    }
    
    public static bool Validate()
    {
        // TODO: How to validate???
        return true;
    }
}