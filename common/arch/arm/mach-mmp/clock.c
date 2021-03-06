/*
 *  linux/arch/arm/mach-mmp/clock.c
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/delay.h>

#include <mach/regs-apbc.h>
#include "clock.h"

static void apbc_clk_enable(struct clk *clk)
{
	unsigned long data;

	data = __raw_readl(clk->clk_rst) & ~(APBC_FNCLKSEL(7));
	data |= APBC_FNCLK | APBC_FNCLKSEL(clk->fnclksel);
	__raw_writel(data, clk->clk_rst);
	/*
	 * delay two cycles of the solwest clock between the APB bus clock
	 * and the functional module clock.
	 */
	udelay(10);

	data |= APBC_APBCLK;
	__raw_writel(data, clk->clk_rst);
	udelay(10);

	data &= ~APBC_RST;
	__raw_writel(data, clk->clk_rst);
}

static void apbc_clk_disable(struct clk *clk)
{
	unsigned long data;

	data = __raw_readl(clk->clk_rst) & ~(APBC_FNCLK | APBC_FNCLKSEL(7));
	__raw_writel(data, clk->clk_rst);
	udelay(10);

	data &= ~APBC_APBCLK;
	__raw_writel(data, clk->clk_rst);
}

struct clkops apbc_clk_ops = {
	.enable = apbc_clk_enable,
	.disable = apbc_clk_disable,
};

static void apmu_clk_enable(struct clk *clk)
{
	__raw_writel(clk->enable_val, clk->clk_rst);
}

static void apmu_clk_disable(struct clk *clk)
{
	__raw_writel(0, clk->clk_rst);
}

static int apmu_clk_setrate(struct clk *clk, unsigned long rate)
{
	__raw_writel(rate, clk->clk_rst);
	return 0;
}

struct clkops apmu_clk_ops = {
	.enable = apmu_clk_enable,
	.disable = apmu_clk_disable,
	.setrate = apmu_clk_setrate,
};

static void smc_clk_enable(struct clk *clk)
{
	__raw_writel(0x1f, clk->clk_rst);
}

static void smc_clk_disable(struct clk *clk)
{
	__raw_writel(0, clk->clk_rst);
}

static unsigned long smc_clk_getrate(struct clk *clk)
{
	unsigned long rate = 0;
	unsigned int reg = __raw_readl(clk->clk_rst);
	switch (reg & (~(0x3 << 6))) {
	case 0:
		rate = 31200000;
		break;
	case 1:
		rate = 62400000;
		break;
	case 2:
		rate = 78000000;
		break;
	case 3:
		rate = 104000000;
		break;
	default:
		rate = 0;
	}
	return rate;
}

static int smc_clk_setrate(struct clk *clk, unsigned long rate)
{
	unsigned int reg = 0;
	unsigned int temp = 0;
	switch (rate) {
	case 31200000:
		reg = 0;
		break;
	case 62400000:
		reg = 1;
		break;
	case 78000000:
		reg = 2;
		break;
	case 104000000:
		reg = 3;
		break;
	default:
		return -EINVAL;
	}
	temp = __raw_readl(clk->clk_rst);
	temp &= (~(0x3 << 6));
	temp |= reg;
	__raw_writel(temp, clk->clk_rst);
	return 0;
}

struct clkops smc_clk_ops = {
	.enable = smc_clk_enable,
	.disable = smc_clk_disable,
	.getrate = smc_clk_getrate,
	.setrate = smc_clk_setrate,
};

static DEFINE_SPINLOCK(clocks_lock);

int clk_enable(struct clk *clk)
{
	unsigned long flags;

	spin_lock_irqsave(&clocks_lock, flags);
	if (clk->enabled++ == 0)
		clk->ops->enable(clk);
	spin_unlock_irqrestore(&clocks_lock, flags);
	return 0;
}

EXPORT_SYMBOL(clk_enable);

void clk_disable(struct clk *clk)
{
	unsigned long flags;

	WARN_ON(clk->enabled == 0);

	spin_lock_irqsave(&clocks_lock, flags);
	if (--clk->enabled == 0)
		clk->ops->disable(clk);
	spin_unlock_irqrestore(&clocks_lock, flags);
}

EXPORT_SYMBOL(clk_disable);

unsigned long clk_get_rate(struct clk *clk)
{
	unsigned long rate;

	if (clk->ops->getrate)
		rate = clk->ops->getrate(clk);
	else
		rate = clk->rate;

	return rate;
}

EXPORT_SYMBOL(clk_get_rate);

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	unsigned long flags;
	int ret = -EINVAL;

	if (clk->ops->setrate) {
		spin_lock_irqsave(&clocks_lock, flags);
		ret = clk->ops->setrate(clk, rate);
		spin_unlock_irqrestore(&clocks_lock, flags);
	}

	return ret;
}

EXPORT_SYMBOL(clk_set_rate);
