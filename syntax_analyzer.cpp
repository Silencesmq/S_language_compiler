/*
����S����Դ���� 
������ʷ��Ŷ�Ԫʽ<�����ʾ�����ʵ�����ֵ>
1~9��Ӧ�ؼ��֣�10��Ӧ��ʶ����11��Ӧ�޷���������
12~22��Ӧ����� ��23~26��Ӧ�ֽ�� 
*/

/*
����S����Դ����
�������ʽ����
�ݹ��½��﷨����
����ʽ�������жϵ�ǰsyn�ڲ�����select����
�ڼ��������ʽ��ƥ�����������ж� 
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
        	token[m++]=ch;
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
void lexicalPrint() 
{	   
    if(syn==11)//�޷���������������ֵΪ��value 
        printf("  %s:<%d,%d>\n",lexicalType[syn],syn,sum);
    else//������������ֵΪ�䵥������ 
        printf("  %s:<%d,%s>\n",lexicalType[syn],syn,token);
}

bool Constan_Defined()
{
    if(syn==10)//ƥ���ʶ�� 
    {
    	printf("  ����ʽ��<��������>��<��ʶ��>��<�޷�������>\n"); 
    	printf("  ����ʽ��<��ʶ��>��%s;\n",token);
        Scanner(); 
        if(syn==16)//ƥ��Ⱥ� 
        {
            Scanner();
            if(syn==11)//ƥ���޷������� 
            {   
                printf("  ����ʽ��<�޷�������>��%s;\n",token);
                return true;
            }
            else
			{
				printf("���󣺳�������δָ���޷�������\n");
				return false;
			} 
        }
        else
        {
        	printf("����:���������޵ȺŸ�ֵ\n"); 
        	return false;
        }    
    }
    else
        return false;
}

bool Constan_Description()//ָ�벻�������һ�� 
{
	if(syn==7)//ƥ��Const�ؼ��� 
    {
    	printf("  ����ʽ��<G>��<����˵��>\n");
    	printf("  ����ʽ��<����˵��>��Const <��������><A>��\n");
        Scanner(); 
        if(Constan_Defined())//ƥ��<��������> 
        {
            Scanner();
            while(syn==26)//ƥ�䶺�� 
            {
            	printf("  ����ʽ��<A>����<��������><A> \n");
            	Scanner();
			    if(Constan_Defined())//ƥ��<��������> 
			    {
				    Scanner();
				    continue;
			    }
			    else
				{
					printf("����ȱ�ٳ�������\n"); 
    				return false;
    			} 
            }
            printf("  ����ʽ��<A>����\n");
            if(syn==23)//ƥ��ֺ� 
			{
				return true; 
			} 
			else
   			{
   				printf("����ȱ�ٷֺ�\n"); 
			   	return false;
            } 
        }
        else
        {
			printf("����ȱ�ٳ�������\n"); 
			return false;
        }
    }
    else
    {
    	printf("  ����ʽ��<G>����\n");
    	return false;
    } 
}

bool Variable_Description()//ָ�벻�������һ�� 
{
	if(syn==8)//ƥ��Var�ؼ��� 
    {
    	printf("  ����ʽ��<H>��<����˵��>\n");
    	printf("  ����ʽ��<����˵��>��Var <��ʶ��><B>��\n");
        Scanner(); 
        if(syn==10)//ƥ���ʶ�� 
        {
        	printf("  ����ʽ��<��ʶ��>��%s;\n",token);
            Scanner();
            while(syn==26)//ƥ�䶺�� 
            {
            	printf("  ����ʽ��<B>����<��ʶ��><B> \n");
            	Scanner();
			    if(syn==10)//ƥ���ʶ��
			    {
			    	printf("  ����ʽ��<��ʶ��>��%s;\n",token);
				    Scanner();
				    continue;
			    }
			    else
				{
					printf("����ȱ�ٱ�ʶ��\n"); 
    				return false;
    			} 
            }
            printf("  ����ʽ��<B>����\n");
            if(syn==23)//ƥ��ֺ� 
			{
				return true; 
			} 
			else
   			{
   				printf("����ȱ�ٷֺ�\n"); 
			   	return false;
            } 
        }
        else
        {
			printf("����ȱ�ٱ�ʶ��\n"); 
			return false;
        }
    }
    else
    {
    	printf("  ����ʽ��<H>����\n");
    	return false;
    } 
} 
bool Item_expression();
bool Expression();
bool Factor();
bool Statement();

bool Item_expression()//ָ��������һ�� select={syn=10,11,24}
{
	if(syn==10||syn==11||syn==24)//ƥ��select 
	{
		printf("  ����ʽ��<��>��<����><D>\n");
		Factor();
		Scanner();
		while(syn==14||syn==15)//ƥ����<�˷������>
		{
			printf("  ����ʽ��<D>��<�˷������><����><D>\n");
			printf("  ����ʽ��<�˷������>��%s\n",token);
			Scanner();
			if(Factor())//ƥ��<����> 
			{
				Scanner();
				continue;
			}
			else
			{
				printf("����ȱ������\n");
				return false;
			}    
		} 
		printf("  ����ʽ��<D>����\n");
		return true;
	}
	else
	    return false;
}

bool Expression()//ָ��������һ�� 
{
    int i;
	char str[50]="  ����ʽ��<���ʽ>��";
	if(syn==12)//ƥ��+
	{
		for(i=0;str[i]!='\0';i++);
	    str[i]='+';	
		Scanner();
	}
	else if(syn==13)//ƥ��- 
	{
		for(i=0;str[i]!='\0';i++);
	    str[i]='-';	
		Scanner();
	}
	if(syn==10||syn==11||syn==24)//ƥ��select�� 
	{
		printf("%s<��><C>\n",str);
		Item_expression();//ƥ��<��>
		while(syn==12||syn==13)//ƥ��<�ӷ������>
        {
		    printf("  ����ʽ��<C>��<�ӷ������><��><C>\n");
		    printf("  ����ʽ��<�ӷ������>��%s\n",token);
			Scanner();
			if(Item_expression())//ƥ��<��> 
			{
			    continue;
			}
			else
			{
				printf("����ȱ����\n"); 
                return false;
		    }     
        } 
        printf("  ����ʽ��<C>����\n");
        return true;
    }
    else
        return false; 
}

bool Factor()//ָ�벻�������һ�� select={syn=10,11,24}
{
    if(syn==10)//ƥ���ʶ�� 
    { 
        printf("  ����ʽ��<����>��<��ʶ��>\n");
        printf("  ����ʽ��<��ʶ��>��%s\n",token);
        return true;
    }
    else if(syn==11)//ƥ���޷������� 
    {
    	printf("  ����ʽ��<����>��<�޷�������>\n");
    	printf("  ����ʽ��<�޷�������>��%s\n",token);
        return true;
    }
    else if(syn==24)//ƥ�������� 
    {
        Scanner();
        if(Expression())//ƥ��<���ʽ> 
        {
        	if(syn==25)//ƥ�������� 
        	{
	        	return true;
	        }
	        else
	        {
        		printf("����û��������\n");
				return false; 
        	}
        }
        else
        {
        	printf("����û�б��ʽ\n");
        	return false;
        }
    }
    else
        return false;
}


bool Assignment_statement()//ָ��������һ�� 
{
    if(syn==10)//ƥ���ʶ��
	{
		printf("  ����ʽ��<��ֵ���>��<��ʶ��>��<���ʽ>;\n");
		printf("  ����ʽ��<��ʶ��>��%s;\n",token);
		Scanner();
		if(syn==16)//ƥ��Ⱥ�
		{
			Scanner();
			if(Expression())//ƥ����ʽ 
			{
				return true;
			}
			else
			{
				printf("����ȱ�ٱ��ʽ\n");
				return false;
			} 
		}
		else
		{
			printf("����ȱ�ٵȺ�\n");
			return false;
		} 
	}
	else 
	    return false; 
}


bool Condition()//ָ��������һ�� 
{
	printf("  ����ʽ��<����>��<���ʽ><��ϵ�����><���ʽ>\n");
	if(Expression())//ƥ��<���ʽ> 
	{
		if(syn==17||syn==18||syn==19||syn==20||syn==21
        ||syn==22)//ƥ��<��ϵ�����>
		{
			printf("  ����ʽ��<��ϵ�����>��%s\n",token);
			Scanner();
			if(Expression())//ƥ��<���ʽ> 
			{
				return true;
			}
			else 
            {
            	printf("����ȱ�ٱ��ʽ\n");
				return false; 
            }
		} 
		else
		{
			printf("����ȱ�ٹ�ϵ�����\n");
            return false;
		}
	}
	else
	    return false;
}

bool Conditional_statements()//ָ��������һ�� 
{
	if(syn==2)//ƥ��if
	{
		printf("  ����ʽ��<�������>��if <����> then <���><E>\n"); 
		Scanner();
		if(Condition())//ƥ��<����> 
		{
			if(syn==3)//ƥ��then
			{
				Scanner();
				if(Statement())//ƥ��<���>
				{
					if(syn==4)//ƥ��else
					{
						printf("  ����ʽ��<E>��else<���>\n");
						Scanner();
						if(Statement())//ƥ��<���>
						{
							return true;
						} 
						else 
						{
							printf("����else��ȱ�����\n");
		                    return false;
						}
					}
					printf("  ����ʽ��<E>����\n");
					return true;
				}
				else
				{
					printf("����then��ȱ�����\n"); 
					return false;
				} 

			}
			else
			{
				printf("����ȷʵthen\n");
				return false;
			} 
		}
		else
        {
        	printf("����if��ȱ������\n");
        	return false;
        }
	}
	else
	    return false;    
}

bool While_Statement()//ָ��������һ��  
{
	if(syn==5)//ƥ��while
	{
		printf("  ����ʽ��<��ѭ�����>��while <����> do <���>\n");
		Scanner();
		if(Condition())//ƥ��<����> 
		{
			if(syn==6)//ƥ��do
			{
				Scanner();
				if(Statement())//ƥ��<���>
				{
					return true;
				} 
				else 
                {
                	printf("����do��ȱ�����\n");
                	return false;
                }
			}
			else 
			{
				printf("����ȱ��do\n");
				return false;
			} 
		}
		else
		{
			printf("����ȱ������\n");
			return false;
		}
	} 
	else 
	    return false;
}

bool Compound_statements()//ָ��������һ��  
{
	if(syn==1)//ƥ��begin 
	{
		printf("  ����ʽ��<�������>��begin <���><F>end\n");
		Scanner();
		if(Statement())//ƥ��<���>
		{
			while(syn==23)//ƥ��ֺ� 
		    {
		    	printf("  ����ʽ��<F>����<���><F>\n");
			    Scanner();
			    if(Statement())//ƥ��<���> 
			    {
				    continue;
			    }
			    else
			    {
			    	printf("���󣺷ֺź�ȱ�����\n");
    				return false;
    			}    
		    } 
		    printf("  ����ʽ��<F>����\n");
		    if(syn==9)//ƥ��end
			{
				Scanner();
				return true; 
			} 
			else
            {
            	printf("����ȱ��end\n");
            	return false;
            }
		} 
		else 
        {
        	printf("����begin��ȱ�����\n");
        	return false;
		} 
	}
	else
	    return false;
}

bool Statement()//ָ��������һ�� 
{
    if(syn==10)//ƥ��<��ֵ���> 
    {
    	printf("  ����ʽ��<���>��<��ֵ���>\n");
    	Assignment_statement();
        return true;    
    }
    else if(syn==5)//ƥ��<��ѭ�����> 
    { 
        printf("  ����ʽ��<���>��<��ѭ�����>\n");
        While_Statement();
        return true;
    }
    else if(syn==1)//ƥ��<�������> 
    {
    	printf("  ����ʽ��<���>��<�������>\n");
    	Compound_statements();
        return true;
    }
    else if(syn==2)//ƥ��<�������> 
    {
    	printf("����ʽ��<���>��<�������>\n");
    	Conditional_statements();
        return true;
    }
    else
    {
        return false;//������䲻��Ϊ�� 
    }
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
	printf("  ����ʽ��<����>��<G><H><���>\n");
	Scanner();
	Constan_Description();
	Scanner();
	Variable_Description();
	Scanner(); 
	Statement();
}
