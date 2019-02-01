#include <iostream>
#include <iomanip>
#include <SFML/Network.hpp>
#include "map.h"
#include "network.h"

int main() {
    sf::TcpSocket socket;
    if (socket.connect("localhost", PORT) != sf::TcpSocket::Done) {
        std::cout << "Connection failed" << std::endl;
        return 0;
    } else {
        std::cout << "Connected" << std::endl;
    }

    int16_t symbol;


    sf::Packet packet;
    socket.receive(packet);
    packet >> symbol;
    packet.clear();
    std::cout << static_cast<int>(symbol) << std::endl;

    Map map;

    int16_t y, x;
    if (symbol == 0) {
        std::cout << "Your symbol is KRESTIK" << std::endl;
    } else {
        std::cout << "Your symbol is NOLIK" << std::endl;
    }

    bool somebody_won = false;

    while (!somebody_won) {
        socket.receive(packet);
        int16_t info;
        packet >> info;

        if (info == 0 || info == 2) {
            if (info == 0) {
                packet >> y >> x;
                map.make_a_move(y, x, symbol == 0 ? NOLIK : KRESTIK);
            }
            packet.clear();
            map.draw();

            std::cout << "Your move:" << std::endl;
            std::cin >> y >> x;
            while (y < 0 || y >= map.get_size() || x < 0 || x >= map.get_size() || !map.is_empty(y, x)) {
                std::cout << "Please make a right move:" << std::endl;
                std::cin >> y >> x;
            }

            map.make_a_move(y, x, symbol == 0 ? KRESTIK : NOLIK);

            packet << y << x;
            socket.send(packet);
            packet.clear();
        } else {
            packet >> info;
            if (info == 0) {
                std::cout << "You won!" << std::endl;
            } else
                std::cout << "You lost" << std::endl;
            somebody_won = true;
        }
    }

    return 0;
}