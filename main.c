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
struct student/*����ѧ�����ͣ����ڴ�Ž�����鼮*/
{
	int cardnum;
	char lendBook[10];
 } student[1000];
 struct employ/*����ְ������*/ 
 {
 	long int employnum;
 	char employname[15];
 	int employage;
 	char employsex[4];
 	char employleve[10];
 	long int employtage;
 }employ[50];
 struct book/*�����������*/
 {
 	int booknum;
 	char bookname[10];
 	char bookcreat[10];
 	int truefalse;/*���ڽ���ͻ���ģ�� �ж�һ�����Ƿ���������*/ 
  } book[1000];
  struct card/*���鿨����������*/
  {
  	int cardnum;
  	char studentname[10];
  	int studentclass;
   } card[100];
   
void returnBook()/*���麯��*/
{ 
	FILE*fp,*fp2;/*���������ļ�ָ�룬fp2�����޸�����ʱ������ʱ�ļ��ã���ֹ�������ƻ�*/
	int i,n,flag=0;
	int cardnum;
	char lendBook[10];
	printf("������Ŀ���\n");
	scanf("%d",&cardnum);
	if(!(fp=fopen("card.txt","r")))
	{
		printf("�������޿��ţ������������������");
		getch();
		return; 
	}/*��ȡ���ż�¼*/
	for(i=0;fread(&card[i],sizeof(struct card),1,fp)!=0;i++)/*forѭ���жϿ����Ƿ����*/
	{
		if(card[i].cardnum==cardnum)/*���Ŵ��ڣ�������һѭ��*/
		{
			fclose(fp);
			printf("������Ҫ�����������\n");
			scanf("%s",lendBook);
			fp=fopen("record.txt","r");
			for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)/*�ж��Ƿ�������������*/
			{
				if(strcmp(student[i].lendBook,lendBook)==0)/*�����˸��飬������һѭ�������������ʾ*/
				{
					fclose(fp);
					if(!(fp=fopen("record.txt","r")))
					{
						printf("���޽��ļ�¼�������������������");
						getch();
						return; 
					}
					fp2=fopen("book1.txt","w");
					for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)
					{
						if(strcmp(student[i].lendBook,lendBook)==0)
						{
							continue;/*ɾ����������Ľ����¼*/ 
						}
						fwrite(&student[i],sizeof(struct student),1,fp2);/*д��ԭ��û������ļ�¼*/ 
					}
					fclose(fp);
					fclose(fp2);
					fp=fopen("record.txt","w");
					if(!(fp2=fopen("book1.txt","r")))
					return;
					for(i=0;fread(&student[i],sizeof(struct student),1,fp2)!=0;i++)
					{
						fwrite(&student[i],sizeof(struct student),1,fp);/*�������¼��Ϣд��*/ 
					}
					fclose(fp);
					fclose(fp2);
					fopen("book1.txt","w");/*����ʱ�ļ��ļ�¼*/
					fclose(fp2);
					if(!(fp=fopen("book1.txt","r")))
					return;
					fp2=fopen("book1.txt","w");
					for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)/*����ļ�¼д����ʱ�ļ�����ֹ��Ϊ�޸���Ϣ�ƻ���ǰ�ļ�¼*/
					{
						if(strcmp(book[i].bookname,lendBook)==0)
						{
							book[i].truefalse=1;
							fwrite(&book[i],sizeof(struct book),1,fp2);/*���������ԭ��״̬��Ϊ���˽��ĵ�*/
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
					 	fwrite(&book[i],sizeof(struct book),1,fp2);/*����ʱ�ļ�д��*/ 
					  } 
					  fclose(fp);
					  fclose(fp2);
					  fopen("book1.txt","w");/*����ʱ�ļ�*/
					  fclose(fp2);
					  printf("������ϣ������������\n");
					  flag=1; 
				 } 
			 } 
			 if(flag==0)
			 printf("û�н��������顣���������\n");/*������ʾ*/
			 fclose(fp);
			 getch();
			 return; 
		 } 
	 } 
	 printf("ϵͳû�����Ŀ����͹���Ա��ϵ�������������\n");/*������ʾ*/
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
 		printf("Ŀǰ����ͼ�飡�����������ַ�����");
		 return; 
	 }
	 printf("������Ҫ���ҵ�����\n");
	 scanf("%s",bookname);
	 for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
	 {
	 	if(strcmp(bookname,book[i].bookcreat)==0)
	 	{
	 		flag=1;
	 		if(book[i].truefalse==1)
	 		{
	 			printf("�Ȿ�����ϸ�����ǣ���ţ�%d ������ %s ���ߣ� %s �����������˽���\n",book[i].booknum,book[i].bookname,book[i].bookcreat);} 
			 else {printf("�Ȿ�����ϸ�����ǣ���ţ�%d ������ %s ���ߣ� %s �����������˽���\n",book[i].booknum,book[i].bookname,book[i].bookcreat);}
			 }
		 }
		 
		 if (flag==0)
		 printf("û��Ҫ��ѯ���鼮\n");
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
		printf("Ŀǰ����ͼ��ɹ���ѯ�������������ַ�����");
		return; 
	}
	printf("������Ҫ��ѯ�������������\n");
	scanf("%s",bookname);
	for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
	{
		if(strcmp(bookname,book[i].bookcreat)==0)
		{
			flag=1;
			if(book[i].truefalse==1)
			{
				printf("�Ȿ�����ϸ�����ǣ���ţ� %d ������ %s ���ߣ� %s �����������˽���\n",book[i].booknum,book[i].bookname,book[i].bookcreat);
			}
			else{
				printf("�Ȿ�����ϸ�����ǣ���ţ� %d ������ %s ���ߣ� %s �����������˽��\n",book[i].booknum,book[i].bookname,book[i].bookcreat);
			}
		}
	}
	if(flag==0)
	printf("û��Ҫ��ѯ���鼮\n");
	fclose(fp);
	return; 
}


	 void lendCount()
	 {
	 	FILE*fp;
	 	int i,n=0;
	 	if(!(fp=fopen("record.txt","r")))
	 	{
	 		printf("Ŀǰ���������������������ַ�����");
			 getch();
			 return; 
		 }
		 for(i=0;fread(&student[i],sizeof(struct student),1,fp)!=0;i++)
		 {
		 	printf("���ţ�%d ������鼮��%s\n",student[i].cardnum,student[i].lendBook);
		 	n=n+1;
		 }
		 fclose(fp);
		 printf("Ŀǰ����%d������\n",n);
		 printf("�������\n");
		 getch();
	 }
	 
	 void queryBook()
	 {
	 	char ch5;
	 	do
	 	{
	 		printf("\n-------------��ӭ����ͼ��ݲ�ѯϵͳ----------------\n");
	 		printf(" 1: <����������>\n");
	 		printf(" 2: <�����߲���>\n");
	 		printf(" 0: <����>\n");
	 		printf("������0--2����������Ƿ���\n");
	 		scanf("%s",&ch5);
	 		ch5=getch();
	 		switch(ch5)
	 		{
	 			case'1':findBook();getch();break;
	 			case'2':findAuthor();getch();break;
	 			case'0':break;
	 			default:printf("�޴˲���\n�����������\n");getch();break;
			 }
		 }while(ch5!='0');
	 }
	 
	 
	 void lendBook()
	 {
	 	FILE*fp,*fp2;
	 	int i,n;
	 	int cardnum;
	 	printf("������Ŀ���\n");
	 	scanf("%d",&cardnum);
	 	if(!(fp=fopen("card.txt","r")))
	 	{
	 		printf("Ŀǰ���޿��ţ������������ַ�����");
			getch();
			return; 
		 }
		 for(i=0;fread(&card[i],sizeof(struct card),1,fp)!=0;i++)
		 {
		 	if(card[i].cardnum==cardnum)
		 	{
		 		n=i;
		 		fclose(fp);
		 		printf("������Ҫ���ĵ��������\n");
		 		scanf("%s",student[n].lendBook);
		 		if(!(fp=fopen("book.txt","r")))
		 		{
		 			printf("Ŀǰͼ�������ͼ�飡�����������ַ�����");
					getch();
					return; 
				 }
				 for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
				 {
				 	if(strcmp(book[i].bookname,student[n].lendBook)==0)
				 	{
				 		if(book[i].truefalse==0){printf("�Բ��𣬴������˽�������������\n");fclose(fp);getch();return;}
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
						 printf("������ϣ������������\n");
						 getch();
						 return;
					 }
				 }
				 printf("�������������飬���������\n");
				 fclose(fp);
				 getch();
				 return;
			 }
		 }
		 printf("���Ų����ڣ��������¿��������������\n");
		 fclose(fp);
		 getch();
	 }
	 
	 void cardCount()
	 {
	 	FILE*fp;
	 	int i,n=0;
	 	if(!(fp=fopen("card.txt","r")))
	 	{
	 		printf("Ŀǰ���޿�����������������ַ�����");
			 getch();
			 return; 
		 }
		for(i=0;fread(&card[i],sizeof(struct card),1,fp)!=0;i++)
		{
			printf("��%d �ſ�<����: %d ����: %s �༶: %d>\n",i+1,card[i].cardnum,card[i].studentname,card[i].studentclass);
			n=n+1;
		}
		fclose(fp);
		printf("Ŀǰ����%d�ſ�\n",n);
		printf("�������\n");
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
	 		printf("Ŀǰ����Ա���쿨�����������������");
			 getch();
			 return; 
		 }
		 fp2=fopen("book1.txt","w");
		 printf("�������Ŀ��Ŵ��ڣ�ϵͳ�Զ�ɾ������Ϣ����������ڣ�ϵͳ�����κθĶ�\n");
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
		 printf("�Ƿ����Ҫɾ���ÿ���ɾ������鼮������Ϣ���޷��ָ�<y/n>\n");
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
			 printf("�����������\n");
			 getch();
			 return;
		 }
		 else{
		 	printf("�����������\n");
		 	getch();
		 	return;
		 }
	 }
	 
	 
	 void addCard()
	 {
	 	FILE*fp;
	 	int i=0;
	 	fp=fopen("card.txt","a");
	 	printf("�����뿨��(����Ϊ����)\n");
	 	scanf("%d",&card[i].cardnum);
	 	printf("������ѧ������\n");
	 	scanf("%s",card[i].studentname);
	 	printf("������༶\n");
	 	scanf("%d",&card[i].studentclass);
	 	fwrite(&card[i],sizeof(struct card),1,fp);
	 	fclose(fp);
	 	printf("������ϣ����������\n");
	 	getch();
	 }
	 void changeEmployee()
	 {
	 	FILE*fp,*fp2;
	 	char employname[10],choice;
	 	int i;
	 	if(!(fp=fopen("employ.txt","r")))
	 	{
	 		printf("Ŀǰ����Ա���쿨�������������ַ�����");
			getch();
			return; 
		 }
		 fp2=fopen("book1.txt","w");
		 printf("������Ҫ�޸ĵ�ְ��������\n");
		 scanf("%s",employname);
		 for(i=0;fread(&employ[i],sizeof(struct employ),1,fp)!=0;i++)
		 {
		 	if(strcmp(employ[i].employname,employname)==0)
		 	{
		 		printf("��Ҫ�޸ĵ�ְ�����������£���ѡ��Ҫ�޸ĵ�����\n");
		 		printf("<ְ���ţ�%1d ְ������%s ���䣺%d �Ա�%s ѧ����%s ���ʣ�%d>\n",employ[i].employnum,employ[i].employname,employ[i].employage,employ[i].employsex,
				 employ[i].employleve,employ[i].employtage);
				 printf("1: �޸�ְ���ĺ�\n");
				 printf("2: �޸�ְ����\n");
				 printf("3: �޸�ְ������\n");
				 printf("4: �޸�ְ������\n");
				 printf("5: �޸�ְ��ѧ��\n");
				 printf("������1-5��");
				 scanf("%s",&choice);
				 choice=getch();
				 switch(choice)
				 {
				 	case '1':
				 		{
				 			printf("�������µ�ְ����\n");
				 			scanf("%1d",&employ[i].employnum);
				 			fwrite(&employ[i],sizeof(struct employ),1,fp2);
						 }break;
				    case '2':
				    	{
				    		printf("�������µ�ְ������\n");
				    		scanf("%s",employ[i].employname);
				    		fwrite(&employ[i],sizeof(struct employ),1,fp2);
						}break;
					case '3':
						{
							printf("�������µ�����\n");
							scanf("%d",&employ[i].employage);
							fwrite(&employ[i],sizeof(struct employ),1,fp2); 
						}break;
					case '4':
						{
							printf("�������µ�ְ������\n");
							scanf("%1d",&employ[i].employtage);
							fwrite(&employ[i],sizeof(struct employ),1,fp2);
						}break;
					case '5':
						{
							printf("�������µ�ְ��ѧ��\n");
							scanf("%s",employ[i].employleve);
							fwrite(&employ[i],sizeof(struct employ),1,fp2);
						}break;
						default:printf("û�������Ĳ���");break; 
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
		 printf("�����������\n");
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
	 		printf("Ŀǰ����Ա���쿨�������������ַ�����");
			 getch();
			 return; 
		 }
		fp2=fopen("book1.txt","w");
		printf("������Ҫɾ����ְ����\n");
		printf("��������ְ�����ڣ�ϵͳ�Զ�ɾ������Ϣ����������ڣ�ϵͳ�����κθĶ�\n");
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
		printf("�Ƿ����Ҫɾ����ְ����Ϣ��ɾ�����������Ϣ���޷��ָ�<y/n>\n");
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
			printf("�����������\n");
			getch();
			return;
		}
		else
		{
			printf("�����������\n");
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
			printf("Ŀǰ��ְ���Ǽǣ��������ְ���������������ַ�����");
			return;
		}
		for(i=0;fread(&employ[i],sizeof(struct employ),1,fp)!=0;i++)
		{
			printf("��%dְ������Ϣ���£�\n<ְ���ţ�%1d ְ������%s ���䣺%d �Ա�%s ѧ����%s ���ʣ�%1d>\n",i+1,employ[i].employnum,employ[i].employname,employ[i].employage,
			employ[i].employsex,employ[i].employleve,employ[i].employtage);
			n=n+1;
		}
		fclose(fp);
		printf("Ŀǰ����%d��ְ��\n",n);
		printf("�����������"); 
	}
	
	
	void addEmployee()
	{
		FILE*fp;
		char choice='y';
		int i=1;
		fp=fopen("employ.txt","a");
		while(choice=='y'||choice=='Y')
		{
			printf("������ְ������\n");
			scanf("%1d",&employ[i].employnum);
			printf("������ְ����\n");
			scanf("%s",employ[i].employname);
			printf("������ְ������\n");
			scanf("%d",&employ[i].employage);
			printf("�������Ա�\n");
			scanf("%s",employ[i].employsex);
			printf("������ְ����ѧ��ˮƽ\n");
			scanf("%s",employ[i].employleve);
			printf("������ְ���Ĺ���\n");
			scanf("%1d",&employ[i].employtage);
			
			fwrite(&employ[i],sizeof(struct employ),1,fp);
			printf("�Ƿ�Ҫ�����¸�ְ����Ϣ��(y/n)\n");
			while((choice=getchar())=='\n');
		}
		printf("�����������\n");
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
			printf("�������%d��������\n",i+1);
			scanf("%d",&book[i].booknum);
			printf("����������\n");
			scanf("%s",book[i].bookname);
			printf("�������������\n");
			scanf("%s",book[i].bookcreat);
			printf("����Ϊ1��0��1�����黹û�˽裬0�������Ѿ������������ֵ����������ʱ�޷��ó��������\n");
			printf("���趨���״̬\n");
			scanf("%d",&book[i].truefalse);
			fwrite(&book[i],sizeof(struct book),1,fp);
			printf("�Ƿ�Ҫ�����±���(y/n)\n");
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
			printf("Ŀǰ��������鼮,������ӣ������������ַ�����");
			return; 
		}
		for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
		{
			if(book[i].booknum!=0&&strlen(book[i].bookname)!=0&&strlen(book[i].bookcreat)!=0)
			{
			printf("��%d����<��ţ�%d ������%s ���ߣ�%s ״̬��%d>\n",i+1,book[i].booknum,book[i].bookname,book[i].bookcreat,book[i].truefalse);
			n=n+1;
		}
	}
	fclose(fp);
	printf("Ŀǰ����%d����\n",n);
	printf("�������\n");
 }
 
 void delBook()
 {
 	FILE*fp,*fp2;
 	int i;
 	char bookname[10],choice;
 	if(!(fp=fopen("book.txt","r")))
 	{
 		printf("Ŀǰ����ͼ��ɹ�ɾ���������������ַ�����");
		 getch();
		 return; 
	 }
	 fp2=fopen("book.txt","w");
	 printf("������Ҫɾ��������\n");
	 printf("���������������ڣ�ϵͳ�Զ�ɾ������Ϣ����������ڣ�ϵͳ�����κθĶ�\n");
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
 printf("�Ƿ����Ҫɾ�����鼮��ɾ������鼮��������Ϣ���޷��ָ�<y/n>\n");
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
	 printf("�����������\n");
	 getch();
	 return; 
 }
 else
 {
 	printf("�����������\n");
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
		printf("Ŀǰ������飡�����������ַ�����");
		getch();
		return;
	}
	fp2=fopen("book1.txt","w");
	printf("������Ҫ�޸ĵ��鼮������\n");
	scanf("%s",bookname);
	for(i=0;fread(&book[i],sizeof(struct book),1,fp)!=0;i++)
	{
		printf("��Ҫ�޸ĵ�����������£���ѡ��Ҫ�޸ĵ�����\n");
		printf("��ţ� <%d>  ������<%s> ���ߣ�<%s> \n",book[i].booknum,book[i].bookname,book[i].bookcreat);
		printf("1: �޸�������\n");
		printf("2: �޸�����\n");
		printf("3: �޸�����\n");
		printf("������1-3:");
		choice=getch();
		switch(choice)
		{
			case '1':
				{
					printf("�������µ����\n");
					scanf("%d",&book[i].booknum);
					fwrite(&book[i],sizeof(struct book),1,fp2);
				}break;
			case '2':
				{
					printf("�������µ�����\n");
					scanf("%s",book[i].bookname);
					fwrite(&book[i],sizeof(struct book),1,fp2);
				}break;
			case '3':
				{
					printf("�������µ�����\n");
					scanf("%s",book[i].bookcreat);
					fwrite(&book[i],sizeof(struct book),1,fp2); 
				}break;
			default:printf("û�������Ĳ���");break; 
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
	printf("�����������\n");
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
		printf("**********************��ӭ��������ͼ��ݹ���ϵͳ��*****************************\n");
		printf("*******************************************************************************\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~\t\t\t\t~~~~~~~~~~~~~~~~~~~\n");
		printf("\t\t��ѡ��������ͣ�\n");
		printf("1: <����ͼ��>\n");
		printf("2: <����ͼ��>\n");
		printf("3: <����ϵͳ>\n");
		printf("4: <����>\n");
		printf("0: <�˳�>\n");
		printf("������ 0--4\n");
		ch1=getch();
		switch(ch1)
		{
			case '1':queryBook();break;
			case '2':lendBook();break;
			case '3':{
				do
				{
					system("cls");
					printf("\n-----------��ӭ�������ϵͳ��--------\n");
					printf("1: <����ͼ��>\n");
					printf("2: <ɾ��ͼ��>\n");
					printf("3: <�޸�ͼ������>\n");
					printf("4: <�鼮ͳ��>\n");
					printf("5: <ְ������ϵͳ>\n");
					printf("6��<ѧ������ϵͳ>\n");
					printf("0: <����>\n");
					printf("������0--6����������Ƿ���\n");
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
						printf("----------��ӭ����ְ������ϵͳ��-----------\n");
						printf("1: <����Ա��>\n");
						printf("2: <ɾ��Ա��>\n");
						printf("3: <�޸�Ա������>\n");
						printf("4: <Ա��ͳ��>\n");
						printf("0: <����>\n");
						printf("������0---4����������Ƿ���\n");
					ch3=getch();
					switch(ch3)
					{
						 case '1':addEmployee();getch();break;
						 case '2':delEmployee();break;
						 case '3':changeEmployee();break;
						 case '4':employeeCount();getch();break;
						 case '0':break;
						 default:printf("�޴˲���\n");getch();break;
					 } 
					}while(ch3!='0');
					
						}break;
					case '6':{
						do
						{
						system("cls");
						printf("-------------��ӭ����ѧ������ϵͳ��-----------\n");
						printf("1: <�����¿�>\n");
						printf("2: <ɾ������>\n");
						printf("3: <����ͳ��>\n");
						printf("4: <����ͳ��>\n");
						printf("0: <����>\n");
						printf("������ 0---4����������Ƿ���\n");
					ch4=getch();
					switch(ch4)
					{
						case '1':addCard();break;
						case '2':delCard();break;
						case '3':lendCount();break;
						case '4':cardCount();break;
						case '0':break;
						default:printf("�޴˲���\n�����������\n");getch();break;
					 } 
					}
					while(ch4!='0');
					}break;
				case '0':break;
				default:printf("�޴˲��������������\n");getch();break;
				}
			}while(ch2!='0');
		}break;
		case '4':returnBook();break;
		case '0':break;
		default:printf("�޴˲���\n�����������\n");getch();break;
	}
 }while(ch1!='0'); 
}


 
