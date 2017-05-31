#ifndef TRASHCAN_H
#define TRASHCAN_H

#include "location.h"

class trashCan : public location {
public:
    trashCan();
    int getUses();

private:
    int uses;
};

#endif // TRASHCAN_H
