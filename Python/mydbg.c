#include "mydbg.h"
#define EMPTYSTR ""

char* opcodeName[]={
/*		0						1					2					3					4					5					6						7						8						9*/
/*0*/	"STOP_CODE",			"POP_TOP",			"ROT_TWO",			"ROT_THREE" ,		"DUP_TOP" ,			"ROT_FOUR" ,		EMPTYSTR ,				EMPTYSTR			,	EMPTYSTR			,	"NOP",
/*1*/	"UNARY_POSITIVE",		"UNARY_NEGATIVE",	"UNARY_NOT",		"UNARY_CONVERT",	EMPTYSTR		,	"UNARY_INVERT",		EMPTYSTR,				EMPTYSTR		,		EMPTYSTR			,	"BINARY_POWER",
/*2*/	"BINARY_MULTIPLY",		"BINARY_DIVIDE",	"BINARY_MODULO",	"BINARY_ADD",		"BINARY_SUBTRACT",	"BINARY_SUBSCR",	"BINARY_FLOOR_DIVIDE",	"BINARY_TRUE_DIVIDE",	"INPLACE_FLOOR_DIVIDE", "INPLACE_TRUE_DIVIDE",
/*3*/	"SLICE",				EMPTYSTR,			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,				EMPTYSTR,				EMPTYSTR			,	EMPTYSTR,
/*4*/	"STORE_SLICE",			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,				EMPTYSTR,				EMPTYSTR,				EMPTYSTR,
/*5*/	"DELETE_SLICE",			EMPTYSTR,			EMPTYSTR,			EMPTYSTR,			"STORE_MAP",		"INPLACE_ADD",		"INPLACE_SUBTRACT",		"INPLACE_MULTIPLY",		"INPLACE_DIVIDE",		"INPLACE_MODULO",
/*6*/	"STORE_SUBSCR",			"DELETE_SUBSCR",	"BINARY_LSHIFT",	"BINARY_RSHIFT",	"BINARY_AND",		"BINARY_XOR",		"BINARY_OR",			"INPLACE_POWER",		"GET_ITER",				EMPTYSTR,
/*7*/	"PRINT_EXPR",			"PRINT_ITEM",		"PRINT_NEWLINE",	"PRINT_ITEM_TO",	"PRINT_NEWLINE_TO",	"INPLACE_LSHIFT",	"INPLACE_RSHIFT",		"INPLACE_AND",			"INPLACE_XOR",			"INPLACE_OR",
/*8*/	"BREAK_LOOP",			"WITH_CLEANUP",		"LOAD_LOCALS",		"RETURN_VALUE",		"IMPORT_STAR",		"EXEC_STMT",		"YIELD_VALUE",			"POP_BLOCK",			"END_FINALLY",			"BUILD_CLASS",
		/*HAVE_ARGUMENT和STORE_NAME一样*/
/*9*/	"STORE_NAME",			"DELETE_NAME",		"UNPACK_SEQUENCE",	"FOR_ITER",			"LIST_APPEND",		"STORE_ATTR",		"DELETE_ATTR",			"STORE_GLOBAL",			"DELETE_GLOBAL",		"DUP_TOPX",
/*10*/	"LOAD_CONST",			"LOAD_NAME",		"BUILD_TUPLE",		"BUILD_LIST",		"BUILD_SET",		"BUILD_MAP",		"LOAD_ATTR",			"COMPARE_OP",			"IMPORT_NAME",			"IMPORT_FROM",
/*11*/	"JUMP_FORWARD",		"JUMP_IF_FALSE_OR_POP",	"JUMP_IF_TRUE_OR_POP","JUMP_ABSOLUTE",	"POP_JUMP_IF_FALSE","POP_JUMP_IF_TRUE",	"LOAD_GLOBAL",			EMPTYSTR,				EMPTYSTR,				"CONTINUE_LOOP",
/*12*/	"SETUP_LOOP",			"SETUP_EXCEPT",		"SETUP_FINALLY",	EMPTYSTR,			"LOAD_FAST",		"STORE_FAST",		"DELETE_FAST",			EMPTYSTR,				EMPTYSTR,				EMPTYSTR,
/*13*/	"RAISE_VARARGS",		"CALL_FUNCTION",	"MAKE_FUNCTION",	"BUILD_SLICE",		"MAKE_CLOSURE",		"LOAD_CLOSURE",		"LOAD_DEREF",			"STORE_DEREF",			EMPTYSTR,				EMPTYSTR,
/*14*/	"CALL_FUNCTION_VAR",	"CALL_FUNCTION_KW",	"CALL_FUNCTION_VAR_KW","SETUP_WITH",	EMPTYSTR,			"EXTENDED_ARG",		"SET_ADD",				"MAP_ADD"
};


