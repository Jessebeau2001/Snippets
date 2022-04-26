using System;
using System.Collections.Generic;
using System.Text;

namespace GradeSystem
{
	class Student
	{
		private readonly DateTime _birthDate;
		private readonly int _studentNumber;

		public string firstName { get; set; }
		public string lastName { get; set; }
		public string fullName { get { return firstName + " " + lastName; } } // They asked for a readonly, but then first & lastname should also be readonly
	
		public Student(string fName, string lName, DateTime bDay, int sNumber)
		{
			firstName = fName;
			lastName = lName;
			_birthDate = bDay;
			_studentNumber = sNumber;
		}

		public DateTime birthDay { get { return _birthDate; } }
		public int studentNumber { get { return _studentNumber; } }
	}
}
