using System;
using System.Collections.Generic;

namespace GradeSystem
{
    public struct Command
    {
        public Command(string[] args)
        {
            
        }


        private static T GetEnum<T>(string str) where T : struct, Enum
        {
            Enum.TryParse<T>(str, out var r);
            return r;
        }
        
        
        private enum Option  { Student, Grade, Help, Exit  }
        private enum ParamStudent { List, Edit, Add, Delete}
        private enum ParamGrade { Find, Edit, Average, Freeze}
    }
}