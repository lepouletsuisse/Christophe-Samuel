//
//  DirectoryStl.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef DirectoryStl_h
#define DirectoryStl_h

#include <string>
#include <cctype>
#include <iostream>
#include <functional>

class DirectoryStl {
private:
    std::string avs;
    std::string name;
    std::string firstname;
    std::string gender;
    std::string birthday;
    
public:
    DirectoryStl();
    DirectoryStl(std::string avs,
                   std::string name,
                   std::string firstname,
                   std::string gender,
                   std::string birthday);
    
    std::string getAvs() const;
    
    //operators
    bool operator ==(const DirectoryStl &that) const;
    friend std::ostream& operator <<(std::ostream&, const DirectoryStl&);
    
};

namespace std
{
    template <>
    struct hash<DirectoryStl>
    {
        size_t operator()(const DirectoryStl& d) const
        {
            //we use stl hash function for int string
            return hash<std::string>()(d.getAvs());
            
        }
    };
}

#endif /* DirectoryStl_h */
