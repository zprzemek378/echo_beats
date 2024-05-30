//
// Created by Przemysław Zieliński on 28.05.2024.
//

#ifndef ECHO_BEATS_SEQUENCE_H
#define ECHO_BEATS_SEQUENCE_H

#include <vector>
#include <random>

class Sequence {
public:
    Sequence();
    void addElement();
    int getElement(int index);
    void reset();
private:
    std::vector<int> sequence;
};


#endif //ECHO_BEATS_SEQUENCE_H
