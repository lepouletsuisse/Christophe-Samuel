//
//  Config.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 17.11.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef CONFIG_H
#define CONFIG_H

// we need to determine the system environment
// source: http://stackoverflow.com/a/12338526
// Check windows
#if _WIN32 || _WIN64
    #if _WIN64
        #define ENV64BIT
    #else
        #define ENV32BIT
    #endif
#endif

// Check GCC
#if __GNUC__
    #if __x86_64__ || __ppc64__
        #define ENV64BIT
    #else
        #define ENV32BIT
    #endif
#endif

#endif /* CONFIG_H */
