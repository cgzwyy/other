#************************************************************************/
#* SISCO SOFTWARE MODULE HEADER *****************************************/
#************************************************************************/
#*			       
#* MODULE NAME : uca_srvr_l.mak                       
#* PRODUCT(S)  : MMS-EASE-Lite
#*			       
#* MODULE DESCRIPTION :        
#* This makefile is used by the QNX 'make' utility to build the Server
#* example for MMS-EASE-Lite. All paths including header 
#* files and object modules are relative to the current project directory 
#* which makes this file as environment independent as possible.  
#* Usage instructions are given below as well as a brief description of 
#* each switch used in the process.  
#*
#* To make the UOSITCPE_L executable (logging/no debug) enter the following:
#*
#* 	make -f uca_srvr_l.mak
#*
#* Description of QNX compiler options used:
#*
#*  -c     Suppress the link phase and retain object files
#*  -g     Produce symbolic info in the object file for debugger
#*  -Od    Generate non-optimized code sequences
#*  -Wc,-s No stack overflow checking (Watcom compiler)
#*  -w3    Warning level
#*  -j     Change char default from unsigned to signed
#*			       
#* Description of QNX linker options used:
#*  -N stacksize	Reserve stacksize space for stack
#*  -o outfile   	Output file path for executable file
#*  -M			Produce a symbolic map file (defults to .map ext)
#*
#* MODIFICATION LOG :	       
#*  Date     Who  	Comments			
#* --------  ---   -------------------------------------------	
#* 03/13/02  JRB   Chg FOUNDYDIR. Add ALIGNDIR.
#* 02/14/02  GLB   Removed ml_inits.c
#* 02/05/02  GLB   Delete MVL_NUM_CALLED
#* 01/09/02  GLB   Use slog_l instaed of slog_n
#* 12/21/01  GLB   Split from server.mak to build 
#*                  logging/no debug version only
#* 12/11/01  GLB   Removed mvlu_rpt.c                             #
#* 12/06/01  GLB   Removed mbufcalc.cfg & mbufcalc.c (ml_init.c)  #
#*                  added ml_inits.c							  #
#* 08/07/01  RKR   Removed S_THISFILE				 
#* 11/08/00  GLB   Added logcfgx.c to parse logcfg.xml            #
#* 10/26/00  JRB   Add MVL_UCA. Chg to link in mvlud.lib
#* 08/15/00  GLB   Added VPATH macro to work with new "make"
#* 12/03/99  GLB   Print build file name on screen during build
#* 11/15/99  GLB   Added .c.o: 
#* 10/06/99  RKR   Updated with ETHERNET define
#* 08/18/97  EJV   Created from DOS version
#************************************************************************/

#************************************************************************/
# Define directories here

LIBDIR = ../../../lib
OBJDIR = .
INCDIR = ../../../inc
SRCDIR = ../../../src
MMSOPDIR = .
MMSSRCDIR = ../../../src
MVLSRCDIR = ../../src
USRSRCDIR = ../../usr
ACSESRCDIR = ../../src/acse
FOUNDRYDIR = ../../../exe
ALIGNDIR = ../../util/foundry/qnx
EXEDIR = .
VPATH = $(MVLSRCDIR):$(USRSRCDIR):$(ACSESRCDIR):$(SRCDIR)

PROJ  = uositcpe_l
OPT   =
DEFS  =
LIST  = >> cc_l.lst 2>&1

#************************************************************************/
# Define compiler/linker switches to use. These depend on the target ...

CFLAGS = -c -j -w3 -Od $(OPT) -I$(INCDIR) $(DEFS) -DMMS_LITE \
	 -DMOSI -DLEAN_T -I$(MMSOPDIR) -DDEBUG_SISCO \
         -DMVL_UCA \
         -DETHERNET

LIBS = $(LIBDIR)/mvlu_l.lib $(LIBDIR)/mmsl_l.lib $(LIBDIR)/mmsle_l.lib \
       $(LIBDIR)/asn1l_l.lib $(LIBDIR)/mem_l.lib $(LIBDIR)/slog_l.lib \
       $(LIBDIR)/util_l.lib $(LIBDIR)/ositcpe_l.lib 

EXE = $(EXEDIR)/$(PROJ)
LFLAGS = -M -j -o$(EXE) 

#************************************************************************/
# Define includes dependancies

