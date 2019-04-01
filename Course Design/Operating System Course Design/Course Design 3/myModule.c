#include <linux/kernel.h>   //
#include <linux/module.h>   //支持动态添加模块和卸载模块
#include <linux/fs.h>       //包含文件操作相关的struct定义，例如file_operations
#include <linux/errno.h>    //包含对于返回值的宏定义，这样用户程序可以用perror输出错误信息
#include <linux/types.h>    //对于特殊类型的定义
#include <linux/cdev.h>     //对于字符设备结构cdev以及一系列操作函数的定义
#include <linux/init.h>
#include <linux/slab.h>     //包含对于kacalloc以及kzalloc内存分配函数的定义
#include <linux/uaccess.h>  //包含了copy_to_user、copy_from_user等内核访问用户内存地址的函数定义

//#if CONFIG_MODVERSIONS==1
//#define MODVERSIONS
//#include "linux/version.h"
//#endif

#define MAX_SIZE 1024

int device_num;
char *devName = "XRL_Module";
char message[MAX_SIZE];

int init_module(void );
void cleanup_module(void );
int xrl_open(struct inode *, struct file *);
int xrl_release(struct inode *, struct file *);
ssize_t xrl_read(struct file *, char __user *, size_t, loff_t *);
ssize_t xrl_write(struct file *, const char __user *, size_t, loff_t *);

struct file_operations fops = {
    .open = xrl_open,
    .release = xrl_release,
    .read = xrl_read,
    .write = xrl_write
};

/* 注册 */
int init_module()
{
    int ret;

    if ((ret = register_chrdev(0,devName,&fops))<0) {
        printk("failed to register %s.\n",devName);
        return -1;
    }
    else {
        device_num = ret;
        printk("the %s has been registered!\n", devName);
        printk("the device ID is %d.\n", ret);
        return 0;
    }
}

void cleanup_module()
{
    unregister_chrdev(device_num,devName);
    printk("unregister %s successfully！\n",devName);
}

int xrl_open(struct inode *inode, struct file *file)
{
    printk("open %s successfully!\n",devName);
    try_module_get(THIS_MODULE);
    return 0;
}

int xrl_release(struct inode *inode, struct file *file)
{
    printk("release %s successfully!\n",devName);
    module_put(THIS_MODULE);
    return 0;
}

ssize_t xrl_read(struct file *file, char __user *user, size_t t, loff_t *f)
{
    int length=MAX_SIZE<t?MAX_SIZE:t;
    if (copy_to_user(user,message,length))
    {
        return -2;
    }
    return length;
}

ssize_t xrl_write(struct file *file, const char __user *user, size_t t, loff_t *f)
{
    int length=MAX_SIZE<t?MAX_SIZE:t;
    if (copy_from_user(message,user,length))
    {
        return -3;
    }
    return length;
}

MODULE_LICENSE("Dual BSD/GPL");
