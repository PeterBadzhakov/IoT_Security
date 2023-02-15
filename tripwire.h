#ifndef TRIPWIRE_H
#define TRIPWIRE_H

struct Tripwire
{
    static const int tripwirePin = 0x17;
    int connected = 0;
};

void tripwireInit();
int tripwireCheck();

#endif // TRIPWIRE_H
