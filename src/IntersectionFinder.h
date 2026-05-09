#ifndef INTERSECTIONFINDER_H
#define INTERSECTIONFINDER_H

#include "Rectangle.h"
#include <vector>
#include <map>
#include <set>

struct Intersection {
    Rectangle rect;
    std::set<int> contributingRectIds;
    
    Intersection(const Rectangle& r, const std::set<int>& ids);
    bool operator==(const Intersection& other) const;
    std::string toString() const;
};

class IntersectionFinder {
private:
    std::vector<Rectangle> rectangles;
    
    // Find all subsets of rectangles (size >= 2) that have a common intersection
    std::vector<Intersection> findAllIntersections() const;
    
public:
    IntersectionFinder(const std::vector<Rectangle>& rects);
    
    std::vector<Rectangle> getRectangles() const { return rectangles; }
    std::vector<Intersection> getIntersections() const;
};

#endif