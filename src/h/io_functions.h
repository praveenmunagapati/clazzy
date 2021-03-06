#ifndef __CLAZZY_IO_FUNCTIONS__
#define __CLAZZY_IO_FUNCTIONS__

#include <iostream>
#include <fstream>
#include <string>

namespace clazzy {
    // returns true iff:
    // - the path already exists and is a directory
    // - the path did not exist and a directory was created
    bool chk_mkdir(const std::string &);
    // does the following
    // - creates or opens a file into the passed ofstream object (if it cannot, returns false)
    // - writes a notification at the top of the file using the given comment characters
    // - returns true (assuming the rest went well)
    bool open_file(const std::string &, std::ofstream &, const std::string &); 
}

#endif
