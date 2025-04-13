#include "led.h"
#include <stdexcept>

// Add a strip to the system
void LEDSystem::addStrip(Adafruit_NeoPixel &strip) {
    strips.push_back(&strip);
}

// Set the geometry of the LED system
void LEDSystem::setGeometry(int n_rows, int n_cols, int n_pixels_per_substrip,
                           float hex_size, float led_distance,
                           int between_substrip_led_offset,
                           int first_led_offset, float strip_offset_from_ground, float strip_offset_from_ceiling);
{
    // Validate input
    if (n_rows <= 0 || n_cols <= 0 || n_pixels_per_substrip <= 0 || hex_size <= 0 || led_distance <= 0) {
        throw std::invalid_argument("Geometry parameters must be positive.");
    }

    // Store geometry parameters
    this->n_rows = n_rows;
    this->n_cols = n_cols;
    this->n_pixels_per_substrip = n_pixels_per_substrip;
    this->between_substrip_offset = between_substrip_led_offset;
    this->strip_offset_from_ground = strip_offset_from_ground;
    this->strip_offset_from_ceiling = strip_offset_from_ceiling;

    // Store distances
    this->hex_size = hex_size;             // Distance between nodes in the hexagonal grid
    this->edge_size = hex_size / 1.73205f; // Edge size of the hexagon
    this->led_distance = led_distance;     // Distance between LEDs on a strip
    this->first_led_offset = first_led_offset;

    // Calculate offsets for the hexagonal grid
}
void LEDSystem::drawPixel(coordinate coor, float radius, int r, int g, int b) {
    int x_min = static_cast<int>(std::floor(coor.x - radius));
    int x_max = static_cast<int>(std::ceil(coor.x + radius));
    int y_min = static_cast<int>(std::floor(coor.y - radius));
    int y_max = static_cast<int>(std::ceil(coor.y + radius));
    int z_min = static_cast<int>(std::floor(coor.z - radius));
    int z_max = static_cast<int>(std::ceil(coor.z + radius));

    for (int x = x_min; x <= x_max; ++x) {
        for (int y = y_min; y <= y_max; ++y) {
            for (int z = z_min; z <= z_max; ++z) {
                coordinate current = {x, y, z};
                if (coordinate_pixel_map.find(current) != coordinate_pixel_map.end()) {
                    led_PIN_pixel led_pixel = coordinate_pixel_map[current];
                    strips[led_pixel.PIN]->setPixelColor(led_pixel.pixel_index, r, g, b);
                }
            }
        }
    }
}
void LEDSystem::show() {
    for (auto &strip : strips) {
        strip->show();
    }
}
void LEDSystem::clear(){
    for (auto &strip : strips) {
        for (int i = 0; i < strip->numPixels(); ++i) {
            strip->setPixelColor(i, 0, 0, 0); // Set all pixels to off
        }
        strip->show();
    }
}

// Build the LED system
void LEDSystem::build() {
    buildCoordinatePixelMap();
    // in case something here
}

// Get the number of strips
int LEDSystem::stripCount() {
    return strips.size();
}

// Build the coordinate-to-pixel map
void LEDSystem::buildCoordinatePixelMap() {
    coordinate_pixel_map.clear();
    for (int col = 0; col < n_cols; ++col) {
        buildColumnCoordinatePixelMap(col);
    }

}

void LEDSystem::buildColumnCoordinatePixelMap(int col) {
    int led_start = first_led_offset;
    bool is_long_column = (col % 2 == 0); // Determine if the column is a long column
    float x_start = is_long_column 
                    ? edge_size + 3 * col / 2 * edge_size 
                    : 2.5 * edge_size + (col / 2) * 3 * edge_size;
    float y_start = is_long_column ? hex_size / 2 : hex_size;
    bool from_ground = true;

    int max_rows = is_long_column ? n_rows : n_rows - 1;

    for (int row = 0; row < max_rows; ++row) {
        float x = is_long_column ? x_start : x_start + col * edge_size * 2;
        float y = y_start + row * hex_size;
        float z_start = strip_offset_from_ground;

        for (int i = 0; i < n_pixels_per_substrip; ++i) {
            float z = z_start + i * led_distance;
            int x_floor = static_cast<int>(std::floor(x));
            int y_floor = static_cast<int>(std::floor(y));
            int z_floor = static_cast<int>(std::floor(z));

            int pixel_index = from_ground ? led_start + i : (led_start + n_pixels_per_substrip - 1 - i);
            led_PIN_pixel led_pixel = {col, pixel_index};
            coordinate coord = {x_floor, y_floor, z_floor};
            coordinate_pixel_map[coord] = led_pixel;
        }

        led_start = led_start + n_pixels_per_substrip + between_substrip_offset;
        from_ground = !from_ground; // Toggle if needed per row
    }
}