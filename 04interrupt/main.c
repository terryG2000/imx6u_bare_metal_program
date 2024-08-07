
#include "led.h"
#include "common.h"
#include "gic.h"


void init_pins(void)
{
	/* led pins */
    // IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER3_GPIO5_IO03, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER3_GPIO5_IO03, 
    //                     IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
	
	//led pins GPIO1_IO03
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

	// key0 GPIO1_IO18
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0U);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 
                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_DSE(1U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

						

	// /* uart1 pins */	
	// IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0U);
	// IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 
	// 					IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_PKE_MASK);
	// IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0U);
	// IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 
	// 					IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_PKE_MASK);

	// /* KEY1 pins GPIO5_1 SNVS_TAMPER1 */
	// IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0U);
	// IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 
	// 					IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
	// 					IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

	// /* KEY2 pins GPIO4_IO14 */
	// IOMUXC_SetPinMux(IOMUXC_NAND_CE1_B_GPIO4_IO14, 0U);
	// IOMUXC_SetPinConfig(IOMUXC_NAND_CE1_B_GPIO4_IO14, 
	// 					IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
	// 					IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
	// 					IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

}

// void delay(volatile unsigned int d)
// {
// 	while(d--);
// }
/*
 * @description	: 短时间延时函数
 * @param - n	: 要延时循环次数(空操作循环次数，模式延时)
 * @return 		: 无
 */
void delay_short(volatile unsigned int n)
{
	while(n--){}
}

/*
 * @description	: 延时函数,在396Mhz的主频下
 * 			  	  延时时间大约为1ms
 * @param - n	: 要延时的ms数
 * @return 		: 无
 */
void delay(volatile unsigned int n)
{
	while(n--)
	{
		delay_short(0x7ff);
	}
}

void boot_clk_gate_init(void)
{
    CCM->CCGR0 = 0xFFFFFFFFU;
    CCM->CCGR1 = 0xFFFFFFFFU;
    CCM->CCGR2 = 0xFFFFFFFFU;
    CCM->CCGR3 = 0xFFFFFFFFU;
    CCM->CCGR4 = 0xFFFFFFFFU;
    CCM->CCGR5 = 0xFFFFFFFFU;
    CCM->CCGR6 = 0xFFFFFFFFU;
}

