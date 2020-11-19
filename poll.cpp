/*
** EPITECH PROJECT, 2020
** poll
** File description:
** poll.cpp
*/

#include "poll.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <time.h>

void dispHelp()
{
    std::ifstream fs("help");

    if (!fs.fail()) {
        std::cout << fs.rdbuf() << std::endl;
    }
}

bool parseArgs(Datas &datas, char **&args, const int &ac)
{
    std::vector<std::string> numbers;

    for (int i = 1; i < ac; i++) {
        std::string arg = args[i];
        if (arg.size() <= 0) {
            return false;
        }
        for (size_t pos = 0; pos < arg.length(); pos++) {
            if (arg[pos] < '0' || arg[pos] > '9') {
                if (!(i == 3 && arg[pos] == '.')) {
                    return false;
                }
            }
        }
        numbers.push_back(arg);
    }
    if (numbers.size() == 3) {
        datas.pSize = std::stod(numbers[0]);
        datas.sSize = std::stod(numbers[1]);
        datas.percent = std::stod(numbers[2]);
    }
    else {
        return false;
    }
    if (datas.pSize <= 1) {
        return false;
    }
    if (datas.sSize >= datas.pSize || datas.sSize <= 0) {
        return false;
    }
    if (datas.percent < 0 || datas.percent > 100) {
        return false;
    }
    return true;
}

double computeMin(const double &nb)
{
    double result = 0;

    if (nb >= 0) {
        result = nb;
    }
    return result;
}

double computeMax(const double &nb)
{
    double result = 100;

    if (nb <= 100) {
        result = nb;
    }
    return result;
}

bool displayResults(Datas &datas)
{
    std::cout << std::setprecision(0) << std::fixed;
    std::cout << "Population size:         " << datas.pSize << std::endl;
    std::cout << "Sample size:             " << datas.sSize << std::endl;
    
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "Voting intentions:       " << datas.percent << "%" << std::endl;

    datas.percent /= 100;
    double var = ((datas.percent * (1 - datas.percent)) / datas.sSize) * ((datas.pSize - datas.sSize) / (datas.pSize - 1));
    std::cout << std::setprecision(6) << std::fixed;
    std::cout << "Variance:                " << var << std::endl;

    datas.percent *= 100;
    double percent = 196 * std::sqrt(var);
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "95% confidence interval: [" << computeMin(datas.percent - percent) << "%; " << computeMax(datas.percent + percent) << "%]" << std::endl;

    percent = 258 * std::sqrt(var);
    std::cout << "99% confidence interval: [" << computeMin(datas.percent - percent) << "%; " << computeMax(datas.percent + percent) << "%]" << std::endl;
    return true;
}

int poll(int ac, char **&args)
{
    int result = MY_SUCCESS;
    Datas datas;

    if (ac == 2) {
        std::string arg(args[1]);
        if (ac == 2 && arg == "-h") {
            dispHelp();
        }
        else {
            return MY_ERROR;
        }
    }
    else if (ac == 4) {
        if (!parseArgs(datas, args, ac) || !displayResults(datas)) {
            return MY_ERROR;
        }
    }
    else
        result = MY_ERROR;
    return result;
}