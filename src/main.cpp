#include <array>
#include <iostream>

#include "constants.h"

using Constants::CcEnum;

int main()
{
    std::array<int, 10> arr{ 31, 28, 47 };
    std::cout << arr[CcEnum::CLASS_NAME] << std::endl;
    std::cout << arr[CcEnum::SPELL_NAME] << std::endl;
}
