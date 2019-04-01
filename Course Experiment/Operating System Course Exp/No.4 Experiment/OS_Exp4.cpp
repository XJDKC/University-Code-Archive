#include "OS_Exp4.h"
#include "mainwindow.h"

MainWindow *GUI;
vector<extraInfo> info(128);

void *run(void *GUI)
{
    string path;
    ::GUI=static_cast<MainWindow *>(GUI);
    path=::GUI->dir->text().toStdString();
    printDir(const_cast<char *>(path.c_str()), 0);
    ::GUI->endThread();
    return 0;
}
void printDir(char *dir, int depth)
{
    DIR *dp;
    int count=0;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(dir))==NULL)
    {
        printInfo(string("Fail to open the dir:")+dir);
        return;
    }
    if (depth==0)
        printInfo(string(dir) + "\n");
    chdir(dir);
    getInfo(dp,depth);
    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        info[depth/4].end=(++count)==info[depth/4].Total;

        printTree(depth);
        printStat(&statbuf, entry, depth);
        if (entry->d_type == DT_DIR)
        {
            printDir(entry->d_name, depth + 4);
        }
    }
    if (depth)
        chdir("..");
    closedir(dp);
}

void printInfo(string s)
{
    QString text=GUI->label->text();
    text+=QString::fromStdString(s);
    GUI->label->setText(text);
    GUI->label->adjustSize();
}

void printStat(struct stat *statbuf, struct dirent *entry, int depth)
{
    QString text=GUI->label->text();
    stringstream out;
    struct tm modify_time;
    struct passwd *usr;
    struct group *group;

    localtime_r(&statbuf->st_mtim.tv_sec, &modify_time);
    usr = getpwuid(statbuf->st_uid);
    if (usr==NULL)
        perror("ERROR:");
    group = getgrgid(statbuf->st_gid);

    S_ISDIR(statbuf->st_mode);

    //print name
    //cout << left << setw(info[depth / 4].maxLength + strlen(entry->d_name) - utf8_strlen(entry->d_name))
    //     << setfill(' ') << (entry->d_name) << " ";

    //print st_mode
    out << (statbuf->st_mode & 0x4000 ? 'd' : '-');
    for (int i = 0; i < 3; i++)
        out << (statbuf->st_mode & 1 << (8 - 3 * i) ? 'r' : '-')
             << (statbuf->st_mode & 1 << (7 - 3 * i) ? 'w' : '-')
             << (statbuf->st_mode & 1 << (6 - 3 * i) ? 'x' : '-');
    out << " ";

    //print usr
    out << usr->pw_name << " ";

    //print group
    out << group->gr_name << " ";

    //print size
    out << right << setw(to_string(info[depth / 4].maxSizeNum).size()) << setfill(' ') << statbuf->st_size << " ";

    //print time
    out << modify_time.tm_mon + 1 << "月 "
         << modify_time.tm_mday << " "
         << setw(2) << setfill('0') << modify_time.tm_hour << ":"
         << setw(2) << setfill('0') << modify_time.tm_min << " ";

    //print d_name
    out << entry->d_name << endl;

    text+=QString::fromStdString(out.str());
    GUI->label->setText(text);
    GUI->label->adjustSize();
    GUI->label->scroll(0,GUI->label->size().height());
}

int filter(const struct dirent *entry)
{
    struct stat statbuf;
    lstat(entry->d_name, &statbuf);
    if (S_ISDIR(statbuf.st_mode))
        return true;
    return false;
}

void printTree(int depth)
{
    for (int i = 0; i <= depth;i+=4)
    {
        if (i!=depth)
        {
            if (!info[i / 4].end)
                printInfo("│   ");
            else
                printInfo("    ");
        }
        else
        {
            if (info[i/4].end)
                printInfo("└── ");
            else
                printInfo("├── ");
        }
    }
}

void getInfo(DIR *dp,int depth)
{
    struct stat statbuf;
    struct dirent *entry, **namelist=NULL;

    if (info.size()<=depth/4)
        info.push_back(extraInfo());
    info[depth / 4]=0;
    while ((entry = readdir(dp)) != NULL)
    {
        info[depth / 4].Total++;
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            info[depth / 4].dirNum++;
            //info[depth / 4].maxDirNum = (info[depth / 4].maxDirNum, scandir(dir, &namelist, filter, alphasort));
            //free(namelist);
        }
        info[depth / 4].maxSizeNum = max(info[depth / 4].maxSizeNum, (int)statbuf.st_size);
        info[depth / 4].maxLength = max(info[depth / 4].maxLength, utf8_strlen(entry->d_name));
    }
    info[depth / 4].Total-=2;
    rewinddir(dp);
}

int utf8_strlen(const char *s)
{
    int i, j;
    int len = 0;
    for (i = 0; s[i] != 0; i++)
    {
        if (s[i] & 0x80)
        {
            j = 1;
            while ((s[++i] & 0x80) && !(s[i] & 0x40))
                j++;
            len += 2;
            i--;
        }
        else
            len++;
    }
    return len;
}
