#include "Segment.h"

Segment::Segment(const Point& p1, const Point& p2)
	: p1(p1), p2(p2)
{
	if (p1 == p2)
		throw std::invalid_argument("Two points of segments cannot be the same");
}

void Segment::draw(Renderer& renderer, int alpha) const
{
	renderer.drawLine(p1, p2, (int)Renderer::Default::LineWidth, sf::Color(255, 255, 255, alpha));
}

bool Segment::operator==(const Segment& other) const
{
	return contains(other.p1) && contains(other.p2);
}

bool Segment::contains(const Point& point) const
{
	return p1 == point || p2 == point;
}