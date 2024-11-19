#pragma once

// overall configuration constants

const int DIMENSION = 2;
const int GRID_SIZE = 500;
const double LX = 10;
double DT; //= 1/static_cast<double>(TIME_STEPS);
const double DX = LX / (GRID_SIZE - 1);
const double WAVE_SPEED = 3;

const double CFL_MAX = 0.25;