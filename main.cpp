//制作一个学生选课系统，包括以下功能：
//	查询课程信息、增加课程信息、修改课程信息、查询学生选课信息、学生退课、修改学生选课信息、退出
//	要求：
//	1.课程信息包括课程编号、名称、开课院系、任课教师、座位数量、剩余座位数量等信息。要求可以按照前面两个变量进行课程的查询及修改。要求超过10门以上的课程信息。
//	2.选课时要求记录学生姓名、学号、课程号，其它信息从课程信息中拷贝过来，同时修改课程信息中剩余座位数量，如该课程已选满，给出提示。
//	3.可以按照学生学号、姓名、课程号查询选课信息。可以对选课信息删除和修改。
//	4.要求程序格式清晰，尽量多利用函数,必要时有程序解释。
//	5. 最好用结构体和文件。
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
struct course
{
	char no[11];//课程编号
	char name[31];//课程名称
	char department[21];//开课院系
	char teacher[21];//任课教师
	int total;//座位数量
	int remain;//剩余座位数量
	struct course *next;
};

struct select
{
	char courseno[11];//课程号
	char studentno[11];//学号
	char studentname[21];//学生姓名
	struct select *next;
};

course *createCourseFromFile()//读取记录创建选课信息列表
{
	FILE *fp;
	int i,n=0;
	course *head=NULL;
	course *p=NULL;
	course *q=NULL;

	fp=fopen("course.txt","r");
	if(fp==NULL)
	{
		printf("不存在选课信息记录！\n");
		return head;
	}else
	{
		fscanf(fp,"%d",&n);
		for(i=0;i<n;i++)
		{
			p=(struct course *)malloc(sizeof course);
			if(p==NULL)
			{
				printf("内存分配失败！");
				exit(1);
			}
			fscanf(fp,"%s",p->no);
			fscanf(fp,"%s",p->name);
			fscanf(fp,"%s",p->department);
			fscanf(fp,"%s",p->teacher);
			fscanf(fp,"%d",&p->total);
			fscanf(fp,"%d",&p->remain);
			p->next=NULL;
			if(head==NULL)
			{
				head=p;
				q=p;
			}
			else
			{
				q->next=p;
				q=q->next;
			}
		}
	}
	fclose(fp);
	return head;
}

course *addcourse(course *head)
{
	course *p,*q;

	p=(course *)malloc(sizeof course);
	if(p==NULL)
	{
		printf("内存分配失败！");
		return head;
	}
	p->next=NULL;
	printf("请输入课程编号\n");
	scanf("%s",p->no);
	printf("请输入课程名称\n");
	scanf("%s",p->name);
	printf("请输入开课院系\n");
	scanf("%s",p->department);
	printf("请输入任课教师\n");
	scanf("%s",p->teacher);
	printf("请输入座位数量\n");
	scanf("%d",&p->total);
	p->remain=p->total;

	if(head==NULL)head=p;
	else
	{
		for(q=head;q->next!=NULL;q=q->next){}
		q->next=p;
	}

	return head;
}

void modifyCourse(course *p)
{
	printf("请输入课程编号\n");
	scanf("%s",p->no);
	printf("请输入课程名称\n");
	scanf("%s",p->name);
	printf("请输入开课院系\n");
	scanf("%s",p->department);
	printf("请输入任课教师\n");
	scanf("%s",p->teacher);
	printf("请输入座位数量\n");
	scanf("%d",&p->total);
	printf("请输入剩余座位数量\n");
	scanf("%d",&p->remain);
	printf("修改成功!\n");
}

void printCourse(course *p)
{
	printf("课程号：%s\t课程名：%s\n开课院系:%s\t任课教师:%s\n座位数量:%d\t剩余座位数量:%d\n\n",p->no,p->name,p->department,p->teacher,p->total,p->remain);
}

void printAllCourse(course *head)
{
	course *p=head;
	while(p!=NULL)
	{
		printCourse(p);
		p=p->next;
	}
}

course *searchCourse(course *head, char *courno)
{
	course *p;
	for(p=head;p!=NULL;p=p->next)
	{
		if(strcmp(p->no,courno)==0)return p;
	}
	return NULL;
}

