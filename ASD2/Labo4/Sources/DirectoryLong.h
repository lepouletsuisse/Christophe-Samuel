//
//  DirectoryLong.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef DirectoryLong_h
#define DirectoryLong_h

#include <string>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <functional>

class DirectoryLong {
private:
    std::string avs;
    std::string name;
    std::string firstname;
    std::string gender;
    std::string birthday;
        
public:
    DirectoryLong();
    DirectoryLong(std::string avs,
                  std::string name,
                  std::string firstname,
                  std::string gender,
                  std::string birthday);
    
    std::string getAvs() const;
    
    //operators
    bool operator ==(const DirectoryLong &that) const;
    friend std::ostream& operator <<(std::ostream&, const DirectoryLong&);
    
    //helper
    static int isNotDigit(int ch) {
        return !std::isdigit(ch);
    }
    
};

namespace std
{
    template <>
    struct hash<DirectoryLong>
    {
        size_t operator()(const DirectoryLong& d) const
        {
            unsigned long avsLong;
            std::string avsCpy(d.getAvs());
            
            //we remove all non-numerical caracters
            avsCpy.erase(std::remove_if(avsCpy.begin(), avsCpy.end(), (int(*)(int)) DirectoryLong::isNotDigit), avsCpy.end());
            
            //convert string to long
            try {
                //we should use std::stol(std::string s) but unfortunately it's not available on MinGW gcc 4.8.1
                avsLong = std::atol(avsCpy.c_str());
            } catch(std::invalid_argument& e) {
                std::cerr << "Not a valid avs number: " << avsCpy << std::endl;
                avsLong = 0L; //default value
            }
            
            //we use stl hash function for long type
            return hash<long>()(avsLong);
        }
    };
}

#endif /* DirectoryLong_h */
