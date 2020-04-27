#include <fstream>
#include <iostream>
#include "SingleLink.cpp"
#include "String.cpp"

using namespace std;

void Menu(SingleLink<SString> link);

int get_len(char* a)
{
    int len = 0;
    for (int i = 0; a[i] != '\0'; i++)
        len++;
    return len;
}


int main()
{
    cout << "显示文件内容ing" << endl << endl;
    fstream file1;
    file1.open("hey.txt",ios::in|ios::out);

    if (!file1)
    {
        cout << "Error opening the file! Aborting…\n";
        exit(1);
    }


    //生成链表
    SingleLink<SString> link;

    char mline[MAXSIZE]; //每个整行将会陆续被存储在这里

    while(!file1.eof())
    {
    file1.getline(mline,MAXSIZE); // MAXSIZE是数组的大小
    cout << mline << endl;

    SString str(mline);
    link.insert_last(str);
    }
    for (int i = 0; i < MAXSIZE; i++)
        mline[i] = '\0';
    cout  << "---------------" << endl;

    // char ch[10] = {"123456789"};
    // char ch2[10] = {"long"};
    // SString a(ch), b(ch2);
    // link.mSearch(ch2);
    Menu(link);

    // char a[MAXSIZE] = {"000000"};
    // link.mInsert(a, get_len(a), 1, 8);
    // link.mDelete(4, 0, 14);
    // link.mReplace(a, get_len(a), 4, 4, 6);
    // link.show();
    // link.mSave();

    file1.close();
    return 0;
}


void Menu(SingleLink<SString> link)
{
    while (1)
    {
        cout << endl << endl;
        cout << " -------菜单--------"  << endl;
        cout << "|  信息显示：    1  |"  << endl;
        cout << "|  字符串的查找：2  |"  << endl;
        cout << "|  字符串的替换：3  |"  << endl;
        cout << "|  字符串的插入：4  |"  << endl;
        cout << "|  字符串的删除：5  |"  << endl;
        cout << "|  保存：        6  |"  << endl;
        cout << "|  退出：        7  |"  << endl;
        cout << " -------------------"  << endl;
        cout << "请选择一个操作,回车："  << endl;

        int x;
        cin >> x;
        cout << endl;

        switch (x)
        {
            case 1:
            {
                link.show();
                break;
            }

            case 2:
            {
                cout << "请输入要查找的字符串：" << endl;
                char a[MAXSIZE];
                cin >> a;
                link.mSearch(a);
                break;
            }

            case 3:
            {
                int slen,row,col,len;
                cout << "请输入行数（从1开始）：" << endl;
                cin >> row;
                cout << "请输入列数（从0开始）" << endl;
                cin >> col;
                cout << "请输入要替换的字符串：" << endl;
                char b[MAXSIZE]; 
                cin >> b;
                slen = get_len(b);
                cout << "请输入需要替换的长度" << endl;
                cin >> len;
                link.mReplace(b, slen, row, col, len);
                break;
            }

            case 4:
            {
                int len, row, col;
                cout << "请输入行数（从1开始）：" << endl;
                cin >> row;
                cout << "请输入列数（从0开始）：" << endl;
                cin >> col;
                cout << "请输入要插入的字符串：" << endl;
                char c[MAXSIZE];
                cin >> c;
                len = get_len(c);
                link.mInsert(c, len, row, col);
                break;
            }


            case 5:
            {
                int row,col,len;
                cout << "请输入删除字符串的行:" << endl;
                cin >> row;
                cout << "请输入删除字符串的列:" << endl;
                cin >> col;
                cout << "请输入删除字符串的长度:" << endl;
                cin >> len;
                link.mDelete(row, col, len);
                break;
            }
            
            case 6:
            {
                link.mSave();
                break;
            }
            
            case 7:
            {
                cout << "正在退出，请稍等..." << endl;
                exit(0);
                break;
            }

            defalt:
            {
                cout << "请输入整数1~7" << endl;
                break;
            }
        }
    }
}