#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <string>

struct Rectangle {
    int x, y, w, h;
    int id;
    
    Rectangle(int x_, int y_, int w_, int h_, int id_);
    
    // Get right and bottom coordinates
    int right() const { return x + w; }
    int bottom() const { return y + h; }
    
    // Check if this rectangle intersects with another
    bool intersects(const Rectangle& other) const;
    
    // Get intersection rectangle with another
    Rectangle intersection(const Rectangle& other) const;
    
    // For ordering in sets
    bool operator<(const Rectangle& other) const;
    bool operator==(const Rectangle& other) const;
    
    std::string toString() const;
};

#endif