//
//  DirectoryIntAVS.cpp
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#include "DirectoryInt.h"

DirectoryInt::DirectoryInt() {}

DirectoryInt::DirectoryInt(std::string avs,
                             std::string name,
                             std::string firstname,
                             std::string gender,
                             std::string birthday) : avs(avs), name(name), firstname(firstname), gender(gender), birthday(birthday) {
    
}

std::string DirectoryInt::getAvs() const {
    return this->avs;
}

//operators

bool DirectoryInt::operator ==(const DirectoryInt &that) const {
    return this->avs == that.avs;
}

std::ostream& operator <<(std::ostream& os, const DirectoryInt& mi) {
    os << mi.name << " " << mi.firstname << " " << mi.avs;
    return os;
}
