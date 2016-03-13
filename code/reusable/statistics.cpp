
#include <cmath>
#include "statistics.h"
#include <limits>

using namespace codingInterview;

statistics::statistics() :
  mKeepSamples(false),
  mNumberOfSamples(0),
  mSum(0.0),
  mSumSquared(0.0),
  mMin(std::numeric_limits<double>::max()),
  mMax(-std::numeric_limits<double>::max())
{}

//-------------------------------------------------------------------------
statistics::statistics(const statistics& iRhs) :
mKeepSamples(iRhs.isKeepingSamples()),
mNumberOfSamples(iRhs.getNumberOfSamples()),
mSum(iRhs.mSum),
mSumSquared(iRhs.mSumSquared),
mMin(iRhs.mMin),
mMax(iRhs.mMax)
{}

//-------------------------------------------------------------------------
statistics::~statistics()
{ clear(); }

//-------------------------------------------------------------------------
void statistics::add(double iSample)
{
  if(isKeepingSamples())
  { mSamples.push_back(iSample); }
  
  ++mNumberOfSamples;
  mSum += iSample;
  mSumSquared += iSample * iSample;
  mMin = std::min(mMin, iSample);
  mMax = std::max(mMax, iSample);
}

//-------------------------------------------------------------------------
void statistics::add(const std::vector<double>& iSamples)
{
  for(size_t i = 0; i < iSamples.size(); ++i )
  { add(iSamples[i]); }
}

//-------------------------------------------------------------------------
void statistics::add(const double* iSamples, unsigned int iNum)
{
  for(size_t i = 0; i < iNum; ++i )
  { add( iSamples[i] ); }
}
  
//-------------------------------------------------------------------------
void statistics::clear()
{
  mSamples.clear();
  mNumberOfSamples = 0;
  mSum = 0.0;
  mSumSquared = 0.0;
  mMin = std::numeric_limits<double>::max();
  mMax = -std::numeric_limits<double>::max();
}

//-------------------------------------------------------------------------
double statistics::getMean() const
{
  return mSum / getNumberOfSamples();
}

//-------------------------------------------------------------------------
double statistics::getSample(unsigned int iIndex) const
{
  double r = 0.0;
  if(iIndex < getNumberOfSamples())
  { r = mSamples[iIndex]; }
  return r;
}

//-------------------------------------------------------------------------
double statistics::getStandardDeviation() const
{
  const unsigned int n = getNumberOfSamples();
  return sqrt( (mSumSquared - ( mSum * mSum / n)) / (n - 1) );
}

