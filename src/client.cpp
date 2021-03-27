#include <SFML/Network.hpp>
#include <iostream>

struct ArenaBrawlDataPack{
  ArenaBrawlDataPack(){
    status = "alive";
    pos_y = pos_x = 12;
    ammo = 221;
  }
  std::string status;
  float pos_x;
  float pos_y;
  uint32_t ammo;
};

sf::Packet& operator<<(sf::Packet& packet, const ArenaBrawlDataPack& rpacket){
  return packet << rpacket.status << rpacket.pos_x << rpacket.pos_y << rpacket.ammo;
}

sf::Packet& operator>>(sf::Packet& packet, ArenaBrawlDataPack& rpacket){
  return packet >> rpacket.status >> rpacket.pos_x >> rpacket.pos_y >> rpacket.ammo;
}

int main(){
  sf::TcpSocket Client;
  if (Client.connect("127.0.0.1", 7000) != sf::Socket::Done) {
    std::cerr << "Error connection to port.\n";
  }


  sf::Packet data_pack;
  ArenaBrawlDataPack data;

  std::cout << "Receiving data bot...\n";
  Client.receive(data_pack);
  data_pack >> data;
  std::cout << data.status << std::endl;
  std::cout << data.pos_x << std::endl;
  std::cout << data.pos_y << std::endl;
  std::cout << data.ammo << std::endl;

  char message[50] = "ORDER: ROTATE(43.0) MOVE(FORWARD)";
  std::cout << "Sending order...\n";
  Client.send(message, sizeof(message));
  return 0;
}