//
// Created by phitherek on 19.11.15.
//

#ifndef OZIEXPLORER_UIVIEW_CONVERTER_CONVERTER_H
#define OZIEXPLORER_UIVIEW_CONVERTER_CONVERTER_H

#include <string>

class Converter {
private:
    std::string _infilename;
    std::string _outfilename;
public:
    Converter(): _infilename(""), _outfilename("") {}
    Converter(std::string infilename, std::string outfilename): _infilename(infilename), _outfilename(outfilename) {}
    void convert();
};


#endif //OZIEXPLORER_UIVIEW_CONVERTER_CONVERTER_H
