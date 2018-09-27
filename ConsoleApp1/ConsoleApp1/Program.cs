using System;
using System.Collections.Generic;

namespace ConsoleApp1
{
    public interface ISomeInterface
    {
        int FunctionOne(int a, int b);

        int FunctionTwo(int a, int b);

        string ClassName { get; set; }
    }

    public class SomeClass : ISomeInterface
    {
        public string ClassName { get; set; }

        public int FunctionOne(int aa, int ba)
        {
            return aa + ba;
        }

        public int FunctionTwo(int aa, int ba)
        {
            return aa - ba;
        }
    }

    public class SomeOtherClass : ISomeInterface
    {
        public string ClassName{ get; set; }

        public int FunctionOne(int ab, int bb)
        {
            return ab * bb;
        }

        public int FunctionTwo (int ab, int bb)
        {
            return ab / bb;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            SomeClass someClass = new SomeClass();
            someClass.ClassName = "Class A";
            SomeOtherClass someOtherClass = new SomeOtherClass();
            someOtherClass.ClassName = "Class B";

            List<ISomeInterface> someInterfaces = new List<ISomeInterface>();
            someInterfaces.Add(someClass);
            someInterfaces.Add(someOtherClass);

            int a = 10;
            int b = 7;

            Console.WriteLine("Number 1: " + a);
            Console.WriteLine("Number 2: " + b);

            foreach( ISomeInterface interfaceClass in someInterfaces)
            {
                Console.WriteLine(interfaceClass.ClassName + " function A: " + interfaceClass.FunctionOne(a, b));
                Console.WriteLine(interfaceClass.ClassName + " function B: " + interfaceClass.FunctionTwo(a, b));
            }

            a = Console.Read();
        }
    }
}
