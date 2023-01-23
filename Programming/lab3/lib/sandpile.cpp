#include "sandpile.h"
#include <iostream>
#include <vector>


Grid::Grid(uint16_t length, uint16_t width, uint64_t iter, uint64_t freq, std::string outpath) {
    this->length = length;
    this->width = width;
    this->iter = iter;
    this->freq = freq;
    this->outpath = outpath;

    this->fullgrid = new uint64_t *[length];
    for (int i = 0; i < length; i++) this->fullgrid[i] = new uint64_t[width];

    this->info_grid = new bool *[length];
    for (int i = 0; i < length; i++) this->info_grid[i] = new bool[width];

    this->barier_grid = new bool *[length];
    for (int i = 0; i < length; i++) this->barier_grid[i] = new bool[width];
}

Pic::Pic(int length, int width) {
    this->length = length;
    this->width = width;
    this->all_colors = std::vector<Color>(length*width);
}

Color Pic::getcolor(int x, int y) const {
    return all_colors[y * length + x];
}

void Pic::setcolor(const Color &color, int x, int y) {
    all_colors[y * length + x].r = color.r;
    all_colors[y * length + x].g = color.g;
    all_colors[y * length + x].b = color.b;
}

void Pic::draw_exp(const std::string path) const {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (file.is_open()){

        unsigned char bmpPad[3] = {0,0,0};
        const int padding_amount = ((4 - (width * 3) % 4) % 4);

        const int file_header_size = 14;
        const int information_header_size = 40;
        const int file_size = file_header_size + information_header_size + length * width * 3 + padding_amount * length;

        unsigned char file_header[file_header_size];
        file_header[0] = 'B';
        file_header[1] = 'M';

        file_header[2] = file_size;
        file_header[3] = file_size >> 8;
        file_header[4] = file_size >> 16;
        file_header[5] = file_size >> 24;
        file_header[6] = 0;
        file_header[7] = 0;
        file_header[8] = 0;
        file_header[9] = 0;
        file_header[10] = file_header_size + information_header_size;
        file_header[11] = 0;
        file_header[12] = 0;
        file_header[13] = 0;

        unsigned char information_header[information_header_size];

        information_header[0] = information_header_size;
        information_header[1] = 0;
        information_header[2] = 0;
        information_header[3] = 0;

        information_header[4] = length;
        information_header[5] = length >> 8;
        information_header[6] = length >> 16;
        information_header[7] = length >> 24;

        information_header[8] = width;
        information_header[9] = width >> 8;
        information_header[10] = width >> 16;
        information_header[11] = width >> 24;

        information_header[12] = 1;
        information_header[13] = 0;

        information_header[14] = 24;
        information_header[15] = 0;

        for(int i = 16; i < 40; i++){
            information_header[i] = 0;
        }
        file.write((char*)(file_header), file_header_size);
        file.write((char*)(information_header), information_header_size);
        for(int y = 0; y < width; y++){
            for(int x = 0; x < length; x++){
                unsigned char r = static_cast<unsigned char>(getcolor(x,y).r);
                unsigned char g = static_cast<unsigned char>(getcolor(x,y).g);
                unsigned char b = static_cast<unsigned char>(getcolor(x,y).b);

                unsigned char color[] = {b,g,r};
                file.write((char*)(color), 3);
            }
            file.write((char*)(bmpPad), padding_amount);
        }
        file.close();
    }
    else{
        std::cout<<"Output directory not found";
    }
}


void clear_grid(Grid*ex){
    for(int x = 0; x < ex->length; x++){
        for(int y = 0; y < ex->width; y++){
            ex->fullgrid[x][y] = 0;
        }
    }

    for(int x = 0; x < ex->length; x++){
        for(int y = 0; y < ex->width; y++){
            ex->info_grid[x][y] = false;
        }
    }

    for(int x = 0; x < ex->length; x++){
        for(int y = 0; y < ex->width; y++){
            ex->barier_grid[x][y] = false;
        }
    }
}

void set_baries(Grid* ex, std::string barier){
    std::fstream file;
    file.open(barier);

    uint16_t temp_x = 0;
    uint16_t temp_y = 0;

    uint16_t temp_num = 0;
    char arg_count = 0;

    if (file.is_open()){
        while(file >> temp_num){
            switch(arg_count){
                case 0:{
                    temp_x = temp_num;
                    arg_count++;
                    break;
                }

                case 1:{
                     temp_y = temp_num;
                     ex->barier_grid[temp_x][temp_y] = true;
                     arg_count = 0;
                     break;
                }
            }
        }
        file.close();
    }
}


void set_sand(Grid* ex, std::string input){
    std::fstream file;
    file.open(input);

    uint16_t temp_x = 0;
    uint16_t temp_y = 0;
    uint64_t temp_count = 0;

    uint64_t temp_num = 0;
    char arg_count = 0;

    if (file.is_open()){
        while(file >> temp_num){
            switch(arg_count){
                case 0:{
                    temp_x = temp_num;
                    arg_count++;
                    break;
                }

                case 1:{
                    temp_y = temp_num;
                    arg_count++;
                    break;
                }

                case 2:{
                    temp_count = temp_num;
                    ex->fullgrid[temp_x][temp_y] = temp_count;
                    if(temp_count >= 4) ex->info_grid[temp_x][temp_y] = true;
                    arg_count = 0;
                    break;
                }
            }
        }
    file.close();
    }
    else{
        std::cout<<"Incorrect input file directory"<<"\n";
    }
}

