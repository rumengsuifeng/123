/*�ú����Ĺ���Ϊʵ��sdelay�������Լ���д��ʱ����*/
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/jiffies.h>  //������ͷ�ļ�
#include <linux/delay.h>

void sdelay(unsigned long sec)
{
    unsigned long time = jiffies + sec * HZ;  //���������Ҫ��ʱ����ʱ�� sec*HZ���������Ҫ��������ʱ�ӵδ�

    while(time_is_after_jiffies(time))    //�ú���������Ϊ���ʱ�ӵδ𲻵���time����ô��һֱѭ���ڴ�
        ;
}

static int __init test_init(void)
{
    /*local_irq_disable();*/

	printk("jiffies = %lu\n", jiffies);  //ͨ����ӡ�˱���������֪����ǰ�Կ������������˶��ٸ�ʱ�ӵδ�

    sdelay(2);
    /*mdelay(2000);*/
    /*ssleep(2);*/

    printk("jiffies = %lu\n", jiffies);    //���Կ������ڵ�ʱ�ӵδ�ȷʵ����ʱ2s֮���ֵ +400

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

