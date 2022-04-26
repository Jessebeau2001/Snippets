using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualBasic;

namespace GradeSystem
{
	class Student
	{
		private readonly DateTime _birthDate;
		private readonly int _studentNumber;
		private List<Grade> _grades = new List<Grade>();
		public string FirstName { get; set; }
		public string LastName { get; set; }
		public string FullName => FirstName + " " + LastName; // They asked for a readonly, but then first & lastname should also be readonly
	
		public Student(string fName, string lName, DateTime bDay, int sNumber)
		{
			FirstName = fName;
			LastName = lName;
			_birthDate = bDay;
			_studentNumber = sNumber;
		}

		public override string ToString()
		{
			return new string($"Student: (Name: '{FullName}', Birthday: {_birthDate}, Student Number: {_studentNumber})");
		}

		public void PrintGrades()
		{
			foreach (var grade in _grades)
			{
				Console.WriteLine(grade);
			}
		}

		public void SetGrade(int examCode, double value)
		{
			var grades = _grades.FindAll(x => x.ExamCode == examCode);
			if (!grades.Any()) _grades.Add(new Grade(value, examCode, ""));
		}

		public DateTime BirthDay => _birthDate;
		public int StudentNumber => _studentNumber;
	}
}
