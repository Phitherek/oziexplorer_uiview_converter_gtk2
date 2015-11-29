//
// Created by phitherek on 29.11.15.
//

#include "Helper.h"

std::string Helper::endline() {
#ifdef _WIN32
    return "\r\n";
#endif
#ifdef __APPLE__
    return "\r";
#endif
return "\n";
}
