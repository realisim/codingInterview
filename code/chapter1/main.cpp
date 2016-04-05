
#include <algorithm>
#include <string>

//-----------------------------------------------------------------
void e1_1(const std::string& iS)
{
  const int s = (int)iS.size();

  //if iS has more charaters than the ascii table, there is at least
  //a redundant char!
  bool isUnique = s < 256;
  if( isUnique )
  {
    bool validation[256];
    for(int i = 0; i < 256; ++i)
    { validation[i] = false; }
    
    for( int i = 0; i < s && isUnique; ++i )
    {
      if(validation[ (int)iS[i] ])
      { isUnique = false; }
      validation[ (int)iS[i] ] = true;
    }
  }
  
  if( isUnique )
  { printf("%s has only unique characters.\n", iS.c_str() ); }
  else
  { printf("%s has redundant characters.\n", iS.c_str() ); }
}

//-----------------------------------------------------------------
void e1_2(const std::string& iS1, const std::string& iS2)
{
  /*To be a permutationL
    1- both strings need to be same size.
    2- when sorted n * log(n), they should be equal O(n)
   
    So bottom line... this is O(n)
   */
  
  bool isPermutation = iS1.size() == iS2.size();
  
  if( isPermutation )
  {
    std::string s1 = iS1;
    std::string s2 = iS2;
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    isPermutation = s1 == s2;
  }
  
  printf("[%s] is%sa permutation of [%s].\n", iS1.c_str(),
         isPermutation ? " " : " not ",
         iS2.c_str() );
}

//-----------------------------------------------------------------
void e1_3(const std::string& iS1)
{
}

//-----------------------------------------------------------------
int main(int argc, char** argv)
{
  //---
  printf("--- Exercise 1.1:\n");
  e1_1("abcdefgh ijklmnopQrstUvwxyz1234567890");
  e1_1("The quick brown fox jumps over the lazy dog");

  //---
  printf("\n--- Exercise 1.2:\n");
  e1_2("abcdefgh", "hfgedcab");
  e1_2("ho yeah", "ho my god");
  e1_2("a dab of this", "a tab of dhis");
  
  //---
  printf("\n--- Exercise 1.3:\n");
  e1_3("Mr. John Smith    ");
  return 0;
}