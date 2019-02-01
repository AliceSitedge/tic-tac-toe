#ifndef TIC_TAC_TOE_MAP_H
#define TIC_TAC_TOE_MAP_H

#include <array>

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
    bool is_empty(int16_t y, int16_t x);
    int get_size();
    cell get_cell(int16_t y, int16_t x);
    void draw();
private:
    const static int16_t size = 20;
    std::array<std::array<cell, size>, size> field;
};

#endif //TIC_TAC_TOE_MAP_H
