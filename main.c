
#include<iostream>
#include<fstream>
#include<cctype>
using namespace std;

int compareText(const char *,const char *);

class STRING
{
    char *s;

public:

    // Default constructor
    STRING()
    {
        s=new char[1]();
    }

    // Parameterized constructor
    STRING(const char *str)
    {
        int i;
        for(i=0;str[i];i++);

        s=new char[i+1];

        for(i=0;str[i];i++)
            s[i]=str[i];

        s[i]='\0';
    }

    // Copy constructor
    STRING(const STRING &t)
    {
        int i;

        for(i=0;t.s[i];i++);

        s=new char[i+1];

        for(i=0;t.s[i];i++)
            s[i]=t.s[i];

        s[i]='\0';
    }

    // Destructor
    ~STRING()
    {
        delete []s;
        s=nullptr;
    }

    void getdata()
    {
        cout<<s<<endl;
    }

    // Assignment operator
    STRING& operator =(const STRING &t)
    {
        if(this!=&t)
        {
            int i;

            for(i=0;t.s[i];i++);

            char *temp=new char[i+1];

            for(i=0;t.s[i];i++)
                temp[i]=t.s[i];

            temp[i]='\0';

            delete []s;
            s=temp;
        }

        return *this;
    }

    // Addition operator
    STRING operator +(const STRING &t2)
    {
        int i,j;

        for(i=0;s[i];i++);
        for(j=0;t2.s[j];j++);

        char *temp=new char[i+j+1];

        int k;

        for(k=0;s[k];k++)
            temp[k]=s[k];

        for(j=0;t2.s[j];j++,k++)
            temp[k]=t2.s[j];

        temp[k]='\0';

        STRING result(temp);

        delete []temp;

        return result;
    }

    // Subscript operator
    char& operator [](int i)
    {
        return s[i];
    }

    // Comparison operators
    int operator >(const STRING &t)
    {
        return compareText(s,t.s)>0;
    }

    int operator <(const STRING &t)
    {
        return compareText(s,t.s)<0;
    }

    int operator >=(const STRING &t)
    {
        return compareText(s,t.s)>=0;
    }

    int operator <=(const STRING &t)
    {
        return compareText(s,t.s)<=0;
    }

    int operator ==(const STRING &t)
    {
        return compareText(s,t.s)==0;
    }

    int operator !=(const STRING &t)
    {
        return compareText(s,t.s)!=0;
    }

    friend istream& operator >>(istream &,STRING &);
    friend ostream& operator <<(ostream &,const STRING &);

    friend int Strlen(const STRING &);
    friend void Strcpy(STRING &,const STRING &);
    friend void Strncpy(STRING &,const STRING &,int);
    friend int Strcmp(const STRING &,const STRING &);
    friend int Strncmp(const STRING &,const STRING &,int);
    friend void Strcat(STRING &,const STRING &);
    friend void Strncat(STRING &,const STRING &,int);
    friend void Strrev(STRING &);
    friend void Strupr(STRING &);
    friend void Strlwr(STRING &);
    friend const char * Strchr(const STRING &,char);
    friend const char * Strrchr(const STRING &,char);
    friend char * Strstr(STRING &,const char *);
};

////////////////////////////////////////////////////

// Comparison function
int compareText(const char *s1,const char *s2)
{
    int i;

    for(i=0;s1[i] || s2[i];i++)
    {
        if(s1[i]!=s2[i])
            return s1[i]-s2[i];
    }

    return 0;
}

////////////////////////////////////////////////////

// Extraction operator
istream& operator >>(istream &in,STRING &d)
{
    in>>ws;

    int size=16;
    int i=0;
    char ch;

    char *temp=new char[size];

    while(in.peek()!=EOF &&
          !isspace((unsigned char)in.peek()))
    {
        in.get(ch);

        if(i==size-1)
        {
            size=size*2;

            char *newtemp=new char[size];

            for(int j=0;j<i;j++)
                newtemp[j]=temp[j];

            delete []temp;
            temp=newtemp;
        }

        temp[i++]=ch;
    }

    if(i==0)
    {
        delete []temp;
        in.setstate(ios::failbit);
        return in;
    }

    temp[i]='\0';

    delete []d.s;
    d.s=temp;

    return in;
}

// Insertion operator
ostream& operator <<(ostream &out,const STRING &d)
{
    out<<d.s;
    return out;
}

////////////////////////////////////////////////////

// Strlen
int Strlen(const STRING &p)
{
    int i;

    for(i=0;p.s[i];i++);

    return i;
}

// Strcpy
void Strcpy(STRING &d,const STRING &sr)
{
    int i;

    for(i=0;sr.s[i];i++);

    char *temp=new char[i+1];

    for(i=0;sr.s[i];i++)
        temp[i]=sr.s[i];

    temp[i]='\0';

    delete []d.s;
    d.s=temp;
}

// Strncpy
void Strncpy(STRING &d,const STRING &sr,int n)
{
    int i;

    if(n<0)
        return;

    char *temp=new char[n+1];

    for(i=0;i<n && sr.s[i];i++)
        temp[i]=sr.s[i];

    for(;i<n;i++)
        temp[i]='\0';

    temp[n]='\0';

    delete []d.s;
    d.s=temp;
}

// Strcmp
int Strcmp(const STRING &s1,const STRING &s2)
{
    return compareText(s1.s,s2.s);
}

// Strncmp
int Strncmp(const STRING &s1,const STRING &s2,int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        if(s1.s[i]!=s2.s[i])
            return s1.s[i]-s2.s[i];

        if(s1.s[i]=='\0')
            return 0;
    }

    return 0;
}

