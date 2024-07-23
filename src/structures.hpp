#pragma once

#include "sim_config.hpp"

typedef struct InstantGrid
{
	double mesh[GRID_SIZE][GRID_SIZE];
} InstantGrid;

typedef struct CalculationMatrix
{
	InstantGrid instant[3];
} CalculationMatrix;