
#include "sc2api/sc2_micro.h"

#include "sc2api/sc2_common.h"
#include "sc2api/sc2_unit.h"

namespace sc2 {
Boxing::Boxing(sc2::Point2D& p1, sc2::Point2D& p2) {
    OrderPoints(p1, p2);
}

Boxing::Boxing(const Unit* unit, Point2D& offset) {
    Point2D origin = unit->pos;
    Point2D p1 = origin - offset;
    Point2D p2 = origin + offset;
    OrderPoints(p1, p2);
}
Boxing::Boxing(const Unit* unit, float offset) {
    Point2D origin = unit->pos;
    Point2D pt_offset = {offset, offset};
    Point2D p1 = origin - pt_offset;
    Point2D p2 = origin + pt_offset;
    OrderPoints(p1, p2);
}

bool Boxing::IsInBox(Boxing& box, Point2D& point) {
    if (box.x_min <= point.x && point.x <= box.x_max) {
        if (box.y_min <= point.y && point.y <= box.y_max) {
            return true;
        }
    }
    return false;
}

bool Boxing::IsInBox(Boxing& box, Unit* unit) {
    Point2D point = {unit->pos.x, unit->pos.y};
    return Boxing::IsInBox(box, point);
}

void Boxing::OrderPoints(Point2D& p1, Point2D& p2) {
    if (p1.x <= p2.x) {
        x_min = p1.x;
        x_max = p2.x;
    } else {
        x_min = p2.x;
        x_max = p1.x;
    }
    if (p1.y <= p2.y) {
        y_min = p1.y;
        y_max = p2.y;
    } else {
        y_min = p2.y;
        y_max = p1.y;
    }
}

std::ostream& operator<<(std::ostream& os, Boxing& box) {
    os << "x_min: " << box.x_min << std::endl
       << "x_max: " << box.x_max << std::endl
       << "y_min: " << box.y_min << std::endl
       << "y_max: " << box.y_max << std::endl;
    return os;
}
}  // namespace sc2
