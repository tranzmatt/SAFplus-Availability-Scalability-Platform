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
#include <iostream>
#include "MsgHandlerProtocols.hxx"

using namespace std;

namespace SAFplus
{

    MsgHandlerProtocols::MsgHandlerProtocols()
    {
        // TODO Auto-generated constructor stub

    }

    MsgHandlerProtocols::~MsgHandlerProtocols()
    {
        // TODO Auto-generated destructor stub
    }

    void
    MsgHandlerProtocols::msgHandler(ClIocAddressT from, MsgServer* svr, ClPtrT msg, ClWordT msglen, ClPtrT cookie)
    {
        cout<<"Testing handle from:["<<from.iocPhyAddress.nodeAddress<<",";
        cout<<from.iocPhyAddress.portId<<"]"<<endl;
    }

} /* namespace SAFplus */