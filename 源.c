#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
//链表的定义
//这里以学生管理系统为例
//为了统一链表，通常分两部定义
//typedef struct ElemType
//{
	//char num[8];//数据域     学号
	//char name[8];//数据域    姓名 
	//int score;//数据域       成绩
//}ElemType;
typedef struct DuLNode
{
	ElemType date;//数据域
	struct DuLNode* prior;//指向直接前驱
	struct DuLNode* next;//指向直接后继

}DuLNode, * DuLinkList;//LinkList为指向结构体Lnode的指针类型

DuLinkList L;//定义头指针变量

//双向链表的初始化即构造一个空的表
Status linitList_L(DuLinkList L)//  LinkList L 头指针
{
	L = (DuLinkList)malloc(sizeof(DuLNode));//动态获取LNode的字节数，从而开辟新的空间，生成新结点作头结点，用头指针L指向头结点
	if (L == NULL)
	{
		exit(OVERFLOW);
	}
	else
	{
		L->prior = NULL;//指向直接前驱的指针域置空
		L->next = NULL;//指向直接后继的指针域置空
		return OK;
	}
}

//链表判空   判断头结点的指针域是否为空
int ListEmpty(DuLinkList L)
{
	if (L->next == L->prior)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//链表的销毁  从头指针开始，依次释放所有结点  
Status DestroyList_L(DuLinkList L)
{
	DuLNode* p = L;//要销毁的结点
	while (L)  //循环条件：L！=NULL   结束条件  L==NULL
	{
		p = L;
		L = L->next;//把下一个结点赋值给L 依次free
		free(p);
	}
	return OK;
}

//清空单链表  链表依然存在 成为空链表  依次释放所有结点，并将头结点指针域置空
Status ClearList(DuLinkList L)
{
	DuLNode* p = L, * q;
	p = L->next;//第一个结点
	while (p!=L->prior)
	{
		q = p->next;//q存放下一个结点 关键操作
		free(p);//释放第一个结点
		p = q;//把第二个节点还给p 依次循环释放直到表空
	}
	L->next = NULL;//头结点指针域为空
	return OK;
}

//求链表的表长
int ListLength_L(DuLinkList L)
{
	DuLNode* p = L;
	int i = 0;
	p = L->next;//p指向第一个结点
	while (p!=L->prior)
	{
		i++;
		p = p->next;
	}
	return i;
}

//取值，取第i个元素值s(插入用)
DuLinkList GetElem_DuL(DuLinkList L, int i)//根据第i个元素用e返回其值
{
	DuLNode* p = L;
	p = L->next;
	int j = 1;//初始化
	while (p!=L->prior && j < i)
	{
		p = p->next;//向后扫描，直到p指向第i个元素或p为空
		++j;
	}
	if (!p!=L->prior || j > i)//第i个元素不存在
	{
		return ERROR;
	}
	else
	{
		return p;
	}
}

//取值，取第i个元素值s
int GetElem_L(DuLinkList L, int i, ElemType* e)//根据第i个元素用e返回其值
{
	DuLNode* p = L->next;
	int j = 1;//初始化
	while (p!=L->prior && j < i)
	{
		p = p->next;//向后扫描，直到p指向第i个元素或p为空
		++j;
	}
	if (!p!=L->prior || j > i)//第i个元素不存在
	{
		return ERROR;
	}
	else
	{
		*e = p->date;//取第i个元素
		return OK;
	}
}
////查找  按值查找 返回地址
//int LocateELem_L(DuLinkList L, ElemType e)
//{
//	//在线性表L中查找值为e的数据元素
//	//找到，则返回L中值为e的数据元素的地址，查找失败返回NULL
//	DuLNode* p = L->next;
//
//	while (p!=L->prior && p->date != e)
//	{
//		p = p->next;
//
//	}
//	return p;
//}


int LocateELem_L(DuLinkList L, ElemType e)
{
	DuLNode* p = L;
	p = L->next;//初始化，p指向首元结点
	int j = 1;

	while (p!=L->prior && (p->date != e))
	{
		p = p->next;
		j++;
	}
	if (!p!=L->prior)//如果p为空，也就是没找到为假，返回else的值0
		  //如果p找到了，那么p就不为0 执行返回j
	{
		return 0;
	}
	else
	{
		return j;
	}
}

//插入 在第i个结点前插入值为e的新结点
Status LintInsert_L(DuLinkList L, int i, ElemType e)
{
	DuLNode* p = L;//定义一个结点
	//int j = 0;//计数器  从头结点开始
	if (!(p = GetElem_DuL(L, i))) return ERROR;
	else
	{
		DuLNode* s = (DuLNode*)malloc(sizeof(DuLNode));//生成新结点
		if (s == NULL)
		{
			exit(ERROR);
		}
		else
		{
			s->date = e;//将新结点的数据域置为e
			s->prior = p->prior;//把前一结点的地址给新结点的prior  前一结点的地址存在后一结点的prior中
			p->prior->next = s;//把新结点地址放在前驱结点的直接后继指针域
			s->next = p;
			p->prior = s;
			return OK;
		}
	}
}

//删除第i个结点    将线性表L中第i个数据元素删除
Status ListDelete_L(DuLinkList L, int i, ElemType* e)//这里需要对数据域进行操作需要传递指针
{
	DuLNode* p = L;
	if(!(p=GetElem_DuL(L,i)))
	{
		return ERROR;
	}
	else
	{
		*e = p->date;
		p->prior->next = p->next;
		p->next->prior = p->next;
		free(p);
		return OK;
	}
}

//头插法建立单链表   L是头结点
//DuLinkList CreateList_H(DuLinkList L, int n)//n是结点数即要插入多少个结点
//{
//	L = (DuLinkList)malloc(sizeof(DuLNode));//生成头结点
//	if (L == NULL)
//	{
//		exit(ERROR);
//	}
//	else
//	{
//		L->next = NULL;
//	}
//	int i = 0;
//	for (i = n; i > 0; --i)
//	{
//		LNode* p = (LNode*)malloc(sizeof(LNode));//生成新结点
//		if (p == NULL)
//		{
//			exit(ERROR);
//		}
//		else
//		{
//			printf("请输入第%d个结点数据域", i);
//			scanf_s("%d", &p->date);//输入元素值
//			p->next = L->next;//插入到表头 把头结点的指针域赋给新结点的指针域
//			L->next = p;//再把新结点的指针赋给头结点的指针域
//		}
//	}
//	return L;
//}

//尾插法建立单链表  正位序输入n个元素的值
DuLinkList CreateList_R(DuLinkList L, int n)
{
	L = (DuLinkList)malloc(sizeof(DuLNode));//分配空间
	if (L == NULL)
	{
		exit(ERROR);
	}
	else
	{
		L->prior = NULL;
		L->next = NULL;
	}
	DuLNode* r = L;//这里的r为尾指针，只有一个结点时，头指针与尾指针同时指向头结点
	for (int i = 0; i < n; ++i)
	{
		DuLNode* p = (DuLNode*)malloc(sizeof(DuLNode));//生成新结点
		if (p == NULL)
		{
			exit(ERROR);
		}
		else
		{
			scanf_s("%d", &p->date);//输入元素值

			p->next = NULL;
			p->prior = r;
			r->next = p;//把新结点的地址给上一个结点的指针域
			r = p;//r指向新的尾结点
		}
	}
	return L;
}

void PrintLinkList(DuLinkList L)
{
	DuLNode* p = L->next;
	while (p!=NULL)
	{
		printf("-->%d<-- ", p->date);
		p = p->next;
	}
	printf("\n");
}

void menu()
{
	printf("*******************************\n");
	printf("*     1.头插法建立链表        *\n");
	printf("*     2.尾插法建立链表        *\n");
	printf("*     3.查找位置              *\n");
	printf("*     4.删除结点              *\n");
	printf("*     5.插入结点              *\n");
	printf("*     6.查值                  *\n");
	printf("*     7.链表表长              *\n");
	printf("*     8.清空链表              *\n");
	printf("*     9.销毁链表              *\n");
	printf("*     10.查看链表             *\n");
	printf("*******************************\n");
}
int main()
{
	int a = 0;
	menu();
	int n = 0;

	while (!a)
	{
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:
		{
			int n = 0;
			printf("请输入要插入的结点数：");
			scanf_s("%d", &n);
			linitList_L(L);
			//L = CreateList_H(L, n);
			printf("\n插入成功！！\n");
			break;
		}
		case 2:
		{
			int n = 0;
			printf("请输入要插入的结点数：");
			scanf_s("%d", &n);
			linitList_L(L);
			L = CreateList_R(L, n);
			printf("\n插入成功！！\n");
			break;
		}
		case 3:
		{
			ElemType e = 0;
			int sum = 0;
			printf("\n请输入要查找的值：");
			scanf_s("%d", &e);
			sum = LocateELem_L(L, e);
			if (sum == 0)
			{
				printf("查找失败\n");
			}
			else
			{
				printf("你所查的值的位置在第%d个结点\n", sum);
			}
			break;
		}
		case 4:
		{
			int e = 0;
			int i = 0;
			int sum = 0;
			printf("请输入要删除的位置：\n");
			scanf_s("%d", &i);
			sum = ListDelete_L(L, i, &e);
			if (sum == ERROR)
			{
				printf("结点不存在或输入错误\n");
			}
			else
			{
				printf("该结点已删除，删除的结点为:%d\n", e);
			}
			break;
		}
		case 5:
		{
			int i = 0;//结点的位置
			int e = 0;
			int sum = 0;
			printf("\n请输入要插入的位置：");
			scanf_s("%d", &i);
			printf("\n请输入要插入的值：");
			scanf_s("%d", &e);
			sum = LintInsert_L(L, i, e);
			if (sum == ERROR)
			{
				printf("插入失败：输入位置不合法\n");
			}
			else
			{
				printf("插入成功\n");
			}
			break;
		}
		case 6:
		{
			int i = 0;//位置
			int sum = 0;
			int e = 0;
			printf("\n请输入要查询的位置：");
			scanf_s("%d", &i);
			sum = GetElem_L(L, i, &e);
			if (sum == ERROR)
			{
				printf("该结点不存在\n");
			}
			else
			{
				printf("该结点的值为：%d\n", e);
			}
			break;
		}
		case 7:
		{
			int i = 0;
			i = ListLength_L(L);
			printf("该链表表长为：%d\n", i);
			break;
		}
		case 8:
		{
			int i = 0;
			i = ClearList(L);
			if (i == OK)
			{
				printf("链表清空成功\n");
			}
			break;
		}
		case 9:
		{
			int i = 0;
			i = DestroyList_L(L);
			if (i == OK)
			{
				printf("链表销毁成功\n");
				return 0;

			}
			break;
		}
		case 10:
		{
			int i = 0;
			i = ListEmpty(L);
			if (i == 0)
			{
				printf("该链表为空\n");
			}
			else
			{
				printf("该链表不为空\n");
			}
			PrintLinkList(L);
			break;
		}
		}
	}


	return 0;
}


