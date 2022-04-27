using System;

namespace GradeSystem
{
	internal static class Program
	{
		private static Admin _group;
		private static void Main(string[] args)
		{
			_group = new Admin();
			_group.AddStudent(new Student("Jesse", "Visscher", new DateTime(2001, 10, 8),477437));
			_group.AddStudent(new Student("AnotherGuy", "SameBDay", new DateTime(2001, 10, 8),738952));
			_group.AddStudent(new Student("Rick", "Vlake", new DateTime(2002, 5, 24), 355234));
			_group.AddStudent(new Student("Noah", "Visscher", new DateTime(2002, 3, 20), 455736));

			while (true)
			{
				if (_group.ParseCommand(Admin.ParseLine())) break;
			}
			
			//CommandTest();
		}

		private static void CommandTest()
		{
			const string fsA = "-student -find -name Jesse Visscher";	// Finds 1 student named Jesse Visscher
			const string fsB = "-student -find -birthday 08-10-2001";	// Finds 2 students with the same birthday
			const string fsC = "-student -find -number 477437";			// Finds 1 student with student number 477437
			const string fsD = "-student -find -name Doesn't Exist";		// Finds no student and notifies user
			
			RunCommand(fsA);
			RunCommand(fsB);
			RunCommand(fsC);
			RunCommand(fsD);
		}
		private static void RunCommand(string command)
		{
			Console.WriteLine("\n" + command);
			_group.ParseCommand(command.Split(" "));
		}
		private static void UnitTest()
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
		}
	}
}
