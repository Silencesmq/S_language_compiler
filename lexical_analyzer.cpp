/*
输入S语言源代码 
输出单词符号二元式<词类表示，单词的属性值>
1~9对应关键字，10对应标识符，11对应无符号整数，
12~22对应运算符 ，23~26对应分界符 
*/
 
#include<stdio.h>
#include<string.h>

int syn;//存放单词的类型 
int p;//用于遍历程序源代码
int line;//用来标识行数 
char ch;//用于读取程序源代码 
int sum;//用来保存数字的值 

char program[1000],token[10];//program用来存储源代码，token用来存放词素 

 
char *rwtab[9]={"begin","if","then",
                "else","while","do",
				"Const","Var","end"};//关键字 

char* lexicalType[27];//词法类型 

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
//识别字母 
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
	//初始化词素数组为空 
    ch=program[p++];
    while(ch==' '||ch=='\n'||ch=='\t')//剔除空白
    {
    	if(ch=='\n'){
    	    printf("%d:",line);//输出行数及该行代码 
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
        syn=10;//标识符类别号 
        token[m++]='\0';
        for(int n=0;n<=8;n++)
        {
            if(strcmp(token,rwtab[n])==0)
            {
                syn=n+1;//关键字类别号 
                break;
            }//识别关键字 
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
        syn=11;//无符号整数类别号 
        if(isAlpha(ch))
            syn=-1;//词法错误 
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
                        syn=22;//识别<> 
                        token[1]=ch;
                    }
                    else if(ch=='=')
                    {
                        syn=21;//识别<= 
                        token[1]=ch;
                    }
                    else{
                        syn=20;//识别< 
                        p--;
                    }
                    break;
            case '>':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=19;//识别>= 
                        token[1]=ch;
                    }
                    else{
                        syn=18;//识别> 
                        p--;
                    }           
                    break;
            case '=':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=17;//识别== 
                        token[1]=ch;
                    }
                    else{
                        syn=16;//识别= 
                        p--;
                    }
                    break;
            case '+':syn=12;break;//识别+ 
            case '-':syn=13;break;//识别- 
            case '*':syn=14;break;//识别* 
            case '/':syn=15;break;//识别/ 
            case ';':syn=23;break;//识别； 
            case '(':syn=24;break;//识别（ 
            case ')':syn=25;break;//识别） 
            case ',':syn=26;break;//识别， 
            case '#':syn=0;break;//识别# 
            default:syn=-1;break;//词法错误                   
        }
        return;
    }
}

//输出单词符号二元式<词类表示，单词的属性值> 
//1~9对应关键字，10对应标识符，11对应无符号整数，
//12~22对应运算符 ，23~26对应分界符 
void Print() 
{	   
    if(syn==11)//无符号整数类型属性值为其value 
        printf("  %s:<%d,%d>\n",lexicalType[syn],syn,sum);
    else//其余类型属性值为其单词序列 
        printf("  %s:<%d,%s>\n",lexicalType[syn],syn,token);
}


int main()
{
	p=0;
    line=1;
	initLexicalType(); 
    printf("输入词法分析串以#作为结束\n");
    do
    {
        ch=getchar();
        program[p++]=ch;
    }while(ch!='#');
	p=0;
	printf("%d:",line);
	for(int i=0;program[i]!='\0'&&program[i]!='\n';i++)
	    printf("%c",program[i]);//输出第一行代码
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
