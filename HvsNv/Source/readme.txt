1. ����ʹ��������оƬѡ��
�趨��USE_STDPERIPH_DRIVER��STM32F40_41xxx
������stm32f4xx.h�������Target Options������

2. ����ʱ������
�������ⲿ����ʹ��8M
�����Ҫ�޸��ⲿ�����Լ�PLL��صĺ궨��
stm32f4xx.h������
#define HSE_VALUE    ((uint32_t)8000000)
system_stm32f4xx.c������
#define PLL_M        8

3. ��ֲUCOSIII
��һ��, ���ucosiii�ļ�
���cpu,lib,core,port:
Micrium_STM3240G-EVAL_OS3\Micrium\Software
���ucos_config:
Micrium_STM3240G-EVAL_OS3\Micrium\Examples\ST\STM3240G-EVAL\OS3
������os_cpu_bsp.c��os_cpu_bsp.h,�Լ��޸ĵ�,ʵ����SYSTick�Լ�TMR����ؽӿ�,�������������ӹٷ�bsp��Щ���߰���Ķ���
�ڶ���, �޸Ĳ����ļ�
startup_stm32f40xx.s

�����Ҫ����FPU��֧��,��Ҫ��port��������ļ������޸�,�ٷ�����ò�ƻ���������,������ô�Ļ�ûϸ��
os_cpu.h
os_cpu_c.c
os_cpu_a.asm

3. ��ֲlwip,��RTOS,����RTOS�İ汾�����޸�
����Ҫ����sys_arch��ʵ������,�ź���,����Ƚӿ�
LwIP_Init��Ҫ�޸�:
tcpip_init( NULL, NULL );
netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
lwipopts.h�޸���Ӧ����
��󴴽�NET���������NETӦ������

kl----------------------------
20170117
��֧��tcp udp����
��֧�������Ȳ��
ethernetif.c line 88 �����mac�ĸ�ֵΨһ�Բ����������Ҫ������mac��ַ����Ҫ�����

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

*p_tcb ָ������Ŀ��ƿ�OS_TCB
*p_name ָ����������֣�����Ϊÿ������ȡһ������
p_task ִ��������룬Ҳ����������������
*p_arg ���ݸ�����Ĳ���
prio �������ȼ���ֵС����
*p_stk_base ָ�������ջ�Ļ���ַ
stk_limit �����ջ����ȣ�������Ᵽ֤��ջ�����
stk_size �����ջ��С
q_size COSIIIÿ�������ڶ���һ���ڲ���Ϣ���У���OS_CFG_TASK_Q_EN>0�ſ�ʹ��
time_quanta ��ʹ��ʱ��Ƭ��ת����ʱ��������ʱ��Ƭ���ȣ�Ĭ�Ͻ���Ϊʱ�ӽ��ĳ���10
*p_ext ָ���û�����Ĵ洢��
opt ����������ض�ѡ�������ѡ��
OS_OPT_TASK_NONE û���κ�ѡ��
OS_OPT_TASK_STK_CHK �Ƿ������������Ķ�ջ
OS_OPT_TASK_STK_CLR ָ���Ƿ�����������ջ
OS_OPT_TASK_SAVE_FP ָ���Ƿ�渡��Ĵ���
*p_err ������øú����󷵻صĴ������

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
�� mdk521 ���뱨���Ҳ��� core_m4.h�ȣ��� 521 ��װ�µ� 
ARM\PACK\ARM\CMSIS\4.5.0\CMSIS\Include �������� 
Source\CMSIS ����ħ���������ô�·��

20180911
�γɰ汾 HvsNv1.2.0
ֻ���޸� relay.c �� relay ��Ӧ��ϵ , �̵��� IO ȫ�����ţ���Ӧ�ò����
����仯̫Ƶ��~~~


















