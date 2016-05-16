
/* Parse tree node interface */

#ifndef Py_NODE_H
#define Py_NODE_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _node {
    short		n_type;//n_type代表着语法树的结点的类型，应着Python-2.7/Grammar/Grammar文件中的文法中的终结符/非终结符，主要在graminit.h和token.h中定义
    char		*n_str;//N_str则是对应的字符串的内容
    int			n_lineno;//N_lineno 代表对应行号
    int			n_col_offset;// n_col_offset代表对应列号
	//两个n_nchildren和n_child表示此节点共有n_nchildren个子结点
    int			n_nchildren;
    struct _node	*n_child;
} node;

PyAPI_FUNC(node *) PyNode_New(int type);
PyAPI_FUNC(int) PyNode_AddChild(node *n, int type,
                                      char *str, int lineno, int col_offset);
PyAPI_FUNC(void) PyNode_Free(node *n);
#ifndef Py_LIMITED_API
Py_ssize_t _PyNode_SizeOf(node *n);
#endif

/* Node access functions */
#define NCH(n)		((n)->n_nchildren)
	
#define CHILD(n, i)	(&(n)->n_child[i])
//从右往左第i个子节点,i给负值
//CHILD(n,((n)->n_nchildren)+i)
//
#define RCHILD(n, i)	(CHILD(n, NCH(n) + i)) 
#define TYPE(n)		((n)->n_type)
#define STR(n)		((n)->n_str)

/* Assert that the type of a node is what we expect */
#define REQ(n, type) assert(TYPE(n) == (type))

PyAPI_FUNC(void) PyNode_ListTree(node *);

#ifdef __cplusplus
}
#endif
#endif /* !Py_NODE_H */