select *createSelectFromFile()//读取记录创建选课列表
{
	FILE *fp;
	int i,n=0;
	select *head=NULL;
	select *p=NULL;
	select *q=NULL;

	fp=fopen("select.txt","r");
	if(fp==NULL)
	{
		printf("不存在选课记录！\n");
		return head;
	}else
	{
		fscanf(fp,"%d",&n);
		for(i=0;i<n;i++)
		{
			p=(struct select *)malloc(sizeof select);
			if(p==NULL)
			{
				printf("内存分配失败！");
				exit(1);
			}
			fscanf(fp,"%s",p->courseno);
			fscanf(fp,"%s",p->studentno);
			fscanf(fp,"%s",p->studentname);
			p->next=NULL;
			if(head==NULL)
			{
				head=p;
				q=p;
			}
			else
			{
				q->next=p;
				q=q->next;
			}
		}
	}
	fclose(fp);
	return head;
}

select *addSelect(select *shead,char *stuno,char *stuname,char *couno)
{
	select *p;
	p=(select *)malloc(sizeof select);
	if(p==NULL)
	{
		printf("内存不足！");
		return shead;
	}
	strcpy(p->courseno,couno);
	strcpy(p->studentno,stuno);
	strcpy(p->studentname,stuname);
	p->next=shead;
	shead=p;
	return shead;
}

select *searchSelect(select *shead,char *stuno,char *couno)
{
	select *p;
	for(p=shead;p!=NULL;p=p->next)
	{
		if(strcmp(p->studentno,stuno)==0 && strcmp(p->courseno,couno)==0)return p;
	}
	return NULL;
}

select *deleteSelect(select *shead,select *sp)
{
	select *p=shead;
	if(shead==sp)
	{
		shead=shead->next;
	}else
	{
		while(p->next!=sp)p=p->next;
		p->next=sp->next;
	}
	free(sp);
	return shead;
}

void saveSelect(select *shead)
{
	FILE *fp;
	fp=fopen("select.txt","w");
	if(fp==NULL)printf("保存失败！");

	int n=0;
	select *p=shead;
	while(p!=NULL)
	{
		n++;
		p=p->next;
	}
	fprintf(fp,"%d\n",n);

	p=shead;
	while(p!=NULL)
	{
		fprintf(fp,"%s\t%s\t%s\n",p->courseno,p->studentno,p->studentname);
		p=p->next;
	}
	fclose(fp);
}

void saveCourse(course *chead)
{
	FILE *fp;
	fp=fopen("course.txt","w");
	if(fp==NULL)printf("保存失败！");

	int n=0;
	course *p=chead;
	while(p!=NULL)
	{
		n++;
		p=p->next;
	}
	fprintf(fp,"%d\n",n);

	p=chead;
	while(p!=NULL)
	{
		fprintf(fp,"%s\t",p->no);
		fprintf(fp,"%s\t%s\t%s\t",p->name,p->department,p->teacher);
		fprintf(fp,"%d\t%d\n",p->total,p->remain);
		p=p->next;
	}
	fclose(fp);
}

void printSelectCourse(select* shead,char *stuno,course *chead)
{
	select *p=shead;
	course *q;
	for(;p!=NULL;p=p->next)
	{
		if(strcmp(stuno,p->studentno)==0)
		{
			for(q=chead;q!=NULL;q=q->next)
			{
				if(strcmp(p->courseno,q->no)==0)
					printCourse(q);
			}
		}
	}
}

void printSelectCourseByName(select* shead,char *stuname,course *chead)
{
	select *p=shead;
	course *q;
	for(;p!=NULL;p=p->next)
	{
		if(strcmp(stuname,p->studentname)==0)
		{
			for(q=chead;q!=NULL;q=q->next)
			{
				if(strcmp(p->courseno,q->no)==0)
					printCourse(q);
			}
		}
	}
}

void printSelectByCouNo(select* shead,char *couno)
{
	select *p=shead;
	course *q;
	for(;p!=NULL;p=p->next)
	{
		if(strcmp(couno,p->courseno)==0)
		{
			printf("%s\t%s\n",p->studentno,p->studentname);
		}
	}
}

