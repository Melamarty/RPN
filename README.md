
---

# Reverse Polish Notation (RPN) Calculator

This program implements a Reverse Polish Notation (RPN) calculator with a recursive aproach. It processes an input string that contains a mathematical expression in RPN format, then evaluates the expression using a stack-based approach. This README explains how the main components work, focusing primarily on the core RPN evaluation logic.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Functions Overview](#functions-overview)
  - [rpn](#rpn-function)
  - [doOp](#doop-function)
---

## Installation

Simply compile and run the program using any standard C++ compiler.

```bash
g++ -o RPN rpn_calculator.cpp
./RPN "expression"
```

or if you have make installed you can run

```bash
make
./RPN "expression"
```

## Usage

The RPN calculator takes a space-separated RPN expression, such as:

```
"3 4 + 2 * 7 /"
```

This expression corresponds to the following infix operation:

```
(3 + 4) * 2 / 7
```

To use it, you can provide an RPN string as input to `parseNotation`, which tokenizes the expression into a stack, and then pass that stack to `rpn` for evaluation.

---

In this description, I will focus on explaining the rpn function and related operations because parseNotation, split, and trim are primarily for parsing the input arguments. You can modify them as needed or simply initialize your stack in the main function.

## Functions Overview

### `rpn` Function

The `rpn` function is the core of this program. It evaluates an RPN expression using a stack-based approach. The function recursively processes operators and operands, performing operations as they are encountered.

#### How it works:

1. **Base Case**: If the token is a number, it is converted into a double and returned.
2. **Recursive Case**: If the token is an operator (`+`, `-`, `*`, `/`), it pops the next two operands from the stack (recursively), applies the operation, and returns the result.
3. **Error Handling**: It throws an error if the expression is invalid (e.g., division by zero or invalid tokens).

```cpp
double rpn(std::stack<std::string> &st)
{
    if (st.empty())
        throw std::runtime_error("invalid expression");

    std::string token = st.top();
    st.pop();

    if (token == "+" || token == "-" || token == "*" || token == "/")
    {

        // We take nb2 first and then nb1 because RPN works that way.
        // For example, in the expression "3 4 -", the result is -1,
        // which means nb2 = 4 and nb1 = 3. So, 3 - 4 = -1.
        // i hope you understand (^_^)

        // Second operand
        double nb2 = rpn(st);
        // First operand
        double nb1 = rpn(st);
        // Perform operation
        return doOp(nb1, nb2, token);
    }
    // Token is a number, convert to double
    return atof(token.c_str());
}
```

#### Example:
For an input stack containing `3 4 + 2 *`, the function evaluates as follows:

1. `+` is an operator, so it pops `4` and `3`, adds them, and pushes the result (`7`).
2. `*` is an operator, so it pops `7` and `2`, multiplies them, and returns the result (`14`).

---

### `doOp` Function

The `doOp` function is responsible for performing basic arithmetic operations (`+`, `-`, `*`, `/`). It takes two operands and an operator as input and returns the result of the operation. It also handles division by zero by throwing an exception.

```cpp
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
```

### License

This project is open-source and available under the MIT License.

---

Let me know if you'd like any additional information or changes!
