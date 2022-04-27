using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Runtime.Serialization;

namespace GradeSystem
{
    public class Admin
    {
        private const string ConfirmKey = "Y";
        public bool NeedConfirmation { get; set; } = true;
        private readonly List<Student> _students = new List<Student>(); // The list itself should not be assignable
        
        public enum SortType { Firstname, Lastname, Birthday, StudentNumber }
        
        public void PrintStudents(SortType type = SortType.StudentNumber)
        {
            var sorted = type switch
            {
                SortType.Firstname => _students.OrderBy(x => x.FirstName).ToList(),
                SortType.Lastname => _students.OrderBy(x => x.LastName).ToList(),
                SortType.Birthday => _students.OrderBy(x => x.BirthDay).ToList(),
                SortType.StudentNumber => _students.OrderBy(x => x.StudentNumber).ToList(),
                _ => _students
            };

            for (var i = 0; i < sorted.Count; i++)
                Console.WriteLine($"[{i}]: {sorted[i]}");
        }

        public void SortList(SortType type)
        {
            _students.Sort();
        }


        public bool AddStudent(Student s)
        {
            if (_students.Any(student => student.StudentNumber == s.StudentNumber))
                return false;     // Can never have to students with the same number
            
            _students.Add(s);
            return true;
        }

        public bool DeleteStudent(Student s)
        {
            return _students.Remove(s);
        }
        
        private List<Student> FindStudent(string name)
        {
            return _students.FindAll(student => student.FullName == name);
        }

        private List<Student> FindStudent(int studentNumber)
        {
            return _students.FindAll(student => student.StudentNumber == studentNumber);
        }

        private List<Student> FindStudent(DateTime birthday)
        {
            return _students.FindAll(student => student.BirthDay == birthday);
        }

        public static string[] ParseLine()
        {
            var line = Console.ReadLine();
            string[] split = { "" };
            
            if (line != null)
                split = line.Split(" ");

            return split;
        }
        
        public bool ParseCommand(IReadOnlyList<string> args)
        {
            switch (args[0])
            {
                case "-grade":
                    Console.WriteLine("Grade option has been chosen");
                    return false;
                case "-student":
                    HandleCommandStudent(args);
                    return false;
                case "-exit":
                    Console.WriteLine("Goodbye!");
                    return true;
                default:
                    Console.WriteLine($"Argument {args[0]} is invalid.");
                    return false;
            }
        }
        
        private void HandleCommandStudent(IReadOnlyList<string> args)
        {
            switch (args[1])
            {
                case "-list":
                    HandleArgumentListStudent(args);
                    break;
                case "-edit":
                    HandleArgumentEditStudent(args);
                    break;
                case "-add":
                    HandleArgumentAddUser(args);
                    break;
                case "-delete":
                    HandleArgumentDeleteStudent(args);
                    break;
                default:
                    Console.WriteLine($"Argument {args[1]} is invalid.");
                    break;
            }
        }
        
        private void HandleArgumentListStudent(IReadOnlyList<string> args)
        {
            List<Student> s = null;
            var term = "";
            
            switch (args[2])
            {
                case "-all":
                    PrintStudents();
                    return;
                case "-name":
                    s = FindStudent(term = args[3] + " " + args[4]);
                    break;
                case "-number":
                    try { s = FindStudent(int.Parse(term = args[3])); }
                    catch (Exception e) { Console.WriteLine($"Could not figure out what student number '{args[3]}' means."); }
                    break;
                case "-birthday":
                    try { s = FindStudent(DateTime.Parse(term = args[3])); }
                    catch (Exception e) { Console.WriteLine($"Could not figure out the date '{args[3]}'."); }
                    break;
                default:
                    Console.WriteLine($"Argument {args[2]} is invalid.");
                    return;
            }

            if (s == null || !s.Any())
            {
                Console.WriteLine($"No students matching criteria {args[2]} '{term}' could be found.");
                return;
            }
            
            foreach (var student in s)
                Console.WriteLine("Found " + student);
        }
        
