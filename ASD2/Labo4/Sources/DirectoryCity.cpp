//
//  DirectoryCity.cpp
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#include "DirectoryCity.h"


DirectoryCity::DirectoryCity() {}

DirectoryCity::DirectoryCity(std::string avs,
                                 std::string name,
                                 std::string firstname,
                                 std::string gender,
                                 std::string birthday) : avs(avs), name(name), firstname(firstname), gender(gender), birthday(birthday) {
}

std::string DirectoryCity::getAvs() const {
    return this->avs;
}

//operators

bool DirectoryCity::operator ==(const DirectoryCity &that) const {
    return this->avs == that.avs;
}

std::ostream& operator <<(std::ostream& os, const DirectoryCity& mi) {
    os << mi.name << " " << mi.firstname << " " << mi.avs;
    return os;
}
