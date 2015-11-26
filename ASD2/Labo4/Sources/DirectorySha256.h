//
//  DirectorySha256.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//


#ifndef DirectorySha256_h
#define DirectorySha256_h

#include <string>
#include <cctype>
#include <iostream>
#include <functional>

#include "Config.h"
#include "libs/sha256.h"

class DirectorySha256 {
private:
    std::string avs;
    std::string name;
    std::string firstname;
    std::string gender;
    std::string birthday;
    
public:
    DirectorySha256();
    DirectorySha256(std::string avs,
                    std::string name,
                    std::string firstname,
                    std::string gender,
                    std::string birthday);
    
    std::string getAvs() const;
    
    //operators
    bool operator ==(const DirectorySha256 &that) const;
    friend std::ostream& operator <<(std::ostream&, const DirectorySha256&);
    
};

namespace std
{
    template <>
    struct hash<DirectorySha256>
    {
        size_t operator()(const DirectorySha256& d) const
        {
            //we use a sha256 implementation on AVS number
            //src: http://www.zedwood.com/article/cpp-sha256-function
                        
            std::string valCpy = d.getAvs();
            std::vector<unsigned char> hash = sha256AsVector(valCpy);
            
            //we need to reduce the SHA256::DIGEST_SIZE bytes to the size of a size_t (for ex. 8 bytes on a 64bits arch.  or 4 bytes on a 32bits arch.)
            
#if defined(ENV64BIT)
    #warning 64-bit SHA-256
            // 64-bit code here.
			size_t valHash = 0x0000000000000000, tmpHash;
            for(size_t round = 0; round < 4; ++round) {
				size_t shift = round * 8;
				tmpHash  = 0x0000000000000000;
				tmpHash |= (size_t)(hash[shift + 0]  & 0x00000000000000FF) << 0;
				tmpHash |= (size_t)(hash[shift + 1]  & 0x00000000000000FF) << 8;
				tmpHash |= (size_t)(hash[shift + 2]  & 0x00000000000000FF) << 16;
				tmpHash |= (size_t)(hash[shift + 3]  & 0x00000000000000FF) << 24;
				tmpHash |= (size_t)(hash[shift + 4]  & 0x00000000000000FF) << 32;
				tmpHash |= (size_t)(hash[shift + 5]  & 0x00000000000000FF) << 40;
				tmpHash |= (size_t)(hash[shift + 6]  & 0x00000000000000FF) << 48;
				tmpHash |= (size_t)(hash[shift + 7]  & 0x00000000000000FF) << 56;
				valHash  = valHash ^ tmpHash; //xor
			}
#elif defined (ENV32BIT)
    #warning 32-bit SHA-256
            // 32-bit code here.
            size_t valHash = 0x00000000, tmpHash;
			for(size_t round = 0; round < 8; ++round) {
				size_t shift = round * 4;
				tmpHash  = 0x00000000;
				tmpHash |= (size_t)(hash[shift + 0]  & 0x000000FF) << 0;
				tmpHash |= (size_t)(hash[shift + 1]  & 0x000000FF) << 8;
				tmpHash |= (size_t)(hash[shift + 2]  & 0x000000FF) << 16;
				tmpHash |= (size_t)(hash[shift + 3]  & 0x000000FF) << 24;
				valHash  = valHash ^ tmpHash; //xor
			}
#else
    // CANNOT DETERMINE ENV
	#error "Must define either ENV32BIT or ENV64BIT"
#endif
            return valHash;
        }
    };
}

#endif /* DirectorySha256_h */
