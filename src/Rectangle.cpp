#include "Rectangle.h"
#include <algorithm>
#include <sstream>

Rectangle::Rectangle(int x_, int y_, int w_, int h_, int id_)
    : x(x_), y(y_), w(w_), h(h_), id(id_) {}

bool Rectangle::intersects(const Rectangle& other) const {
    return !(other.x >= right() || 
             other.right() <= x ||
             other.y >= bottom() ||
             other.bottom() <= y);
}

Rectangle Rectangle::intersection(const Rectangle& other) const {
    int interX = std::max(x, other.x);
    int interY = std::max(y, other.y);
    int interRight = std::min(right(), other.right());
    int interBottom = std::min(bottom(), other.bottom());
    
    int interW = interRight - interX;
    int interH = interBottom - interY;
    
    // Use -1 as temporary ID for intersection rectangles
    return Rectangle(interX, interY, interW, interH, -1);
}

bool Rectangle::operator<(const Rectangle& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    if (w != other.w) return w < other.w;
    return h < other.h;
}

bool Rectangle::operator==(const Rectangle& other) const {
    return x == other.x && y == other.y && w == other.w && h == other.h;
}

std::string Rectangle::toString() const {
    std::stringstream ss;
    ss << "Rectangle at (" << x << "," << y << "), w = " << w << " h = " << h;
    return ss.str();
}