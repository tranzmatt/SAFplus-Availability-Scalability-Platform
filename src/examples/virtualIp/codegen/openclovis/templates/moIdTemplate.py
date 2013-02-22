import string
from string import Template

mainTemplate = Template("""\
/******************************************************************************
 *
 * clMOID.h
 *
 ******************************************************************************
 * This code is auto-generated by OpenClovis IDE Version 3.1
 *
 ***************************** Description ************************************
 *
 * 
 *****************************************************************************/
#ifndef _CL_MOID__H_
#define _CL_MOID_H_
#ifdef __cplusplus
extern "C"
{
#endif

${moIDs}

#ifdef __cplusplus
}
#endif
#endif /* _CL_MOID_H_*/

""")

idTemplate = Template("""\
#define ${moIdString} "${moId}"
""")