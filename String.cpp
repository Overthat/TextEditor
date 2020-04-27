#ifndef ST
#define ST

#ifndef MAXSIZE
#define MAXSIZE 80
#endif

// 串类
class SString
{
private:
    char ch[MAXSIZE];
    int len;

public:
    SString()=default;
    SString(char* s);
    bool StrInsert(int pos, SString t);
    bool StrDelete(int pos, int len);

    // int StrCompare(SString t);
    int StrIndex(int pos,  SString t);

    char* get_ch(){return ch;}
    int get_len(){return len;}
};


SString::SString(char* s): len(0)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        ch[i] = s[i];
        len++;
        ch[i+1] = {'\0'};
    }
}


// 串插入函数
// pos = 指定位置 t = 注意,是SString类型
bool SString::StrInsert(int pos, SString t)
{
    if (pos < 0 || pos > len)
        return false;

    int i;

    if (len + t.len <= MAXSIZE)
    {
        for (i=len+t.len-1; i+1-t.len-pos > 0; i--)
            ch[i] = ch[i-t.len];
        for (i=0; i < t.len; i++)
            ch[i+pos] = t.ch[i];
        len += t.len;
    }

    else if (pos + t.len <= MAXSIZE)
    {
        for (i=MAXSIZE-1; i+1-pos-t.len > 0; i--)
            ch[i] = ch[i-t.len];
        for (i=0; i < t.len; i++)
            ch[i+pos] = t.ch[i];
        len = MAXSIZE;
        
    }

    else
    {
        for (i=0; i < MAXSIZE-pos; i++)
            ch[i+pos] = t.ch[i];
        len = MAXSIZE;
    }

    ch[len-1] = '\0';

    return true;
}


// 串删除函数
// pos = 指定位置 l = 删除字符的数量
bool SString::StrDelete(int pos, int l)
{
    if (pos < 0 || pos+l > len)
        return false;
    
    int i;

    for (i=pos+l; i < len ; i++)
        ch[i-l] = ch[i];
    len -= l;
    ch[len] = '\0';

    return true; 
}


// // 串比较函数,若比t大则返回正数
// // t = 待比较的串
// int SString::StrCompare(SString t)
// {
//     int i;
//     for (i=0; i<len&&i<t.len; i++)
//         if (ch[i] != t.ch[i])
//             return (ch[i]-t.ch[i]);
//     return (len - t.len);
// }


// 串查找函数,返回第一次出现t的位置
// pos = 开始比较的位置 t = 待查找的串
int SString::StrIndex(int pos,  SString t)
{
    int i, j, start;
    if (t.len == 0)
        return 0;
    start = pos;
    i = start;
    j = 0;
    while (i < len && j < t.len)
    {
        if (ch[i] == t.ch[j])
        {
            i++;
            j++;
        }
        else
        {
            start++;
            i = start;
            j = 0;
        }

    }
    return (j>=t.len ? start : -1);
}

#endif