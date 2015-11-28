//
// Created by phitherek on 20.11.15.
//
#include <iostream>
#include <cstdlib>
#include "Converter.h"
#include "ConversionError.h"

using namespace std;

int main() {
    cout << "ConversionTest for OziExplorer to UI-View Converter v. 0.2 (C) 2015 by Phitherek_ SO9PH" << endl;
    try {
        Converter c("siatka.map", "siatka.inf");
        c.convert();
    } catch(ConversionError& e) {
        cerr << "Caught ConversionError: " << e.what() << endl;
        cout << "Failure!" << endl;
        return EXIT_FAILURE;
    }
    cout << "Success!" << endl;
    return EXIT_SUCCESS;
}