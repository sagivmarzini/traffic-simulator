#pragma once

#include "Graph.h"

class RoadNetwork
{
public:
	RoadNetwork(const Graph& graph);

	void setGraph(const Graph& graph);

	void draw(Renderer& renderer) const;

private:
	Graph _graph;
	float _roadWidth = 80.f;
};
