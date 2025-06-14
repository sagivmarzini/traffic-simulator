#include "Segment.h"

Segment::Segment(const Point& p1, const Point& p2)
	: p1(p1), p2(p2)
{
}

void Segment::draw(Renderer& renderer) const
{
	renderer.drawLine(p1, p2, (int)Renderer::Default::LineWidth);
}

bool Segment::operator==(const Segment& other) const
{
	return contains(other.p1) && contains(other.p2);
}

bool Segment::contains(const Point& point) const
{
	return p1 == point || p2 == point;
}