void crumbling(Grid* ex){
    for (uint64_t i = 1; i < ex->iter+1; i++) {
        for (int x = 0; x < ex->length; x++) {
            for (int y = 0; y < ex->width; y++) {
                if(ex->info_grid[x][y]){
                    if ((x > 0) && !(ex->barier_grid[x - 1][y])){
                        ex->fullgrid[x - 1][y] += 1;
                    }
                    if ((y > 0) && !(ex->barier_grid[x][y - 1])){
                        ex->fullgrid[x][y - 1] += 1;
                    }
                    if ((x < ex->length - 1) && !(ex->barier_grid[x + 1][y])){
                        ex->fullgrid[x + 1][y] += 1;
                    }
                    if ((y < ex->width - 1) && !(ex->barier_grid[x][y + 1])) {
                        ex->fullgrid[x][y + 1] += 1;
                    }
                    ex->fullgrid[x][y] -= 4;
                }
                if(ex->fullgrid[x][y] > 3) ex->info_grid[x][y] = true;
                else ex->info_grid[x][y] = false;
            }
        }
        for(int k = 0; k < ex->length; k++){
            for(int p = 0; p < ex->width; p++){
                if(ex->fullgrid[k][p] > 3){
                    ex->info_grid[k][p] = true;
                }
            }
        }
        if ((ex->freq != 0) && (((i+1) % ex->freq) == 0)){
            const int length = ex->length;
            const int width = ex->width;

            Pic picture(length, width);

            for(int x = 0; x < length; x++){
                for(int y = 0; y < width; y++){
                    if(ex->fullgrid[x][y] > 3){
                        Color colorpixel;
                        colorpixel.r = 0;
                        colorpixel.g = 0;
                        colorpixel.b = 0;
                        picture.setcolor(colorpixel, x, y);
                    }
                    if(ex->fullgrid[x][y] == 3){
                        Color colorpixel;
                        colorpixel.r = 255;
                        colorpixel.g = 255;
                        colorpixel.b = 0;
                        picture.setcolor(colorpixel, x, y);
                    }
                    if(ex->fullgrid[x][y] == 2){
                        Color colorpixel;
                        colorpixel.r = 152;
                        colorpixel.g = 10;
                        colorpixel.b = 250;
                        picture.setcolor(colorpixel, x, y);
                    }
                    if(ex->fullgrid[x][y] == 1){
                        Color colorpixel;
                        colorpixel.r = 0;
                        colorpixel.g = 255;
                        colorpixel.b = 0;
                        picture.setcolor(colorpixel, x, y);
                    }
                    if(ex->fullgrid[x][y] == 0){
                        Color colorpixel;
                        colorpixel.r = 255;
                        colorpixel.g = 255;
                        colorpixel.b = 255;
                        picture.setcolor(colorpixel, x, y);
                    }
                }
            }
            std::string temp_path = ex->outpath;
            temp_path.push_back('/');
            char temp_char [100];
            std::snprintf(temp_char, sizeof(temp_char), "%d", i+1);
            int index = 0;
            while(index < 100 && temp_char[index] != '\0') {
                temp_path.push_back(temp_char[index]);
                index++;
            }
            temp_path.push_back('.');
            temp_path.push_back('b');
            temp_path.push_back('m');
            temp_path.push_back('p');
            picture.draw_exp(temp_path);
        }
    }
    if(ex->freq == 0){
        const int length = ex->length;
        const int width = ex->width;

        Pic picture(length, width);

        for(int x = 0; x < length; x++){
            for(int y = 0; y < width; y++){
                if(ex->fullgrid[x][y] > 3){
                    Color colorpixel;
                    colorpixel.r = 0;
                    colorpixel.g = 0;
                    colorpixel.b = 0;
                    picture.setcolor(colorpixel, x, y);
                }
                if(ex->fullgrid[x][y] == 3){
                    Color colorpixel;
                    colorpixel.r = 255;
                    colorpixel.g = 255;
                    colorpixel.b = 0;
                    picture.setcolor(colorpixel, x, y);
                }
                if(ex->fullgrid[x][y] == 2){
                    Color colorpixel;
                    colorpixel.r = 152;
                    colorpixel.g = 10;
                    colorpixel.b = 250;
                    picture.setcolor(colorpixel, x, y);
                }
                if(ex->fullgrid[x][y] == 1){
                    Color colorpixel;
                    colorpixel.r = 0;
                    colorpixel.g = 255;
                    colorpixel.b = 0;
                    picture.setcolor(colorpixel, x, y);
                }
                if(ex->fullgrid[x][y] == 0){
                    Color colorpixel;
                    colorpixel.r = 255;
                    colorpixel.g = 255;
                    colorpixel.b = 255;
                    picture.setcolor(colorpixel, x, y);
                }
            }
        }
        std::string temp_path = ex->outpath;
        temp_path.push_back('/');
        char temp_char [100];
        uint64_t i = ex->iter;
        std::snprintf(temp_char, sizeof(temp_char), "%d", i);
        int index = 0;
        while(index < 100 && temp_char[index] != '\0') {
            temp_path.push_back(temp_char[index]);
            index++;
        }
        temp_path.push_back('.');
        temp_path.push_back('b');
        temp_path.push_back('m');
        temp_path.push_back('p');
        picture.draw_exp(temp_path);
    }
}
