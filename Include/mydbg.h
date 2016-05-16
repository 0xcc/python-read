#ifndef  Py_MYDBG_H
#define  Py_MYDBG_H
#include <Windows.h>
#include <DbgHelp.h>

#include <stdio.h>
#include <stdlib.h>

#include "Python.h"
#include "code.h"
#include "frameobject.h"
#include "eval.h"
#include "opcode.h"
#include "structmember.h"

#include "frameobject.h"


void mydbg_show_instruction_info(PyFrameObject* f,unsigned char instruction,int oparg);
void mydbg_show_evalstack(PyFrameObject *f,PyObject  **stack_pointer);

void mydbg_show_frameinfo(PyFrameObject *f);

void mydbg_show_f_localsplus(PyFrameObject *f,PyObject  **stack_pointer,PyObject **freevars,int oparg);

void mydbg_show_CellObject(PyCellObject* pobj);

void mydbg_show_f_blockstack(PyFrameObject *f);

void mydbg_show_traceback(PyFrameObject *f);


int isDbgFileEx(PyFrameObject* f);
void print_obj(PyObject* pobj);

void mydbg_show_PyTypeObject(PyTypeObject* pObj);

void mydbg_show_PyMethodDef(PyMethodDef *pMethodDef);

void mydbg_show_PyMemberDef(PyMemberDef *pyMemberDef);

void mydbg_show_PyGetSetDef(PyGetSetDef *pyGetSetDef);



//PSYMBOL_INFO mydbg_get_symbol(DWORD64 addr);  



#endif	
 