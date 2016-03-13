
#include "utilities.h"
#include <sstream>

using namespace std;

namespace codingInterview
{
  //---------------------------------------------------------
  string toString(const statistics& iSt)
  {
    ostringstream oss;
    oss << "number of sample: " << iSt.getNumberOfSamples() << "\n" <<
      "min: " << iSt.getMin() << "\n" <<
      "max: " << iSt.getMax() << "\n" <<
      "mean: " << iSt.getMean() << "\n" <<
      "std. dev.: " << iSt.getStandardDeviation() << "\n";
    return oss.str();
  }
  
  //---------------------------------------------------------
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
