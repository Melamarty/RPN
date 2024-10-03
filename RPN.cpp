#include "RPN.hpp"

std::string trim(const std::string &s)
{
    size_t start = 0;
    size_t end = s.length();

    while (start < end && s[start] == ' ') {
        ++start;
    }

    while (end > start && (s[end - 1] == ' ')) {
        --end;
    }

    return s.substr(start, end - start);
}

std::list<std::string> split(std::string s, char del)
{
    std::stringstream ss(s);
    std::string word;
    std::list <std::string> tokens;

    while (!ss.eof())
    {
        std::getline(ss, word, del);
        tokens.push_back(trim(word));
    }
    return tokens;
}

bool isoperator(std::string token)
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool valid_token(std::string &token)
{
    if (token.length() != 1)
        return (false);
    if (!isoperator(token) && !isdigit(token[0]))
        return (false);
    return true;
}

bool validList(std::list<std::string> &tokens)
{
    std::list <std::string>::iterator it;
    int i = 0;
    
    for (it = tokens.begin(); it != tokens.end(); ++it)
    {
        if (((std::string)*it).empty())
            continue;
        if (i <= 1)
        {
            if (isoperator(*it))
                return false;
        }
        else
        {
            if (!(i % 2) && !isoperator(*it))
                return false;
            if ((i % 2) && isoperator(*it))
                return false;
        }
        i++;
    }
    if (i == 1)
        return true;
    if (i < 3 || i %2 == 0)
        return false;
    return true;
}

std::stack<std::string> parseNotation(const std::string &s)
{
    std::list<std::string> tokens = split(s, ' ');
    std::stack<std::string> stack;
    std::list <std::string>::iterator it;

    for (it = tokens.begin(); it != tokens.end(); ++it)
    {
        if (((std::string)(*it)).empty())
            continue;
        if (!valid_token(*it))
            throw std::runtime_error("an invalid token found");
        stack.push(*it);
    }
    return stack;
}

void displayStack(std::stack<std::string> &stack)
{
    if (!stack.empty())
    {
        std::cout << stack.top() << std::endl;
        stack.pop();
        displayStack(stack);
    }
}

double doOp(double nb1, double nb2, const std::string &op)
{
    if (op == "+")
        return nb1 + nb2;
    if (op == "-")
        return nb1 - nb2;
    if (op == "*")
        return nb1 * nb2;
    if (op == "/")
    {
        if (nb2 == 0)
            throw std::runtime_error("division by zero");
        return nb1 / nb2;
    }
    throw std::runtime_error("invalid operator");
}

double rpn(std::stack<std::string> &st)
{
    if (st.empty())
        throw std::runtime_error("invalid expression");

    std::string token = st.top();
    st.pop();

    if (token == "+" || token == "-" || token == "*" || token == "/")
    {
        double nb2 = rpn(st);
        double nb1 = rpn(st);
        return doOp(nb1, nb2, token);
    }
    return atof(token.c_str());
}
