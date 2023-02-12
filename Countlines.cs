
class Countlines
{
    static void Main()
    {
        
        int code_lines = 0;
        int not_code_lines = 0;
        int only_comments = 0;
        int blank_lines = 0;
        bool doc_switch = false;

        string filePath = "C:\\Users\\murph\\Desktop\\cvtools.py";

        string comm_symbol = "#";
        
        string[] lines = File.ReadAllLines(@filePath);       // is equiv to System.IO.File.ReadAllLines..

        foreach (string i in lines)                                   // can use "var" var in c# is auto in c++
        {
            string k = i.Trim();

            if (k.Contains("'''") && doc_switch == true || k.Contains("\"\"\"") && doc_switch == true)
            {
                // Console.WriteLine(k);
                doc_switch = false;
                not_code_lines += 1;
                only_comments += 1;
                continue;
            }
            
            // Turn on
            if (k.Length >= 3)
            {
                if (k.Substring(0, 3) == "'''" && doc_switch == false || k.Substring(0, 3) ==
                    "\"\"\"" && doc_switch == false)
                {
                    if (k.Substring(3).Contains("'''") || k.Substring(3).Contains("\"\"\""))
                    {
                        not_code_lines += 1;
                        only_comments += 1;
                        continue;
                    }
                    else
                    {
                        doc_switch = true;
                    }
                }
            }

            if (doc_switch == true)
            {
                    not_code_lines += 1;
                    
                    if (k != "")
                    {
                        only_comments += 1;
                    }
                    else
                    {
                        blank_lines += 1;
                    }
            }

            else
            {
                if (k != "")
                {
                        
                    if (k.Substring(0, 1) != comm_symbol)
                    { 
                        code_lines += 1;
                    }
                    else
                    { 
                        not_code_lines += 1;
                        only_comments += 1;
                    }
                        
                }
                else
                {
                    not_code_lines += 1;
                    blank_lines += 1;
                }
            }
            
        }
        
        Console.WriteLine("Lines of Code: " + code_lines);
        Console.WriteLine("Lines that are not code: " + not_code_lines);
        Console.WriteLine("Total Lines: " + lines.Length);
        Console.WriteLine("\nBlank Lines: " + blank_lines);
        Console.WriteLine("Lines that are just comments: " + only_comments);

        Console.WriteLine("------------------------------------------");
        
    }
}
