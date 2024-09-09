// cli.cpp - Function declarations for the eng_format class
// 
// 09-Sep-24  F.Khan         Created.
#ifndef _ENG_FORMAT_H_
#define _ENG_FORMAT_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
#include "conio.h"

class eng_format
{
private:
    /* data */
    std::string Api_Key;

public:
    eng_format(/* args */);
    ~eng_format();
    void Api_Call();
    void Save_File();

};

#endif //_ENG_FORMAT_ H_
