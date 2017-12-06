/*
����S����Դ���� 
������ʷ��Ŷ�Ԫʽ<�����ʾ�����ʵ�����ֵ>
1~9��Ӧ�ؼ��֣�10��Ӧ��ʶ����11��Ӧ�޷���������
12~22��Ӧ����� ��23~26��Ӧ�ֽ�� 
*/

/*
����S����Դ����
�������ʽ����
����ʽ�������жϵ�ǰsyn�ڲ�����select����
�ڼ��������ʽ��ƥ�����������ж� 
*/ 

/*
����S����Դ����
����м����
��ʵ���˳�������������ű�ͱ�������������ű�
�͸�ֵ�����м����������û���Ż� 
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


struct symbol{
	char name[10];
	int value;
};//���ű��� 

symbol symbolTable[100];//���ű� 

int q;//�������������ű��������Ŀ 

char id[10];//���ڴ洢id 

char temp[100][10]={"t1","t2","t3","t4","t5"};//�м���� 

int w;//�������������м���� 
 
bool lookup(char *id)
{
	int i;
	for(i=0;symbolTable[i].name[0]!='\0';i++){
		if(strcmp(id,symbolTable[i].name)==0)
		    return true;    
	}
	return false;
}

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
        token[m++]='\0';
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
    	if(!lookup(token)){
	    	strcpy(symbolTable[q].name,token);
    	    //printf("����ʽ��<��������>��<��ʶ��>��<�޷�������>\n"); 
        	Scanner(); 
        	if(syn==16)//ƥ��Ⱥ� 
        	{
            	Scanner();
            	if(syn==11)//ƥ���޷������� 
            	{   
                	symbolTable[q].value=sum;
                	printf("  add %s:=%d\n",symbolTable[q].name,symbolTable[q].value);
                	q++;
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
		{
			printf("�����ظ�����%s\n",token);
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
    	//printf("����ʽ��<G>��<����˵��>\n");
    	//printf("����ʽ��<����˵��>��Const <��������><A>��\n");
        Scanner(); 
        if(Constan_Defined())//ƥ��<��������> 
        {
            Scanner();
            while(syn==26)//ƥ�䶺�� 
            {
	            //printf("����ʽ��<A>����<��������><A> \n");
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
            //printf("����ʽ��<A>����\n");
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
    	//printf("����ʽ��<G>����\n");
    	return false;
    } 
}

bool Variable_Description()//ָ�벻�������һ�� 
{
	if(syn==8)//ƥ��Var�ؼ��� 
    {
    	//printf("����ʽ��<H>��<����˵��>\n");
    	//printf("����ʽ��<����˵��>��Var <��ʶ��><B>��\n");
        Scanner(); 
        if(syn==10)//ƥ���ʶ�� 
        {
        	if(!lookup(token)){
	        	strcpy(symbolTable[q].name,token);
	        	printf("  add %s\n",symbolTable[q].name);
	        	q++;
	            Scanner();
	            while(syn==26)//ƥ�䶺�� 
	            {
					//printf("����ʽ��<B>����<��ʶ��><B> \n");
	            	Scanner();
				    if(syn==10)//ƥ���ʶ��
				    {
				    	strcpy(symbolTable[q].name,token);
	        	        printf("  add %s\n",symbolTable[q].name);
	        	        q++;
					    Scanner();
					    continue;
				    }
				    else
					{
						printf("����ȱ�ٱ�ʶ��\n"); 
	    				return false;
	    			} 
	            }
	            //printf("����ʽ��<B>����\n");
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
	        	printf("�ظ�����%s\n",token);
				return false;
	        }
        }
        else
        {
			printf("�����ظ�����%s\n",token); 
			return false;
        }
    }
    else
    {
    	//printf("����ʽ��<H>����\n");
    	return false;
    } 
} 
char * Item_expression();
char * Expression();
char * Factor();
bool Statement();

char *Item_expression()//ָ��������һ�� select={syn=10,11,24}
{
	char lastid[10],op[10];
	if(syn==10||syn==11||syn==24)//ƥ��select 
	{
		//printf("����ʽ��<��>��<����><D>\n");
		Factor();
		strcpy(lastid,id);//����id��ʶ�� 
		Scanner();
		while(syn==14||syn==15)//ƥ����<�˷������>
		{
			strcpy(op,token);
			//printf("����ʽ��<D>��<�˷������><����><D>\n");
			Scanner();
			if(Factor())//ƥ��<����> 
			{
				printf("  %s:=%s%s%s\n",temp[w],lastid,op,id);
				strcpy(lastid,temp[w]);
				w++;
				Scanner();
				continue;
			}
			else
			{
				printf("����ȱ������\n");
				return NULL;
			}    
		} 
		//printf("����ʽ��<D>����\n");
		strcpy(id,lastid);
		return id;
	}
	else
	    return NULL;
}

char * Expression()//ָ��������һ�� 
{
	char lastid[10],op[10];
    int i;
	char str[50]="����ʽ��<���ʽ>��";
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
		//printf("%s<��><C>\n",str);
		Item_expression();//ƥ��<��>
		strcpy(lastid,id);
		while(syn==12||syn==13)//ƥ��<�ӷ������>
        {
        	strcpy(op,token);
		    //printf("����ʽ��<C>��<�ӷ������><��><C>\n");
			Scanner();
			if(Item_expression())//ƥ��<��> 
			{
				printf("  %s:=%s%s%s\n",temp[w],lastid,op,id);
				strcpy(lastid,temp[w]);
				w++;
			    continue;
			}
			else
			{
				printf("����ȱ����\n"); 
                return NULL;
		    }     
        } 
        //printf("����ʽ��<C>����\n");
        strcpy(id,lastid);
		return id;
    }
    else
        return NULL; 
}

char * Factor()//ָ�벻�������һ�� select={syn=10,11,24}
{
	strcpy(id,token);
    if(syn==10)//ƥ���ʶ�� 
    { 
        return id;
    }
    else if(syn==11)//ƥ���޷������� 
    {
        return id;
    }
    else if(syn==24)//ƥ�������� 
    {
        Scanner();
        if(Expression())//ƥ��<���ʽ> 
        {
        	if(syn==25)//ƥ�������� 
        	{
	        	return id;
	        }
	        else
	        {
        		printf("����û��������\n");
				return NULL; 
        	}
        }
        else
        {
        	printf("����û�б��ʽ\n");
        	return NULL;
        }
    }
    else
		return NULL; 
}


bool Assignment_statement()//ָ��������һ�� 
{
	char lastid[10];
    if(syn==10)//ƥ���ʶ��
	{
		if(lookup(token)){
		    strcpy(lastid,token);
			//printf("����ʽ��<��ֵ���>��<��ʶ��>��<���ʽ>;\n");
			Scanner();
			if(syn==16)//ƥ��Ⱥ�
			{
				Scanner();
				if(Expression())//ƥ����ʽ 
				{
					printf("  %s:=%s\n",lastid,id);
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
		{
			printf("����δ�������%s\n",token); 
			return false;
		} 
	}
	else 
	    return false; 
}


bool Condition()//ָ��������һ�� 
{
	printf("����ʽ��<����>��<���ʽ><��ϵ�����><���ʽ>\n");
	if(Expression())//ƥ��<���ʽ> 
	{
		if(syn==17||syn==18||syn==19||syn==20||syn==21
        ||syn==22)//ƥ��<��ϵ�����>
		{
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
		printf("����ʽ��<�������>��if <����> then <���><E>\n"); 
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
						printf("����ʽ��<E>��else<���>\n");
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
					printf("����ʽ��<E>����\n");
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
		printf("����ʽ��<��ѭ�����>��while <����> do <���>\n");
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
		//printf("����ʽ��<�������>��begin <���><F>end\n");
		Scanner();
		if(Statement())//ƥ��<���>
		{
			while(syn==23)//ƥ��ֺ� 
		    {
		    	//printf("����ʽ��<F>����<���><F>\n");
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
		    //printf("����ʽ��<F>����\n");
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
    	//printf("����ʽ��<���>��<��ֵ���>\n");
    	Assignment_statement();
        return true;    
    }
    else if(syn==5)//ƥ��<��ѭ�����> 
    { 
        //printf("����ʽ��<���>��<��ѭ�����>\n");
        While_Statement();
        return true;
    }
    else if(syn==1)//ƥ��<�������> 
    {
    	//printf("����ʽ��<���>��<�������>\n");
    	Compound_statements();
        return true;
    }
    else if(syn==2)//ƥ��<�������> 
    {
    	//printf("����ʽ��<���>��<�������>\n");
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
	q=0;
	w=0; 
	printf("%d:",line);
	for(int i=0;program[i]!='\0'&&program[i]!='\n';i++)
	    printf("%c",program[i]);//�����һ�д���
    printf("\n"); 
	line++;
	//printf("����ʽ��<����>��<G><H><���>\n");
	Scanner();
	Constan_Description();
	Scanner();
	Variable_Description();
	Scanner(); 
	Statement();
}
