#ifndef PSLEEP_H
#define PSLEEP_H

/*
 * This file offers the sleep method, letting the code being plateform independent
 *
 * */
#if defined (WIN32) || defined (_WIN32)
  #include <windows.h>
  #define sleep(s) Sleep((s)*1000)
#elif defined (__linux) || defined (linux)
  #include <unistd.h>
  #define sleep(s) sleep(s)
#endif

#endif // PSLEEP_H
