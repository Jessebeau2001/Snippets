using System;
using System.Collections.Generic;

namespace GradeSystem
{
	class Program
	{
		static void Main(string[] args)
		{
			var student = new Student("Jesse", "Visscher", new DateTime(2001, 10, 8),477437);

			student.SetGrade(1234, 12);
			student.SetGrade(4321, 2);
			student.SetGrade(1234, 2.33);
			
			student.PrintGrades();
		}
	}
}
