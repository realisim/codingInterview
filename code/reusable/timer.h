
#ifndef realisim_utils_timer_hh
#define realisim_utils_timer_hh

#include <chrono>

namespace codingInterview
{
  //Cette classe fonctionne comme un chronomètre. Elle sert a calculer
  //des intervals de temps.
  
  class timer
  {
  public:
    timer();
    virtual ~timer();
    
    double getElapsed() const;
//void pause();
    void start();
    void stop();
    
  protected:
    enum state{ sIdle, sRunning, sStopped };
    
    timer(const timer&);
    timer& operator=(const timer&);
    
    state getState() const {return mState;}
    void goToState(state);
    
    state mState;
    std::chrono::high_resolution_clock::time_point mT1;
    std::chrono::high_resolution_clock::time_point mT2;
  };

} // end of namespace
#endif
