/*
����S����Դ���� 
������ʷ��Ŷ�Ԫʽ<�����ʾ�����ʵ�����ֵ>
1~9��Ӧ�ؼ��֣�10��Ӧ��ʶ����11��Ӧ�޷���������
12~22��Ӧ����� ��23~26��Ӧ�ֽ�� 
*/
 
#include<stdio.h>
#include<string.h>

int syn;//��ŵ��ʵ����� 
int p;//���ڱ�������Դ����
int line;//������ʶ���� 
char ch;//���ڶ�ȡ����Դ���� 
int sum;//�����������ֵ�ֵ 

char program[1000],token[10];//program�����洢Դ���룬token������Ŵ��� 

 
char *rwtab[9]={"begin","if","then",
                "else","while","do",
				"Const","Var","end"};//�ؼ��� 

char* lexicalType[27];//�ʷ����� 

void initLexicalType()
{
	int i;
	for(i=1;i<=9;i++)
	    lexicalType[i]="ReservedWord";
    lexicalType[10]="Identifier";
    lexicalType[11]="Number";
	for(i=12;i<=22;i++)
	    lexicalType[i]="Operator"; 
	for(i=23;i<=26;i++)
	    lexicalType[i]="Delimiter";
}              
 
bool isDigital(char ch)
{
    if(ch<='9'&&ch>='0')
        return true;
    else
        return false;
}
//ʶ����ĸ 
bool isAlpha(char ch)
{
    if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
        return true;
    else
        return false;
}

void Scanner()
{
	int m;
    for(m=0;m<10;m++)
    {
        token[m]='\0';
    }
    m=0;
	//��ʼ����������Ϊ�� 
    ch=program[p++];
    while(ch==' '||ch=='\n'||ch=='\t')//�޳��հ�
    {
    	if(ch=='\n'){
    	    printf("%d:",line);//������������д��� 
    	    for(int i=p;program[i]!='\0'&&program[i]!='\n';i++)
	            printf("%c",program[i]);
	        printf("\n");    
		    line++; 
		}
        ch=program[p++];
    }
    if(isAlpha(ch)){
        do{
            token[m++]=ch;
            ch=program[p++];
        }while(isAlpha(ch)||isDigital(ch));
        p--;
        syn=10;//��ʶ������ 
        token[m++]='\0';
        for(int n=0;n<=8;n++)
        {
            if(strcmp(token,rwtab[n])==0)
            {
                syn=n+1;//�ؼ������� 
                break;
            }//ʶ��ؼ��� 
        }
        return;
    }
    else if(isDigital(ch))
    {
        sum=0;
        while(isDigital(ch))
        {
            sum=sum*10+ch-'0';
            ch=program[p++];
        }
        p--;
        syn=11;//�޷����������� 
        if(isAlpha(ch))
            syn=-1;//�ʷ����� 
        return;
    }
    else
    {
        token[0]=ch;
        switch(ch)
        {
            case '<':ch=program[p++];
                    if(ch=='>')
                    {
                        syn=22;//ʶ��<> 
                        token[1]=ch;
                    }
                    else if(ch=='=')
                    {
                        syn=21;//ʶ��<= 
                        token[1]=ch;
                    }
                    else{
                        syn=20;//ʶ��< 
                        p--;
                    }
                    break;
            case '>':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=19;//ʶ��>= 
                        token[1]=ch;
                    }
                    else{
                        syn=18;//ʶ��> 
                        p--;
                    }           
                    break;
            case '=':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=17;//ʶ��== 
                        token[1]=ch;
                    }
                    else{
                        syn=16;//ʶ��= 
                        p--;
                    }
                    break;
            case '+':syn=12;break;//ʶ��+ 
            case '-':syn=13;break;//ʶ��- 
            case '*':syn=14;break;//ʶ��* 
            case '/':syn=15;break;//ʶ��/ 
            case ';':syn=23;break;//ʶ�� 
            case '(':syn=24;break;//ʶ�� 
            case ')':syn=25;break;//ʶ�� 
            case ',':syn=26;break;//ʶ�� 
            case '#':syn=0;break;//ʶ��# 
            default:syn=-1;break;//�ʷ�����                   
        }
        return;
    }
}

//������ʷ��Ŷ�Ԫʽ<�����ʾ�����ʵ�����ֵ> 
//1~9��Ӧ�ؼ��֣�10��Ӧ��ʶ����11��Ӧ�޷���������
//12~22��Ӧ����� ��23~26��Ӧ�ֽ�� 
void Print() 
{	   
    if(syn==11)//�޷���������������ֵΪ��value 
        printf("  %s:<%d,%d>\n",lexicalType[syn],syn,sum);
    else//������������ֵΪ�䵥������ 
        printf("  %s:<%d,%s>\n",lexicalType[syn],syn,token);
}


int main()
{
	p=0;
    line=1;
	initLexicalType(); 
    printf("����ʷ���������#��Ϊ����\n");
    do
    {
        ch=getchar();
        program[p++]=ch;
    }while(ch!='#');
	p=0;
	printf("%d:",line);
	for(int i=0;program[i]!='\0'&&program[i]!='\n';i++)
	    printf("%c",program[i]);//�����һ�д���
    printf("\n"); 
	line++; 
    do{
        Scanner();      
        switch(syn)
        {
            case -1:printf("wrong\n",token);break;
            default:Print();break;
        }
    }while(syn!=0&&syn!=-1);
    if(syn==0)printf("success");

}
