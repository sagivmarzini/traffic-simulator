#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "Point.h"

struct Segment
{
	Point p1;
	Point p2;

	Segment(const Point& p1, const Point& p2);

	void draw(Renderer& renderer, int alpha = 255) const;

	bool operator==(const Segment& other) const;
	bool contains(const Point& point) const;
};