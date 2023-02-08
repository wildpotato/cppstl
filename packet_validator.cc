/******
<src_ip>:<dst_ip>:<message_type>[:<payload>]
******/

/**********************************************************
#ifndef __TIMER_HPP__
#define __TIMER_HPP__
#include <chrono>
using hr_clock = std::chrono::high_resolution_clock();
using sec = std::chrono::seconds;
using tp = hr_clock::time_point;
class Timer {
public:

  void start()
  {
    last_start = hr_clock::now();
    last_checkpoint = last_start;
  }
  template <typename ResolutionType = sec>
  ResolutionType checkpoint()
  {
    tp now(hr_clock::());
    ResolutionType diff = std::chrono::duration_cast<ResolutionType>(now - last_checkpoint);
    last_checkpoint = now;
    return diff; // remember to call count() when trying to print result
  }
  template <typename ResolutionType = sec>
  ResolutionType stop()
  {
    return std::chrono::duration_cast<ResoltuionType>(hr_clock::now() - last_start);
  }
private:
  tp last_start;
  tp last_checkpoint;
};
#endif
**********************************************************/

class packet_validator
{
public:
  using time_point = uint64_t;
  struct config
  {
    int timeout_sec; // timeout in seconds between packets when connection considered closed
    size_t connections_per_ip; // opening extra connection is invalid
    size_t bytes_per_connection; // data packet exceeding the limit is invalid
  };
  
  packet_validator(const config &cfg);
  
  // return 'true' if packet is valid
  bool handle_packet(time_point now, std::string_view pkt);
  
  // periodically called often enough for the validator to detect connection timeouts to properly handle further packets
  // return: number of connection timeouts detected in this call
  int handle_timeouts(time_point now);

  
private:


};
