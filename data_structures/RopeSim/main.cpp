#include <iostream>
#include <limits>
#include "RopeSimulation.h"

static const std::string INPUT_FILENAME = "input.txt";
static const std::string OUTPUT_FILENAME = "output.txt";

static const std::string MENU[3] = {
    "1) Animate simulation", 
    "2) Save sim to output.txt",
    "3) Exit"
};

using std::cout;
using std::cin;
using std::endl;

int main() {
    RopeSimulation sim(INPUT_FILENAME);

    char input = '0';
    do {
        int num_knots;
        int width;
        int height;
        int fps;

        cout << endl;
        switch (input) {
            case '1':
                do { 
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Number of knots to simulate: ";
                    cin >> num_knots;
                } 
                while (cin.fail() || num_knots <= 0);

                do { 
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Character width of simulation (Width must be odd): ";
                    cin >> width;
                } 
                while (cin.fail() || width <= 0 || width % 2 == 0);

                do {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Character height of simulation (Height must be odd): ";
                    cin >> height;
                } 
                while (cin.fail() || height <= 0 || height % 2 == 0);

                do {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "FPS: ";
                    cin >> fps;
                } 
                while (cin.fail() || fps <= 0);

                sim.animate(num_knots, cout, width, height, fps);
                break;
            case '2':
                do {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Number of knots to simulate: ";
                    cin >> num_knots;
                } 
                while (cin.fail() || num_knots <= 0);

                sim.save_sim(num_knots, OUTPUT_FILENAME);
                break;
            case '3': return 0;
            default: break;
        }

        // Reprint menu
        cout << endl;
        for (const std::string& option : MENU) { cout << option << endl; }
        cout << endl << "Select option: ";
    } while (cin >> input);

    return 0;
}