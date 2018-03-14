/****************************************************************************
*  Copyright (c) 2011 by Michael Fischer. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*	are met:
*  
*  1. Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the 
*     documentation and/or other materials provided with the distribution.
*  3. Neither the name of the author nor the names of its contributors may 
*     be used to endorse or promote products derived from this software 
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
*  THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
*  SUCH DAMAGE.

/*
 * To set the entry point
 * If the entry point is not set, other entry points can be -
 * 1. Address of first byte of .text section.
 * 2. Address 0.
 */
/* ENTRY(ResetHandler) */		/* Entry point set as ResetHandler	*/

/*
 * "The MEMORY command describes the location and size of 
 * blocks of memory in the target."
 */
MEMORY
{
   FLASH (rwx) : ORIGIN = 0x00000000, LENGTH = 512K
   RAM1  (rwx) : ORIGIN = 0x10000000, LENGTH = 32K
   RAM2  (rwx) : ORIGIN = 0x2007C000, LENGTH = 32K
}

/*
 * "The SECTIONS command tells the linker how to map input
 * sections into output sections, and how to place the output
 * sections in memory.
 */
SECTIONS
{
   /*
    * The ".text" section is used for the code, and
    * read only (.rodata) data and the vectors (.vectors)
    * is saved at the start of this section.
    */
   .text :
   {
      _stext = .;          /* Label to indicate the start of this section */
      
      CREATE_OBJECT_SYMBOLS
      KEEP(*(.vectors))
      
      *(.text)
      *(.text.*)
            
      . = ALIGN(4);        /* Align the start of the rodata part */
      *(.rodata)
      *(.rodata.*)
	  
      . = ALIGN(4);        /* Align the end of the section */
	} > FLASH = 0
  
    .ARM.extab : 
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

   _etext = .;             /* Label to indicate the end of this section */
   
   /*
    * The ".data" section is used for initialized data
    * and for functions (.fastrun) which should be copied 
    * from flash to ram. This functions will later be
    * executed from ram instead of flash.
    * AT(_etext) defines the load address(LMA) of this section
	* Startup routines will copy this section from FLASH(LMA) to RAM addresses(VMA)
	*/

   .data : AT (_etext)
   {
      . = ALIGN(4);        /* Align the start of the section */
      _sdata = .;          /* Label to indicate the start of this section */
      
      *(.data)
      *(.data.*)
      
      . = ALIGN(4);        /* Align the start of the fastrun part */
      *(.fastrun)
      *(.fastrun.*)
      
      . = ALIGN(4);        /* Align the end of the section */
   } > RAM2
   _edata = .;             /* Label to indicate the end of this section */
   

   /*
    * The ".bss" section is used for uninitialized data.
    * This section will be cleared by the startup code.
    */
   .bss :
   {
      . = ALIGN(4);        /* Align the start of the section */
      _sbss = .;           /* Label to indicate the start of this section */
      
      *(.bss)
      *(.bss.*)
      
      . = ALIGN(4);        /* Align the end of the section */
   } > RAM1
   _ebss = .;              /* Label to indicate the end of this section */
   
	.heap (COPY):		   /* COPY-it describes type of an o/p section.To mark section as non-allocatable. */
	{					   /* memory is not allocated for the section when the program is run. */
		__end__ = .;
		PROVIDE(end = .);  /*PROVIDE keyword is used to define a symbol */
		*(.heap*)
		__HeapLimit = .;
	} > RAM2

   
   /* 
    * The ".stack" section is our stack.
    * Here this section starts at the end of the ram segment.
    */
   _estack = ORIGIN(RAM2) + LENGTH(RAM2);
}