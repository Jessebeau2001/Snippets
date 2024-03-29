﻿using System;
using System.Collections.Generic;

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
			_group.AddStudent(new Student("Emir", "Bachivan", "10/10/2002", "584932"));
			
			/*while (true)
			{
				if (_group.ParseCommand(Admin.ParseLine())) break;
			}*/
			
			//CommandTest();
		}

		private static void CommandTest()
		{
			
			var commands = new List<string>
			{
				"-student -list -name Jesse Visscher",		// Finds 1 student named Jesse Visscher
				"-student -list -birthday 08-10-2001",		// Finds 2 students with the same birthday
				"-student -list -number 477437",			// Finds 1 student with student number 477437
				"-student -list -name Doesn't Exist",		// Finds no student and notifies user
				
				"-student -list -all",						// Prints unsorted list
				"-student -list -all number",				// Prints list sorted based on student number
				"-student -list -all typo",					// Doesn't print list and notifies user of unknown type
				
				"-student -edit -firstname 477437 Jesse2",	// Edits firstname of 477437
				"-student -edit -lastname 477437 Visscher2",// Edits lastname of 477437
				"-student -edit -birthday 477437 8/10/2002",// Edits birthday of 477437
				"-student -edit -firstname 123456 none",	// Doesnt find student 123456 and notifies user
				"-student -edit -firstname invalid none",	// Fails to convert student number
				"-student -edit -birthday 477437 invalid",	// Fails to convert date
				
				"-student -add Mikal Bossink 6/05/2002, 218967",	// Adds new student to system
				"-student -add Mikal Bossink 6/05/2002, 218967",	// Adds existing user to system but fails
				"-student -add Mikal Bossink 6/05/2002, NoNumber",	// Fails to add new student
				"-student -add Mikal Bossink NoDate, 218967",		// Fails to add new student
				
				"-student -delete 1",						// Fails and prints failed student number
				"-student -delete 218967",					// Deletes student Mikal Bossink (218967)
			};
			
			_group.NeedConfirmation = false;
			foreach (var c in commands)
				RunCommand(c);
			
			_group.NeedConfirmation = true;
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
