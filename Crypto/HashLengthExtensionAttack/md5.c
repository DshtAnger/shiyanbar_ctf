#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
#include<vector>
using namespace std;




int ROL(int x, int s) //因为存储字符串用的是int类型，所以循环移位要考虑符号的问题
{
    int temp1 = x << s;
    int temp2 = x >> (32 - s);
    int temp3 = 0;
    for(int i = 0; i<s; i++)
    {
        temp3 += temp2 & (1<<i);
    }
    return temp1 | temp3;
}


//int ROL(int x, int s)  //如果用unsigned int类型，这种循环移位就行了，不用考虑符号位的影响
//{
// return (x << s) | (x >> (32 - s));
//}


//int ROR(int x, int s)  //循环右移，这个程序中不用
//{
// return (x >> s) | (x << (32 - s));
//}


int F(int x ,int y, int z)
{
    return (x & y) | ((~x) & z);
}


int G(int x, int y, int z)
{
    return (x & z) | (y & (~z));
}


int H(int x, int y, int z)
{
    return x ^ y ^ z;
}


int I(int x, int y, int z)
{
    return y ^ (x | (~z));
}


void FF(int &a, int b, int c, int d, int m, unsigned char s, int ti)
{
    a = a + F(b, c, d) + m + ti;
    a = ROL(a, s);
    a += b;
}


void GG(int &a, int b, int c, int d, int m, unsigned char s, int ti)
{
    a = a + G(b, c, d) + m + ti;
    a = ROL(a, s);
    a += b;
}


void HH(int &a, int b, int c, int d, int m, unsigned char s,int ti)
{
    a = a + H(b, c, d) + m + ti;
    a = ROL(a, s);
    a += b;
}


void II(int &a, int b, int c, int d, int m, unsigned char s, int ti)
{
    a = a + I(b, c, d) + m + ti;
    a = ROL(a, s);
    a += b;
}


void output(int a) //以小端规则输出
{ 
    for(int i = 0; i<4; i++)
    {
        int temp = a & 0xff;
        if( temp < 16)
            {
                cout<<"0";
            }
        printf("%x",temp);
        a = a >> 8;
    }
}