void boot_clk_init(void)
{
	if ((CCM->CCSR & (1 << 2)) == 0 ) /* CPU runs on ARM PLL : bit2 pll1_sw_clk_sel*/
	{
		CCM->CCSR &= ~(1 << 8);/* Set Step MUX to OSC : bit8 STEP_SEL */
		CCM->CCSR |= (1 << 2);/* Let CPU run on Step MUX : bit2 pll1_sw_clk_sel*/
	}

	CCM_ANALOG->PLL_ARM = (1 << 13) | (88 << 0); /*Configure ARM PLL to 1056M:bit13 Enable, bit0~6 DIV_SELECT*/
	CCM->CCSR &= ~(1 << 2); /* Now CPU runs again on ARM PLL*/
	CCM->CACRR = 1; /* Configure ARM clock root with divide 2 */

#if 0
	/* Set periph2_clk2 and periph_clk2 MUX to OSC */
	CCM->CBCMR &= ~((3 << 20) | ( 3 << 12));
	CCM->CBCMR |= (1 << 20) | ( 1 << 12);
	/* Let BUS and mmdc clock run on OSC */
	CCM->CBCDR &= ~((1 << 6) | ( 1 << 25) | ( 1 << 26));
	CCM->CBCDR |= (0 << 6) | ( 1 << 25) | ( 1 << 26);
	/* Wait handshake process */
	while (CCM->CDHIPR & ((1 << 5) | (1 << 3)))
	{
	}

	/* Configure SYS PLL to 528M */
	CCM_ANALOG->PLL_SYS_SS &= (1 << 15);
	CCM_ANALOG->PLL_SYS_NUM = 0; 
	CCM_ANALOG->PLL_SYS = (1 << 13) | (1 << 0);
	/* wait for PLL is locked */
	while ((CCM_ANALOG->PLL_SYS & (1 << 31)) == 0)
	{
	}
#endif

	 /* Configure PFD_528
	 * PFD0     : Enable, set divider 27 352M
	 * PFD1     : Enable, set divider 16 594M
	 * PFD2     : Enable, set divider 24 396M
	 * PFD3     : Enable, set divider 48 198M
	 */
	 /* Disable all clock output first. */
	//CCM_ANALOG->PFD_528 |= (1 << 31) | ( 1 << 23) | (1 << 15) | ( 1 << 7);
	/* Clear first, then Set default divide value for all PFD. */
	CCM_ANALOG->PFD_528 &= ~((0x3F << 24) | (0x3F << 16) | (0x3F << 8) | (0x3F << 0));
	CCM_ANALOG->PFD_528 |= (0x30 << 24) | (0x18 << 16) | (0x10 << 8) | (0x1B << 0);
	/* Enable PFD_528 PFD0~3*/
	//CCM_ANALOG->PFD_528 &= ~((1 << 31) | ( 1 << 23) | (1 << 15) | ( 1 << 7));
	

	/* Configure PFD_480
	 * PFD0     : Enable, set divider 12 720M
	 * PFD1     : Enable, set divider 16 540M
	 * PFD2     : Enable, set divider 17 508.2M
	 * PFD3     : Enable, set divider 19 454.7M
	 */
	/* Disable all clock output. */
	//CCM_ANALOG->PFD_480 |= (1 << 31) | ( 1 << 23) | (1 << 15) | ( 1 << 7);
	/* Clear first, then Set default divide value for all PFD. */
	CCM_ANALOG->PFD_480 &= ~((0x3F << 24) | (0x3F << 16) | (0x3F << 8) | (0x3F << 0));
	CCM_ANALOG->PFD_480 |= (0x13 << 24) | (0x11 << 16) | (0x10 << 8) | (0xC << 0);
	/* Enable PFD_528 PFD0~3*/
	//CCM_ANALOG->PFD_480 &= ~((1 << 31) | ( 1 << 23) | (1 << 15) | ( 1 << 7));

    /* Configure BUS clcok
     * AHB     : Sourced from SYS PLL PFD2 396M with divider 3 132M
     * IPG     : Sourced from AHB with divider 2 66M
     * AXI     : Sourced from SYS PLL PFD2 396M with divider 2 198M
     * MMDC    : Sourced from SYS PLL PFD2 396M with divider 1 396M
     */
     /*
      *AHB_CLK_ROOT<= PLL2 PFD2(pre_periph_clk=1 periph_clk=0 ahb_podf=3)
      *IPG_CLK_ROOT<=AHB_CLK_ROOT(ipg_pdof=2)
      *AXI_CLK_ROOT<= PLL2 PFD2(AXI_pdof=2)
      */

    /* Set pre_periph2_clk and pre_periph_clk MUX to SYS PLL PFD2*/
    CCM->CBCMR &= ~((3 << 18) | ( 3 << 21));
	CCM->CBCMR |= (1 << 18) | ( 1 << 21);

    /* Set periph2_clk and periph_clk MUX to PLL2*/
    CCM->CBCDR &= ~((1 << 26) | ( 1 << 25));
	CCM->CBCDR |= (0 << 26) | ( 0 << 25);//no use, just for tidy

	/* Config AXI divide by 2, AHB divide by 3, IPG divide by 2 */
	//CCM->CBCDR &= ~((7 << 16) | ( 7 << 10) | ( 3 << 8));
	//CCM->CBCDR |= (1 << 16) | ( 2 << 10) | ( 1 << 8);
	/* Config AXI divide by 2, IPG divide by 2 */
	CCM->CBCDR &= ~((7 << 16) | ( 3 << 8));
	CCM->CBCDR |= (1 << 16) | ( 1 << 8);

	/* Config other filed in CBCDR to certain value */
	/* AXI root clock from PLL2 PFD2, PERIPH_CLK2_PODF=0,PERIPH2_CLK2_PODF=0*/
	CCM->CBCDR &= ~((1 << 7) | ( 7 << 27) | ( 7 << 0));
	CCM->CBCDR |= (0 << 7) | ( 0 << 27) | ( 0 << 0);

	/* Wait handshake process */
	while (CCM->CDHIPR & ((1 << 5) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0)))
	{
	}

	/* Select PLL3 to generate pll3_sw_clk from pll3_main_clk */
    CCM->CCSR &= ~(1 << 0);

    CCM->CSCDR1 &= ~(1 << 6); /* Set UART source to PLL3 80M */
    CCM->CSCDR1 &= ~(0x3F << 0); /* Set UART divider to 1 */

	/* Set PERCLK_CLK_ROOT (I2C/EPIT source) to IPG 66M */
	CCM->CSCMR1 &= ~(1 << 6); /* Set I2C/EPIT source to IPG 66M */
    CCM->CSCMR1 &= ~(0x3F << 0); /* Set I2C/EPIT divider to 1 */

}


