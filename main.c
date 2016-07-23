#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <process.h>

#define STACK_INIT_SIZE 10
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
struct student/*定义学生类型，用于存放借出的书籍*/
{
	int cardnum;
	char lendBook[10];
 } student[1000];
 struct employ/*定义职工类型*/ 
 {
 	long int employnum;
 	char employname[15];
 	int employage;
 	char employsex[4];
 	char employleve[10];
 	long int employtage;
 }employ[50];
 struct book/*定义书的类型*/
 {
 	int booknum;
 	char bookname[10];
 	char bookcreat[10];
 	int truefalse;/*用于借书和还书模块 判断一本书是否借出的条件*/ 
  } book[1000];
  struct card/*借书卡的数据类型*/
  {
  	int cardnum;
  	char studentname[10];
  	int studentclass;
   } card[100];
   
void returnBook()/*还书函数*/
{ 
	FILE*fp,*fp2;/*定义两个文件指针，fp2用于修改数据时设立临时文件用，防止数据遭破坏*/
	int i,n,flag=0;
	int cardnum;
	char lendBook[10];
	printf("请输入的卡号\n");
	scanf("%d",&cardnum);
	if(!(fp=fopen("card.txt","r")))
	{
		printf("库中尚无卡号！请输入任意键继续！");
		getch();
		return; 
	}/*读取卡号记录*/
	for(i=0;fread(&card[i],sizeof(struct card),1,fp)!=0;i++)/*for循环判断卡号是否存在*/
	{
		if(card[i].cardnum==cardnum)/*卡号存在，进入下一循环*/
		{
			fclose(fp);
			printf("请输入要还的书的名字\n");
			scanf("%s",lendBook);
			fp=fopen("record.txt","r");
			for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)/*判断是否借阅了输入的书*/
			{
				if(strcmp(student[i].lendBook,lendBook)==0)/*借阅了该书，进入下一循环，否则出错显示*/
				{
					fclose(fp);
					if(!(fp=fopen("record.txt","r")))
					{
						printf("尚无借阅记录！请输入任意键继续！");
						getch();
						return; 
					}
					fp2=fopen("book1.txt","w");
					for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)
					{
						if(strcmp(student[i].lendBook,lendBook)==0)
						{
							continue;/*删除还掉的书的借书记录*/ 
						}
						fwrite(&student[i],sizeof(struct student),1,fp2);/*写入原来没还的书的记录*/ 
					}
					fclose(fp);
					fclose(fp2);
					fp=fopen("record.txt","w");
					if(!(fp2=fopen("book1.txt","r")))
					return;
					for(i=0;fread(&student[i],sizeof(struct student),1,fp2)!=0;i++)
					{
						fwrite(&student[i],sizeof(struct student),1,fp);/*将借书记录信息写回*/ 
					}
					fclose(fp);
					fclose(fp2);
					fopen("book1.txt","w");/*清临时文件的记录*/
					fclose(fp2);
					if(!(fp=fopen("book1.txt","r")))
					return;
					fp2=fopen("book1.txt","w");
					for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)/*将书的记录写入临时文件，防止因为修改信息破坏以前的记录*/
					{
						if(strcmp(book[i].bookname,lendBook)==0)
						{
							book[i].truefalse=1;
							fwrite(&book[i],sizeof(struct book),1,fp2);/*将还的书的原来状态设为无人借阅的*/
							continue; 
						}
						fwrite(&book[i],sizeof(struct book),1,fp2);
					 }
					 fclose(fp);
					 fclose(fp2);
					 fp=fopen("book.txt","w");
					 if(!(fp2=fopen("book1.txt","r")))
					 return;
					 for(i=0;fread(&book[i],sizeof(struct book),1,fp2)!=0;i++)
					 {
					 	fwrite(&book[i],sizeof(struct book),1,fp2);/*将临时文件写回*/ 
					  } 
					  fclose(fp);
					  fclose(fp2);
					  fopen("book1.txt","w");/*清临时文件*/
					  fclose(fp2);
					  printf("还书完毕，按任意键返回\n");
					  flag=1; 
				 } 
			 } 
			 if(flag==0)
			 printf("没有借这样的书。任意键返回\n");/*出错提示*/
			 fclose(fp);
			 getch();
			 return; 
		 } 
	 } 
	 printf("系统没这样的卡，和管理员联系，按任意键返回\n");/*出错提示*/
	 fclose(fp);
	 getch(); 
 } 
 
 
 void findBook()
 {
 	FILE*fp;
 	char bookname[10];
 	int i,flag=0;
 	if(!(fp=fopen("book.txt","r")))
 	{
 		printf("目前尚无图书！请输入任意字符继续");
		 return; 
	 }
	 printf("请输入要查找的书名\n");
	 scanf("%s",bookname);
	 for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
	 {
	 	if(strcmp(bookname,book[i].bookcreat)==0)
	 	{
	 		flag=1;
	 		if(book[i].truefalse==1)
	 		{
	 			printf("这本书的详细资料是：序号：%d 书名： %s 作者： %s 此书现在无人借阅\n",book[i].booknum,book[i].bookname,book[i].bookcreat);} 
			 else {printf("这本书的详细资料是：序号：%d 书名： %s 作者： %s 此书现在有人借阅\n",book[i].booknum,book[i].bookname,book[i].bookcreat);}
			 }
		 }
		 
		 if (flag==0)
		 printf("没有要查询的书籍\n");
		 fclose(fp);
		 return;
	 }
