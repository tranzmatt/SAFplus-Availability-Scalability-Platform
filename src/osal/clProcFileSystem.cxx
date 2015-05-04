/*
 * Copyright (C) 2002-2014 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 *
 * The source code for  this program is not published  or otherwise
 * divested of  its trade secrets, irrespective  of  what  has been
 * deposited with the U.S. Copyright office.
 *
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * For more  information, see  the file  COPYING provided with this
 * material.
 */


#include <string>
#include <fstream>

#include "clLogApi.hxx"
#include "clProcFileSystem.hxx"

namespace SAFplusI
{

ProcFile::ProcFile(const char *fileName)
{
    name = fileName;
}

ProcFile::~ProcFile()
{
}

std::string ProcFile::loadFileContents()
{
    std::ifstream fStr(name.c_str());
    fStr.open(name.c_str());
    
    if(fStr.is_open())
    {
        std::string contents;
        fStr.seekg(0, std::ios::end);
        contents.resize(fStr.tellg());
        fStr.seekg(0, std::ios::beg);
        fStr.read(&contents[0], contents.size());
        fStr.close();
        return contents;
    }

    logError("PROC", "LOAD", "Error in loading contents of the file %s", name.c_str());
    
    // Returning an empty string for error case. 
    // The caller should check it
    return std::string(); 
}

} /* namespace SAFplus */
