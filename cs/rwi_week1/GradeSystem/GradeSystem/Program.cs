using System;

namespace GradeSystem
{
	class Program
	{
		static void Main(string[] args)
		{
			Grade grade = new Grade(7.36, 477437, "D4534231");
			grade.grade = 2.33;

			Console.WriteLine(grade);
		}
	}
}
