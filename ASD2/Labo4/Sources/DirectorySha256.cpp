//
//  DirectorySha256.cpp
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#include "DirectorySha256.h"

DirectorySha256::DirectorySha256() {}

DirectorySha256::DirectorySha256(std::string avs,
                                 std::string name,
                                 std::string firstname,
                                 std::string gender,
                                 std::string birthday) : avs(avs), name(name), firstname(firstname), gender(gender), birthday(birthday) {
}

std::string DirectorySha256::getAvs() const {
    return this->avs;
}

//operators

bool DirectorySha256::operator ==(const DirectorySha256 &that) const {
    return this->avs == that.avs;
}

std::ostream& operator <<(std::ostream& os, const DirectorySha256& mi) {
    os << mi.name << " " << mi.firstname << " " << mi.avs;
    return os;
}
