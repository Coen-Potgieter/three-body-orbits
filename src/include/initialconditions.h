#ifndef INITIAL_CONDS_H
#define INITIAL_CONDS_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <any>
#include <iostream>
#include "constants.h"

std::unordered_map<std::string, std::any> lagrangeOrbit();
std::unordered_map<std::string, std::any> eulerOrbit();
std::unordered_map<std::string, std::any> figure8Orbit();
std::unordered_map<std::string, std::any> BroukeA3();
std::unordered_map<std::string, std::any> BroukeA7();

#endif
