using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;

namespace GradeSystem
{
    public class Admin
    {
        private readonly List<Student> _students = new List<Student>(); // The list itself should not be assignable
        
        public void PrintStudents()
        {
            foreach (var s in _students)
                Console.WriteLine(s);
        }

        public void AddStudent(Student s)
        {
            if (_students.Any(student => student.StudentNumber == s.StudentNumber))
                return;     // Can never have to students with the same number
            
            _students.Add(s);
        }

        public void RemoveStudent(Student s)
        {
            _students.Remove(s);
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
        // TODO: Implement -grade param
        public bool ParseCommand(string[] args)
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
                case "-find":
                    HandleArgumentFindStudent(args);
                    break;
                case "-edit":
                    HandleArgumentEditStudent(args);
                    break;
                default:
                    Console.WriteLine($"Argument {args[1]} is invalid.");
                    break;
            }
        }
        private void HandleArgumentFindStudent(IReadOnlyList<string> args)
        {
            List<Student> s = null;
            var term = "";
            
            switch (args[2])
            {
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
        
    Student options: -find, -edit, TODO: -add, -delete
        Options (-find): -name, -number, -birthday
            Params (-name):  full name
            Params (-number): student number
            Params (-birthday): birthday (eg: 08/10/2001)
        Options (edit): -firstname, -lastname, -birthday => Search term is always student number because it is the only unique identifier
            Params (-firstname): student-number, new first name
            Params (-lastname): student-number, new last name
            Params (-birthday): student-number, new birthday
        Options (-add): TODO: NONE
            Params: first-name, last-name, birthday, student-number
        Options (-remove): TODO: NONE
            Params: student-number, full-name => Type full name as well to make sure that deletion was no mistake
            
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