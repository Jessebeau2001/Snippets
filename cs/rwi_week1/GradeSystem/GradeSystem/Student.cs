using System;
using System.Collections.Generic;
using System.Linq;

namespace GradeSystem
{
	public class Student
	{
		private readonly int _studentNumber;
		private readonly List<Grade> _grades = new List<Grade>();
		// ReSharper disable MemberCanBePrivate.Global
		public DateTime BirthDay { get; set; }
		public string FirstName { get; set; }
		public string LastName { get; set; }
		public string FullName => FirstName + " " + LastName;
		// ReSharper restore MemberCanBePrivate.Global

		public Student(string fName, string lName, DateTime bDay, int sNumber)
		{
			FirstName = fName;
			LastName = lName;
			BirthDay = bDay;
			_studentNumber = sNumber;
		}

		public override string ToString()
		{	// String.Format() ??
			return new string($"Student: (Name: '{FullName}', Birthday: {BirthDay}, Student Number: {_studentNumber})");
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
			var grades = GradesFor(examCode);											// Find all matching coded grades
			var meltedGrades = grades.FindAll(x => x.IsFrozen == false);			// Store unfrozen grades
			
			if (meltedGrades.Any())																// If any unfrozen exist
			{
				foreach (var grade in meltedGrades)												// Change all unfrozen grades
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
			return _grades.FindAll(grade => grade.ExamCode == examCode);
		}
		
		public double GradePointAverage()
		{
			var final = new List<Grade>();			// Final marks used for calculating average
			foreach (var grade in _grades)
			{
				var found = final.Find(x => x.ExamCode == grade.ExamCode);
				if (found == null)
				{
					final.Add(grade);
				} else {
					if (grade.GradeNum < found.GradeNum) continue;
					final.Remove(found);
					final.Add(grade);
				}
			}
			
			return final.Average(grade => grade.GradeNum);
			// return _grades.Where(grade => !grade.IsFrozen).Average(grade => grade.GradeNum);
		}

		public int StudentNumber => _studentNumber;

		private static bool InRange(DateTime date, DateTime start, DateTime end)
		{
			return date >= start && date< end;
		}
	}
}
