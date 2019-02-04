#include <map.h>
#include <iostream>
#include <iomanip>
#include <functional>

Map::Map() {
    for (auto &row : field) {
        for (auto &square : row) {
            square = EMPTY;
        }
    }
}

bool Map::is_this_a_win(int16_t y, int16_t x, cell what) {
    field[y][x] = what;

    if (row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(1, 0), what) +
        row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(-1, 0), what) >= win_num - 1) {
        return true;
    }

    if (row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(0, 1), what) +
        row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(0, -1), what) >= win_num - 1) {
        return true;
    }

    if (row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(1, 1), what) +
        row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(-1, -1), what) >= win_num - 1) {
        return true;
    }

    if (row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(-1, 1), what) +
        row_len_in_direction(sf::Vector2i(x, y), sf::Vector2i(1, -1), what) >= win_num - 1) {
        return true;
    }

    /*row_length = 1;
    i = x + 1;
    while (i <= size && field[i][y] == what) {
        row_length++;
        i++;
    }
    i = x - 1;
    while (i >= 0 && field[i][y] == what) {
        row_length++;
        i--;
    }
    if (row_length == 5) {
        return true;
    }

    row_length = 1;
    j = y + 1;
    while (j <= size && field[x][j] == what) {
        row_length++;
        j++;
    }
    j = y - 1;
    while (j >= 0 && field[x][j] == what) {
        row_length++;
        j--;
    }*/
    return false;
}

bool Map::is_empty(int16_t y, int16_t x) const {
    return field[y][x] == EMPTY;
}

int Map::get_size() const {
    return size;
}

cell Map::get_cell(int16_t y, int16_t x) const {
    return field[y][x];
}

void Map::draw() const {
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

int Map::row_len_in_direction(sf::Vector2i where_from, sf::Vector2i dir, cell what) const {
    int next_x = where_from.x + dir.x;
    int next_y = where_from.y + dir.y;
    if (next_x < 0 || next_x >= size || next_y < 0 || next_y >= size) {
        return 0;
    }

    if (field[next_x][next_y] != what) {
        return 0;
    } else {
        return 1 + row_len_in_direction(where_from + dir, dir, what);
    }
}
