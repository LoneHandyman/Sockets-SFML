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
  sf::TcpListener listener;
  if (listener.listen(7000) != sf::Socket::Done){
    std::cerr << "Error in listener.\n";
  }

  sf::TcpSocket Client;
  if(listener.accept(Client) != sf::Socket::Done){
    std::cerr << "Error listener can not accept socket.\n";
  }

  sf::Packet data_pack;
  ArenaBrawlDataPack data;

  data_pack << data;

  std::cout << "Sending data bot...\n";
  Client.send(data_pack);

  std::cout << "Receiving order...\n";
  char buffer[50];
  std::size_t received_size;
  Client.receive(buffer, sizeof(buffer), received_size);
  std::cout << buffer << std::endl;
  std::cout << "Parsing order...\n";
  return 0;
}