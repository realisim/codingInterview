
#include "utilities.h"


using namespace std;

namespace codingInterview
{

vector<string> split(const string& s, char sep)
{
  vector<string> r;
  string t;
  for(size_t i = 0; i < s.size(); ++i)
  {
    char c = s[i];
    if(c == sep)
    {
      r.push_back(t);
      t = string();
    }
    else
    { t += c; } 
  }
  
  if(!t.empty())
  { r.push_back(t); }
  return r;
}

  
}
