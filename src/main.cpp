#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "Rectangle.h"
#include "IntersectionFinder.h"
#include <json/json.hpp>

using json = nlohmann::json;

class JSONRectangleParser {
public:
    static std::vector<Rectangle> parseFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        json data;
        try {
            file >> data;
        } catch (const json::parse_error& e) {
            throw std::runtime_error("Invalid JSON format: " + std::string(e.what()));
        }
        
        if (!data.contains("rects") || !data["rects"].is_array()) {
            throw std::runtime_error("JSON missing 'rects' array");
        }
        
        std::vector<Rectangle> rectangles;
        int id = 1;
        
        for (const auto& rect : data["rects"]) {
            // Validate required fields
            if (!rect.contains("x") || !rect.contains("y") || 
                !rect.contains("w") || !rect.contains("h")) {
                throw std::runtime_error("Rectangle missing required fields (x,y,w,h)");
            }
            
            int x = rect["x"];
            int y = rect["y"];
            int w = rect["w"];
            int h = rect["h"];
            
            if (w < 0 || h < 0) {
                throw std::runtime_error("Width and height must be non-negative");
            }
            
            rectangles.emplace_back(x, y, w, h, id);
            id++;
            
            // Limit to 10 rectangles
            if (rectangles.size() >= 10) {
                std::cout << "Warning: Only processing first 10 rectangles\n";
                break;
            }
        }
        
        return rectangles;
    }
};

void printRectangles(const std::vector<Rectangle>& rects) {
    std::cout << "Input:\n";
    for (const auto& rect : rects) {
        std::cout << rect.id << ": " << rect.toString() << "\n";
    }
    std::cout << std::endl;
}

void printIntersections(const std::vector<Intersection>& intersections) {
    std::cout << "Intersections\n";
    if (intersections.empty()) {
        std::cout << "No intersections found.\n";
        return;
    }
    
    for (const auto& inter : intersections) {
        std::cout << inter.toString() << ".\n";
    }
}

int main(int argc, char* argv[]) {
    try {
        // Check command line arguments
        if (argc != 2) {
            std::cerr << "Usage: " << argv[0] << " <json_file>\n";
            return 1;
        }
        
        std::string filename = argv[1];
        
        // Parse JSON file
        std::cout << "Loading rectangles from: " << filename << "\n\n";
        std::vector<Rectangle> rectangles = JSONRectangleParser::parseFile(filename);
        
        if (rectangles.empty()) {
            std::cout << "No valid rectangles found in file.\n";
            return 0;
        }
        
        // Find intersections
        IntersectionFinder finder(rectangles);
        
        // Print results
        printRectangles(rectangles);
        printIntersections(finder.getIntersections());
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}