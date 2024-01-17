#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstdint>
#include <vector>

// Your code goes here...
struct Packet {
    
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;

    bool found = false;
    // Add other fields as needed
}__attribute__((packed));

inline std::vector<uint8_t> toVector(const Packet & data)
{
  std::vector<uint8_t> packet(sizeof(Packet));
  std::copy(
    reinterpret_cast<const uint8_t *>(&data),
    reinterpret_cast<const uint8_t *>(&data) + sizeof(Packet), packet.begin());
  return packet;
}

#endif // PACKET_HPP
