//
//  DirectoryInt.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef DirectoryInt_h
#define DirectoryInt_h

#include <string>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <functional>

class DirectoryInt {
private:
    std::string avs;
    std::string name;
    std::string firstname;
    std::string gender;
    std::string birthday;
    
public:
    DirectoryInt();
    DirectoryInt(std::string avs,
                  std::string name,
                  std::string firstname,
                  std::string gender,
                  std::string birthday);
    
    std::string getAvs() const;
    
    //operators
    bool operator ==(const DirectoryInt &that) const;
    friend std::ostream& operator <<(std::ostream&, const DirectoryInt&);
    
    //helper
    static int isNotDigit(int ch) {
        return !std::isdigit(ch);
    }
    
};

namespace std
{
    template <>
    struct hash<DirectoryInt>
    {
        size_t operator()(const DirectoryInt& d) const
        {
            unsigned int avsInt;
            std::string avsCpy(d.getAvs());
            
            //we remove all non-numerical caracters
            avsCpy.erase(std::remove_if(avsCpy.begin(), avsCpy.end(), (int(*)(int)) DirectoryInt::isNotDigit), avsCpy.end());
            std::string avsCpyTrimmed = avsCpy.substr(3, 9); //the first 3 digits are fixed, the last one is a checksum
            
            //convert string to long
            try {
                //we should use std::stoi(std::string s) but unfortunately it's not available on MinGW gcc 4.8.1
                avsInt = std::atoi(avsCpyTrimmed.c_str());
            } catch(std::out_of_range& e) {
                std::cerr << "Not a valid int: " << avsCpyTrimmed << std::endl;
                avsInt = 0; //default value
            }
            
            //we use stl hash function for int type
            return hash<int>()(avsInt);
        }
    };
}

#endif /* DirectoryInt_h */
