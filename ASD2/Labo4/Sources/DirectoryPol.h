//
//  DirectoryPol.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef DirectoryPol_h
#define DirectoryPol_h

#include <string>
#include <cctype>
#include <iostream>
#include <functional>

template <unsigned int N>
class DirectoryPol {
private:
    std::string avs;
    std::string name;
    std::string firstname;
    std::string gender;
    std::string birthday;
    
public:
    
    DirectoryPol() {}
    
    DirectoryPol(std::string avs,
                 std::string name,
                 std::string firstname,
                 std::string gender,
                 std::string birthday) : avs(avs), name(name), firstname(firstname), gender(gender), birthday(birthday) {
    }
    
    std::string getAvs() const {
        return this->avs;
    }
    
    std::string getName() const {
        return this->name;
    }
    
    std::string getFirstname() const {
        return this->firstname;
    }
    
    std::string getGender() const {
        return this->gender;
    }
    
    std::string getBirthday() const {
        return this->birthday;
    }
    
    //operators
    friend std::ostream& operator <<(std::ostream& os, const DirectoryPol<N>& mi) {
		os << mi.name << " " << mi.firstname << " " << mi.avs;
		return os;
	}
    
    bool operator ==(const DirectoryPol &that) const {
        return this->avs == that.avs;
    }
    
};

//hash function
namespace std
{
    template <unsigned int N>
    struct hash<DirectoryPol<N>>
    {
        size_t operator()(const DirectoryPol<N>& d) const
        {
            //we use polynomial compression
            size_t h = 0L;
            size_t z = N;
            
            std::string avs = d.getAvs();
            for(int i = 0; i < avs.length(); ++i) {
                h = (z*h) + avs[i];
            }
            
            return h;
        }
    };
}

#endif /* DirectoryPol_h */
