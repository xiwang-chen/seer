#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

//创建学生的信息的数据结构体 
struct student
{
	int id;
	char name[32];
	int age;
};
typedef struct student stu;

//创建一个节点的数据结构体 
struct Node
{
	stu DATE;
	struct Node* next;
};
typedef struct Node lnode;
lnode* head=NULL;

//创建一个头节点 
lnode* creatlist()
{
	lnode* l=(lnode*)malloc(sizeof(lnode));
	return l;
}

//在链表的结尾插入数据 
void insertafter(stu d)
{
	lnode* p=(lnode*)malloc(sizeof(lnode));
	p->DATE=d;
	p->next=NULL;
	lnode* current=head;
	while(current->next != NULL)
	{
		current=current->next;
	}
	current->next=p;
}

//遍历输入信息的数据 
void slam()
{
	for(lnode* current=head->next;current!=NULL;current=current->next)
	{
		printf("student.id = %d \n  student.name = %s \n  student.age = %d\n",current->DATE.id,current->DATE.name,current->DATE.age);
	}
	printf("\n");
}

//在链表的数据中插入数据
int listlen()
{
	int num=0;
	for(lnode* current=head->next;current != NULL;current=current->next)
	{
		num++;
	}
	return num;
 } 
 
 
 //寻找链表中的数据信息，以name为查找信息突破点
 lnode* find(char* name)
 {
 	lnode* current=NULL;
 	for(current=head->next;current!=NULL;current=current->next)
 	{
 		if(strcmp(current->DATE.name,name)==0)
 		{
 			return current;
		 }
	 }
	 return current;
  } 
  

  //删除中间的那个节点， 返回值1，表示删除成功，0表示删除失败;
  //需要多一个空的节点，来使用一下， 
  int deldata(char *name)
  {
  	lnode* current=head;
  	lnode* p=NULL;
  	for(;current->next != NULL;current=current->next)
  	{
  		if(strcmp(current->DATE.name,name)==0)
  		{
  			p=current->next;
  			current->next=p->next;
  			free(p);
  			return 1;
		  }
	  }
  	return 0;
   } 
   
   //将链表的数据存到文本文件当中
int listtofile()
{
   	FILE* fp=NULL;
   	fp=fopen("student.txt","w");
	if(fp=NULL)
	{
		printf("open file error!\n");
		return 1;
	}
	for(lnode* current=head->next;current!=NULL;current=current->next)
	{
		fprintf(fp,"%d %s %d\n",current->DATE.id,current->DATE.name,current->DATE.age);
	}
	fclose(fp);
	return 0;
} 
   

//将文本文件读到链表中
int filetolist()
{
	FILE* fp=NULL;
	fp=fopen("student.txt","r");
	if(fp=NULL)
	{
		printf("read file error!\n");
		return 1;
	}
	for(lnode* current=head->next;current!=NULL;current=current->next)
	{
		fscanf(fp,"%d %s %d\n",current->DATE.id,current->DATE.name,current->DATE.age);
		printf("stu.id = %d \nstu.name = %s \n stu.age = %d\n\n",current->DATE.id,current->DATE.name,current->DATE.age);
	}
	fclose(fp);
 } 
   
   void show()
{
	slam();
} 
  
 void input()
 {
 	stu s1;
 	printf("please input employee information!\n");
 	printf("id name age\n");
 	scanf("%d %s %d\n",&(s1.id),s1.name,&(s1.age));
 	insertafter(s1);
 	
 }
 
void update()
{
	printf("please input update name!\n");
	char name[32];
	scanf("%s",name);
	lnode* p=find(name);
	if(p==NULL)
	{
		printf("no such student\n");
		
	}
	else
	{
		stu s1;
		printf("please input new student information!\n");
 		printf("id name age\n");
 		scanf("%d %s %d\n",&(s1.id),s1.name,&(s1.age));
 		p->DATE=s1;
 		
	}
	
} 
 
void del()
{
	printf("please input you want to delete name:");
	char name[32];
	scanf("%s",name);
	int t=deldata(name);
	if(t==1)
	{
		printf("del successful!\n");
	}
	else
	{
		printf("No such student!\n");
	}
} 


void adminlogin()
{
	printf("************Welcome adminlogin Employee System!******\n");
	printf("	Please input admin and password\n\n\n");
	char admin[32];
	printf("admin = ");
	scanf("%s",admin); 
	int password=0;
	printf("password =");
	scanf("%d",&password); 
	if((strcmp(admin,"admin")==0) && (password == 123))
	{
			
		while(1)
		{
			printf("*****************************************\n");
			printf("*		1、INPUT		*\n");
			printf("*		2、SHOW			*\n");
			printf("*		3、UPDATE		*\n");
			printf("*		4、DELETE		*\n");
			printf("*		5、QUIT			*\n");
			printf("*****************************************\n");
			int temp;
			printf("您的选择是(填写数字)："); 
			scanf("%d",&temp);
			switch(temp)
			{
				case 1:input();
					break;
				case 2:show();
					break;
				case 3:update();
					break;
				case 4:del();
					break;
				default:{
					listtofile();
					exit(0);}break;
			}
		}
	}
	else
	{
		printf("your admin or password error!");
	}
}

void employeelogin()
{
	printf("************Welcome Employee System!******\n");
	printf("请输入员工的名字：");
	char admin[32];
	printf("employee name is:");
	scanf("%s",admin);
	lnode* p=NULL;
	if((p=find(admin))==NULL)
	{
		printf("no such employee!\n");
	}
	else
	{
		printf("*****************************************\n");
		printf("*		1、SHOW	myself	*\n");
		printf("*		2、UPDATE		*\n");
		printf("*		3、QUIT			*\n");
		printf("*****************************************\n");
		while(1)
		{
			int temp;
			printf("您的选项是(输入数字)："); 
			scanf("%d",&temp);
			switch(temp)
			{
				case 1:
				{
				printf("id=%d name=%s age=%d\n",p->DATE.id,p->DATE.name,p->DATE.age);
				};break;
				case 2:{
					stu s1;
					printf("please input new information!\n");
			 		printf("id name age\n");
			 		scanf("%d %s %d\n",&(s1.id),s1.name,&(s1.age));
			 		p->DATE=s1;
					};break;
				default:{
					listtofile();
					exit(0);}break;
			}
		} 
	} 
}

void login()
{
	printf("请输入你的身份：\n");
	printf("1、管理员登陆		2、员工登陆\n");
	int temp=0;
	scanf("%d",&temp);
	switch(temp)
	{
		case 1:adminlogin();break;
		case 2:employeelogin();break;
		default:printf("请输入1或2！\n");break;
	}
}

//	lnode* head=NULL;
//	head=creatlist();
  int main()
{
	//创建链表节点，链表就是将节点一个一个链接再一起，形成一个链表，每个链表里面还可以添加数据再里面的，下面就是自己
	//可以创建一个整体的，创建链表的头，删除末尾的节点/添加末尾的节点/插入到中间的节点/答应整个链表的数据等； 
	//节点：数据区+指针区 
//	lnode* head=NULL;
	head=creatlist();
	filetolist();
	login();
	return 0;
		 
}
 
