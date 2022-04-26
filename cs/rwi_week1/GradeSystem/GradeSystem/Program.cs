using System;

namespace GradeSystem
{
	internal static class Program
	{
		private static void Main(string[] args)
		{
			var student = new Student("Jesse", "Visscher", new DateTime(2001, 10, 8),477437);

			student.SetGrade(1, 12.33);	// Add a grade
			student.SetGrade(2, 9);		// Add a grade
			student.SetGrade(1, 8);		// Attempt overwrite first grade
			foreach (var grade in student.GradesFor(2))
				grade.Freeze();							// Freeze all grades with code 2
			student.SetGrade(2, 7);		// Attempt overwrite frozen code
			student.AddGrade(new Grade(7.8, new DateTime(2020, 1, 18), 3, "I have a custom date"));
			
			Console.WriteLine("\n## All Grades ##");
			student.PrintGrades();
			
			Console.WriteLine("\n## Grades from 2020 ##");
			student.PrintGrades(new DateTime(2019, 10, 10), new DateTime(2021, 10, 10));
			
			Console.WriteLine("\n## Grades with code 2 ##");
			foreach (var grade in student.GradesFor(2))
				Console.WriteLine(grade);
			
			Console.WriteLine($"\nAverage: {student.GradePointAverage()}");
			
			Console.WriteLine(args[0]);
		}
	}
}
