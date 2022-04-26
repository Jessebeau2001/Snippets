using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using Microsoft.VisualBasic;

namespace GradeSystem
{
	class Student
	{
		private readonly DateTime _birthDate;
		private readonly int _studentNumber;
		private readonly List<Grade> _grades = new List<Grade>();
		// ReSharper disable MemberCanBePrivate.Global
		public string FirstName { get; set; }
		public string LastName { get; set; }
		public string FullName => FirstName + " " + LastName;
		// ReSharper restore MemberCanBePrivate.Global

		public Student(string fName, string lName, DateTime bDay, int sNumber)
		{
			FirstName = fName;
			LastName = lName;
			_birthDate = bDay;
			_studentNumber = sNumber;
		}

		public override string ToString()
		{	// String.Format() ??
			return new string($"Student: (Name: '{FullName}', Birthday: {_birthDate}, Student Number: {_studentNumber})");
		}

		public void PrintGrades()
		{
			foreach (var grade in _grades)
				Console.WriteLine(grade);
		}

		public void PrintGrades(DateTime start, DateTime end)
		{
			foreach (var grade in _grades.Where(grade => InRange(grade.Date, start, end)))
				Console.WriteLine(grade);
		}

		public void SetGrade(int examCode, double value)
		{
			var grades = GradesFor(examCode);
			if (grades.Any())
			{
				if (grades.Find(x => x.IsFrozen) == null)
					foreach (var grade in grades)
						grade.GradeNum = value;
			} else {
				_grades.Add(new Grade(value, examCode, ""));
			}
		}

		// For debugging only
		public void AddGrade(Grade grade)
		{
			_grades.Add(grade);
		}

		public List<Grade> GradesFor(int examCode)
		{
			return _grades.FindAll(x => x.ExamCode == examCode);
		}
		
		public DateTime BirthDay => _birthDate;
		public int StudentNumber => _studentNumber;

		private static bool InRange(DateTime date, DateTime start, DateTime end)
		{
			return date >= start && date< end;
		}
	}
}
