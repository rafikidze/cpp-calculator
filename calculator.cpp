#include <iostream>
#include <string>
#include <cmath>

#include "calculator.h"

bool ReadNumber(Number& result)
{
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    } 
    return true;
}

bool RunCalculatorCycle()
{
    Number first_number = 0;
     
    if (ReadNumber(first_number)) {
        std::string command;
        Number second_number = 0;
        Number saving_number = 0;
        bool was_saving = false;

        while (true)
        {
            std::cin >> command;
            if (command == "+") {
                if (!ReadNumber(second_number)) break;
                first_number += second_number;
            }
            else if (command == "-") {
                if (!ReadNumber(second_number)) break;
                first_number -= second_number;
            }
            else if (command == "*") {
                if (!ReadNumber(second_number)) break;
                first_number *= second_number;
            }
            else if (command == "/") {
                if (!ReadNumber(second_number)) break;
                first_number /= second_number;
            }
            else if (command == "**") {
                if (!ReadNumber(second_number)) break;
                first_number = std::pow(first_number, second_number);
            }
            else if (command == ":") {
                if (!ReadNumber(second_number)) break;
                first_number = second_number;
            }
            else if (command == "c") {
                first_number = 0;
            }
            else if (command == "=") {
                std::cout << first_number << std::endl;
            }
            else if (command == "s") {
                was_saving = true;
                saving_number = first_number;
            }
            else if (command == "l") {
                if (!was_saving) {
                    std::cerr << "Error: Memory is empty" << std::endl;
                    break;
                }
                first_number = saving_number;
            }
            else if (command == "q") {
                return true;
            }
            else {
                std::cerr << "Error: Unknown token " << command << std::endl;
                break;
            }
        }
    }
    return false;
}