// Strcat
void Strcat(STRING &s1,const STRING &s2)
{
    int i,j;

    for(i=0;s1.s[i];i++);
    for(j=0;s2.s[j];j++);

    char *temp=new char[i+j+1];

    int k;

    for(k=0;s1.s[k];k++)
        temp[k]=s1.s[k];

    for(j=0;s2.s[j];j++,k++)
        temp[k]=s2.s[j];

    temp[k]='\0';

    delete []s1.s;
    s1.s=temp;
}

// Strncat
void Strncat(STRING &s1,const STRING &s2,int n)
{
    int i,j;

    if(n<0)
        return;

    for(i=0;s1.s[i];i++);

    for(j=0;j<n && s2.s[j];j++);

    char *temp=new char[i+j+1];

    int k;

    for(k=0;s1.s[k];k++)
        temp[k]=s1.s[k];

    for(j=0;j<n && s2.s[j];j++,k++)
        temp[k]=s2.s[j];

    temp[k]='\0';

    delete []s1.s;
    s1.s=temp;
}

// Strrev
void Strrev(STRING &p)
{
    char t;
    int i,j;

    for(i=0;p.s[i];i++);

    for(i=0,j=i-1;i<j;i++,j--)
    {
        t=p.s[i];
        p.s[i]=p.s[j];
        p.s[j]=t;
    }
}

// Strupr
void Strupr(STRING &p)
{
    int i;

    for(i=0;p.s[i];i++)
    {
        if(p.s[i]>='a' && p.s[i]<='z')
            p.s[i]=p.s[i]-32;
    }
}

// Strlwr
void Strlwr(STRING &p)
{
    int i;

    for(i=0;p.s[i];i++)
    {
        if(p.s[i]>='A' && p.s[i]<='Z')
            p.s[i]=p.s[i]+32;
    }
}

// Strchr
const char * Strchr(const STRING &p,char ch)
{
    int i;

    for(i=0;p.s[i];i++)
    {
        if(p.s[i]==ch)
            return &p.s[i];
    }

    if(ch=='\0')
        return &p.s[i];

    return nullptr;
}

// Strrchr
const char * Strrchr(const STRING &p,char ch)
{
    int i;

    for(i=0;p.s[i];i++);

    for(i=i-1;i>=0;i--)
    {
        if(p.s[i]==ch)
            return &p.s[i];
    }

    if(ch=='\0')
        return &p.s[i+1];

    return nullptr;
}

// Strstr
char * Strstr(STRING &m,const char *str)
{
    int i,j;

    if(str[0]=='\0')
        return m.s;

    for(i=0;m.s[i];i++)
    {
        if(m.s[i]==str[0])
        {
            for(j=0;str[j];j++)
            {
                if(m.s[i+j]!=str[j])
                    break;
            }

            if(str[j]=='\0')
                return &m.s[i];
        }
    }

    return nullptr;
}



int main()
{
    ifstream fin("input.txt");

    if(!fin)
    {
        cout<<"File not opened"<<endl;
        return 0;
    }

    STRING s1,s2("vector"),s3(s2),s4,s5;

    fin>>s1;
    fin>>s5;

    fin.close();

    cout<<"s1="<<s1<<"<------default constructor"<<endl;
    cout<<"s2="<<s2<<"<------parameterized constructor"<<endl;
    cout<<"s3="<<s3<<"<------copy constructor"<<endl;

    s4=s1;

    cout<<"assignment operator s4=s1----->"<<s4<<endl;

    s4=s1+s2;

    cout<<"concatenation s4=s1+s2----->"<<s4<<endl;

    cout<<"index operator s1[2]----->"<<s1[2]<<endl;

    cout<<"checking s1>s2----->"<<(s1>s2)<<endl;
    cout<<"checking s1<s2----->"<<(s1<s2)<<endl;
    cout<<"checking s1>=s2----->"<<(s1>=s2)<<endl;
    cout<<"checking s1<=s2----->"<<(s1<=s2)<<endl;
    cout<<"checking s1!=s2----->"<<(s1!=s2)<<endl;
    cout<<"checking s1==s2----->"<<(s1==s2)<<endl;

    cout<<"Strlen(s1)----->"<<Strlen(s1)<<endl;

    Strcpy(s2,s1);
    cout<<"Strcpy(s2,s1)----->s2="<<s2<<endl;

    Strcat(s3,s1);
    cout<<"Strcat(s3,s1)----->s3="<<s3<<endl;

    const char *p2=Strchr(s3,'r');

    if(p2==nullptr)
        cout<<"Strchr----->no char found"<<endl;
    else
        cout<<"Strchr(s3,'r')----->"<<p2<<endl;

    Strupr(s4);
    Strlwr(s1);

    cout<<"Strupr(s4)----->s4="<<s4<<endl;
    cout<<"Strlwr(s1)----->s1="<<s1<<endl;

    cout<<"Strcmp(s1,s3)----->"<<Strcmp(s1,s3)<<endl;

    cout<<"s5="<<s5<<endl;

    cout<<"Strstr(s3,\"lo\")----->"<<Strstr(s3,"lo")<<endl;

    Strrev(s2);
    cout<<"Strrev(s2)----->s2="<<s2<<endl;

    Strncat(s5,s1,2);
    cout<<"Strncat(s5,s1,2)----->s5="<<s5<<endl;

    STRING s6;

    Strncpy(s6,s5,3);
    cout<<"Strncpy(s6,s5,3)----->s6="<<s6<<endl;

    cout<<"Strncmp(s5,s6,3)----->"<<Strncmp(s5,s6,3)<<endl;

    const char *p=Strrchr(s5,'t');

    if(p==nullptr)
        cout<<"Strrchr----->no char found"<<endl;
    else
        cout<<"Strrchr(s5,'t')----->"<<p<<endl;

    return 0;
}
