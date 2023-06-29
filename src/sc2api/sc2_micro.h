#include "sc2api/sc2_common.h"
#include "sc2api/sc2_unit.h"

namespace sc2 {
struct Boxing {
    float x_min = 0;
    float x_max = 0;
    float y_min = 0;
    float y_max = 0;

    constexpr Boxing() = default;
    Boxing(Point2D& p1, Point2D& p2);
    Boxing(const Unit* unit, Point2D& offset);
    Boxing(const Unit* unit, float offset);
    static bool IsInBox(Boxing& box, Point2D& point);
    static bool IsInBox(Boxing& box, Unit* unit);
    void OrderPoints(Point2D& p1, Point2D& p2);
};
std::ostream& operator<<(std::ostream& os, Boxing& box);
}  // namespace sc2
