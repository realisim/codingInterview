
#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

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
void e1_3(const std::string& iS1, int trueSize)
{
  std::string r = iS1;
  for(size_t i = 0; i < r.size(); ++i)
  {
    if( r[i] == ' ' )
    {
      memcpy(&r[i+3], &r[i+1], trueSize - i);
      r[i] = '%'; r[i+1] = '2'; r[i+2] = '0';
      trueSize+=2;
    }
  }
  
  printf("%s -> %s\n", iS1.c_str(), r.c_str());
}

//-----------------------------------------------------------------
//--- 1.4
//-----------------------------------------------------------------
//in this exercise, palindrome can be in the form
// "taco cat"
bool isPalindrome(const string& iS)
{
  //first we remove all white space and we put everything to lowercaps
  string s = iS;
  
  size_t p = s.find(' ');
  while( p != string::npos )
  {
    s.erase( s.begin() + p );
    p = s.find(' ');
  }
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  
  bool r = true;
  for(size_t i = 0, j = s.size() - 1;
      i < s.size() && r; ++i, --j)
  {
    r = s[i] == s[j];
  }
  return r;
}

vector<string> generatePermutation(const string& iS1,
                                        int iIndex,
                                        const vector<string>& iPrevious)
{
  //all permutations at this stage
  vector<string> p;
  
  //one string permutation
  string s; s.resize(iIndex + 1);
  
  //for all string of previous stage, we will add a character
  for(size_t i = 0; i < iPrevious.size(); ++i)
  {
    //shuffle char at iIndex in every position of s;
    const char c = iS1[iIndex];
    int toIndex = 0;
    for( int j = 0; j < s.size(); ++j )
    {
      int fromIndex = 0;
      //make the permutation string char by char
      //on each iteration c will go at a different
      //spot(toIndex).
      //fromIndex is there only to be able to iterate
      //on the previous permutations.
      for( int k = 0; k < s.size(); ++k )
      {
        if(k == toIndex)
        { s[k] = c; }
        else
        { s[k] = iPrevious[i][fromIndex++]; }
      }
      toIndex++;
      p.push_back(s);
//printf("a permutation: %s\n", s.c_str());
    }
  }
  
  if(iIndex < iS1.size() - 1 )
  { p = generatePermutation(iS1, ++iIndex, p); }
  return p;
}

//-----------------------------------------------------------------
void e1_4(const string& iS1)
{
  vector<string> allPermutations;
  if( iS1.size() == 1 )
  { allPermutations.push_back(iS1); }
  else if( iS1.size() >= 2 )
  {
    //generate all permutations
    vector<std::string> p;
    p.push_back( iS1.substr(0, 1) );
    allPermutations = generatePermutation(iS1, 1, p);
  }
  else //empty
  {}
  
  //print all permutations
//  printf("\nall %d permutations for %s:\n",
//         (int)allPermutations.size(),
//         iS1.c_str() );
//  for(size_t i = 0; i < allPermutations.size(); ++i)
//  { printf("%s\n", allPermutations[i].c_str()); }
  
    for(size_t i = 0; i < allPermutations.size(); ++i)
    {
      if( isPalindrome( allPermutations[i]) )
      { printf("%s\n", allPermutations[i].c_str()); }
    }
}

//-----------------------------------------------------------------
void e1_5(const string& s1, const string& s2)
{
  int isOneAway = false;
  if( abs( (long)s1.size() - (long)s2.size()) <= 1 )
  {

    string small, big;
    if( s1.size() > s2.size() )
    { small = s2; big = s1; }
    else
    { small = s1; big = s2; }
    
    int offBy = 0;
    for(size_t i = 0; i < small.size() && offBy < 2; ++i)
    {
      if( small[i] != big[i] && small[i] != big[i+offBy] )
      { ++offBy; }
    }
    
    isOneAway = offBy < 2;
  }
  
  printf("%s to %s are %sone away\n", s1.c_str(), s2.c_str(), isOneAway ? "" : "not ");
}

//-----------------------------------------------------------------
void e1_6(const string& s1)
{
  string compressed;
  if(!s1.empty())
  {
    char c = s1[0];
    int count = 1;
    for(size_t i = 1; i <= s1.size(); ++i)
    {
      if( i < s1.size() && c == s1[i] )
      { count++; }
      else
      {
        char toString[4];
        sprintf(toString, "%d", count);
        compressed += c + string(toString);
        c = s1[i];
        count = 1;
      }
    }
    
    compressed = compressed.size() > s1.size() ? s1 : compressed;
    
    printf( "%s compressed -> %s\n", s1.c_str(), compressed.c_str() );
  }
}

