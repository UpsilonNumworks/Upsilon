#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <ion/external.h>
#include <ion/unicode/code_point.h>
#include <ion/unicode/utf8_decoder.h>

namespace Reader
{

bool stringEndsWith(const char* str, const char* end);
int filesWithExtension(const char* extension, Ion::External::Archive::File* files, int filesSize);
void stringNCopy(char* dest, int max, const char* src, int len);
const char * EndOfPrintableWord(const char * word, const char * end);
const char * StartOfPrintableWord(const char * word, const char * start);
  
}
#endif