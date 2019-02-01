#include <map.h>
#include <iostream>
#include <iomanip>

Map::Map() {
    for (auto &row : field) {
        for (auto &square : row) {
            square = EMPTY;
        }
    }
}

bool Map::is_this_a_win(int16_t y, int16_t x, cell what) {
    field[y][x] = what;
    return false;
}

bool Map::is_empty(int16_t y, int16_t x) {
    return field[y][x] == EMPTY;
}

int Map::get_size() {
    return size;
}

cell Map::get_cell(int16_t y, int16_t x) {
    return field[y][x];
}

void Map::draw() {
    const int width = 4;

    std::cout << std::setw(width) << "";
    for (int16_t i = 0; i < size; i++) {
        std::cout << std::setw(width) << static_cast<int>(i);
    }
    std::cout << std::endl;

    for (int16_t i = 0; i < size; i++) {
        std::cout << std::setw(width) << static_cast<int>(i);
        for (int16_t j = 0; j < size; j++) {
            switch(field[i][j]) {
                case EMPTY: std::cout << std::setw(width) << "-"; break;
                case KRESTIK: std::cout << std::setw(width) << "x"; break;
                case NOLIK: std::cout << std::setw(width) << "o"; break;
                default: break;
            }
        }
        std::cout << std::endl;
    }
}

void Map::make_a_move(int16_t y, int16_t x, cell what) {
    field[y][x] = what;
}
