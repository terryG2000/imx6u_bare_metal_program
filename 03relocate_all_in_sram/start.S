	
.text
.global  _start

_start: 

	/* 设置栈 */
	ldr  sp,=0x80200000


	bl copy_data			 /* 跳转到函数copy_data并将r1,r2,r3作为函数参数传入 */

	bl clean_bss			/* 跳转到函数clean_bss并将r0, r1作为函数参数传入*/

	/* 跳转到主函数 */
	// bl main		/* 相对跳转，程序仍在DDR3内存中执行 */
	ldr pc, =main 	/* 绝对跳转，程序在片内RAM中执行 */

halt:
	b  halt 