void findAuthor()
{
	FILE*fp;
	char bookname[10];
	int i,flag=0;
	if(!(fp=fopen("book.txt","r")))
	{
		printf("目前尚无图书可供查询！请输入任意字符继续");
		return; 
	}
	printf("请输入要查询的书的作者姓名\n");
	scanf("%s",bookname);
	for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
	{
		if(strcmp(bookname,book[i].bookcreat)==0)
		{
			flag=1;
			if(book[i].truefalse==1)
			{
				printf("这本书的详细资料是：序号： %d 书名： %s 作者： %s 此书现在无人借阅\n",book[i].booknum,book[i].bookname,book[i].bookcreat);
			}
			else{
				printf("这本书的详细资料是：序号： %d 书名： %s 作者： %s 此书现在有人借出\n",book[i].booknum,book[i].bookname,book[i].bookcreat);
			}
		}
	}
	if(flag==0)
	printf("没有要查询的书籍\n");
	fclose(fp);
	return; 
}


	 void lendCount()
	 {
	 	FILE*fp;
	 	int i,n=0;
	 	if(!(fp=fopen("record.txt","r")))
	 	{
	 		printf("目前尚无书借出！请输入任意字符继续");
			 getch();
			 return; 
		 }
		 for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)
		 {
		 	printf("卡号；%d 借出的书籍；%s\n",student[i].cardnum,student[i].lendBook);
		 	n=n+1;
		 }
		 fclose(fp);
		 printf("目前共有%d本书借出\n",n);
		 printf("按任意键\n");
		 getch();
	 }
	 
	 void queryBook()
	 {
	 	char ch5;
	 	do
	 	{
	 		printf("\n-------------欢迎进入图书馆查询系统----------------\n");
	 		printf(" 1: <按书名查找>\n");
	 		printf(" 2: <按作者查找>\n");
	 		printf(" 0: <返回>\n");
	 		printf("请输入0--2，其他输入非法！\n");
	 		scanf("%s",&ch5);
	 		ch5=getch();
	 		switch(ch5)
	 		{
	 			case'1':findBook();getch();break;
	 			case'2':findAuthor();getch();break;
	 			case'0':break;
	 			default:printf("无此操作\n按任意键返回\n");getch();break;
			 }
		 }while(ch5!='0');
	 }
	 
	 
	 void lendBook()
	 {
	 	FILE*fp,*fp2;
	 	int i,n;
	 	int cardnum;
	 	printf("请输入的卡号\n");
	 	scanf("%d",&cardnum);
	 	if(!(fp=fopen("card.txt","r")))
	 	{
	 		printf("目前尚无卡号！请输入任意字符继续");
			getch();
			return; 
		 }
		 for(i=0;fread(&card[i],sizeof(struct card),1,fp)!=0;i++)
		 {
		 	if(card[i].cardnum==cardnum)
		 	{
		 		n=i;
		 		fclose(fp);
		 		printf("请输入要借阅的书的名字\n");
		 		scanf("%s",student[n].lendBook);
		 		if(!(fp=fopen("book.txt","r")))
		 		{
		 			printf("目前图书馆尚无图书！请输入任意字符继续");
					getch();
					return; 
				 }
				 for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
				 {
				 	if(strcmp(book[i].bookname,student[n].lendBook)==0)
				 	{
				 		if(book[i].truefalse==0){printf("对不起，此书有人借出，请借其他书\n");fclose(fp);getch();return;}
				 		else
				 		fclose(fp);
				 		fp=fopen("record.txt","a");
				 		student[n].cardnum=cardnum;
				 		fwrite(&student[n],sizeof(struct student),1,fp);
				 		fclose(fp);
				 		fp=fopen("book.txt","r");
				 		fp2=fopen("book1.txt","w");
				 		for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i)
				 		{
				 			if(strcmp(book[i].bookname,student[n].lendBook)==0)
				 			{
				 				book[i].truefalse=0;
				 				fwrite(&book[i],sizeof(struct book),1,fp2);
				 				continue;
							}
							fwrite(&book[i],sizeof(struct book),1,fp);
						 }
						 fclose(fp);
						 fclose(fp2);
						 fopen("book1.txt","w");
						 fclose(fp2);
						 printf("借书完毕，按任意键返回\n");
						 getch();
						 return;
					 }
				 }
				 printf("不存在这样的书，任意键返回\n");
				 fclose(fp);
				 getch();
				 return;
			 }
		 }
		 printf("卡号不存在，请申请新卡，按任意键返回\n");
		 fclose(fp);
		 getch();
	 }
	 
	 void cardCount()
	 {
	 	FILE*fp;
	 	int i,n=0;
	 	if(!(fp=fopen("card.txt","r")))
	 	{
	 		printf("目前尚无卡办出！请输入任意字符继续");
			 getch();
			 return; 
		 }
		for(i=0;fread(&card[i],sizeof(struct card),1,fp)!=0;i++)
		{
			printf("第%d 张卡<卡号: %d 姓名: %s 班级: %d>\n",i+1,card[i].cardnum,card[i].studentname,card[i].studentclass);
			n=n+1;
		}
		fclose(fp);
		printf("目前共有%d张卡\n",n);
		printf("按任意键\n");
		getch();
	 }
	 
	 void delCard()
	 {
	 	FILE*fp,*fp2;
	 	int i;
	 	int cardnum;
	 	char choice;
	 	if(!(fp=fopen("card.txt","r")))
	 	{
	 		printf("目前尚无员工办卡！请输入任意键继续");
			 getch();
			 return; 
		 }
		 fp2=fopen("book1.txt","w");
		 printf("如果输入的卡号存在，系统自动删除该信息！如果不存在，系统不做任何改动\n");
		 scanf("%d",&cardnum);
		 for(i=0;fread(&card[i],sizeof(struct card),1,fp)!=0;i++)
		 {
		 	if(card[i].cardnum!=cardnum)
		 	{
		 		fwrite(&card[i],sizeof(struct card),1,fp2);
			 }
		 }
		 fclose(fp);
		 fclose(fp2);
		 printf("是否真的要删除该卡？删除后该书籍所有信息将无法恢复<y/n>\n");
		 scanf("%s",&choice);
		 if(choice=='y'||choice=='Y')
		 {
		 	fp=fopen("card.txt","w");
		 	fp2=fopen("book1.txt","r");
		 	for(i=0;fread(&card[i],sizeof(struct card),1,fp2)!=0;i++)
		 	{
		 		fwrite(&card[i],sizeof(struct card),1,fp);
			 }
			 fclose(fp);
			 fclose(fp2);
			 fp2=fopen("book1.txt","w");
			 fclose(fp2);
			 printf("按任意键返回\n");
			 getch();
			 return;
		 }
		 else{
		 	printf("按任意键返回\n");
		 	getch();
		 	return;
		 }
	 }
	 
	 
	 void addCard()
	 {
	 	FILE*fp;
	 	int i=0;
	 	fp=fopen("card.txt","a");
	 	printf("请输入卡号(卡号为整数)\n");
	 	scanf("%d",&card[i].cardnum);
	 	printf("请输入学生姓名\n");
	 	scanf("%s",card[i].studentname);
	 	printf("请输入班级\n");
	 	scanf("%d",&card[i].studentclass);
	 	fwrite(&card[i],sizeof(struct card),1,fp);
	 	fclose(fp);
	 	printf("输入完毕，任意键返回\n");
	 	getch();
	 }
	 void changeEmployee()
	 {
	 	FILE*fp,*fp2;
	 	char employname[10],choice;
	 	int i;
	 	if(!(fp=fopen("employ.txt","r")))
	 	{
	 		printf("目前尚无员工办卡！请输入任意字符继续");
			getch();
			return; 
		 }
		 fp2=fopen("book1.txt","w");
		 printf("请输入要修改的职工的姓名\n");
		 scanf("%s",employname);
		 for(i=0;fread(&employ[i],sizeof(struct employ),1,fp)!=0;i++)
		 {
		 	if(strcmp(employ[i].employname,employname)==0)
		 	{
		 		printf("所要修改的职工的资料如下，请选择要修改的内容\n");
		 		printf("<职工号：%1d 职工名：%s 年龄：%d 性别：%s 学历：%s 工资：%d>\n",employ[i].employnum,employ[i].employname,employ[i].employage,employ[i].employsex,
				 employ[i].employleve,employ[i].employtage);
				 printf("1: 修改职工的号\n");
				 printf("2: 修改职工名\n");
				 printf("3: 修改职工年龄\n");
				 printf("4: 修改职工工资\n");
				 printf("5: 修改职工学历\n");
				 printf("请输入1-5：");
				 scanf("%s",&choice);
				 choice=getch();
				 switch(choice)
				 {
				 	case '1':
				 		{
				 			printf("请输入新的职工号\n");
				 			scanf("%1d",&employ[i].employnum);
				 			fwrite(&employ[i],sizeof(struct employ),1,fp2);
						 }break;
				    case '2':
				    	{
				    		printf("请输入新的职工姓名\n");
				    		scanf("%s",employ[i].employname);
				    		fwrite(&employ[i],sizeof(struct employ),1,fp2);
						}break;
					case '3':
						{
							printf("请输入新的年龄\n");
							scanf("%d",&employ[i].employage);
							fwrite(&employ[i],sizeof(struct employ),1,fp2); 
						}break;
					case '4':
						{
							printf("请输入新的职工工资\n");
							scanf("%1d",&employ[i].employtage);
							fwrite(&employ[i],sizeof(struct employ),1,fp2);
						}break;
					case '5':
						{
							printf("请输入新的职工学历\n");
							scanf("%s",employ[i].employleve);
							fwrite(&employ[i],sizeof(struct employ),1,fp2);
						}break;
						default:printf("没有这样的操作");break; 
				  } 
				  continue;
			 }
			 fwrite(&employ[i],sizeof(struct employ),1,fp2);
		 }
		 fclose(fp);
		 fclose(fp2);
		 fp=fopen("employ.txt","w");
		 fp2=fopen("book1.txt","r");
		 for(i=0;fread(&employ[i],sizeof(struct employ),1,fp2)!=0;i++)
		 {
		 	fwrite(&employ[i],sizeof(struct employ),1,fp);
		 }
		 fclose(fp);
		 fclose(fp2);
		 fp2=fopen("book1.txt","w");
		 fclose(fp2);
		 printf("按任意键返回\n");
		 getchar();
		 return;
	 }
	 
	 
	 void delEmployee()
	 {
	 	FILE*fp,*fp2;
	 	int i;
	 	char employname[10],choice;
	 	if(!(fp=fopen("employ.txt","r")))
	 	{
	 		printf("目前尚无员工办卡！请输入任意字符继续");
			 getch();
			 return; 
		 }
		fp2=fopen("book1.txt","w");
		printf("请输入要删除的职工名\n");
		printf("如果输入的职工存在，系统自动删除该信息！如果不存在，系统不做任何改动\n");
		scanf("%s",employname);
		for(i=0;fread(&employ[i],sizeof(struct employ),1,fp)!=0;i++)
		{
			if(strcmp(employname,employ[i].employname)!=0)
			{
				fwrite(&employ[i],sizeof(struct employ),1,fp2);
			}
		}
		fclose(fp);
		fclose(fp2);
		printf("是否真的要删除该职工信息？删除后的所有信息将无法恢复<y/n>\n");
		scanf("%s",&choice);
		if(choice=='y'||choice=='Y')
		{
			fp=fopen("employ.txt","w");
			fp2=fopen("book1.txt","r");
			for(i=0;fread(&employ[i],sizeof(struct employ),1,fp2)!=0;i++)
			{
			fwrite(&employ[i],sizeof(struct employ),1,fp);
			}
			fclose(fp);
			fclose(fp2);
			fp2=fopen("book1.txt","w");
			fclose(fp2);
			printf("按任意键返回\n");
			getch();
			return;
		}
		else
		{
			printf("按任意键返回\n");
			getch();
			return; 
		}
	 }
	 
	void employeeCount()
	{
		FILE*fp;
		int i,n=0;
		if(!(fp=fopen("employ.txt","r")))
		{ 
			printf("目前无职工登记，请先添加职工！请输入任意字符继续");
			return;
		}
		for(i=0;fread(&employ[i],sizeof(struct employ),1,fp)!=0;i++)
		{
			printf("第%d职工的信息如下：\n<职工号：%1d 职工名：%s 年龄：%d 性别：%s 学历：%s 工资：%1d>\n",i+1,employ[i].employnum,employ[i].employname,employ[i].employage,
			employ[i].employsex,employ[i].employleve,employ[i].employtage);
			n=n+1;
		}
		fclose(fp);
		printf("目前共有%d个职工\n",n);
		printf("按任意键返回"); 
	}
	
	
	void addEmployee()
	{
		FILE*fp;
		char choice='y';
		int i=1;
		fp=fopen("employ.txt","a");
		while(choice=='y'||choice=='Y')
		{
			printf("请输入职工号码\n");
			scanf("%1d",&employ[i].employnum);
			printf("请输入职工名\n");
			scanf("%s",employ[i].employname);
			printf("请输入职工年龄\n");
			scanf("%d",&employ[i].employage);
			printf("请输入性别\n");
			scanf("%s",employ[i].employsex);
			printf("请输入职工的学历水平\n");
			scanf("%s",employ[i].employleve);
			printf("请输入职工的工资\n");
			scanf("%1d",&employ[i].employtage);
			
			fwrite(&employ[i],sizeof(struct employ),1,fp);
			printf("是否要输入下个职工信息？(y/n)\n");
			while((choice=getchar())=='\n');
		}
		printf("按任意键返回\n");
		fclose(fp);
		return;
	}
	
	
	void addBook()
	{
		FILE*fp;
		int i=0;
		char choice='y';
		fp=fopen("book.txt","a");
		while(choice=='y'||choice=='Y')
		{
			printf("请输入第%d本书的序号\n",i+1);
			scanf("%d",&book[i].booknum);
			printf("请输入书名\n");
			scanf("%s",book[i].bookname);
			printf("请输入书的作者\n");
			scanf("%s",book[i].bookcreat);
			printf("请设为1或0，1代表书还没人借，0代表书已经借出，设其他值，程序运行时无法得出正常结果\n");
			printf("请设定书的状态\n");
			scanf("%d",&book[i].truefalse);
			fwrite(&book[i],sizeof(struct book),1,fp);
			printf("是否要输入下本书(y/n)\n");
			while((choice=getchar())=='\n');
			i++; 
		}
		fclose(fp);
	}
	
	void bookCount()
	{
		FILE*fp;
		int i,n=0;
		if(!(fp=fopen("book.txt","r")))
		{
			printf("目前尚无入库书籍,请先添加！请输入任意字符继续");
			return; 
		}
		for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
		{
			if(book[i].booknum!=0&&strlen(book[i].bookname)!=0&&strlen(book[i].bookcreat)!=0)
			{
			printf("第%d本书<序号：%d 书名：%s 作者：%s 状态：%d>\n",i+1,book[i].booknum,book[i].bookname,book[i].bookcreat,book[i].truefalse);
			n=n+1;
		}
	}
	fclose(fp);
	printf("目前共有%d本书\n",n);
	printf("按任意键\n");
 }
 
 void delBook()
 {
 	FILE*fp,*fp2;
 	int i;
 	char bookname[10],choice;
 	if(!(fp=fopen("book.txt","r")))
 	{
 		printf("目前尚无图书可供删除！请输入任意字符继续");
		 getch();
		 return; 
	 }
	 fp2=fopen("book.txt","w");
	 printf("请输入要删除的书名\n");
	 printf("如果输入的书名存在，系统自动删除该信息！如果不存在，系统不做任何改动\n");
	 scanf("%s",bookname);
	 for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
	 {
	 if(strcmp(bookname,book[i].bookname)!=0)
	 {
	 	fwrite(&book[i],sizeof(struct book),1,fp2);
	  } 
 }
 fclose(fp);
 fclose(fp2);
 printf("是否真的要删除该书籍？删除后该书籍的所有信息将无法恢复<y/n>\n");
 scanf("%s",&choice);
 if(choice=='y'||choice=='Y')
 {
 	fp=fopen("book.txt","w");
 	fp2=fopen("book1.txt","r");
 	for(i=0;fread(&book[i],sizeof(struct book),1,fp2)!=0;i++)
 	{
 		fwrite(&book[i],sizeof(struct book),1,fp);
	 }
	 fclose(fp);
	 fclose(fp2);
	 fp2=fopen("book1.txt","w");
	 fclose(fp2);
	 printf("按任意键返回\n");
	 getch();
	 return; 
 }
 else
 {
 	printf("按任意键返回\n");
 	getch();
 	return;
 }
}


