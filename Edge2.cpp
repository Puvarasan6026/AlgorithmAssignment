#include <iostream>
#include <vector>
#include <limits.h>
#include <stdio.h>
#include "Classes.h"

#define V 10

bool Edge2::connects(Node* node1, Node* node2)
{
    return (
        (node1 == this->node1 &&
        node2 == this->node2) ||
        (node1 == this->node2 &&
        node2 == this->node1));
}
