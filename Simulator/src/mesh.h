#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <stdlib.h>

#include "particles.h"
#include "triangles.h"
#include "tetrahedrons.h"
#include "bounds.h"

class Mesh
{
public:
	std::shared_ptr<Particles> vertices;
	std::shared_ptr<Triangles> triangles;
	std::shared_ptr<Tetrahedrons> tetras;
	Bounds AABB;

	//create a grid

	Mesh( float _gridCellSize, float density = 1000.0f, float poissonsRatio = 0.3f, float youngsModulus = 500000.0f ) ;
	Mesh( std::shared_ptr<Particles> _vertices, std::shared_ptr<Triangles> _triangles, 
		  std::shared_ptr<Tetrahedrons> _tetras, float _gridCellSize );

	void calcBounds();
	void updateBounds();

private:
	float gridCellSize;
	float density;
	float poissonsRatio;
	float youngsModulus;
};