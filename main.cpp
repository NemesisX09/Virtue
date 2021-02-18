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
	/*
  newfile.open("libs.txt",ios::in);
   if (newfile.is_open()){
      string tp;
      while(getline(newfile, tp)){
         cout << tp << "\n"; 
				 lib.push_back(tp);
      }
      newfile.close();
   }
	 */
  newfile.open("code.txt",ios::in);
   if (newfile.is_open()){
      string tp;
      while(getline(newfile, tp)){
         cout << tp << "\n"; 
         string f ("%s.%s(%s);");
				 string df ("function %s() {");
         if(std::strcmp(f.c_str(),tp.c_str()) >= 0){
          size_t i = tp.find_first_of(".");
          string library(tp.substr(0, i));
          string fpi(tp.substr(i));
          fpi = string_replace(fpi,".","",UINT_MAX);
          size_t e = fpi.find_first_of("(");
          string input (fpi.substr(i));
          input = string_replace(input,"\"","",UINT_MAX);
          input = string_replace(input,"(","",UINT_MAX);
          input = string_replace(input,")","",UINT_MAX);
          input = string_replace(input,";","",UINT_MAX);
          string function (fpi.substr(0,i));
          cout << library << ", " << function << ", and " << input << "\n";
        }else if(std::strcmp(df.c_str(),tp.c_str()) >= 0) {
					cout << "func dec.\n";
				}
      }
      newfile.close();
   }
  return 0;
}