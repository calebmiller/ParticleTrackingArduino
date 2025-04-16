#include <iostream>
#include <map>
#include <cmath>

struct coordinate {
    float x, y, z;

    bool operator<(const coordinate& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
};

struct pixel_ID {
    int strip, pixel;
};

std::map<coordinate, pixel_ID> coordinate_pixel_map;

void generate_grid(int rows, float distance) {
    std::map<int, int> pin_dict = {{8, 2}, {21, 3}, {35, 4}, {50, 5}, {63, 6}, {77, 7}, {91, 8}};
    int cnt = 0;
    for (int row = 0; row < rows; row++) {
        int num_points = (row % 2 == 0) ? 7 : 6;
        bool top = (row % 2 == 0);
        int ledcnt = 99;
        for (int col = 0; col < num_points; col++) {
            float x = col * distance * sqrt(3) / 2;
            float y = row * distance * sqrt(3) / 2;
            if (row % 2 == 1) {
                x += distance * sqrt(3) / 4;
            }
            x += 8;
            y += 8;
            for (int lay = 0; lay < 10; lay++) {
                int ledid = top ? (ledcnt - 9 + lay) : (ledcnt - lay);
                float z = lay * 10 + 5;
                coordinate pnt = {x, y, z};
                pixel_ID pxl = {pin_dict[int(y)], ledid};
                coordinate_pixel_map[pnt] = pxl;
        		cnt++;
            }
            top = !top;
            ledcnt -= 13;
        }
    }
}

int main() {
    generate_grid(7, 16.0);
    return 0;

}

