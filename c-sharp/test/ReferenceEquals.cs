namespace Test
{
    public static class Watcher
    {
        public static void AdressWatch()
        {
            {
                var a = new MyClass(3);
                var b = a;
                var c = b;

                Console.WriteLine("Classes equals: " + ReferenceEquals(a, c));
            }

            {
                var a = new MyStruct(3);
                var b = a;
                var c = b;

                Console.WriteLine("Structs equals: " + ReferenceEquals(a, c));
            }

            {
                var a = new MyReadonlyStruct(3);
                var b = a;
                var c = b;

                Console.WriteLine("Readonly structs equals: " + ReferenceEquals(a, c));
            }

            {
                var a = new MyReadonlyRecordStruct(3);
                var b = a;
                var c = b;

                Console.WriteLine("Readonly record structs equals: " + ReferenceEquals(a, c));
            }

            {
                var a = new MyRecordClass(3);
                var b = a;
                var c = b;

                Console.WriteLine("Readonly record structs equals: " + ReferenceEquals(a, c));
            }
        }
    }

    internal class MyClass
    {
        readonly int a;
        public MyClass(int a) { this.a = a; }
    }

    internal struct MyStruct
    {
        readonly int a;
        public MyStruct(int a) { this.a = a; }
    }

    internal readonly struct MyReadonlyStruct
    {
        readonly int a;
        public MyReadonlyStruct(int a) { this.a = a; }
    }

    internal readonly record struct MyReadonlyRecordStruct(int a);

    internal record class MyRecordClass(int a);
}
