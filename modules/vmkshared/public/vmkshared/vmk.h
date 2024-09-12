// std requires
#include <mutex>
#include <thread>

#include <memory>
#include <string>
#include <array>
#include <queue>
#include <vector>
#include <fstream>
#include <functional>
#include <unordered_map>


#ifndef __VMK_H__
#define __VMK_H__

// if WIN32 is defined, vmk will be compiled to exe, else, to elf

#ifdef VMK_EXPORT

#ifdef WIN32
#define VMK_API __declspec(dllexport)
#else
#define VMK_API  __attribute__((visibility ("default")))
#endif // WIN32

#else 

#ifdef WIN32
#define VMK_API __declspec(dllimport)
#else
#define VMK_API
#endif // WIN32

#endif // VMK_EXPORT


#endif // __VMK_H__
