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
            //AddDllExportForNestedSums();
            //AddPrivateHeaderForGINACRA();
            //AddDllExportForGINACRA();
            //AddIncludeBackForGINACRA();
            //Fix1ForGINACRAtest();

            //pasue
            Console.WriteLine("work done, press enter to exit...");
            string byebye = Console.ReadLine();
        }

        #region GINACRATEST

        static void Fix1ForGINACRAtest()
        {
            Console.Write(System.AppDomain.CurrentDomain.BaseDirectory);

            DirectoryInfo dirinfo = new DirectoryInfo("..\\..\\..\\Code\\GINACRA_Test\\test");

            FileInfo[] files = dirinfo.GetFiles("*.*", SearchOption.AllDirectories).Where(s => s.FullName.EndsWith(".cpp") || s.FullName.EndsWith(".h")).ToArray();
            string sNewHeadFiles = "";
            string sMainFunctions = "";
            foreach (FileInfo f in files)
            {
                //Console.WriteLine(f.Name);
                string textf = File.ReadAllText(f.FullName);

                textf = removeAllinc(textf);
                textf = "#include \"ginacra_test.h\"\n";

                if (f.FullName.EndsWith(".h"))
                {
                    sNewHeadFiles = sNewHeadFiles + "#include \"test/" + f.Name + "\"\n";
                }
                
                 //Console.Write(textf);
                 File.WriteAllText(f.FullName, textf);
            }

            dirinfo = new DirectoryInfo("..\\..\\..\\Code\\GINACRA_Test\\examples");
            files = dirinfo.GetFiles("*.h", SearchOption.AllDirectories);
            foreach (FileInfo f in files)
            {
                //Console.WriteLine(f.Name);
                string textf = File.ReadAllText(f.FullName);
                textf = removeAllinc(textf);
                //textf = "#include \"ginacra_test.h\"\n";

                string sMainFunction = RenameMainFunctions(ref textf, f.Name.Substring(0, f.Name.Length - 2));

                sNewHeadFiles = sNewHeadFiles + "#include \"example/" + f.Name + "\"\n";
                sMainFunctions = sMainFunctions + "    cout << \"error = \" << error << endl;\n    " + sMainFunction + "\n";

                File.WriteAllText(f.FullName, textf);
            }

            //Add Head Files
            FileInfo headerfile = new FileInfo("..\\..\\..\\Code\\GINACRA_Test\\ginacra_test.h");
            string headContent = File.ReadAllText(headerfile.FullName);
            headContent = headContent.Replace("//AddOtherIncludeHere", sNewHeadFiles + "\n//AddOtherIncludeHere");

            FileInfo cppfile = new FileInfo("..\\..\\..\\Code\\GINACRA_Test\\ginacra_test.cpp");
            string cppContent = File.ReadAllText(cppfile.FullName);
            cppContent = cppContent.Replace("//ADDTESTFUNCTIONS", sMainFunctions + "\n//ADDTESTFUNCTIONS");

            Console.Write(headContent);
            Console.Write(cppContent);

            File.WriteAllText(headerfile.FullName, headContent);
            File.WriteAllText(cppfile.FullName, cppContent);
        }

        static public string removeAllinc(string sIn)
        {
            sIn = Regex.Replace(sIn, @"(#include\s+<[^>]+>)", @"//$1");
            return Regex.Replace(sIn, "(#include\\s+\\\"[^\\\"]+>)", @"//$1");
        }

        static public string RenameMainFunctions(ref string sIn, string sFileName)
        {
            sIn = Regex.Replace(sIn, @"(int\s+)main\s*\([^\)]*\)", "$1" + sFileName + "main()");
            return "error += " + sFileName + "main();";
        }

        #endregion

        #region GINACRA

        static void AddIncludeBackForGINACRA()
        {
            Console.Write(System.AppDomain.CurrentDomain.BaseDirectory);
            DirectoryInfo dirinfo = new DirectoryInfo("..\\..\\..\\Code\\GINACRA\\src\\lib");
            FileInfo[] files = dirinfo.GetFiles("*.*", SearchOption.AllDirectories).Where(s => s.FullName.EndsWith(".cpp") || s.FullName.EndsWith(".h")).ToArray();

            foreach (FileInfo f in files)
            {
                Console.WriteLine(f.FullName);

                string textf = File.ReadAllText(f.FullName);
                textf = Regex.Replace(textf, @"//(#include\s+<[^>]+>)", @"$1");
                textf = Regex.Replace(textf, @"(#include\s+<ginac/ginac.h>)", @"//$1");
                textf = Regex.Replace(textf, @"(#include\s+<cln/cln.h>)", @"//$1");
                //Console.Write(textf);
                File.WriteAllText(f.FullName, textf);
            }
        }

        static void AddPrivateHeaderForGINACRA()
        {
            Console.Write(System.AppDomain.CurrentDomain.BaseDirectory);
            DirectoryInfo dirinfo = new DirectoryInfo("..\\..\\..\\Code\\GINACRA\\src\\lib");
            FileInfo[] files = dirinfo.GetFiles("*.cpp", SearchOption.AllDirectories);
            foreach (FileInfo f in files)
            {
                Console.WriteLine(f.FullName);

                string textf = File.ReadAllText(f.FullName);
                textf = "#include \"..\\ginacra_private.h\"\n" + textf;
                File.WriteAllText(f.FullName, textf);
            }
        }

        static void AddDllExportForGINACRA()
        {
            Console.Write(System.AppDomain.CurrentDomain.BaseDirectory);
            DirectoryInfo dirinfo = new DirectoryInfo("..\\..\\..\\Code\\GINACRA\\src\\lib");
            FileInfo[] files = dirinfo.GetFiles("*.h", SearchOption.AllDirectories);

            foreach (FileInfo f in files)
            {
                string fileContent = File.ReadAllText(f.FullName);
                fileContent = Regex.Replace(fileContent,
                    @"class(\s+[\d\w_]+\s*[:\{;])",
                    @"class GINACRA_API$1");
                //Console.Write(fileContent);
                File.WriteAllText(f.FullName, fileContent);
            }
        }

        #endregion

        #region Nested Sum
        static void AddDllExportForNestedSums()
        {
            Console.Write(System.AppDomain.CurrentDomain.BaseDirectory);
            DirectoryInfo dirinfo = new DirectoryInfo("..\\..\\..\\Code\\NestedSum\\nestedsums");
            FileInfo[] files = dirinfo.GetFiles("*.h", SearchOption.AllDirectories);

            foreach (FileInfo f in files)
            {
                string fileContent = File.ReadAllText(f.FullName);
                fileContent = Regex.Replace(fileContent,
                    @"class(\s+[\d\w_]+\s*[:\{])",
                    @"class NESTEDSUMS_API$1");
                //Console.Write(fileContent);
                File.WriteAllText(f.FullName, fileContent);
            }
        }
        #endregion

        #region GINAC_CHECK

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

        #endregion

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
