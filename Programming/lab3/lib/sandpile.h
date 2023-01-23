#ifndef LABWORK_3_RISKMAN5_SANDPILE_H
#define LABWORK_3_RISKMAN5_SANDPILE_H

#endif //LABWORK_3_RISKMAN5_SANDPILE_H

#include <string>
#include <vector>
#include <fstream>

struct Color{
    float r;
    float g;
    float b;
};

struct Grid{
    uint16_t length;
    uint16_t width;
    uint64_t iter;
    uint64_t freq;
    uint64_t** fullgrid;
    std::string outpath;
    bool** info_grid;
    bool** barier_grid;
    Grid();
    Grid(uint16_t length, uint16_t width, uint64_t iter, uint64_t freq, std::string outpath);
};

struct Pic{
    Pic();
    Pic(int length, int width);

    Color getcolor(int x, int y) const;

    void setcolor(const Color& color, int x, int y);

    void draw_exp(std::string path) const;

    int length;
    int width;
    std::vector<Color> all_colors;
};

void crumbling(Grid* ex);

void clear_grid(Grid*ex);

void set_baries(Grid* ex, std::string barier);

void set_sand(Grid* ex, std::string input);
