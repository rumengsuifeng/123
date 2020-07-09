/*该函数的功能为实现sdelay函数，自己编写延时函数*/
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/jiffies.h>  //包含的头文件
#include <linux/delay.h>

void sdelay(unsigned long sec)
{
    unsigned long time = jiffies + sec * HZ;  //计算出来你要延时多少时间 sec*HZ计算出来你要经过多少时钟滴答

    while(time_is_after_jiffies(time))    //该函数的作用为如果时钟滴答不等于time，那么就一直循环于此
        ;
}

static int __init test_init(void)
{
    /*local_irq_disable();*/

	printk("jiffies = %lu\n", jiffies);  //通过打印此变量，可以知道当前自开机以来经过了多少个时钟滴答

    sdelay(2);
    /*mdelay(2000);*/
    /*ssleep(2);*/

    printk("jiffies = %lu\n", jiffies);    //可以看到现在的时钟滴答确实是延时2s之后的值 +400

    /*local_irq_enable();*/

	return 0;
}

static void __exit test_exit(void)
{

}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lzc");

