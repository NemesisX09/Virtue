#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

std::string string_replace(const std::string& str, const std::string& match, 
        const std::string& replacement, unsigned int max_replacements = UINT_MAX)
{
    size_t pos = 0;
    std::string newstr = str;
    unsigned int replacements = 0;
    while ((pos = newstr.find(match, pos)) != std::string::npos
            && replacements < max_replacements)
    {
         newstr.replace(pos, match.length(), replacement);
         pos += replacement.length();
         replacements++;
    }
    return newstr;
}

int main () {
	fstream newfile;
	vector <string> lib;
	ofstream outfile;
  outfile.open("output.cpp", std::ios_base::app);
  newfile.open("code.txt",ios::in);
   if (newfile.is_open()){
      string tp;
			string f ("%s.%s(%s);");
			string df ("function %s() {");
			string ef ("}");
			string il ("import %s;");
      while(getline(newfile, tp)){
				 if(std::strcmp("",tp.c_str()) != 0){
					 if(std::strcmp(f.c_str(),tp.c_str()) >= 0){
						size_t i = tp.find_first_of(".");
						string library(tp.substr(0, i));
						string fpi(tp.substr(i));
						fpi = string_replace(fpi,".","",UINT_MAX);
						size_t e = fpi.find_first_of("(");
						string function (fpi.substr(0,e));
						string input (fpi.substr(e));
						input = string_replace(input,"\"","",UINT_MAX);
						input = string_replace(input,"(","",UINT_MAX);
						input = string_replace(input,")","",UINT_MAX);
						input = string_replace(input,";","",UINT_MAX);
						outfile << "\t" << function << "(\"" << input << "\");\n";
					}else if (std::strcmp(ef.c_str(),tp.c_str()) == 0) {
						outfile << "}";
					} else if(std::strcmp(il.c_str(),tp.c_str()) <= 0){
						string libraryps (string_replace(tp.c_str(),"import ","",UINT_MAX));
						string library (string_replace(libraryps,";","",UINT_MAX));
						outfile << "#include \"" << library << ".cpp\"\n";
					} else if(std::strcmp(df.c_str(),tp.c_str()) <= 0) {
						string fnpp (string_replace(tp.c_str(),"function ","",UINT_MAX));
						string fnp (string_replace(fnpp,"(","",UINT_MAX));
						string fn (string_replace(fnp,")","",UINT_MAX));
						string f (string_replace(fn,"{","",UINT_MAX));
						string rf (string_replace(f," ","",UINT_MAX));
						outfile << "int " << rf.c_str() << "() {\n\n";
					}
				 }
      }
      newfile.close();
   }
	std::system("clang++-7 -pthread -std=c++17 -o output output.cpp");
	std::system("./output");
	std::ofstream ofs;
	ofs.open("output.cpp", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
  return 0;
}