//
// Created by Przemysław Zieliński on 28.05.2024.
//

#include "Sequence.h"


Sequence::Sequence() {
}

void Sequence::reset() {
    sequence.clear();
}

void Sequence::addElement() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 7);

    int random_number = dist(gen);

    sequence.push_back(random_number);
}

int Sequence::getElement(int index) {
    return sequence[index];
}