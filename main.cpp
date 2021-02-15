#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
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

bool CheckSubstring(std::string firstString, std::string secondString){
    if(secondString.size() > firstString.size())
        return false;

    for (int i = 0; i < firstString.size(); i++){
        int j = 0;
        // If the first characters match
        if(firstString[i] == secondString[j]){
            int k = i;
            while (firstString[i] == secondString[j] && j < secondString.size()){
                j++;
                i++;
            }
            if (j == secondString.size())
                return true;
            else // Re-initialize i to its original value
                i = k;
        }
    }
    return false;
}

int main () {
  fstream newfile;
  newfile.open("code.txt",ios::in);
   if (newfile.is_open()){
      string tp;
      while(getline(newfile, tp)){
         cout << tp << "\n"; 
         string w ("Main.print(\"skjdh\");");
         if(std::strcmp(w.c_str(),tp.c_str()) >= 0){
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
          cout << library << "," << function << ", and " << input << "\n";
         }
         cout<< std::strcmp(w.c_str(),tp.c_str());
      }
      newfile.close();
   }
  return 0;
}