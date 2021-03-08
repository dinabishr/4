#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/slab.h>


struct myfile{

	struct file *f;
	mm_segment_t fs;
	loff_t pos;

};

struct myfile *open_file_for_read(char *filename){
	struct myfile *m_f;

	m_f->f=filp_open(filename,O_RDONLY,0);

return m_f;

}

volatile int read_from_file_until(struct myfile *mf,char *buff,unsigned long vlen,char c){
	int result;

	result=vfs_read(mf->f,buff,vlen,&(mf-> pos));


return result;

}


void close_file(struct myfile *mf){

	filp_close(mf->f,NULL);

}


static int init(void){
	struct myfile *_file;
	char *buf;
	int val;
	buf= kmalloc(80,GFP_KERNEL);
	printk(KERN_INFO "Hello World CSCE-3402 :)\n");
	_file->fs=get_fs();
	set_fs(KERNEL_DS);
	_file = open_file_for_read("/proc/version");

	val=read_from_file_until(_file,buf,80,'.');
	printk(KERN_INFO "%s\n",buf);
	set_fs(_file->fs);
	close_file(_file);
	kfree(buf);
	return 0;
}



static void cleanup(void){

	printk(KERN_INFO "Bye bye CSCE-3402 :) \n");
/*f*/
}


module_init(init);
module_exit(cleanup);

MODULE_LICENSE("GPL");