void changeBook()
{
	FILE*fp,*fp2;
	char bookname[10],choice;
	int i;
	if(!(fp=fopen("book.txt","r")))
	{
		printf("目前书库无书！请输入任意字符继续");
		getch();
		return;
	}
	fp2=fopen("book1.txt","w");
	printf("请输入要修改的书籍的名字\n");
	scanf("%s",bookname);
	for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
	{
		printf("所要修改的书的资料如下，请选择要修改的内容\n");
		printf("序号： <%d>  书名：<%s> 作者：<%s> \n",book[i].booknum,book[i].bookname,book[i].bookcreat);
		printf("1: 修改书的序号\n");
		printf("2: 修改书名\n");
		printf("3: 修改作者\n");
		printf("请输入1-3:");
		choice=getch();
		switch(choice)
		{
			case '1':
				{
					printf("请输入新的序号\n");
					scanf("%d",&book[i].booknum);
					fwrite(&book[i],sizeof(struct book),1,fp2);
				}break;
			case '2':
				{
					printf("请输入新的书名\n");
					scanf("%s",book[i].bookname);
					fwrite(&book[i],sizeof(struct book),1,fp2);
				}break;
			case '3':
				{
					printf("请输入新的作者\n");
					scanf("%s",book[i].bookcreat);
					fwrite(&book[i],sizeof(struct book),1,fp2); 
				}break;
			default:printf("没有这样的操作");break; 
		 } 
		 continue;
	}
	fwrite(&book[i],sizeof(struct book),1,fp2);
    fclose(fp);
	fclose(fp2);
	fp=fopen("book.txt","w");
	fp2=fopen("book1.txt","r");
	for(i=0;fread(&book[i],sizeof(struct book),1,fp2)!=0;i++)
	{
	fwrite(&book[i],sizeof(struct book),1,fp);
	}
	fclose(fp);
	fclose(fp2);
	fp2=fopen("book1.txt","w");
	fclose(fp2);
	printf("按任意键返回\n");
	getchar();
	return;
}


