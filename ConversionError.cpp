//
// Created by phitherek on 19.11.15.
//

#include "ConversionError.h"

ConversionError::~ConversionError() {

}

const char *ConversionError::what() const noexcept {
    return _what.c_str();
}

ConversionError::ConversionError(std::string what) {
    _what = what;
}