const int dbgFileCnt=2;
char* dbgFileName[]={"E:\\pyproj\\inside python\\B.py","E:\\pyproj\\inside python\\p.py"};

int isDbgFile(char* fileName){
	
	int i=0;
	for (i;i<dbgFileCnt;++i)
	{
		if (strcmp(fileName,dbgFileName[i])==0)
		{
			return 1;
		}
	}

	return 0;
}

int isDbgFileEx(PyFrameObject* f){
	PyStringObject *strobj=(PyStringObject*)(f->f_code->co_filename);
	return isDbgFile(strobj->ob_sval);
}



void print_obj(PyObject* pobj){
	if (pobj==NULL)
	{
		return ;
	}

	if (strcmp(pobj->ob_type->tp_name,"int")==0)
	{
		PyIntObject *pintboj=(PyIntObject* )pobj;
		printf("int: %d",pintboj->ob_ival);
	}else if(strcmp(pobj->ob_type->tp_name,"type")==0){
		//PyTypeObject
		PyTypeObject *ptypeobj=(PyTypeObject*)pobj;
		printf("type name: %s\t metaclass(ob_type):%s\n",ptypeobj->tp_name,pobj->ob_type->tp_name);
		
		
	}else if(strcmp(pobj->ob_type->tp_name,"tuple")==0){	
		printf("%s","tuple : ");

		PyTuple_Dump((PyTupleObject*)pobj,stdout,0);

	}else if(strcmp(pobj->ob_type->tp_name,"dict")==0){
		printf("%s","dict : ");
		PyDict_Dump((PyDictObject*)pobj,stdout,0);
	}else if(strcmp(pobj->ob_type->tp_name,"list")==0){
		printf("%s","list : ");
		PyList_Dump((PyListObject*)pobj,stdout,0);
	}else if(strcmp(pobj->ob_type->tp_name,"cell")==0){
		printf("%s addr 0x%x :","cell : ",pobj);
		print_obj(((PyCellObject*)pobj)->ob_ref);

	}
	else if (strcmp(pobj->ob_type->tp_name,"str")==0){
		PyStringObject *pstrobj=(PyStringObject *)pobj;
		printf("str: %s",pstrobj->ob_sval);
	}
	else{
		PyTypeObject *ptypeobj=(PyTypeObject*)pobj;
		printf("other type object\n");
		printf("tp_name: %s\t ob_type:%s\n",ptypeobj->tp_name,ptypeobj->ob_type->tp_name);
	}

}

void mydbg_show_instruction_info(PyFrameObject* f,unsigned char instruction,int oparg){


	if ( isDbgFileEx(f)){
		PyStringObject *co_name=(PyStringObject*)(f->f_code->co_name);;
		printf("%s : %s ",co_name->ob_sval,opcodeName[instruction]);
		if (HAS_ARG(instruction)){
			if (instruction==MAKE_FUNCTION){
				printf("  arg=%x", oparg);
			}else if (instruction==CALL_FUNCTION)
			{
				printf("  arg=%x ",oparg);
			}
			else{
				printf(" arg=%x",oparg);
			}
		}
		printf("\n");
	}
}

