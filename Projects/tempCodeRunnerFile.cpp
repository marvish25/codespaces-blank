#include <iostream>
#include <cmath>  // Needed for sqrt and pow
#include <string>

// ANSI Color Codes (You know these!)
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLUE = "\033[34m";
const std::string RESET = "\033[0m";

void draw_circle(int radius)
{
    // 1. Loop through the Y axis (Height)
    // We go from -radius to +radius to center the circle at (0,0)
    for (int y = -radius; y <= radius; y++)
    {
        // 2. Loop through the X axis (Width)
        for (int x = -radius; x <= radius; x++)
        {
            // 3. The Distance Formula: d = sqrt(x^2 + y^2)
            float distance = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

            // 4. Check if the point is inside the circle
            // We use (radius - 0.5) to smooth the edge slightly
            if (distance <= radius)
            {
                // Print two spaces because console characters are tall/thin.
                // Using two spaces makes it look more circular and less like an oval.
                std::cout << RED << "██"<< RESET; 
            }
            else
            {
                std::cout << "  "; // Empty space
            }
        }
        std::cout << "\n"; // New line after every row
    }
}

int main()
{
    std::cout << "Here is a circle with radius 8:\n\n";
    draw_circle(8);
    return 0;
}