INCLUDES = $(INCDIR)/glbtypes.h \
	$(INCDIR)/sysincs.h \
	$(INCDIR)/mmsdefs.h \
	$(INCDIR)/glberror.h \
	$(INCDIR)/gen_list.h \
	$(INCDIR)/mem_chk.h \
	$(INCDIR)/mms_pvar.h \
	$(INCDIR)/mms_mp.h \
	$(INCDIR)/asn1defs.h \
	$(INCDIR)/slog.h \
	$(INCDIR)/mms_vvar.h \
	$(INCDIR)/mms_err.h \
	$(INCDIR)/mms_def2.h \
	$(INCDIR)/mmsintr2.h \
	$(INCDIR)/mmsldefs.h \
	$(INCDIR)/mms_dfun.h \
	$(INCDIR)/mms_perr.h \
	$(INCDIR)/mms_log.h \
	$(INCDIR)/mmslog.h \
	$(INCDIR)/mms_pcon.h \
	$(INCDIR)/mms_pdom.h \
	$(INCDIR)/mms_pevn.h \
	$(INCDIR)/mms_pfil.h \
	$(INCDIR)/mms_pjou.h \
	$(INCDIR)/mms_pocs.h \
	$(INCDIR)/mms_pprg.h \
	$(INCDIR)/mms_psem.h \
	$(INCDIR)/mms_pvmd.h \
	$(INCDIR)/mmsefun.h \
	$(MMSOPDIR)/mmsop_en.h \
	uca_srvr.h \
	uca_obj.h 

#************************************************************************/
# Define objects used in the exectable

OBJECTS = $(OBJDIR)/uca_srvr.o \
	$(OBJDIR)/rdwrind.o \
	$(OBJDIR)/mmsop_en.o \
	$(OBJDIR)/mvlop_en.o \
	$(OBJDIR)/mvl_acse.o \
	$(OBJDIR)/event.o \
	$(OBJDIR)/log_cfg.o \
	$(OBJDIR)/logcfgx.o \
	$(OBJDIR)/uca_obj.o 

#************************************************************************/
# The main target is the execcutable

$(EXE):	$(OBJECTS) $(LIBS)
	rm -f $(EXE)
	$(CC) $(LFLAGS)\
		$(OBJECTS) \
		$(LIBS) $(LIST)
	@echo "FINISHED GENERATING $(EXE) EXECUTABLE" $(LIST)
	@echo "-----------------------------------------------------" $(LIST)
	rm $(OBJDIR)/*.o

# uca_obj.c (and uca_obj.h) are created using the foundry utility.
uca_obj.c: uca_obj.odf 
	$(FOUNDRYDIR)/foundry -o -c$(ALIGNDIR)/align.cfg -tuca_obj.tfn uca_obj.odf $(LIST)

uca_obj.h: uca_obj.odf 
	$(FOUNDRYDIR)/foundry -o -c$(ALIGNDIR)/align.cfg -tuca_obj.tfn uca_obj.odf $(LIST)

#************************************************************************/
# Here is where we compile the C files into objects

.c.o:
	echo uca_srvr_l.mak: $< $(LIST)
	$(CC) $(CFLAGS) $< $(LIST)

$(OBJDIR)/uca_srvr.o:	uca_srvr.c $(INCLUDES)

$(OBJDIR)/rdwrind.o:	rdwrind.c $(INCLUDES)

$(OBJDIR)/mmsop_en.o:	$(MMSSRCDIR)/mmsop_en.c $(INCLUDES)
	echo uca_srvr_l.mak: $(MMSSRCDIR)/mmsop_en.c $(LIST)
	$(CC) $(CFLAGS) $(MMSSRCDIR)/mmsop_en.c $(LIST) 

$(OBJDIR)/mvlop_en.o:	$(MVLSRCDIR)/mvlop_en.c $(INCLUDES)

$(OBJDIR)/mvl_acse.o:	$(ACSESRCDIR)/mvl_acse.c $(INCLUDES)

$(OBJDIR)/event.o:	$(USRSRCDIR)/event.c $(INCLUDES)

$(OBJDIR)/log_cfg.o:	$(USRSRCDIR)/log_cfg.c $(INCLUDES)

$(OBJDIR)/logcfgx.o:	$(USRSRCDIR)/logcfgx.c $(INCLUDES)

$(OBJDIR)/uca_obj.o:	uca_obj.c $(INCLUDES)