void key_gpio5_handle_irq(void)
{
	/* read GPIO5_DR to get GPIO5_IO01 status*/
	if((GPIO5->DR >> 1 ) & 0x1) {
		// printf("key 1 is release\r\n");
		/* led off, set GPIO5_DR to configure GPIO5_IO03 output 1 */
		GPIO5->DR |= (1<<3); //led on
	} else {
		// printf("key 1 is press\r\n");
		/* led on, set GPIO5_DR to configure GPIO5_IO03 output 0 */
		GPIO5->DR &= ~(1<<3); //led off
	}
	/* write 1 to clear GPIO5_IO03 interrput status*/
	GPIO5->ISR |= (1 << 1);
}

void key_gpio4_handle_irq(void)
{
	/* read GPIO4_DR to get GPIO4_IO014 status*/
	if((GPIO4->DR >> 14 ) & 0x1)
		led_ctl(1);
		// printf("key 2 is release\r\n");
	else
		led_ctl(0);
		// printf("key 2 is press\r\n");
	/* write 1 to clear GPIO4_IO014 interrput status*/
	GPIO4->ISR |= (1 << 14);
}

void key_gpio1_18_handle_irq(uint32_t nr, void *param){
	static char last_status =  0;
	/* read GPIO4_DR to get GPIO4_IO014 status*/
	if((GPIO1->DR >> 18 ) & 0x1)
		led_ctl(1);
	else
		led_ctl(0);


	// if(last_status == 0){
    // 	led_ctl(1);
	// 	last_status = 1;
	// }
	// else{
    // 	led_ctl(0);
	// 	last_status = 0;
	// }
	/* write 1 to clear GPIO4_IO014 interrput status*/
	GPIO1->ISR |= (1 << 18);
}

void key_irq_init(void)
{
	GPIO1->ICR2 |= (0x2u << 4); // gpio1 18 
	// /* if set detects any edge on the corresponding input signal 会覆盖ICR 的配置*/
	// GPIO1->EDGE_SEL &= ~(1 << 18);
	/* if set 1, unmasked, Interrupt n is enabled */
	GPIO1->IMR |= (1 << 18);
	/* clear interrupt first to avoid unexpected event */
	GPIO1->ISR |= (1 << 18);



	request_irq(GPIO1_Combined_16_31_IRQn, (irq_handler_t)key_gpio1_18_handle_irq, NULL);// GPIO1_IO18
	// request_irq(GPIO5_Combined_0_15_IRQn, (irq_handler_t)key_gpio5_handle_irq, NULL);
	// request_irq(GPIO4_Combined_0_15_IRQn, (irq_handler_t)key_gpio4_handle_irq, NULL);
}
void key_input_init(void){
	//设置为输入 GPIO1 18
	GPIO1->GDIR &= ~(1<<18);
}

void system_init()
{
	init_pins();
	led_gpio_init();
	key_input_init();
	led_ctl(0);//turn off led
	boot_clk_gate_init();
	boot_clk_init();
	system_init_irq_table();
	key_irq_init();
	gic_init();
	gic_enable_irq(GPIO1_Combined_16_31_IRQn);
	// gic_enable_irq(GPIO4_Combined_0_15_IRQn);
}

int  main()
{
	unsigned char c;
	#if 0
	GIC_Type *gic = (GIC_Type *)0xa00000;
	printf("GICD_TYPER is 0x%x\r\n", gic->D_TYPER);
	printf("GICD_IIDR is 0x%x\r\n", gic->D_IIDR);
	printf("GICD_CTLR is 0x%x\r\n", gic->D_CTLR);
	printf("GICC_RPR is 0x%x\r\n", gic->C_RPR);
	printf("GICC_IAR is 0x%x\r\n", gic->C_IAR);
	#endif

	while(1)
	{
		// delay(1000);
		// led_ctl(0);
		// delay(1000);
		// led_ctl(1);
	}
					
	return 0;
}


