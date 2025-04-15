#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>

struct coordinate{
  float x;
  float y;
  float z;
  
  bool operator<(const coordinate& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return z < other.z;
  }
};

struct pixel_ID
{
  int strip;
  int pixel;
};

class LEDSystem {
    public:
        void initLEDs();
        // Add a strip to the system
        void addStrip(Adafruit_NeoPixel &strip);

		    //load geometry map from csv
		    void loadGeometry();

        // Set the geometry of the LED system
        // n_rows, n_cols, n_pixels_per_substrip are setting the grid structures
        // hex_space, led_distance are setting real world metric in cm. hex space is the distance between two centers of the hexagons
        // between_substrip_led_offset: # of led not used between sub-strips
        // first_led_offset: # of led not used before the first led, 
        // strip_offset: the distance between the ceiling and the first led, used for making coordinate
        void setGeometry(int n_rows, int n_cols, int n_pixels_per_substrip,
                        float hex_size, float led_distance,
                        int between_substrip_led_offset, 
                        int first_led_offset, float strip_offset_from_ground, float strip_offset_from_ceiling);

        // Build the LED system
        void build();

        void clear();

        // Get the number of strips
        int stripCount();
        //void drawPixel(coordinate coor, float radius, int r, int g, int b);
        void show();
        void printMap();
        void setPixel(int pixel, int r, int g, int b);

    private:
        // Attributes
        Adafruit_NeoPixel strips[7];
        coordinate points[460];
        pixel_ID pins[460];
        // Pixels per string

        int n_rows = 0;                     // Number of rows in the LED grid
        int n_cols = 0;                     // Number of columns in the LED grid
        int n_pixels_per_substrip = 0;      // Number of pixels per sub-strip
        int between_substrip_offset = 0;    // Offset between sub-strips
        int strip_offset = 0;               // Offset between strips
        float hex_size = 0.0f;              // Distance between nodes in the hexagonal grid
        float led_distance = 0.0f;          // Distance between LEDs on a strip
        float horizontal_offset = 0.0f;     // Horizontal offset between nodes
        float vertical_offset = 0.0f;       // Vertical offset between nodes
        int first_led_offset = 0;           // Number of LEDs not used before the first LED

        const int LED_PINS[7] = {2, 3, 4, 5, 6, 7, 8};

        // Helper function to build the coordinate-to-pixel map
        void buildCoordinatePixelMap();
        void buildColumnCoordinatePixelMap(int col);
        void generate_grid(int rows, float distance);
        //void populate_map(std::map<int, coordinate> points, std::vector<float> z_coords, std::map<float, int> pin_dict);
        int get_pin_id(int yval);
        
};

#endif // LED_H
