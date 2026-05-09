#include "IntersectionFinder.h"
#include <algorithm>
#include <sstream>
#include <functional>
#include <bitset>
#include <cstdint>

Intersection::Intersection(const Rectangle& r, const std::set<int>& ids)
    : rect(r), contributingRectIds(ids) {}

bool Intersection::operator==(const Intersection& other) const {
    return rect == other.rect && contributingRectIds == other.contributingRectIds;
}

std::string Intersection::toString() const {
    std::stringstream ss;
    ss << "Between rectangle ";
    auto it = contributingRectIds.begin();
    ss << *it;
    ++it;
    for (; it != contributingRectIds.end(); ++it) {
        ss << ", " << *it;
    }
    ss << " at (" << rect.x << "," << rect.y << "), w = " << rect.w << " h = " << rect.h;
    return ss.str();
}

IntersectionFinder::IntersectionFinder(const std::vector<Rectangle>& rects)
    : rectangles(rects) {}

// Helper function to count bits (works on all compilers)
// Fixed: takes uint32_t to avoid signed/unsigned issues
int countBits(uint32_t n) {
    // Use std::bitset for portable bit counting
    return static_cast<int>(std::bitset<32>(n).count());
}

std::vector<Intersection> IntersectionFinder::findAllIntersections() const {
    std::vector<Intersection> result;
    size_t n = rectangles.size();
    
    // Early return if not enough rectangles
    if (n < 2) {
        return result;
    }
    
    // For n up to 10, 1 << n is safe (max 1024)
    uint32_t maxMask = (n >= 31) ? UINT32_MAX : (static_cast<uint32_t>(1) << n);
    
    // Find all combinations of 2 or more rectangles that intersect
    for (uint32_t mask = 0; mask < maxMask; ++mask) {
        // Skip masks with less than 2 bits set
        if (countBits(mask) < 2) continue;
        
        // Get contributing rectangles
        std::vector<int> contributingIds;
        std::vector<Rectangle> contributingRects;
        contributingIds.reserve(n);  // Pre-allocate for performance
        contributingRects.reserve(n);
        
        for (size_t i = 0; i < n; ++i) {
            if (mask & (static_cast<uint32_t>(1) << i)) {
                contributingIds.push_back(rectangles[i].id);
                contributingRects.push_back(rectangles[i]);
            }
        }
        
        // Find intersection of all contributing rectangles
        bool hasIntersection = true;
        Rectangle currentIntersection = contributingRects[0];
        
        for (size_t i = 1; i < contributingRects.size(); ++i) {
            if (!currentIntersection.intersects(contributingRects[i])) {
                hasIntersection = false;
                break;
            }
            currentIntersection = currentIntersection.intersection(contributingRects[i]);
        }
        
        if (hasIntersection && currentIntersection.w > 0 && currentIntersection.h > 0) {
            std::set<int> idSet(contributingIds.begin(), contributingIds.end());
            result.emplace_back(currentIntersection, idSet);
        }
    }
    
    // Sort by number of contributors and then by rectangle coordinates
    std::sort(result.begin(), result.end(), 
        [](const Intersection& a, const Intersection& b) {
            if (a.contributingRectIds.size() != b.contributingRectIds.size()) {
                return a.contributingRectIds.size() < b.contributingRectIds.size();
            }
            if (a.rect.x != b.rect.x) return a.rect.x < b.rect.x;
            if (a.rect.y != b.rect.y) return a.rect.y < b.rect.y;
            // Fixed: Use long long to avoid potential overflow warning
            long long areaA = static_cast<long long>(a.rect.w) * a.rect.h;
            long long areaB = static_cast<long long>(b.rect.w) * b.rect.h;
            return areaA < areaB;
        });
    
    return result;
}

std::vector<Intersection> IntersectionFinder::getIntersections() const {
    return findAllIntersections();
}