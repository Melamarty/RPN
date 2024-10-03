#pragma once

#include <iostream>

#include <list>
#include <iterator>
#include <sstream>
#include <stack>

std::stack<std::string> parseNotation(const std::string &s);
std::string trim(const std::string &s);
std::list<std::string> split(std::string s, char del);
void displayStack(std::stack<std::string> &stack);
double rpn(std::stack<std::string> &st);