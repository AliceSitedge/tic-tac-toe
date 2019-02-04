#ifndef TIC_TAC_TOE_MAP_H
#define TIC_TAC_TOE_MAP_H

#include <array>
#include <SFML/System/Vector2.hpp>

enum cell {
    EMPTY = 0,
    KRESTIK,
    NOLIK
};

class Map {
  public:
    Map();
    void make_a_move(int16_t y, int16_t x, cell what);
    bool is_this_a_win(int16_t y, int16_t x, cell what);
    bool is_empty(int16_t y, int16_t x) const;
    int get_size() const;
    cell get_cell(int16_t y, int16_t x) const;
    void draw() const;
  private:
    const static int16_t size = 20;
    const static int16_t win_num = 5; 
    std::array<std::array<cell, size>, size> field;
    int row_len_in_direction (sf::Vector2i where_from, sf::Vector2i dir, cell what) const;
};

#endif //TIC_TAC_TOE_MAP_H