void main()
{
	char ch1,ch2,ch3,ch4;
	do
	{
		system("cls");
		printf("*******************************************************************************\n");
		printf("**********************欢迎进入中文图书馆管理系统！*****************************\n");
		printf("*******************************************************************************\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~\t\t\t\t~~~~~~~~~~~~~~~~~~~\n");
		printf("\t\t请选择操作类型：\n");
		printf("1: <查阅图书>\n");
		printf("2: <借阅图书>\n");
		printf("3: <管理系统>\n");
		printf("4: <还书>\n");
		printf("0: <退出>\n");
		printf("请输入 0--4\n");
		ch1=getch();
		switch(ch1)
		{
			case '1':queryBook();break;
			case '2':lendBook();break;
			case '3':{
				do
				{
					system("cls");
					printf("\n-----------欢迎进入管理系统！--------\n");
					printf("1: <增加图书>\n");
					printf("2: <删除图书>\n");
					printf("3: <修改图书资料>\n");
					printf("4: <书籍统计>\n");
					printf("5: <职工管理系统>\n");
					printf("6；<学生管理系统>\n");
					printf("0: <返回>\n");
					printf("请输入0--6，其他输入非法！\n");
					ch2=getch();
					switch(ch2)
					{
						case '1':addBook();break;
						case '2':delBook();break;
						case '3':changeBook();break;
						case '4':bookCount();getch();break;
						case '5':{
					do{
						system("cls");
						printf("----------欢迎进入职工管理系统！-----------\n");
						printf("1: <增加员工>\n");
						printf("2: <删除员工>\n");
						printf("3: <修改员工资料>\n");
						printf("4: <员工统计>\n");
						printf("0: <返回>\n");
						printf("请输入0---4，其他输入非法！\n");
					ch3=getch();
					switch(ch3)
					{
						 case '1':addEmployee();getch();break;
						 case '2':delEmployee();break;
						 case '3':changeEmployee();break;
						 case '4':employeeCount();getch();break;
						 case '0':break;
						 default:printf("无此操作\n");getch();break;
					 } 
					}while(ch3!='0');
					
						}break;
					case '6':{
						do
						{
						system("cls");
						printf("-------------欢迎进入学生管理系统！-----------\n");
						printf("1: <申请新卡>\n");
						printf("2: <删除卡号>\n");
						printf("3: <借书统计>\n");
						printf("4: <卡号统计>\n");
						printf("0: <返回>\n");
						printf("请输入 0---4，其他输入非法！\n");
					ch4=getch();
					switch(ch4)
					{
						case '1':addCard();break;
						case '2':delCard();break;
						case '3':lendCount();break;
						case '4':cardCount();break;
						case '0':break;
						default:printf("无此操作\n按任意键返回\n");getch();break;
					 } 
					}
					while(ch4!='0');
					}break;
				case '0':break;
				default:printf("无此操作按任意键返回\n");getch();break;
				}
			}while(ch2!='0');
		}break;
		case '4':returnBook();break;
		case '0':break;
		default:printf("无此操作\n按任意键返回\n");getch();break;
	}
 }while(ch1!='0'); 
}


 
