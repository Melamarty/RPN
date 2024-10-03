#include "RPN.hpp"

int main (int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error\n";
        return 0;
    }

    try
    {
        std::stack <std::string> stack = parseNotation(av[1]);
        double res = rpn(stack);
        std::cout << res;
    }catch (std::runtime_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}