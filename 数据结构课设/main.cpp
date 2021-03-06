#include <bits/stdc++.h>
#include <math.h>
using namespace std;
char a[100] ;
char fz[100] ; // 符号栈
float sz[100] ; // 数字栈
int fhead = 0 ; // 符号栈指针
int shead = 0 ; // 数字栈指针
/*
已发现的错误：
9+2- 正确答案：错误样例  输出答案：7
2+9- 正确答案：错误样例  输出答案：-7
*/
void math(char f) // 从数字栈中取出栈顶的两个数字 进行 f 运算 结果继续放在栈中
{
    switch(f)
    {
        case '+' : sz[-- shead] += sz[shead + 1] ; break ;
        case '-' : sz[-- shead] -= sz[shead + 1] ; break ;
        case '*' : sz[-- shead] *= sz[shead + 1] ; break ;
        case '/' : sz[-- shead] /= sz[shead + 1] ; break ;
    }
    -- fhead ;
    sz[shead + 1] = 0 ;
}

int check_order(char a)
{
if((a>= '0' && a<= '9') || a=='+' || a=='-' || a=='*' || a=='/' || a=='(' || a==')' || a=='N' || a=='#')return 1;
else return 0;
}

int main()
{
    cout << "本程序用于进行简易的算数表达式求值\n输入表达式，每次表达式以 ‘#’ 或者回车作为结束标志\n输入 ‘N’ 表示结束该程序\n接下来请您输入算式：\n" ;
    while(gets(a) != NULL)
    {
    char watch_a;   //观测型对应字符
    char watch_fz; // 观测型符号栈对应符号
    float watch_sz ; // 观测型数字栈对应数字
    int watch_fhead = 0 ; // 观测型符号栈指针对应数字
    int watch_shead = 0 ; // 观测型数字栈指针对应数字
    int watch_i = 0;   //用于观测非法数据是否输入
    int check=1;  //测试数据输入是否合法

    for(int k=0 ; k < strlen(a) ; k++)
    {
        check = check_order(a[k]);
        if(check==0)break;
        if(a[k]=='(' && a[k+1]==')')
        {cout << "输入不符合规定！请重新输入！" << endl;
        check = 0;
        break;
        }
    }

    if(check == 0)
    {cout << "输入不符合规定！请重新输入！" << endl;
    continue;}

    memset(fz,0,sizeof(fz));
    memset(sz,0,sizeof(sz));
    fhead = 0;
    shead = 0;

    if(a[0]=='N')break;

    int len = strlen(a)-1;
    int num_zuo = 0;
    int num_you = 0;

    for(int k=0 ; k <= len ; k++)
    {
        if(a[k]=='(')num_zuo++;
        if(a[k]==')')num_you++;
    }

    if(num_zuo != num_you)
    {
    cout << "格式错误！请重新输入！" << endl;
    continue;
    }

    for(int i = 0 ; i <= len ; ++ i )
    {
        check=1;
        // 如果读到 "("  则直接放入栈中
        watch_a = a[i];
        if(a[i] == '(' )
        {//////////////////////////////////////////////////////////////////////要在栈中寻找错误
                for(watch_fhead=fhead ; watch_fhead>=0 ; watch_fhead--)
                {
                        if(fz[watch_fhead]==')')
                        {
                        check=0;
                        cout << "格式错误！请重新输入！" << endl;
                        break;
                        }
                }
                if(check==0)break;
                fz[++ fhead] = a[i] ;
                watch_fz = a[i];
                watch_fhead = fhead;
                continue ;
        }
        // 如果读到 ")"  则将 "(" 之前的运算符全部出栈
        if(a[i]==')')
        {
                watch_i = i;
                for(watch_fhead=fhead ;  ; watch_fhead--)
                {
                        if(watch_fhead==-1)
                        {
                        check=0;
                        cout << "格式错误！请重新输入！" << endl;
                        break;
                        }
                        if(fz[watch_fhead]=='(')break;
                }
                if(check==0)break;
                while(fz[fhead] != '(')
                math(fz[fhead]) ;
                -- fhead ;
                watch_fhead = fhead;
                watch_fz = fz[fhead];
                continue ;
        }
        // 读到数字直接放在数字栈顶
        if(a[i] >= '0' && a[i] <= '9')
        {
            ++ shead ;
            watch_shead = shead;
            float xiaoshu = 0;
            int weishu = 0;
            while((a[i] >= '0' && a[i] <= '9') || a[i]=='.')
                {
                watch_a = a[i];
                sz[shead] = sz[shead] *10 + a[i] - '0';
                watch_sz = sz[shead];
                i++;
                watch_a = a[i];
                if(a[i]=='.')
                {
                    i++;
                    watch_a = a[i];
                    while(a[i] >= '0' && a[i] <= '9')
                    {xiaoshu = xiaoshu *10 + a[i] - '0';
                    i++;
                    weishu++;
                    }
                }
                }
                xiaoshu=xiaoshu*1.00/pow(10,weishu);
                sz[shead]+=xiaoshu;
                watch_sz = sz[shead];
            i--;
            continue;
        }
        else {
            if(a[i] == '/' || a[i] == '*')
                {
                // 如果读到 "/" 或 "*"  直接放在符号栈栈顶
                while(fz[fhead] == '/' || fz[fhead] == a[i])
                {
                math(fz[fhead]);
                }
                fz[++fhead] = a[i];
                continue;
                }
            else
                while(fz[fhead] == '*' || fz[fhead] == '/' || fz[fhead] == a[i])
                {
                // 如果读到 "+" 或 "-"
                // 则将栈顶跟自己一样的符号和 "/"  "*" 全部弹出
                math(fz[fhead]);
                }
            fz[++ fhead] = a[i] ;
            }
    }
    if(check == 0)continue;
    while(fhead != 0 && check==1) {
        math(fz[fhead]) ;
        }
    // 当栈中仅有一个数字的时候 运算式的答案就是它
    if(check == 1)cout << "答案为：" << sz[shead] <<endl;
    }
    return 0 ;
}
