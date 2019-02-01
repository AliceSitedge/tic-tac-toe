#include <iostream>
#include <SFML/Network.hpp>
#include "map.h"
#include "network.h"

struct player {
    sf::TcpSocket socket;
    int16_t symbol = 0;
};

int main() {
    sf::TcpListener listener;
    std::array<player, 2> players;
    if (listener.listen(PORT) != sf::Socket::Status::Done) {
        return 1;
    }
    std::cout << "Listening..." << std::endl;

    listener.accept(players[0].socket);
    std::cout << "Player 1 is connected" << std::endl;
    listener.accept(players[1].socket);
    std::cout << "Player 2 is connected" << std::endl;

    srand(unsigned(std::time(nullptr)));
    players[0].symbol = static_cast<int16_t>(rand()%2);
    if (players[0].symbol == 0) {
        players[1].symbol = 1;
    } else {
        players[1].symbol = 0;
    }

    sf::Packet packet;
    for (int i = 0; i < 2 ; i++) {
        packet << players[i].symbol;
        players[i].socket.send(packet);
        packet.clear();
    }

    Map map;

    int curr_player = players[0].symbol == 0 ? 0 : 1;
    int16_t info = 2;
    packet << info;
    players[curr_player].socket.send(packet);
    packet.clear();
    
    bool somebody_won = false;

    while (!somebody_won) {
        int16_t y, x;
        cell move = players[curr_player].symbol == 0 ? KRESTIK : NOLIK;
        players[curr_player].socket.receive(packet);
        packet >> y >> x;
        packet.clear();

        somebody_won = map.is_this_a_win(y, x, move);

        if (!somebody_won) {
            int16_t info = 0;
            packet << info;
            packet << y << x;
            players[curr_player == 0 ? 1 : 0].socket.send(packet);
            packet.clear();

            curr_player = curr_player == 0 ? 1 : 0;
        }
    }

    std::cout << "Player " << curr_player + 1 << " won" << std::endl;
    packet << 1 << 0;
    players[curr_player].socket.send(packet);
    packet.clear();
    packet << 1 << 1;
    players[curr_player == 0 ? 1 : 0].socket.send(packet);
    packet.clear();

    return 0;
}