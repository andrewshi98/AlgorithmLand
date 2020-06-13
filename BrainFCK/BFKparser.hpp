#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "BFKengine.hpp"

namespace parse {

    std::vector<script::Command*> *parse(std::ifstream &is);

}