void mydbg_show_evalstack(PyFrameObject* f,PyObject  **stack_pointer){
	
	PyCodeObject *co_code=(PyCodeObject *)f->f_code;
	PyObject  **base=f->f_valuestack;
	PyObject *pobj;
	if (isDbgFileEx(f))
	{
		printf("dump eval stack:\n");
		while(base<stack_pointer){
			pobj=*base;
			printf("\t 0x%x ----> 0x%x : %s  : value =",base,pobj,pobj->ob_type->tp_name);
			print_obj(pobj);
			/*
			if (strcmp(pobj->ob_type->tp_name,"int")==0)
			{
				PyIntObject *pintboj=(PyIntObject* )pobj;
				printf(" %d",pintboj->ob_ival);
			}else if(strcmp(pobj->ob_type->tp_name,"type")==0){
				//PyTypeObject

			}
			else if (strcmp(pobj->ob_type->tp_name,"str")==0){
				PyStringObject *pstrobj=(PyStringObject *)pobj;
				printf("%s",pstrobj->ob_sval);
			}
			else{
				printf("unknown");
			}*/
			printf("\n");
			++base;
		}
	}
}



void mydbg_show_frameinfo(PyFrameObject* f){

	if (isDbgFileEx(f)){
		PyCodeObject* co_code=(PyCodeObject*)f->f_code;
		
		PyStringObject* pstrobj=(PyStringObject*)co_code->co_name;
		//显示 code block 名称 （函数名、模块名，类名）
		printf("%s : ",pstrobj->ob_sval);
		pstrobj=(PyStringObject*)co_code->co_filename;
		printf(" %s ",pstrobj->ob_sval);
		
	
		printf("\n");
	}
}

char* dbgCodeBlockName[]={"<module>","f","calc"};
#define dbgCodeBlockCnt 3

int isDbgBlock(PyFrameObject* f){
	if (isDbgFileEx(f))
	{
		int i=0;
		PyCodeObject *f_code=(PyCodeObject *) f->f_code;
		PyStringObject * co_name= (PyStringObject *)f_code->co_name;
		
		for (i;i<dbgCodeBlockCnt;++i)
		{
			if (strcmp(co_name->ob_sval,dbgCodeBlockName[i])==0)
			{
				return 1;
			}
		}
	}
	return 0;
}

void mydbg_show_f_localsplus(PyFrameObject *f,PyObject  **stack_pointer,PyObject **freevars,int oparg){
	PyObject **f_localsplus=(PyObject **)f->f_localsplus;
	PyCodeObject *co_code=(PyCodeObject*)f->f_code;
	Py_ssize_t ncells=PyTuple_GET_SIZE(co_code->co_cellvars);
	Py_ssize_t nfrees = PyTuple_GET_SIZE(co_code->co_freevars);
	if (isDbgBlock(f))
	{
		printf("f_localsplus=0x%x \n",f_localsplus);
		printf("freevars=0x%x\n",freevars);
		printf("stack_pointer=0x%x\n",stack_pointer);
		printf("oparg=0x%x\n",oparg);
		while(f_localsplus<stack_pointer){
			if (f_localsplus==f->f_localsplus)
			{
				printf("----------------------------------f_localsplus------------------------------\n");
			}else if (f_localsplus==f->f_localsplus+co_code->co_argcount)
			{
				printf("---------------------------f_localsplus+co_argcount-------------------------\n");
			}else if (f_localsplus==f->f_localsplus+co_code->co_nlocals)
			{
				printf("--------------------------------f_localsplus+co_nlocals----------------------\n");
			}else if (f_localsplus==f->f_localsplus + co_code->co_nlocals + ncells)
			{
				printf("--------------------------f_localsplus+co_nlocals+ncells----------------------\n");
			}else if (f_localsplus==f->f_localsplus + co_code->co_nlocals + ncells + nfrees)
			{
				printf("----------------------f_localsplus+co_nlocals+ncells+nfrees--------------------\n");
			}
			printf("0x%x  : ",f_localsplus);
			if (f_localsplus && (*f_localsplus)){
				PyObject* pobj=*f_localsplus;

				print_obj(pobj);
	
			}else{
				printf("Null");
			}
			printf("\n");
			f_localsplus++;//sizeof(PyObject*);
		}
		
		//printf("*************************\n");
	}

	
}
 
