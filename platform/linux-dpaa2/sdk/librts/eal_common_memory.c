/*   Derived from DPDK's eal_common_memory.h
 *   BSD LICENSE
 *
 *   Copyright(c) 2010-2014 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <inttypes.h>

#include <dpaa2_internal.h>
#include <dpaa2_memory.h>
#include <dpaa2_memzone.h>
#include <dpaa2_memconfig.h>
#include <dpaa2_log.h>


#include <dpaa2.h>
#include <dpaa2_common.h>


/*
 * Return a pointer to a read-only table of struct dpaa2_physmem_desc
 * elements, containing the layout of all addressable physical
 * memory. The last element of the table contains a NULL address.
 */
const struct dpaa2_memseg *
dpaa2_eal_get_physmem_layout(void)
{
	return dpaa2_get_mem_config()->memseg;
}


/* get the total size of memory */
uint64_t
dpaa2_eal_get_physmem_size(void)
{
	const struct dpaa2_mem_config *mcfg;
	unsigned i = 0;
	uint64_t total_len = 0;

	/* get pointer to global configuration */
	mcfg = dpaa2_eal_get_configuration()->mem_config;

	for (i = 0; i < DPAA2_MAX_MEMSEG; i++) {
		if (mcfg->memseg[i].addr == NULL)
			break;

		total_len += mcfg->memseg[i].len;
	}

	return total_len;
}

/* Dump the physical memory layout on console */
void
dpaa2_dump_physmem_layout(FILE *f)
{
	const struct dpaa2_mem_config *mcfg;
	unsigned i = 0;

	/* get pointer to global configuration */
	mcfg = dpaa2_eal_get_configuration()->mem_config;

	for (i = 0; i < DPAA2_MAX_MEMSEG; i++) {
		if (mcfg->memseg[i].addr == NULL)
			break;

		fprintf(f, "Segment %u: phys:0x%"PRIx64", len:%zu, "
			"virt:%p, hugepage_sz:%"PRIu64"\n", i,
			mcfg->memseg[i].phys_addr,
			mcfg->memseg[i].len,
			mcfg->memseg[i].addr,
			mcfg->memseg[i].hugepage_sz);
	}
}
