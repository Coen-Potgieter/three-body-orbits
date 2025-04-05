
#ifndef INITIAL_CONDS_H
#define INITIAL_CONDS_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <any>
#include "constants.h"

std::unordered_map<std::string, std::any> lagrangeOrbit();
std::unordered_map<std::string, std::any> test();

#endif
