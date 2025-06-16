#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "Node.h"

struct Segment
{
	Node p1;
	Node p2;

	Segment() = default;
	Segment(const Node& p1, const Node& p2);

	void draw(Renderer& renderer, int alpha = 255) const;

	bool operator==(const Segment& other) const;
	bool contains(const Node& point) const;
};