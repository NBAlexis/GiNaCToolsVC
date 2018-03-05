using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using System.IO;

namespace CodeHelper
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("start work");

            //AddPrivateHeaderForGINAC();
            //ChangeAllConstDefine();
            //ChangeAllNum();
            //ChangeAllNum2();
            //ChangeAllNum3();
            //ChangeMainFunction();

            //pasue
            Console.WriteLine("work done, press enter to exit...");
            string byebye = Console.ReadLine();
        }

        static void ChangeMainFunction()
        {
            Console.Write(System.AppDomain.CurrentDomain.BaseDirectory);
            DirectoryInfo dirinfo = new DirectoryInfo("..\\..\\..\\Code\\GINAC_Test\\check");
            FileInfo[] files = dirinfo.GetFiles("*.cpp", SearchOption.AllDirectories);
            string sAddFunctions = "";
            foreach (FileInfo f in files)
            {
                string fileContent = File.ReadAllText(f.FullName);
                if (Regex.Match(fileContent, "int\\s+main").Length > 0)
                {
                    string sReplaceMainName = "main_" + f.Name.Replace(".cpp", "");
                    Console.WriteLine("file " + f.FullName + "has main, to be replaced with " + sReplaceMainName);
                    sReplaceMainName = "int " + sReplaceMainName + "()";
                    sAddFunctions = sAddFunctions + "\nextern " + sReplaceMainName + ";";

                    fileContent = Regex.Replace(fileContent, 
                        @"int\s+main\(\s*int\s+argc\s*,\s*char\s*\*\s*\*\s+argv\s*\)", 
                        sReplaceMainName);

                    //Console.Write(fileContent);
                    File.WriteAllText(f.FullName, fileContent);
                }
            }

            FileInfo headerfile = new FileInfo("..\\..\\..\\Code\\GINAC_Test\\check\\ginac_test.h");
            string headContent = File.ReadAllText(headerfile.FullName);
            headContent = headContent.Replace("#endif", sAddFunctions + "\n#endif");

            //Console.Write(headContent);
            File.WriteAllText(headerfile.FullName, headContent);
        }

        #region Old

        static void AddPrivateHeaderForGINAC()
        {
            Console.Write(System.AppDomain.CurrentDomain.BaseDirectory);
            DirectoryInfo dirinfo = new DirectoryInfo("..\\..\\..\\Code\\GINAC\\ginac");
            FileInfo[] files = dirinfo.GetFiles("*.cpp", SearchOption.AllDirectories);
            foreach (FileInfo f in files)
            {
                Console.WriteLine(f.FullName);

                string textf = File.ReadAllText(f.FullName);
                textf = "#include \"..\\ginac_private.h\"\n" + textf;
                File.WriteAllText(f.FullName, textf);
            }
        }

        static void ChangeAllConstDefine()
        {
            FileInfo fileinfo = new FileInfo("..\\..\\..\\Code\\GINAC\\ginac\\utils.cpp");
            string fileContent = File.ReadAllText(fileinfo.FullName);
            fileContent = Regex.Replace(fileContent, @"const ex _ex([_\d+]+)\s*= _ex([_\d+]+);", @"const ex _ex$1(*_num$1_p);");
            //Console.Write(fileContent);
            File.WriteAllText(fileinfo.FullName, fileContent);
        }

        static void ChangeAllNum()
        {
            FileInfo fileinfo = new FileInfo("..\\..\\..\\Code\\GINAC\\ginac\\utils.cpp");
            string fileContent = File.ReadAllText(fileinfo.FullName);
            fileContent = Regex.Replace(fileContent, @"const numeric \*\s*_num_([\d]+)_p;", @"const numeric *_num_$1_p = (const numeric *)&dynallocate<numeric>(-$1);");
            fileContent = Regex.Replace(fileContent, @"const numeric \*\s*_num_([\d]+)_([\d]+)_p;", @"const numeric *_num_$1_$2_p = (const numeric *)&dynallocate<numeric>(-$1, $2);");
            fileContent = Regex.Replace(fileContent, @"const numeric \*\s*_num([\d]+)_p;", @"const numeric *_num$1_p = (const numeric *)&dynallocate<numeric>($1);");
            fileContent = Regex.Replace(fileContent, @"const numeric \*\s*_num([\d]+)_([\d]+)_p;", @"const numeric *_num$1_$2_p = (const numeric *)&dynallocate<numeric>($1, $2);");
            fileContent = fileContent.Replace(@"const basic *_num0_bp;", @"const basic *_num0_bp = _num0_p;");
            //Console.Write(fileContent);
            File.WriteAllText(fileinfo.FullName, fileContent);
        }

        static void ChangeAllNum2()
        {
            FileInfo fileinfo = new FileInfo("..\\..\\..\\Code\\GINAC\\ginac\\utils.cpp");
            string fileContent = File.ReadAllText(fileinfo.FullName);
            fileContent = Regex.Replace(fileContent, @"const ex _ex([_\d+]+)\(\*_num([_\d+]+_p)\);", @"numeric _tmp$1 = *_num$1_p;
const ex _ex$1 = ex(_tmp$1);");
            //Console.Write(fileContent);
            File.WriteAllText(fileinfo.FullName, fileContent);
        }

        static void ChangeAllNum3()
        {
            FileInfo fileinfo = new FileInfo("..\\..\\..\\Code\\GINAC\\ginac\\utils.cpp");
            string fileContent = File.ReadAllText(fileinfo.FullName);
            fileContent = Regex.Replace(fileContent, @"const numeric \*_num([_\d+]+)_p = \(const numeric \*\)&dynallocate<numeric>\(([\d\s-]+)\);\s*numeric _tmp([_\d+]+) = \*_num([_\d+]+)_p;",
                @"static numeric _tmp$1 = numeric($2);
const numeric *_num$1_p = &_tmp$1;");
            //Console.Write(fileContent);
            File.WriteAllText(fileinfo.FullName, fileContent);
        }

        #endregion
    }
}
