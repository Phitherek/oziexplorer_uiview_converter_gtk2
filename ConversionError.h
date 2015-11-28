//
// Created by phitherek on 19.11.15.
//

#ifndef OZIEXPLORER_UIVIEW_CONVERTER_CONVERSIONERROR_H
#define OZIEXPLORER_UIVIEW_CONVERTER_CONVERSIONERROR_H

#include <exception>
#include <string>

class ConversionError: public std::exception {
private:
    std::string _what;
public:
    ConversionError(std::string what);

    virtual ~ConversionError();

    virtual const char *what() const noexcept;
};


#endif //OZIEXPLORER_UIVIEW_CONVERTER_CONVERSIONERROR_H
