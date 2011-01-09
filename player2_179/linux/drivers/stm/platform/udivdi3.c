/*
 * Simple __udivdi3 function which doesn't use FPU.
 */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#ifdef __TDT__
#include <linux/version.h>
#endif

extern u64 __xdiv64_32(u64 n, u32 d);

u64 __udivdi3(u64 n, u64 d)
{
	if (unlikely(d & 0xffffffff00000000ULL))
		panic("Need true 64-bit/64-bit division");
	return __xdiv64_32(n, (u32)d);
}

#if defined(__TDT__) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 30))
EXPORT_SYMBOL(__udivdi3);
#else
#if defined (CONFIG_KERNELVERSION) /* STLinux 2.3 or later */
EXPORT_SYMBOL(__udivdi3);
#endif
#endif
