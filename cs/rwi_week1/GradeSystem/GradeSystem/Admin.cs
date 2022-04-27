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
            _students.Add(s);
        }

        public void RemoveStudent(Student s)
        {
            _students.Remove(s);
        }

        // ReSharper disable MemberCanBePrivate.Global
        public List<Student> FindStudent(string name)
        {
            return _students.FindAll(student => student.FullName == name);
        }

        public List<Student> FindStudent(int studentNumber)
        {
            return _students.FindAll(student => student.StudentNumber == studentNumber);
        }

        public List<Student> FindStudent(DateTime birthday)
        {
            return _students.FindAll(student => student.BirthDay == birthday);
        }
        // ReSharper restore MemberCanBePrivate.Global
        
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
            var number = 0;
            try
            {
                number = int.Parse(args[2]);
            } catch (Exception e) {
                Console.WriteLine(args[2] + " is not a valid student number.");
                return;
            }
            
            var s = FindStudent(number);
        }
    }
}

/*
    Example: -grade -student 477437
    
    Entry options: grade, student, global-stats
        Grade options: find, edit
            Params (find): -full-name, -std-nr, -code, -date, 
        
        Student options: find, edit
            Params (find): -name, -std-nr, -birthday
            Params (edit): -std-nr   => Because the student number is the only unique identifier
                            ^  This doesn't have to be specified
            
*/