void mydbg_show_f_blockstack(PyFrameObject *f){
	
	PyTryBlock *b;
	int i;
	if (isDbgBlock(f))
	{
		for (i=0;i<f->f_iblock;i++)
		{
			b=&(f->f_blockstack[i]);
			printf("0x%x : b_type=0x%x b_handler=%x  b_level=0x%x \n",b->b_type,b->b_handler,b->b_level);
		}
	}
}

void mydbg_show_PyMethodDef(PyMethodDef *pmethoddef){

	if (pmethoddef==NULL)
	{
		PyObject *list=PyList_New(10);
		PyObject *pstr;
		printf("PyMethodDef:\n");
		printf("name:",pmethoddef->ml_name);
		if (pmethoddef->ml_flags&&METH_VARARGS)
		{
			pstr=PyString_FromString("METH_VARARGS");
			PyList_Append(list,pstr);
			
		}
		
		if (pmethoddef->ml_flags&&METH_KEYWORDS)
		{
			pstr=PyString_FromString("METH_KEYWORDS");
			PyList_Append(list,pstr);
		}

		if (pmethoddef->ml_flags&&METH_NOARGS)
		{
			pstr=PyString_FromString("METH_NOARGS");
			PyList_Append(list,pstr);
			Py_XDECREF(pstr);
		}

		if (pmethoddef->ml_flags&&METH_O)
		{
			pstr=PyString_FromString("METH_O");
			PyList_Append(list,pstr);
			Py_XDECREF(pstr);
		}

		if (pmethoddef->ml_flags&&METH_OLDARGS)
		{
			pstr=PyString_FromString("METH_OLDARGS");
			PyList_Append(list,pstr);
			Py_XDECREF(pstr);
		}
		
		if (pmethoddef->ml_flags&&METH_CLASS)
		{
			pstr=PyString_FromString("METH_CLASS");
			PyList_Append(list,pstr);
			Py_XDECREF(pstr);
		}

		if (pmethoddef->ml_flags&&METH_STATIC)
		{
			pstr=PyString_FromString("METH_STATIC");
			PyList_Append(list,pstr);
			Py_XDECREF(pstr);
		}

		if (pmethoddef->ml_flags&&METH_COEXIST)
		{
			pstr=PyString_FromString("METH_COEXIST");
			PyList_Append(list,pstr);
			Py_XDECREF(pstr);
		}

		PyList_Dump((PyListObject*)list,stdout,0);

		Py_XDECREF(list);
	}

}	




void mydbg_show_PyMemberDef(PyMemberDef *pyMemberDef){
	printf("%s\n",pyMemberDef->name);
}

void mydbg_show_PyGetSetDef(PyGetSetDef *pyGetSetDef){
	printf("%s\n",pyGetSetDef->name);
}


void mydbg_show_PyTypeObject(PyTypeObject* pObj){
	

}


	




/*
debug api wrapper



PSYMBOL_INFO mydbg_get_symbol(DWORD64 addr){
	PSYMBOL_INFO    pSymbol ;

	HANDLE                  hProcess = NULL;  // not using GetCurrentprocess
	char  buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)] ;
	 memset(&buffer,0,sizeof(buffer));
	 hProcess=GetCurrentProcess();
	 
	 pSymbol=malloc(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)); //(SYMBOL_INFO*)buffer;

	 pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	 pSymbol->MaxNameLen = MAX_SYM_NAME;
	
	 
	 SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
	 
	 if ((SymInitialize(
		 hProcess,
		 NULL,
		 FALSE)) == FALSE)
	 {
		 printf("SymInitialize returned error : %X\n", GetLastError());
		 return FALSE;
	 }

 

	if (( SymFromAddr(
		 hProcess,
		addr,
		 0,
		 pSymbol)) == FALSE )
	 {
		 printf("SymFromAddr returned error : %X\n",  GetLastError());
		 return FALSE;
	 }
	SymCleanup(hProcess);
	return pSymbol;
	
}


*/