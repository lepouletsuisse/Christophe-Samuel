//
//  DirectoryCity.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef DirectoryCity_h
#define DirectoryCity_h

#include <string>
#include <cctype>
#include <iostream>
#include <functional>

#include "Config.h"
#include "libs/city.h"

class DirectoryCity {
private:
    std::string avs;
    std::string name;
    std::string firstname;
    std::string gender;
    std::string birthday;
    
public:
    DirectoryCity();
    DirectoryCity(std::string avs,
                    std::string name,
                    std::string firstname,
                    std::string gender,
                    std::string birthday);
    
    std::string getAvs() const;
    
    //operators
    bool operator ==(const DirectoryCity &that) const;
    friend std::ostream& operator <<(std::ostream&, const DirectoryCity&);
    
};

namespace std
{
    template <>
    struct hash<DirectoryCity>
    {
        size_t operator()(const DirectoryCity& d) const
        {
            //using city hash function, implemented by Google
            //source: https://github.com/google/cityhash
            std::string valCpy = d.getAvs();
#if defined(ENV64BIT)
    #warning 64-bit CityHash64
            return CityHash64(valCpy.c_str(), valCpy.length());
#elif defined (ENV32BIT)
    #warning 32-bit CityHash32
            return CityHash32(valCpy.c_str(), valCpy.length());
#else
            // CANNOT DETERMINE ENV
#error "Must define either ENV32BIT or ENV64BIT"
#endif
        }
    };
}

#endif /* DirectoryCity_h */