int main()
{
    vector<int*> v;
    string s1="message digest";
    cout<<"请输入需要加密的信息："<<endl;
    getline(cin,s1);

    int A,B,C,D,a,b,c,d;
    //初始化四个链接变量A,B,C,D
    A = 0x67452301;
    B = 0xefcdab89;
    C = 0x98badcfe;
    D = 0x10325476;



    int bits,len = s1.length(),i,j,p,counter = 0,num;
    bits = len * 8;
    //字符串长度


    //填充字符串，并按512 bit一个分组存入一个int M[16]数组
    p=1;
    for(i = 0; i<len; )
    {
        int M[16];
        for(j = 0; j < 16; j++)
        {
            if(4*p-1 < len)
            {
                num = 4*p-1;
            }
            else
            {
                num = len-1;
            }

            counter = 0;
            M[j] = s1[num];
            counter++;
            i++;

            for(; counter < 4; counter++)
            {
                if(i >= len) break;
                M[j] = M[j] << 8;
                M[j] += s1[num - counter];
                i++;
            }
                p++;
                if(i >= len) break;
        }

        if(j < 16)
        {
            for(int k = j+1; k<16; k++)
            {
                M[k] = 0;
            }
            if( counter < 4)
            {
                M[j] += 0x80 << (counter*8);
            }
            else
            {
                j++;
                M[j] += 0x80;
            }
            if(j < 14)
            {
                M[14] = bits & 0x00000000ffffffff;
                M[15] = bits & 0xffffffff00000000;
                v.push_back(M);
            }
            else
            {
                v.push_back(M);
                int N[16];
                for(int k = 0; k<14; k++)
                {
                    N[k] = 0;
                }
                N[14] = bits & 0x00000000ffffffff;
                N[15] = bits & 0xffffffff00000000;
                v.push_back(N);
            }
        }
    }


    //考虑空字符串的情况
    if( s1.length() == 0)
    {
        int M[16];
        M[0] = 0x00000080;
        for(int n = 1; n<16; n++)
        {
            M[n] = 0;
        }
        v.push_back(M);
    }
    /*for(int l = 0; l<16; l++)
    {
    printf("%x\n",v[0][l]);
    }*/

    vector<int*>::iterator it;
    //主循环
    for(it = v.begin(); it != v.end(); it++)
    {
        a = A; b = B; c = C; d = D;
        //第一轮
        FF(a,b,c,d,(*it)[0],7,0xd76aa478);
        FF(d,a,b,c,(*it)[1],12,0xe8c7b756);
        FF(c,d,a,b,(*it)[2],17,0x242070db); 
        FF(b,c,d,a,(*it)[3],22,0xc1bdceee);
        FF(a,b,c,d,(*it)[4],7,0xf57c0faf);
        FF(d,a,b,c,(*it)[5],12,0x4787c62a); 
        FF(c,d,a,b,(*it)[6],17,0xa8304613);
        FF(b,c,d,a,(*it)[7],22,0xfd469501) ;
        FF(a,b,c,d,(*it)[8],7,0x698098d8) ;
        FF(d,a,b,c,(*it)[9],12,0x8b44f7af) ;
        FF(c,d,a,b,(*it)[10],17,0xffff5bb1) ;
        FF(b,c,d,a,(*it)[11],22,0x895cd7be) ;
        FF(a,b,c,d,(*it)[12],7,0x6b901122) ;
        FF(d,a,b,c,(*it)[13],12,0xfd987193) ;
        FF(c,d,a,b,(*it)[14],17,0xa679438e) ;
        FF(b,c,d,a,(*it)[15],22,0x49b40821);


        //第二轮
        GG(a,b,c,d,(*it)[1],5,0xf61e2562); 
        GG(d,a,b,c,(*it)[6],9,0xc040b340); 
        GG(c,d,a,b,(*it)[11],14,0x265e5a51); 
        GG(b,c,d,a,(*it)[0],20,0xe9b6c7aa) ;
        GG(a,b,c,d,(*it)[5],5,0xd62f105d) ;
        GG(d,a,b,c,(*it)[10],9,0x02441453) ;
        GG(c,d,a,b,(*it)[15],14,0xd8a1e681); 
        GG(b,c,d,a,(*it)[4],20,0xe7d3fbc8) ;
        GG(a,b,c,d,(*it)[9],5,0x21e1cde6) ;
        GG(d,a,b,c,(*it)[14],9,0xc33707d6) ;
        GG(c,d,a,b,(*it)[3],14,0xf4d50d87) ;
        GG(b,c,d,a,(*it)[8],20,0x455a14ed); 
        GG(a,b,c,d,(*it)[13],5,0xa9e3e905); 
        GG(d,a,b,c,(*it)[2],9,0xfcefa3f8) ;
        GG(c,d,a,b,(*it)[7],14,0x676f02d9) ;
        GG(b,c,d,a,(*it)[12],20,0x8d2a4c8a);


        //第三轮
        HH(a,b,c,d,(*it)[5],4,0xfffa3942); 
        HH(d,a,b,c,(*it)[8],11,0x8771f681); 
        HH(c,d,a,b,(*it)[11],16,0x6d9d6122); 
        HH(b,c,d,a,(*it)[14],23,0xfde5380c) ;
        HH(a,b,c,d,(*it)[1],4,0xa4beea44) ;
        HH(d,a,b,c,(*it)[4],11,0x4bdecfa9) ;
        HH(c,d,a,b,(*it)[7],16,0xf6bb4b60) ;
        HH(b,c,d,a,(*it)[10],23,0xbebfbc70); 
        HH(a,b,c,d,(*it)[13],4,0x289b7ec6); 
        HH(d,a,b,c,(*it)[0],11,0xeaa127fa); 
        HH(c,d,a,b,(*it)[3],16,0xd4ef3085); 
        HH(b,c,d,a,(*it)[6],23,0x04881d05); 
        HH(a,b,c,d,(*it)[9],4,0xd9d4d039); 
        HH(d,a,b,c,(*it)[12],11,0xe6db99e5); 
        HH(c,d,a,b,(*it)[15],16,0x1fa27cf8) ;
        HH(b,c,d,a,(*it)[2],23,0xc4ac5665);

        //第四轮
        II(a,b,c,d,(*it)[0],6,0xf4292244) ;
        II(d,a,b,c,(*it)[7],10,0x432aff97) ;
        II(c,d,a,b,(*it)[14],15,0xab9423a7); 
        II(b,c,d,a,(*it)[5],21,0xfc93a039) ;
        II(a,b,c,d,(*it)[12],6,0x655b59c3) ;
        II(d,a,b,c,(*it)[3],10,0x8f0ccc92) ;
        II(c,d,a,b,(*it)[10],15,0xffeff47d); 
        II(b,c,d,a,(*it)[1],21,0x85845dd1) ;
        II(a,b,c,d,(*it)[8],6,0x6fa87e4f) ;
        II(d,a,b,c,(*it)[15],10,0xfe2ce6e0); 
        II(c,d,a,b,(*it)[6],15,0xa3014314) ;
        II(b,c,d,a,(*it)[13],21,0x4e0811a1); 
        II(a,b,c,d,(*it)[4],6,0xf7537e82) ;
        II(d,a,b,c,(*it)[11],10,0xbd3af235); 
        II(c,d,a,b,(*it)[2],15,0x2ad7d2bb); 
        II(b,c,d,a,(*it)[9],21,0xeb86d391);


        A += a;
        B += b;
        C += c;
        D += d;
    }
    cout<<"MD5 = ";
    output(A);
    output(B);
    output(C);
    output(D);
    cout<<endl;
    return 0;
}

