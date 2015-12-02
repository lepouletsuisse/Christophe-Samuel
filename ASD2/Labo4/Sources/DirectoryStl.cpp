//
//  DirectoryStl.cpp
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#include "DirectoryStl.h"

DirectoryStl::DirectoryStl() {}

DirectoryStl::DirectoryStl(std::string avs,
                               std::string name,
                               std::string firstname,
                               std::string gender,
                               std::string birthday) : avs(avs), name(name), firstname(firstname), gender(gender), birthday(birthday) {
}

std::string DirectoryStl::getAvs() const {
    return this->avs;
}

//operators

bool DirectoryStl::operator ==(const DirectoryStl &that) const {
    return this->avs == that.avs;
}

std::ostream& operator <<(std::ostream& os, const DirectoryStl& mi) {
    os << mi.name << " " << mi.firstname << " " << mi.avs;
    return os;
}
