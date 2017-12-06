/*
输入S语言源代码 
输出单词符号二元式<词类表示，单词的属性值>
1~9对应关键字，10对应标识符，11对应无符号整数，
12~22对应运算符 ，23~26对应分界符 
*/

/*
输入S语言源代码
输出产生式序列
递归下降语法分析
产生式函数先判断当前syn在不在其select集，
在即输出产生式，匹配后继续往后判断 
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
        	token[m++]=ch;
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
void lexicalPrint() 
{	   
    if(syn==11)//无符号整数类型属性值为其value 
        printf("  %s:<%d,%d>\n",lexicalType[syn],syn,sum);
    else//其余类型属性值为其单词序列 
        printf("  %s:<%d,%s>\n",lexicalType[syn],syn,token);
}

bool Constan_Defined()
{
    if(syn==10)//匹配标识符 
    {
    	printf("  产生式：<常量定义>→<标识符>＝<无符号整数>\n"); 
    	printf("  产生式：<标识符>→%s;\n",token);
        Scanner(); 
        if(syn==16)//匹配等号 
        {
            Scanner();
            if(syn==11)//匹配无符号整数 
            {   
                printf("  产生式：<无符号整数>→%s;\n",token);
                return true;
            }
            else
			{
				printf("错误：常量定义未指定无符号整数\n");
				return false;
			} 
        }
        else
        {
        	printf("错误:常量定义无等号赋值\n"); 
        	return false;
        }    
    }
    else
        return false;
}

bool Constan_Description()//指针不会读到下一个 
{
	if(syn==7)//匹配Const关键字 
    {
    	printf("  产生式：<G>→<常量说明>\n");
    	printf("  产生式：<常量说明>→Const <常量定义><A>；\n");
        Scanner(); 
        if(Constan_Defined())//匹配<常量定义> 
        {
            Scanner();
            while(syn==26)//匹配逗号 
            {
            	printf("  产生式：<A>→，<常量定义><A> \n");
            	Scanner();
			    if(Constan_Defined())//匹配<常量定义> 
			    {
				    Scanner();
				    continue;
			    }
			    else
				{
					printf("错误：缺少常量定义\n"); 
    				return false;
    			} 
            }
            printf("  产生式：<A>→ε\n");
            if(syn==23)//匹配分号 
			{
				return true; 
			} 
			else
   			{
   				printf("错误：缺少分号\n"); 
			   	return false;
            } 
        }
        else
        {
			printf("错误：缺少常量定义\n"); 
			return false;
        }
    }
    else
    {
    	printf("  产生式：<G>→ε\n");
    	return false;
    } 
}

bool Variable_Description()//指针不会读到下一个 
{
	if(syn==8)//匹配Var关键字 
    {
    	printf("  产生式：<H>→<变量说明>\n");
    	printf("  产生式：<变量说明>→Var <标识符><B>；\n");
        Scanner(); 
        if(syn==10)//匹配标识符 
        {
        	printf("  产生式：<标识符>→%s;\n",token);
            Scanner();
            while(syn==26)//匹配逗号 
            {
            	printf("  产生式：<B>→，<标识符><B> \n");
            	Scanner();
			    if(syn==10)//匹配标识符
			    {
			    	printf("  产生式：<标识符>→%s;\n",token);
				    Scanner();
				    continue;
			    }
			    else
				{
					printf("错误：缺少标识符\n"); 
    				return false;
    			} 
            }
            printf("  产生式：<B>→ε\n");
            if(syn==23)//匹配分号 
			{
				return true; 
			} 
			else
   			{
   				printf("错误：缺少分号\n"); 
			   	return false;
            } 
        }
        else
        {
			printf("错误：缺少标识符\n"); 
			return false;
        }
    }
    else
    {
    	printf("  产生式：<H>→ε\n");
    	return false;
    } 
} 
bool Item_expression();
bool Expression();
bool Factor();
bool Statement();

bool Item_expression()//指针会读到下一个 select={syn=10,11,24}
{
	if(syn==10||syn==11||syn==24)//匹配select 
	{
		printf("  产生式：<项>→<因子><D>\n");
		Factor();
		Scanner();
		while(syn==14||syn==15)//匹配项<乘法运算符>
		{
			printf("  产生式：<D>→<乘法运算符><因子><D>\n");
			printf("  产生式：<乘法运算符>→%s\n",token);
			Scanner();
			if(Factor())//匹配<因子> 
			{
				Scanner();
				continue;
			}
			else
			{
				printf("错误：缺少因子\n");
				return false;
			}    
		} 
		printf("  产生式：<D>→ε\n");
		return true;
	}
	else
	    return false;
}

bool Expression()//指针会读到下一个 
{
    int i;
	char str[50]="  产生式：<表达式>→";
	if(syn==12)//匹配+
	{
		for(i=0;str[i]!='\0';i++);
	    str[i]='+';	
		Scanner();
	}
	else if(syn==13)//匹配- 
	{
		for(i=0;str[i]!='\0';i++);
	    str[i]='-';	
		Scanner();
	}
	if(syn==10||syn==11||syn==24)//匹配select集 
	{
		printf("%s<项><C>\n",str);
		Item_expression();//匹配<项>
		while(syn==12||syn==13)//匹配<加法运算符>
        {
		    printf("  产生式：<C>→<加法运算符><项><C>\n");
		    printf("  产生式：<加法运算符>→%s\n",token);
			Scanner();
			if(Item_expression())//匹配<项> 
			{
			    continue;
			}
			else
			{
				printf("错误：缺少项\n"); 
                return false;
		    }     
        } 
        printf("  产生式：<C>→ε\n");
        return true;
    }
    else
        return false; 
}

bool Factor()//指针不会读到下一个 select={syn=10,11,24}
{
    if(syn==10)//匹配标识符 
    { 
        printf("  产生式：<因子>→<标识符>\n");
        printf("  产生式：<标识符>→%s\n",token);
        return true;
    }
    else if(syn==11)//匹配无符号整数 
    {
    	printf("  产生式：<因子>→<无符号整数>\n");
    	printf("  产生式：<无符号整数>→%s\n",token);
        return true;
    }
    else if(syn==24)//匹配左括号 
    {
        Scanner();
        if(Expression())//匹配<表达式> 
        {
        	if(syn==25)//匹配右括号 
        	{
	        	return true;
	        }
	        else
	        {
        		printf("错误：没有右扩号\n");
				return false; 
        	}
        }
        else
        {
        	printf("错误：没有表达式\n");
        	return false;
        }
    }
    else
        return false;
}


bool Assignment_statement()//指针会读到下一个 
{
    if(syn==10)//匹配标识符
	{
		printf("  产生式：<赋值语句>→<标识符>＝<表达式>;\n");
		printf("  产生式：<标识符>→%s;\n",token);
		Scanner();
		if(syn==16)//匹配等号
		{
			Scanner();
			if(Expression())//匹配表达式 
			{
				return true;
			}
			else
			{
				printf("错误：缺少表达式\n");
				return false;
			} 
		}
		else
		{
			printf("错误：缺少等号\n");
			return false;
		} 
	}
	else 
	    return false; 
}


bool Condition()//指针会读到下一个 
{
	printf("  产生式：<条件>→<表达式><关系运算符><表达式>\n");
	if(Expression())//匹配<表达式> 
	{
		if(syn==17||syn==18||syn==19||syn==20||syn==21
        ||syn==22)//匹配<关系运算符>
		{
			printf("  产生式：<关系运算符>→%s\n",token);
			Scanner();
			if(Expression())//匹配<表达式> 
			{
				return true;
			}
			else 
            {
            	printf("错误：缺少表达式\n");
				return false; 
            }
		} 
		else
		{
			printf("错误：缺少关系运算符\n");
            return false;
		}
	}
	else
	    return false;
}

bool Conditional_statements()//指针会读到下一个 
{
	if(syn==2)//匹配if
	{
		printf("  产生式：<条件语句>→if <条件> then <语句><E>\n"); 
		Scanner();
		if(Condition())//匹配<条件> 
		{
			if(syn==3)//匹配then
			{
				Scanner();
				if(Statement())//匹配<语句>
				{
					if(syn==4)//匹配else
					{
						printf("  产生式：<E>→else<语句>\n");
						Scanner();
						if(Statement())//匹配<语句>
						{
							return true;
						} 
						else 
						{
							printf("错误：else后缺少语句\n");
		                    return false;
						}
					}
					printf("  产生式：<E>→ε\n");
					return true;
				}
				else
				{
					printf("错误：then后缺少语句\n"); 
					return false;
				} 

			}
			else
			{
				printf("错误：确实then\n");
				return false;
			} 
		}
		else
        {
        	printf("错误：if后缺少条件\n");
        	return false;
        }
	}
	else
	    return false;    
}

bool While_Statement()//指针会读到下一个  
{
	if(syn==5)//匹配while
	{
		printf("  产生式：<当循环语句>→while <条件> do <语句>\n");
		Scanner();
		if(Condition())//匹配<条件> 
		{
			if(syn==6)//匹配do
			{
				Scanner();
				if(Statement())//匹配<语句>
				{
					return true;
				} 
				else 
                {
                	printf("错误：do后缺少语句\n");
                	return false;
                }
			}
			else 
			{
				printf("错误：缺少do\n");
				return false;
			} 
		}
		else
		{
			printf("错误：缺少条件\n");
			return false;
		}
	} 
	else 
	    return false;
}

bool Compound_statements()//指针会读到下一个  
{
	if(syn==1)//匹配begin 
	{
		printf("  产生式：<复合语句>→begin <语句><F>end\n");
		Scanner();
		if(Statement())//匹配<语句>
		{
			while(syn==23)//匹配分号 
		    {
		    	printf("  产生式：<F>→；<语句><F>\n");
			    Scanner();
			    if(Statement())//匹配<语句> 
			    {
				    continue;
			    }
			    else
			    {
			    	printf("错误：分号后缺少语句\n");
    				return false;
    			}    
		    } 
		    printf("  产生式：<F>→ε\n");
		    if(syn==9)//匹配end
			{
				Scanner();
				return true; 
			} 
			else
            {
            	printf("错误：缺少end\n");
            	return false;
            }
		} 
		else 
        {
        	printf("错误：begin后缺少语句\n");
        	return false;
		} 
	}
	else
	    return false;
}

bool Statement()//指针会读到下一个 
{
    if(syn==10)//匹配<赋值语句> 
    {
    	printf("  产生式：<语句>→<赋值语句>\n");
    	Assignment_statement();
        return true;    
    }
    else if(syn==5)//匹配<当循环语句> 
    { 
        printf("  产生式：<语句>→<当循环语句>\n");
        While_Statement();
        return true;
    }
    else if(syn==1)//匹配<复合语句> 
    {
    	printf("  产生式：<语句>→<复合语句>\n");
    	Compound_statements();
        return true;
    }
    else if(syn==2)//匹配<条件语句> 
    {
    	printf("产生式：<语句>→<条件语句>\n");
    	Conditional_statements();
        return true;
    }
    else
    {
        return false;//假设语句不能为空 
    }
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
	printf("  产生式：<程序>→<G><H><语句>\n");
	Scanner();
	Constan_Description();
	Scanner();
	Variable_Description();
	Scanner(); 
	Statement();
}
