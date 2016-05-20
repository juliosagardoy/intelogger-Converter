/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileManager.h
 * Author: julio
 *
 * Created on April 27, 2016, 12:59 PM
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>

class FileManager {
public:
    FileManager();
    FileManager(const FileManager& orig);
    virtual ~FileManager();
private:
    std::ofstream mFile;         // Output file
};

#endif /* FILEMANAGER_H */

