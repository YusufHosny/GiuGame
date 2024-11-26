#include "IdGenerator.h"

unsigned int IdGenerator::nextId = 0;

int IdGenerator::generateId() {
    return nextId++;
}
