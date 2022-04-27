using System;

namespace GradeSystem
{
	public class Grade
	{
		private readonly DateTime _date;
		private readonly int _examCode;
		private readonly string _note;
		private double _grade;
		private bool _frozen;

		public Grade(double grade, DateTime date, int examCode, string note)
		{
			GradeNum = grade;
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
			return new string($"(Grade: ({_grade}), Date: {_date}, ExamCode: {_examCode}, Note: '{_note}', {(IsFrozen ? "Is" : "Not")} frozen)");
		}
		public double GradeNum
		{
			get => _grade;
			set { if (_frozen == false) _grade = RoundToFive(Math.Clamp(value, 1, 10)); }
		}
		public DateTime Date => _date;
		public int ExamCode => _examCode;
		public bool IsFrozen => _frozen;

		private static double RoundToFive(double n)
		{
			return Math.Round(n * 2.0) / 2;
		}
	}
}
