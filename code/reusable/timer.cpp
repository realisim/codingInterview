
#include "timer.h"

using namespace codingInterview;
using namespace std;

timer::timer() :
  mState(sIdle),
  mT1(),
  mT2()
{ start(); }

//-------------------------------------------------------------------------
timer::~timer()
{}

//-------------------------------------------------------------------------
//retourne le nombre de secondes écoulées entre le start et le stop;
double timer::getElapsed() const
{
  chrono::duration<double> timeSpan;
  switch (getState())
  {
    case sIdle: break;
    case sRunning:
    {
      chrono::high_resolution_clock::time_point t2 =
        chrono::high_resolution_clock::now();
      timeSpan =
        chrono::duration_cast<chrono::duration<double> >(t2 - mT1);
    }break;
    case sStopped:
    {
      timeSpan =
        chrono::duration_cast<chrono::duration<double> >(mT2 - mT1);
    } break;
      
    default:
      break;
  }
  
  return timeSpan.count();;
}

//-------------------------------------------------------------------------
void timer::goToState(state iState)
{
  switch (getState())
  {
    case sIdle:
      switch (iState)
      {
        case sRunning:
          mT1 = chrono::high_resolution_clock::now();
          mT2 = mT1;
          mState = sRunning;
          break;
        default: break;
      }
      break;
    
    case sRunning:
      switch (iState)
      {
        case sRunning:
          mT1 = chrono::high_resolution_clock::now();
          mT2 = mT1;
          break;
        case sStopped:
          mT2 = chrono::high_resolution_clock::now();
          mState = sStopped;
          break;
        default: break;
      }
      break;
      
    case sStopped:
      switch (iState)
      {
        case sRunning:
          mT1 = chrono::high_resolution_clock::now();
          mT2 = mT1;
          mState = sRunning;
          break;
        default: break;
      }
      break;
      
    default: break;
  }
}
  
//-------------------------------------------------------------------------
void timer::start()
{ goToState(sRunning); }

//-------------------------------------------------------------------------
void timer::stop()
{ goToState(sStopped); }
