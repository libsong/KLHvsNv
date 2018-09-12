1. 关于使用外设库和芯片选择
需定义USE_STDPERIPH_DRIVER和STM32F40_41xxx
具体在stm32f4xx.h定义或者Target Options里配置

2. 关于时钟配置
本工程外部晶振使用8M
因此需要修改外部晶振以及PLL相关的宏定义
stm32f4xx.h里配置
#define HSE_VALUE    ((uint32_t)8000000)
system_stm32f4xx.c里配置
#define PLL_M        8

3. 移植UCOSIII
第一步, 添加ucosiii文件
添加cpu,lib,core,port:
Micrium_STM3240G-EVAL_OS3\Micrium\Software
添加ucos_config:
Micrium_STM3240G-EVAL_OS3\Micrium\Examples\ST\STM3240G-EVAL\OS3
最后添加os_cpu_bsp.c和os_cpu_bsp.h,自己修改的,实现了SYSTick以及TMR的相关接口,这样可以免除添加官方bsp那些乱七八糟的东西
第二步, 修改部分文件
startup_stm32f40xx.s

如果需要增加FPU的支持,则还要对port里的三个文件进行修改,官方给的貌似还是有问题,具体怎么改还没细看
os_cpu.h
os_cpu_c.c
os_cpu_a.asm

3. 移植lwip,有RTOS,在无RTOS的版本上作修改
最主要就是sys_arch里实现邮箱,信号量,任务等接口
LwIP_Init里要修改:
tcpip_init( NULL, NULL );
netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
lwipopts.h修改相应参数
最后创建NET接收任务和NET应用任务

kl----------------------------
20170117
已支持tcp udp连接
已支持网线热插拔
ethernetif.c line 88 加入对mac的赋值唯一性操作，如果需要连外网mac地址是需要购买的

**void  OSTaskCreate (OS_TCB        *p_tcb,
                    CPU_CHAR      *p_name,
                    OS_TASK_PTR    p_task,
                    void          *p_arg,
                    OS_PRIO        prio,
                    CPU_STK       *p_stk_base,
                    CPU_STK_SIZE   stk_limit,
                    CPU_STK_SIZE   stk_size,
                    OS_MSG_QTY     q_size,
                    OS_TICK        time_quanta,
                    void          *p_ext,
                    OS_OPT         opt,
                    OS_ERR        *p_err)**

*p_tcb 指向任务的控制块OS_TCB
*p_name 指向任务的名字，可以为每个任务取一个名字
p_task 执行任务代码，也就是任务函数的名字
*p_arg 传递给任务的参数
prio 任务优先级，值小级高
*p_stk_base 指向任务堆栈的基地址
stk_limit 任务堆栈的深度，用来检测保证堆栈不溢出
stk_size 任务堆栈大小
q_size COSIII每个任务内都有一个内部消息队列，当OS_CFG_TASK_Q_EN>0才可使用
time_quanta 在使能时间片轮转调用时用来设置时间片长度，默认节拍为时钟节拍除以10
*p_ext 指向用户补充的存储区
opt 包含任务的特定选项，有如下选项
OS_OPT_TASK_NONE 没有任何选项
OS_OPT_TASK_STK_CHK 是否允许检测该任务的堆栈
OS_OPT_TASK_STK_CLR 指定是否清除该任务堆栈
OS_OPT_TASK_SAVE_FP 指定是否存浮点寄存器
*p_err 保存调用该函数后返回的错误代码

20180420
ip mask gw  .. defined at net_config.h Line67
port			defined at comm.h Line6

20180421
udpecho.c L76 add data deal 

20180423
the read of mcu info in flash is to read all to a buff
then to modified some in the buff 
final to write back .
do like this is to avoid the chip r/w' erase error.


20180510
turn on 	mulcast macro in opt.h line805
add 		|NETIF_FLAG_IGMP in ethernetif.c line127 to enable IGMP 
del 		init.c line176
modify 		eth_driver.c L113
modify		igmp.c Line705

20180511
mulcast send to 225.226.227.228 54345 mulcast.c Line56

20180524
用 mdk521 编译报错找不到 core_m4.h等，将 521 安装下的 
ARM\PACK\ARM\CMSIS\4.5.0\CMSIS\Include 拷贝到了 
Source\CMSIS 并在魔术棒中设置此路径

20180911
形成版本 HvsNv1.2.0
只是修改 relay.c 中 relay 对应关系 , 继电器 IO 全部开放，由应用层控制
需求变化太频繁~~~


















