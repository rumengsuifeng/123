#include <linux/module.h>
#include <linux/timer.h>

struct timer_list timer;

void timer_main(unsigned long data)
{
    printk("hello %ld\n", data);        //定时时间到了

    mod_timer(&timer, jiffies + 200);  //如果没有该语句，那么定时器函数只执行一遍就结束了,如果有了该条语句，那么
                                           //当第一次定时时间到后会来执行定时器函数,打印一句话之后又会检测定时时间是否
                                           //到了,到的话，就再次执行定时器函数,以此类推，类似于C中的递归了
}

static int __init th_init(void)         //insmod 命令的调用函数
{

    printk(" th_init --------->\n");

    setup_timer(&timer, timer_main, 10); //该函数为注册定时器,参数1是定时器  参数2是定时时间到了之后执行的函数 
                                        //                    参数3是传递给定时器函数的参数

    mod_timer(&timer, jiffies + 200);   //定时器使能   参数1 定时器    参数2 定时时间
                                        //参数2的100是多少时间这个需要查看你内核顶层目录下的.config文件,其
                                        //中的CONFIG_HZ＝200就表示是每秒200个时钟滴答,咱们这里取100,意思也就是说每
                                        //半秒定时器的定时时间会到,那么就会去执行定时器函数

    return 0;
}

static void __exit th_exit(void)    //rmmod 命令调用此函数
{
    printk(" th_exit ----->\n ");
    del_timer_sync(&timer);     
}

module_init(th_init);
module_exit(th_exit);

MODULE_LICENSE("GPL");

