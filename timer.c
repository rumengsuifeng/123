
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

