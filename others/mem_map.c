#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/types.h> /* size_t */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/switch_to.h>
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/fs.h>       // for basic filesystem
#include <linux/mm.h>       // for basic filesystem
#include <linux/proc_fs.h>  // for the proc filesystem
#include <linux/seq_file.h> // for sequence files
#include <linux/mmzone.h>

MODULE_LICENSE("Dual BSD/GPL");

static struct proc_dir_entry* proc_file;


/* memory map functions */
int mem_map_show(struct seq_file *m, void *v);
//virtual_to_physical
inline unsigned long virt_to_phy(unsigned long addr);

inline unsigned long virt_to_phy(unsigned long addr){
	return __pa(addr);
}


int mem_map_show(struct seq_file *m, void *v){

	int ret_val = 0;

	//printk(KERN_INFO "Proc file read %p\n" ,);
	//seq_printf(m, "mem_map phys pages: %lu \n", (long unsigned int)get_num_physpages());
	seq_printf(m, "this is umaraz file\n");

	return ret_val;
}

static int mem_map_open(struct inode *inode, struct file *file){
	printk ("mem_map open is called\n") ;
	return single_open(file, mem_map_show, NULL);
}

struct file_operations mem_map_fops = {

	.owner = THIS_MODULE,

	.open = mem_map_open,
	
	.open = seq_open,

	.read = seq_read,

	.llseek = seq_lseek,

	.release = single_release,
};

static int __init mem_map_init(void){

	printk(KERN_INFO "Loaded mem_map module\n");

	proc_file = proc_create("umasraZ", 0, NULL, &mem_map_fops);

	if(!proc_file){

		printk(KERN_ALERT "Error: Could not initialize /proc/uma_map");

		return -ENOMEM;

	}   

	return 0;
}

static void __exit mem_map_exit(void){

	remove_proc_entry("umasraZ",NULL);  

	printk(KERN_INFO "Proc file unloaded \n");
}


/* Declaration of the init and exit functions */
module_init(mem_map_init);
module_exit(mem_map_exit);

