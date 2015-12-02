//
//  DirectoryWithoutAVS.cpp
//  ASD2_2015
//
//  Created by Fabien Dutoit on 19.10.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#include "DirectoryWithoutAVS.h"

DirectoryWithoutAVS::DirectoryWithoutAVS() {}

DirectoryWithoutAVS::DirectoryWithoutAVS(std::string avs, /* SHOULD NOT BE USED */
                             std::string name,
                             std::string firstname,
                             std::string gender,
                             std::string birthday) : name(name), firstname(firstname), gender(gender), birthday(birthday) {
    
    // we simply ignore AVS value, it's simplier to keep the same interface for testing
}

std::string DirectoryWithoutAVS::getName() const {
    return this->name;
}

std::string DirectoryWithoutAVS::getFirstname() const {
    return this->firstname;
}

std::string DirectoryWithoutAVS::getGender() const {
    return this->gender;
}

std::string DirectoryWithoutAVS::getBirthday() const {
    return this->birthday;
}

//operators

bool DirectoryWithoutAVS::operator ==(const DirectoryWithoutAVS &that) const {
    //we cannot use AVS number, which is unique, to distinguish 2 elements
    return  this->name      == that.name        &&
            this->firstname == that.firstname   &&
            this->gender    == that.gender      &&
            this->birthday  == that.birthday;
}

std::ostream& operator <<(std::ostream& os, const DirectoryWithoutAVS& mi) {
    os << mi.name << " " << mi.firstname << " " << mi.birthday;
    return os;
}
