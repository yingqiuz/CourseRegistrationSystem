//����һ��ѧ��ѡ��ϵͳ���������¹��ܣ�
//	��ѯ�γ���Ϣ�����ӿγ���Ϣ���޸Ŀγ���Ϣ����ѯѧ��ѡ����Ϣ��ѧ���˿Ρ��޸�ѧ��ѡ����Ϣ���˳�
//	Ҫ��
//	1.�γ���Ϣ�����γ̱�š����ơ�����Ժϵ���ον�ʦ����λ������ʣ����λ��������Ϣ��Ҫ����԰���ǰ�������������пγ̵Ĳ�ѯ���޸ġ�Ҫ�󳬹�10�����ϵĿγ���Ϣ��
//	2.ѡ��ʱҪ���¼ѧ��������ѧ�š��γ̺ţ�������Ϣ�ӿγ���Ϣ�п���������ͬʱ�޸Ŀγ���Ϣ��ʣ����λ��������ÿγ���ѡ����������ʾ��
//	3.���԰���ѧ��ѧ�š��������γ̺Ų�ѯѡ����Ϣ�����Զ�ѡ����Ϣɾ�����޸ġ�
//	4.Ҫ������ʽ���������������ú���,��Ҫʱ�г�����͡�
//	5. ����ýṹ����ļ���
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
struct course
{
	char no[11];//�γ̱��
	char name[31];//�γ�����
	char department[21];//����Ժϵ
	char teacher[21];//�ον�ʦ
	int total;//��λ����
	int remain;//ʣ����λ����
	struct course *next;
};

struct select
{
	char courseno[11];//�γ̺�
	char studentno[11];//ѧ��
	char studentname[21];//ѧ������
	struct select *next;
};

