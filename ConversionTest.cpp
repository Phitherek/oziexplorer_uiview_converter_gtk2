//
// Created by phitherek on 20.11.15.
//
#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "Converter.h"
#include "ConversionError.h"

using namespace std;

int main() {
    try {
        cout << "ConversionTest for OziExplorer to UI-View Converter v. 0.2 (C) 2015 by Phitherek_ SO9PH" << std::endl;
        try {
            Converter c("siatka.map", "siatka.inf");
            c.convert();
        } catch(ConversionError& e) {
            cerr << "Caught ConversionError: " << e.what() << std::endl;
            cout << "Failure!" << std::endl;
            return EXIT_FAILURE;
        }
        cout << "Success!" << std::endl;
        return EXIT_SUCCESS;
    } catch(std::exception& e) {
        cout << "Caught exception: " << typeid(e).name() << ": " << e.what() << endl;
        return EXIT_FAILURE;
    }
}