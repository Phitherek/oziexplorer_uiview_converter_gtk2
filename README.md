# OziExplorer to UI-View Converter - GTK+ 2.0 Version
(C) 2015 Phitherek_ SO9PH

## Description

This is a small program that converts OziExplorer .map map file info format to UI-View .inf map file info format. It is written in GTKmm 2.0, so it has an easy to use and descriptive GUI that is compatible with older operating systems.

## Versions

This is a master branch which can contain features that are in testing and/or incomplete. All released versions have their appropriate tags. Current stable version is 0.3-gtk.

## Dependencies

* GTKmm >= 2.4 (dynamic runtime libraries)

## Build dependencies

* CMake >= 3.3

## Building and installing

```
cmake -G"Generator name" .
<then use a build system of your choice>
```

## License

This program is licensed under the MIT License. See LICENSE file for details.

## Changelog

#### v. 0.3-gtk2

* Split into main GTK+ 3.0 version and GTK+ 2.0 compatibility version.

#### v. 0.2

* Fixed coordinate conversion thanks to new information from SP9MZM and SP9TPL.
* Added a delay between the conversions, so that the GUI crashes less often.

#### v. 0.1.2

* Included cstdlib in Converter for std::atof fix.

#### v. 0.1.1

* Fixed build files
* Changed atof to std::atof for Windows builds compatibility in Converter

## Enjoy!