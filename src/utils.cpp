#include "utils.h"

void UTILS::HeartsLoop(Array<Hearts>* hearts)
{

    for (auto heart = hearts->begin(); heart != hearts->end();)
    {
        if (heart->Update())
        {
            heart = hearts->erase(heart);
            //Print << U"HP UP!";
            continue;
        }

        ++heart;
    }
}