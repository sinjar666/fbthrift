/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef  _module_CONSTANTS_H
#define  _module_CONSTANTS_H

#include "module_types.h"



struct module_constants {
};

struct  __attribute__((__deprecated__("module_constants_codemod is a transitional class only intended for codemods from the deprecated moduleConstants to module_constants. Consider switching to the latter as soon as possible."))) module_constants_codemod {
};

class __attribute__((__deprecated__("moduleConstants suffers from the 'static initialization order fiasco' (https://isocpp.org/wiki/faq/ctors#static-init-order) and may CRASH your program. Instead, use module_constants::CONSTANT_NAME()"))) moduleConstants {
public:
  moduleConstants();

};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

extern const moduleConstants __attribute__((__deprecated__("g_module_constants suffers from the 'static initialization order fiasco' (https://isocpp.org/wiki/faq/ctors#static-init-order) and may CRASH your program. Instead, use module_constants::CONSTANT_NAME()"))) g_module_constants;

#pragma GCC diagnostic pop



#endif