        private void HandleArgumentEditStudent(IReadOnlyList<string> args)
        {
            int studentNr;
            Student student;
            var changeWhat = args[2];
            var newValue = args[4];
            
            try { studentNr = int.Parse(args[3]);
            } catch (Exception e) { Console.WriteLine(args[3] + " is not a valid student number."); return; }
            
            var list = FindStudent(studentNr);

            if (list.Any())
            {
                student = list.First(); // Multiple student with the same number should be an impossible scenario, hence selects first
            } else {
                Console.WriteLine($"No student(s) with number {studentNr} found");
                return;
            }

            switch (changeWhat)
            {
                case "-firstname":
                    Console.WriteLine($"Changed firstname from '{student.FirstName}' to '{newValue}'.");
                    student.FirstName = newValue;
                    return;
                case "-lastname":
                    Console.WriteLine($"Changed firstname from '{student.LastName}' to '{newValue}'.");
                    student.LastName = newValue;
                    return;
                case "-birthday":
                    try
                    {
                        var newDate = DateTime.Parse(newValue);
                        Console.WriteLine($"Changed birthday from '{student.BirthDay}' to '{newDate}'.");
                        student.BirthDay = newDate;
                    } catch (Exception e) {
                        Console.WriteLine($"Could not figure out the date '{newValue}'.");
                    }
                    return;
                default:
                    Console.WriteLine($"Argument {args[2]} is invalid.");
                    return;
            }
        }
        
        private void HandleArgumentAddUser(IReadOnlyList<string> args)
        {
            var s = new Student(args[2], args[3], args[4], args[5]);
            if (s.IsDefault)
            {
                Console.WriteLine($"Invalid data format for new student: {args[2]} {args[3]} {args[4]} {args[5]}");
                return;
            }

            Console.WriteLine($"Adding {s} to database, type '{ConfirmKey}' to confirm... ");
            if (UserConfirm())
            {
                Console.WriteLine(AddStudent(s)
                    ? "Successfully added student to database!"
                    : $"Failed to add student, student-number '{s.StudentNumber}' already exists!");
                return;
            }

            Console.WriteLine("Action cancelled!");
        }

        private void HandleArgumentDeleteStudent(IReadOnlyList<string> args)
        {
            int.TryParse(args[2], out var number);
            var match = FindStudent(number);
            if (!match.Any())
            {
                Console.WriteLine($"Could not find student with number {args[2]}");
                return;
            }
            var s = match.First();
            Console.WriteLine($"Attempt to delete {s}, type '{ConfirmKey}' to confirm...");
            if (UserConfirm())
            {
                DeleteStudent(s);
                Console.WriteLine($"Student successfully deleted!");
                return;
            }
            Console.WriteLine("Action cancelled!");
        }

        private bool UserConfirm()
        {
            if (NeedConfirmation == false) return true;
            var line = Console.ReadLine();
            return line != null && line.ToUpper() == ConfirmKey;
        }
    }
}

/*
    TODO: -help should print this
    
    Example: -grade -student 477437
        Lists all grades belonging to student 477437
        
    Example: -student -edit -firstname 477437 Jesse
        Changes the firstname of student 477437 to Jesse
        
    Example: -student -find -birthday 08/10/2001
        Lists all student who's birthday is on the 8th of october 2001
        
    
    Entry options: -student, -exit, TODO: -grade, -help
        
    Student options: -list, -edit, -add, -delete
        Options (-list): -all -name, -number, -birthday
            Params (-all): sort-by
            Params (-name):  full name
            Params (-number): student number
            Params (-birthday): birthday (eg: 08/10/2001)
        Options (edit): -firstname, -lastname, -birthday => Search term is always student number because it is the only unique identifier
            Params (-firstname): student-number, new first name
            Params (-lastname): student-number, new last name
            Params (-birthday): student-number, new birthday
        Options (-add): NONE
            Params: first-name, last-name, birthday, student-number
        Options (-delete): NONE
            Params: student-number
        NOTE: Both -add & -delete ask for extra confirmation
            
    Grade options: TODO: -find, -edit, -average, -freeze
        Options (-find): TODO: -fullname, -number, -code, -date, 
            Params (-fullname): student name
            Params (-number): student number
            Params (-code): exam code
            Params (-date): exam date
        Options (-edit): TODO: -score, -note
            Params (-score): student number, exam code, new grade
            Params (-note): student number, exam code, new note
        Options (-Average): TODO: -number, -code
            Params (-number): student number
            Params (-code): exam code
        Options (-freeze): TODO: NONE
            Params: student number, exam code
            
*/