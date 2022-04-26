using System;
using System.Collections.Generic;

namespace GradeSystem
{
	internal static class Program
	{
		private static void Main(string[] args)
		{
			var student = new Student("Jesse", "Visscher", new DateTime(2001, 10, 8),477437);

			student.SetGrade(1234, 12);	// Add a date
			student.SetGrade(4321, 2);		// Add a date
			student.SetGrade(1234, 2.33);	// Overwrite first date
			student.SetGrade(2346, 6.48);  // Add 2 dates with the same code
			student.AddGrade(new Grade(7.8, new DateTime(2020, 10, 18), 2346, "I am a clone with an custom date"));
			Console.WriteLine("## All Grades ##");
			student.PrintGrades();
			Console.WriteLine("## Grades from 2020 ##");
			student.PrintGrades(new DateTime(2019, 10, 10), new DateTime(2021, 10, 10));
			Console.WriteLine("## Grades with code 2346 ##");
			foreach (var grade in student.GradesFor(2346))
				Console.WriteLine(grade);
		}
	}
}
