
/* Class object interface */

/* Revealing some structures (not for general use) */

#ifndef Py_CLASSOBJECT_H
#define Py_CLASSOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif


//用户自定义 class 对象
typedef struct {
    PyObject_HEAD
    PyObject	*cl_bases;	/* A tuple of class objects */
    PyObject	*cl_dict;	/* A dictionary */
    PyObject	*cl_name;	/* A string */
    /* The following three are functions or NULL */
    PyObject	*cl_getattr;
    PyObject	*cl_setattr;
    PyObject	*cl_delattr;
    PyObject    *cl_weakreflist; /* List of weak references */
} PyClassObject;


//class instance 对象，就是 自定义类的实例对象
typedef struct {
    PyObject_HEAD
    PyClassObject *in_class;	/* The class object */
    PyObject	  *in_dict;	/* A dictionary */
    PyObject	  *in_weakreflist; /* List of weak references */
} PyInstanceObject;
/*
类型 (class) 存储了所有的静态字段和⽅方法 (包括实例⽅方法)，⽽而实例 (instance) 仅存储实例字段，
从基类 object 开始，所有继承层次上的实例字段。官方文档将所有成员统称为 Attribute。
*/
//表示函数、方法对象
typedef struct {
    PyObject_HEAD
    PyObject *im_func;   /* The callable object implementing the method */
    PyObject *im_self;   /* 确定是否是实例绑定方法 The instance it is bound to, or NULL */
    PyObject *im_class;  /* 确定是否是类绑定方法The class that asked for the method */
    PyObject *im_weakreflist; /* List of weak references */
} PyMethodObject;

PyAPI_DATA(PyTypeObject) PyClass_Type, PyInstance_Type, PyMethod_Type;

#define PyClass_Check(op) ((op)->ob_type == &PyClass_Type)
#define PyInstance_Check(op) ((op)->ob_type == &PyInstance_Type)
#define PyMethod_Check(op) ((op)->ob_type == &PyMethod_Type)

PyAPI_FUNC(PyObject *) PyClass_New(PyObject *, PyObject *, PyObject *);
PyAPI_FUNC(PyObject *) PyInstance_New(PyObject *, PyObject *,
                                            PyObject *);
PyAPI_FUNC(PyObject *) PyInstance_NewRaw(PyObject *, PyObject *);
PyAPI_FUNC(PyObject *) PyMethod_New(PyObject *, PyObject *, PyObject *);

PyAPI_FUNC(PyObject *) PyMethod_Function(PyObject *);
PyAPI_FUNC(PyObject *) PyMethod_Self(PyObject *);
PyAPI_FUNC(PyObject *) PyMethod_Class(PyObject *);

/* Look up attribute with name (a string) on instance object pinst, using
 * only the instance and base class dicts.  If a descriptor is found in
 * a class dict, the descriptor is returned without calling it.
 * Returns NULL if nothing found, else a borrowed reference to the
 * value associated with name in the dict in which name was found.
 * The point of this routine is that it never calls arbitrary Python
 * code, so is always "safe":  all it does is dict lookups.  The function
 * can't fail, never sets an exception, and NULL is not an error (it just
 * means "not found").
 */
PyAPI_FUNC(PyObject *) _PyInstance_Lookup(PyObject *pinst, PyObject *name);

/* Macros for direct access to these values. Type checks are *not*
   done, so use with care. */
#define PyMethod_GET_FUNCTION(meth) \
        (((PyMethodObject *)meth) -> im_func)
#define PyMethod_GET_SELF(meth) \
	(((PyMethodObject *)meth) -> im_self)
#define PyMethod_GET_CLASS(meth) \
	(((PyMethodObject *)meth) -> im_class)

PyAPI_FUNC(int) PyClass_IsSubclass(PyObject *, PyObject *);

PyAPI_FUNC(int) PyMethod_ClearFreeList(void);

#ifdef __cplusplus
}
#endif
#endif /* !Py_CLASSOBJECT_H */