course *createCourseFromFile()//��ȡ��¼����ѡ����Ϣ�б�
{
	FILE *fp;
	int i,n=0;
	course *head=NULL;
	course *p=NULL;
	course *q=NULL;

	fp=fopen("course.txt","r");
	if(fp==NULL)
	{
		printf("������ѡ����Ϣ��¼��\n");
		return head;
	}else
	{
		fscanf(fp,"%d",&n);
		for(i=0;i<n;i++)
		{
			p=(struct course *)malloc(sizeof course);
			if(p==NULL)
			{
				printf("�ڴ����ʧ�ܣ�");
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
		printf("�ڴ����ʧ�ܣ�");
		return head;
	}
	p->next=NULL;
	printf("������γ̱��\n");
	scanf("%s",p->no);
	printf("������γ�����\n");
	scanf("%s",p->name);
	printf("�����뿪��Ժϵ\n");
	scanf("%s",p->department);
	printf("�������ον�ʦ\n");
	scanf("%s",p->teacher);
	printf("��������λ����\n");
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
	printf("������γ̱��\n");
	scanf("%s",p->no);
	printf("������γ�����\n");
	scanf("%s",p->name);
	printf("�����뿪��Ժϵ\n");
	scanf("%s",p->department);
	printf("�������ον�ʦ\n");
	scanf("%s",p->teacher);
	printf("��������λ����\n");
	scanf("%d",&p->total);
	printf("������ʣ����λ����\n");
	scanf("%d",&p->remain);
	printf("�޸ĳɹ�!\n");
}

void printCourse(course *p)
{
	printf("�γ̺ţ�%s\t�γ�����%s\n����Ժϵ:%s\t�ον�ʦ:%s\n��λ����:%d\tʣ����λ����:%d\n\n",p->no,p->name,p->department,p->teacher,p->total,p->remain);
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

select *createSelectFromFile()//��ȡ��¼����ѡ���б�
{
	FILE *fp;
	int i,n=0;
	select *head=NULL;
	select *p=NULL;
	select *q=NULL;

	fp=fopen("select.txt","r");
	if(fp==NULL)
	{
		printf("������ѡ�μ�¼��\n");
		return head;
	}else
	{
		fscanf(fp,"%d",&n);
		for(i=0;i<n;i++)
		{
			p=(struct select *)malloc(sizeof select);
			if(p==NULL)
			{
				printf("�ڴ����ʧ�ܣ�");
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
		printf("�ڴ治�㣡");
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
	if(fp==NULL)printf("����ʧ�ܣ�");

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
	if(fp==NULL)printf("����ʧ�ܣ�");

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
		printf("��ѡ����� 1����Ա 2ѧ�� 3�˳�\n");
		printf("***************************************************************\n");
		do 
		{
			choose=getchar();
		} while (choose!='1' && choose!='2'&&choose!='3');

		if(choose=='3')break;
		quitFlag=false;
		if(choose=='1')//����Ա
		{
			while(!quitFlag)
			{
				system("cls");
				printf("***************************************************************\n");
				printf("1��ʾ���пγ���Ϣ\n2���ӿγ���Ϣ\n3�޸Ŀγ���Ϣ\n4��ѯѡ����Ϣ\n5ɾ��ѡ����Ϣ\n6�˳�\n");
				printf("***************************************************************\n");
				do 
				{
					choose=getchar();
				} while (choose!='1' && choose!='2' && choose!='3'&& choose!='4' && choose!='5' && choose!='6');
				switch(choose)
				{
				case '1'://��ʾ���пγ���Ϣ
					printAllCourse(chead);
					break;
				case '2'://���ӿγ���Ϣ
					chead=addcourse(chead);
					break;
				case '3'://�޸Ŀγ���Ϣ
					printf("������γ̺�:");
					scanf("%s",couno);
					cp=searchCourse(chead,couno);
					if(cp==NULL)
					{
						printf("δ�ҵ������Ϣ��\n");
						break;
					}
					modifyCourse(cp);
					break;
				case '4'://��ѯѡ����Ϣ
					printf("1����ѧ�Ž��в�ѯ\n2�����������в�ѯ\n3����γ̺Ž��в�ѯ\n");
					do 
					{
						choose=getchar();
					} while (choose!='1' && choose!='2' && choose!='3');
					if(choose=='1')
					{
						printf("������ѧ��:");
						scanf("%s",stuno);
						printSelectCourse(shead,stuno,chead);
					}else if(choose=='2')
					{
						printf("����������:");
						scanf("%s",stuname);
						printSelectCourseByName(shead,stuname,chead);
					}else if(choose=='3')
					{
						printf("������γ̺�:");
						scanf("%s",couno);
						printSelectByCouNo(shead,couno);
					}
					break;
				case '5'://ɾ��ѡ����Ϣ
					printf("������ѧ��:");
					scanf("%s",stuno);
					printf("������γ̺�:");
					scanf("%s",couno);
					sp=searchSelect(shead,stuno,couno);
					if(sp==NULL)printf("֮ǰû��ѡ�и��ſγ�!\n");
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
		else//ѧ��
		{
			printf("������ѧ��:");
			scanf("%s",stuno);
			printf("����������:");
			scanf("%s",stuname);
			quitFlag=false;
			while(!quitFlag)
			{
				system("cls");
				printf("***************************************************************\n");
				printf("1��ʾ���пγ���Ϣ\n2��ʾ������ѡ�γ�\n3��ѯ�γ���Ϣ\n4ѡ��\n5�˿�\n6�˳�\n");
				printf("***************************************************************\n");
				do 
				{
					choose=getchar();
				} while (choose!='1' && choose!='2' && choose!='3'&& choose!='4' && choose!='5'&& choose!='6');
				switch(choose)
				{
				case '1'://��ʾ���пγ�
					printAllCourse(chead);
					break;
				case '2'://��ʾ������ѡ�γ�
					printSelectCourse(shead,stuno,chead);
					break;
				case '3'://��ѯ�γ���Ϣ
					printf("������γ̺�:");
					scanf("%s",couno);
					cp=searchCourse(chead,couno);
					if(cp!=NULL)printCourse(cp);
					else printf("δ�ҵ������Ϣ��\n");
					break;
				case '4'://ѡ��
					printf("������γ̺�:");
					scanf("%s",couno);
					cp=searchCourse(chead,couno);
					if(cp==NULL)printf("δ�ҵ������Ϣ��\n");
					else
					{
						if(cp->remain==0)printf("ѡ��ʧ�ܣ�������Ϊ0��\n");
						else
						{
							cp->remain--;
							shead=addSelect(shead,stuno,stuname,couno);
							printf("ѡ�γɹ�!\n");
						}
					}
					break;
				case '5'://�˿�
					printf("������γ̺�:");
					scanf("%s",couno);
					sp=searchSelect(shead,stuno,couno);
					if(sp==NULL)printf("֮ǰû��ѡ�и��ſγ�!\n");
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
