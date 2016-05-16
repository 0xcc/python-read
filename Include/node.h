
/* Parse tree node interface */

#ifndef Py_NODE_H
#define Py_NODE_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _node {
    short		n_type;//n_type�������﷨���Ľ������ͣ�Ӧ��Python-2.7/Grammar/Grammar�ļ��е��ķ��е��ս��/���ս������Ҫ��graminit.h��token.h�ж���
    char		*n_str;//N_str���Ƕ�Ӧ���ַ���������
    int			n_lineno;//N_lineno �����Ӧ�к�
    int			n_col_offset;// n_col_offset�����Ӧ�к�
	//����n_nchildren��n_child��ʾ�˽ڵ㹲��n_nchildren���ӽ��
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
//���������i���ӽڵ�,i����ֵ
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
