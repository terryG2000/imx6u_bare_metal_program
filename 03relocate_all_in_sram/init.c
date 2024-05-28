
/**********************************************************************
 * 函数名称： copy_data
 * 功能描述： 将[地址src]上的的数据拷贝到[地址dest] ,拷贝的数据长度为len
 * 输入参数： src, dest, len
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号        修改人        修改内容
 * -------------------------------------------------
 * 2020/02/20	    V1.0         阿和            创建
 ***********************************************************************/
void copy_data (void)  /* src, dest, len */
{
/* 从链接脚本中获得参数 _load_addr, __bss_start, */
// _start 位于start.S中
	extern int _load_addr, _start, __bss_start;
	volatile unsigned int *dest = (volatile unsigned int *)&_start;			//_start = 0x900000
	volatile unsigned int *end = (volatile unsigned int *)&__bss_start;		//__bss_start = 0x9xxxxx
	volatile unsigned int *src = (volatile unsigned int *)&_load_addr;	

	/* 重定位数据 */	
	while (dest < end)
	{
		*dest++ = *src++;
	}
}
		  			 		  						  					  				 	   		  	  	 	  
/**********************************************************************
 * 函数名称： clean_bss
 * 功能描述： 清除.bss段上的数据
 * 输入参数： start, end
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号        修改人        修改内容
 * -------------------------------------------------
 * 2020/02/20	    V1.0         阿和            创建
 ***********************************************************************/
void clean_bss (void)  /* start, end */
{
	extern __bss_start,__bss_end;
	volatile unsigned int *start = (volatile unsigned int *)&__bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&__bss_end;
	while (start <= end)
	{
		*start++ = 0;
	}
}
		  			 		  						  					  				 	   		  	  	 	  
