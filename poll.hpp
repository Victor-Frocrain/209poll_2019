/*
** EPITECH PROJECT, 2020
** poll
** File description:
** poll.hpp
*/

#ifndef POLL_HPP_
#define POLL_HPP_

#include <vector>
#include <map>

#define MY_ERROR 84
#define MY_SUCCESS 0

int poll(int ac, char **&args);

class Datas {
    public:
    double pSize;
    double sSize;
    double percent;
};

#endif /* POLL_HPP_ */