void main()
{
	select *shead=NULL,*sp;
	course *chead=NULL,*cp;
	char choose;
	char stuno[11];
	char stuname[21];
	char couno[11];
	bool quitFlag=false;

	shead=createSelectFromFile();
	chead=createCourseFromFile();

	while(1)
	{
		system("cls");
		printf("***************************************************************\n");
		printf("请选择身份 1管理员 2学生 3退出\n");
		printf("***************************************************************\n");
		do 
		{
			choose=getchar();
		} while (choose!='1' && choose!='2'&&choose!='3');

		if(choose=='3')break;
		quitFlag=false;
		if(choose=='1')//管理员
		{
			while(!quitFlag)
			{
				system("cls");
				printf("***************************************************************\n");
				printf("1显示所有课程信息\n2增加课程信息\n3修改课程信息\n4查询选课信息\n5删除选课信息\n6退出\n");
				printf("***************************************************************\n");
				do 
				{
					choose=getchar();
				} while (choose!='1' && choose!='2' && choose!='3'&& choose!='4' && choose!='5' && choose!='6');
				switch(choose)
				{
				case '1'://显示所有课程信息
					printAllCourse(chead);
					break;
				case '2'://增加课程信息
					chead=addcourse(chead);
					break;
				case '3'://修改课程信息
					printf("请输入课程号:");
					scanf("%s",couno);
					cp=searchCourse(chead,couno);
					if(cp==NULL)
					{
						printf("未找到相关信息！\n");
						break;
					}
					modifyCourse(cp);
					break;
				case '4'://查询选课信息
					printf("1输入学号进行查询\n2输入姓名进行查询\n3输入课程号进行查询\n");
					do 
					{
						choose=getchar();
					} while (choose!='1' && choose!='2' && choose!='3');
					if(choose=='1')
					{
						printf("请输入学号:");
						scanf("%s",stuno);
						printSelectCourse(shead,stuno,chead);
					}else if(choose=='2')
					{
						printf("请输入姓名:");
						scanf("%s",stuname);
						printSelectCourseByName(shead,stuname,chead);
					}else if(choose=='3')
					{
						printf("请输入课程号:");
						scanf("%s",couno);
						printSelectByCouNo(shead,couno);
					}
					break;
				case '5'://删除选课信息
					printf("请输入学号:");
					scanf("%s",stuno);
					printf("请输入课程号:");
					scanf("%s",couno);
					sp=searchSelect(shead,stuno,couno);
					if(sp==NULL)printf("之前没有选中该门课程!\n");
					else
					{
						cp=searchCourse(chead,couno);
						if(cp!=NULL)cp->remain++;
						shead=deleteSelect(shead,sp);
					}
					break;
				case '6':
					quitFlag=true;
					saveSelect(shead);
					saveCourse(chead);
				default:
					break;
				}
				system("pause");
			}
			
		}
		else//学生
		{
			printf("请输入学号:");
			scanf("%s",stuno);
			printf("请输入姓名:");
			scanf("%s",stuname);
			quitFlag=false;
			while(!quitFlag)
			{
				system("cls");
				printf("***************************************************************\n");
				printf("1显示所有课程信息\n2显示所有已选课程\n3查询课程信息\n4选课\n5退课\n6退出\n");
				printf("***************************************************************\n");
				do 
				{
					choose=getchar();
				} while (choose!='1' && choose!='2' && choose!='3'&& choose!='4' && choose!='5'&& choose!='6');
				switch(choose)
				{
				case '1'://显示所有课程
					printAllCourse(chead);
					break;
				case '2'://显示所有已选课程
					printSelectCourse(shead,stuno,chead);
					break;
				case '3'://查询课程信息
					printf("请输入课程号:");
					scanf("%s",couno);
					cp=searchCourse(chead,couno);
					if(cp!=NULL)printCourse(cp);
					else printf("未找到相关信息！\n");
					break;
				case '4'://选课
					printf("请输入课程号:");
					scanf("%s",couno);
					cp=searchCourse(chead,couno);
					if(cp==NULL)printf("未找到相关信息！\n");
					else
					{
						if(cp->remain==0)printf("选课失败！课余量为0！\n");
						else
						{
							cp->remain--;
							shead=addSelect(shead,stuno,stuname,couno);
							printf("选课成功!\n");
						}
					}
					break;
				case '5'://退课
					printf("请输入课程号:");
					scanf("%s",couno);
					sp=searchSelect(shead,stuno,couno);
					if(sp==NULL)printf("之前没有选中该门课程!\n");
					else
					{
						cp=searchCourse(chead,couno);
						if(cp!=NULL)cp->remain++;
						shead=deleteSelect(shead,sp);
					}
					break;
				case '6':
					quitFlag=true;
					saveSelect(shead);
				default:
					break;
				}
				system("pause");
			}
			
		}
	}
	
}
