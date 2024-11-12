#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PRANAV TILAK");
MODULE_DESCRIPTIOM("BASIC READ LOADABLE KERNEL MODULE");

static ssize_t pranav_read
(
    struct file* file_pointer,
    char *user_space_buffer,
    size_t count,loff_t offset);

static struct proc_ops driver_proc_ops={
    .proc_read=pranav_read
};
static struct proc_dir_entry* custom_proc_node;
static char kernel_message[]="Embedded Systems in Pyjama!\n";
static char final_kernel_message[256];
static int driver_call_count=0;

static int __init pranav_module_init (void)
{
    printk("Hello world from Pranav !!");
    custom_proc_node= proc_create("pranav_driver",0,NULL,&driver_proc_ops);
    return 0;
}

static void __exit pranav_module_exit(void)
{
    proc_remove(custom_proc_node);
    printk("Exiting this module --Pranav BYEEE!!");
}

static ssize_t pranav_read(struct file* file_pointer,char *user_space_buffer,size_t count,loff_t* offset)
{
    int message_length;
    int result;
    printk("Pranav_read method called!!!");

    snprintf(final_kernel_message,256,"%d times called - %s",driver_call_count++,kernel_message);
    message_length=strlen(final_kernel_message);
    result=copy_to_user(user_space_buffer,final_kernel_message,message_length);
    if(result)
    printk("copy_to_user failed with error %d\n",result);

*offset = message_length;
}

module_init(pranav_module_init);
module_exit(pranav_module_exit);
