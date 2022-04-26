using System;
using System.Collections.Generic;
using System.Text;

namespace GradeSystem
{
	class Grade
	{
		private readonly DateTime _date;
		private readonly int _examCode;
		private readonly string _note;

		private double _grade;

		private bool _frozen = false;

		public Grade(double grade, DateTime date, int examCode, string note)
		{
			this.grade = grade;
			_date = date;
			_examCode = examCode;
			_note = note;
		}

		public Grade(double grade, int examCode, string note) : this(grade, DateTime.Now, examCode, note) { }

		public void Freeze()
		{
			_frozen = true;
		}

		public override string ToString()
		{
			return new string($"GradeObj: (Grade: ({_grade}), Date: {_date}, ExamCode: {_examCode}, Note: '{_note}')");
		}
		public double grade
		{
			get { return _grade; }
			set { if (_frozen == false) _grade = RoundToFive(Clamp(value, 1, 10)); }
		}

		private static double Clamp(double value, double min, double max)
		{
			return (value < min) ? min : (value > max) ? max : value;
		}

		private static double RoundToFive(double n)
		{
			return (Math.Round((n * 10) / 5.0) * 5) / 10;
		}
	}
}