//-----------------------------------------------------------------
//--- e1_7
//-----------------------------------------------------------------
void printMatrix(const unsigned int* pMat, int iM, int iN)
{
  for(int y = 0; y < iN; ++y)
  {
    for(int x = 0; x < iM; ++x)
    {
      const unsigned int v = pMat[ y*iM + x ];
      char c = '-';
      switch (v)
      {
        case 0: c = '0'; break;
        case 0xffffffff: c = '*'; break;
        default: c = 'x'; break;
      }
      printf("%c ", c);
    }
    printf("\n");
  }
  printf("\n");
}
//-----------------------------------------------------------------
void e1_7()
{
  const size_t n = 7;
  const size_t size = n*n;
  unsigned int* pImage = new unsigned int[size];
  
  //fill with 0;
  memset(pImage, 0, size*sizeof(unsigned int));
  
  //write in the midlle of the image 3 lines thick
  for(int y = -1; y <= 1; ++y)
    for(int x = 0; x < n; ++x)
    {
      pImage[ (n / 2 + y ) * n + x ] = 0xffffffff; //make rgba = (1, 1, 1, 1)
    }
  printf("original image\n");
  printMatrix(pImage, n, n);
  
  //rotate 90 clockwise (because it is easier than counterclockwise)
  int temp;
  for(int y = 0; y < n; ++y)
  {
    for(int x = y; x < n; ++x)
    {
      temp = pImage[y*n+x];
      pImage[y*n+x] = pImage[x*n+y];
      pImage[x*n+y] = temp;
    }
  }
  printf("rotated image\n");
  printMatrix(pImage, n, n);
  
  
  delete[] pImage;
}

//-----------------------------------------------------------------
void e1_8()
{
  const int m = 6;
  const int n = 8;
  const int size = m*n;
  
  unsigned int* pMat = new unsigned int[size];
  
  //fill with non zero
  memset(pMat, 3, size*sizeof(unsigned int));
  
  //add a bunch of zero
  //2, 2
  pMat[2*m + 2] = 0;
  //5,2
  pMat[2*m + 4] = 0;
  //3,7
  pMat[7*m + 3] = 0;
  
  //memset(pMat, 0, size*sizeof(unsigned int));
  printMatrix(pMat, m, n);
  
  std::bitset<m> cols;
  std::bitset<n> rows;
  for(int y = 0; y < n; ++y)
    for(int x = 0; x < m; ++x )
    {
      if( pMat[y*m + x] == 0 )
      {
        rows.set(y);
        cols.set(x);
      }
    }
  
  //set all rows to zero
  for(int i = 0; i < rows.size(); ++i)
  {
    if(rows.test(i))
    {
      for(int j = 0; j < m; ++j)
      { pMat[i*m + j] = 0; }
    }
  }
  //set all cols to zer0
  for(int i = 0; i < cols.size(); ++i)
  {
    if(cols.test(i))
    {
      for(int j = 0; j < n; ++j)
      { pMat[j*m + i] = 0; }
    }
  }
  printMatrix(pMat, m, n);
}


//-----------------------------------------------------------------
int main(int argc, char** argv)
{
  //---
  printf("--- Exercise 1.1:\n");
  e1_1("abcdefgh ijklmnopQrstUvwxyz1234567890");
  e1_1("The quick brown fox jumps over the lazy dog");
  //good

  //---
  printf("\n--- Exercise 1.2:\n");
  e1_2("abcdefgh", "hfgedcab");
  e1_2("ho yeah", "ho my god");
  e1_2("a dab of this", "a tab of dhis");
  //good
  
  //---
  printf("\n--- Exercise 1.3:\n");
  e1_3("Mr John Smith    ", 13);
  e1_3("The quick brown fox jumps over the lazy dog                ", 43);
  //good
  
  //---
  printf("\n--- Exercise 1.4:\n");
  //e1_4("ab");
  //e1_4("abc");
  //e1_4("abcd");
  e1_4("Tact Coa");
  //e1_4("The quick brown fox"); //woa ~1.22e17 results
  //complete failure!!!! Make all permutation is a very bad solution, since
  //it is impractible with string > 10-15...
  //Nontheless it was quite fun! I
  //had not understood the question properly. I thought the question was to
  //show all palindrome from all permutation of a given string...
  
  //---
  printf("\n--- Exercise 1.5:\n");
  e1_5("pale", "ple");
  e1_5("pales", "pale");
  e1_5("pale", "bale");
  e1_5("pale", "bake");
  e1_5("pale", "apale");
  e1_5("pale", "bapale");
  //better than book!
  
  printf("\n--- Exercise 1.6:\n");
  e1_6("aabbbcccccccdda");
  e1_6("abcd");
  e1_6("abBBBBddddEEEEEEfEEEEEFFFFFcd");
  //brute force, just ok.
  
  printf("\n--- Exercise 1.7:\n");
  e1_7();
  
  printf("\n--- Exercise 1.8:\n");
  e1_8();
  
  return 0;
}