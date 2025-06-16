#pragma once

#include "json.hpp"
#include "Point.h"
#include "Segment.h"

using json = nlohmann::json;

// Point to/from JSON
inline void to_json(json& j, const Point& p) {
	j = json{ {"x", p.x}, {"y", p.y} };
}

inline void from_json(const json& j, Point& p) {
	p.x = j.at("x").get<float>();
	p.y = j.at("y").get<float>();
}

// Segment to/from JSON
inline void to_json(json& j, const Segment& s) {
	j = json{ {"p1", s.p1}, {"p2", s.p2} };
}

inline void from_json(const json& j, Segment& s) {
	s.p1 = j.at("p1").get<Point>();
	s.p2 = j.at("p2").get<Point>();
}
