/******
<src_ip>:<dst_ip>:<message_type>[:<payload>]
******/

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
};
