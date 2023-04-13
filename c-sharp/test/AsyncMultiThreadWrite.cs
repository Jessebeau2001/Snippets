namespace Program
{
    public static class FileWriterTest
    {
       public static void AsynMultiFileWrite()
        {
            using var stream = File.OpenWrite($".\\{DateTime.Now:mm-ff}.txt");
            using var writer = new StreamWriter(stream);

            var watch = new System.Diagnostics.Stopwatch();
            watch.Start();

            Task.Run(async () =>
            {
                await Task.Delay(1000);
                writer.WriteLine($"1. Thead {Environment.CurrentManagedThreadId} after {watch.ElapsedMilliseconds}ms");
            });

            Task.Run(async () =>
            {
                await Task.Delay(1000);
                writer.WriteLine($"2. Thead {Environment.CurrentManagedThreadId} after {watch.ElapsedMilliseconds}ms");
            });

            Task.Run(async () =>
            {
                await Task.Delay(1500);
                writer.WriteLine($"3. Thead {Environment.CurrentManagedThreadId} after {watch.ElapsedMilliseconds}ms");
            });

            Task.Run(async () =>
            {
                await Task.Delay(3000);
                writer.WriteLine($"4. Thead {Environment.CurrentManagedThreadId} after {watch.ElapsedMilliseconds}ms");
            });

            Task.Run(async () =>
            {
                await Task.Delay(3000);
                writer.WriteLine($"5. Thead {Environment.CurrentManagedThreadId} after {watch.ElapsedMilliseconds}ms");
            });

            Task.Delay(4000).Wait();
            watch.Stop();
            writer.WriteLine($"End: {watch.ElapsedMilliseconds}ms");

            writer.Close();
            stream.Close();
        }
    }
}
