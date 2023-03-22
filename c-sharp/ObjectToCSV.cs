class Parser
{
  public static string PropertiesToCSV<T>(IEnumerable<T> collection)
  {
      if (collection == null || !collection.Any())
      {
          return "";
      }

      var csv = new StringBuilder();
      var props = collection.First().GetType().GetProperties();
      if (props.Length > 0)
      {
          foreach (var item in collection)
          {
              var first = props[0].GetValue(item);
              csv.Append(first);
              for (int i = 1; i < props.Length; i++)
              {
                  var val = props[i].GetValue(item);
                  csv.Append(", ").Append(val);
              }
              csv.AppendLine();
          }
      }

      return csv.ToString();
  }
}
