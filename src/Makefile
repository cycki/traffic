#
# OMNeT++/OMNEST Makefile for traffic
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = traffic$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -IAdmissionControl \
    -IGenerator \
    -INetPacket \
    -IProfiler \
    -IProfiler/results \
    -IReceiver \
    -IScheudler \
    -IScheudler/results

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/AdmissionControl/AbstractAdmissionControl.o \
    $O/AdmissionControl/MAvgAdmissionControl.o \
    $O/AdmissionControl/PriorityAdmissionControl.o \
    $O/AdmissionControl/SessionAdmissionControl.o \
    $O/AdmissionControl/SourceAdmissionControl.o \
    $O/Generator/AbstractGenerator.o \
    $O/Generator/ExponentialGenerator.o \
    $O/Generator/MMPPGenerator.o \
    $O/Generator/OnOffGenerator.o \
    $O/Generator/PoissonGenerator.o \
    $O/Profiler/AbstractProfiler.o \
    $O/Profiler/JitterControl.o \
    $O/Profiler/LeakyBucket.o \
    $O/Profiler/LoadShedding.o \
    $O/Profiler/TokenBucket.o \
    $O/Receiver/Receiver.o \
    $O/Scheudler/AbstractScheduler.o \
    $O/Scheudler/FIFO.o \
    $O/Scheudler/LIFO.o \
    $O/Scheudler/PriorityScheduler.o \
    $O/Scheudler/RRScheduler.o \
    $O/Scheudler/SJFScheduler.o \
    $O/NetPacket/NetPacket_m.o

# Message files
MSGFILES = \
    NetPacket/NetPacket.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f traffic traffic.exe libtraffic.so libtraffic.a libtraffic.dll libtraffic.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f AdmissionControl/*_m.cc AdmissionControl/*_m.h
	$(Q)-rm -f Generator/*_m.cc Generator/*_m.h
	$(Q)-rm -f NetPacket/*_m.cc NetPacket/*_m.h
	$(Q)-rm -f Profiler/*_m.cc Profiler/*_m.h
	$(Q)-rm -f Profiler/results/*_m.cc Profiler/results/*_m.h
	$(Q)-rm -f Receiver/*_m.cc Receiver/*_m.h
	$(Q)-rm -f Scheudler/*_m.cc Scheudler/*_m.h
	$(Q)-rm -f Scheudler/results/*_m.cc Scheudler/results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc AdmissionControl/*.cc Generator/*.cc NetPacket/*.cc Profiler/*.cc Profiler/results/*.cc Receiver/*.cc Scheudler/*.cc Scheudler/results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/AdmissionControl/AbstractAdmissionControl.o: AdmissionControl/AbstractAdmissionControl.cc \
	AdmissionControl/AbstractAdmissionControl.h \
	NetPacket/NetPacket_m.h
$O/AdmissionControl/MAvgAdmissionControl.o: AdmissionControl/MAvgAdmissionControl.cc \
	AdmissionControl/AbstractAdmissionControl.h \
	AdmissionControl/MAvgAdmissionControl.h \
	NetPacket/NetPacket_m.h
$O/AdmissionControl/PriorityAdmissionControl.o: AdmissionControl/PriorityAdmissionControl.cc \
	AdmissionControl/AbstractAdmissionControl.h \
	AdmissionControl/PriorityAdmissionControl.h \
	NetPacket/NetPacket_m.h
$O/AdmissionControl/SessionAdmissionControl.o: AdmissionControl/SessionAdmissionControl.cc \
	AdmissionControl/AbstractAdmissionControl.h \
	AdmissionControl/SessionAdmissionControl.h \
	NetPacket/NetPacket_m.h
$O/AdmissionControl/SourceAdmissionControl.o: AdmissionControl/SourceAdmissionControl.cc \
	AdmissionControl/AbstractAdmissionControl.h \
	AdmissionControl/SourceAdmissionControl.h \
	NetPacket/NetPacket_m.h
$O/Generator/AbstractGenerator.o: Generator/AbstractGenerator.cc \
	Generator/AbstractGenerator.h \
	NetPacket/NetPacket_m.h
$O/Generator/ExponentialGenerator.o: Generator/ExponentialGenerator.cc \
	Generator/AbstractGenerator.h \
	Generator/ExponentialGenerator.h \
	NetPacket/NetPacket_m.h
$O/Generator/MMPPGenerator.o: Generator/MMPPGenerator.cc \
	Generator/AbstractGenerator.h \
	Generator/MMPPGenerator.h \
	NetPacket/NetPacket_m.h
$O/Generator/OnOffGenerator.o: Generator/OnOffGenerator.cc \
	Generator/AbstractGenerator.h \
	Generator/OnOffGenerator.h \
	NetPacket/NetPacket_m.h
$O/Generator/PoissonGenerator.o: Generator/PoissonGenerator.cc \
	Generator/AbstractGenerator.h \
	Generator/PoissonGenerator.h \
	NetPacket/NetPacket_m.h
$O/NetPacket/NetPacket_m.o: NetPacket/NetPacket_m.cc \
	NetPacket/NetPacket_m.h
$O/Profiler/AbstractProfiler.o: Profiler/AbstractProfiler.cc \
	NetPacket/NetPacket_m.h \
	Profiler/AbstractProfiler.h
$O/Profiler/JitterControl.o: Profiler/JitterControl.cc \
	NetPacket/NetPacket_m.h \
	Profiler/AbstractProfiler.h \
	Profiler/JitterControl.h
$O/Profiler/LeakyBucket.o: Profiler/LeakyBucket.cc \
	NetPacket/NetPacket_m.h \
	Profiler/AbstractProfiler.h \
	Profiler/LeakyBucket.h
$O/Profiler/LoadShedding.o: Profiler/LoadShedding.cc \
	NetPacket/NetPacket_m.h \
	Profiler/AbstractProfiler.h \
	Profiler/LoadShedding.h
$O/Profiler/TokenBucket.o: Profiler/TokenBucket.cc \
	NetPacket/NetPacket_m.h \
	Profiler/AbstractProfiler.h \
	Profiler/TokenBucket.h
$O/Receiver/Receiver.o: Receiver/Receiver.cc \
	NetPacket/NetPacket_m.h
$O/Scheudler/AbstractScheduler.o: Scheudler/AbstractScheduler.cc \
	NetPacket/NetPacket_m.h \
	Scheudler/AbstractScheduler.h
$O/Scheudler/FIFO.o: Scheudler/FIFO.cc \
	NetPacket/NetPacket_m.h \
	Scheudler/AbstractScheduler.h \
	Scheudler/FIFO.h
$O/Scheudler/LIFO.o: Scheudler/LIFO.cc \
	NetPacket/NetPacket_m.h \
	Scheudler/AbstractScheduler.h \
	Scheudler/LIFO.h
$O/Scheudler/PriorityScheduler.o: Scheudler/PriorityScheduler.cc \
	NetPacket/NetPacket_m.h \
	Scheudler/AbstractScheduler.h \
	Scheudler/PriorityScheduler.h
$O/Scheudler/RRScheduler.o: Scheudler/RRScheduler.cc \
	NetPacket/NetPacket_m.h \
	Scheudler/AbstractScheduler.h \
	Scheudler/RRScheduler.h
$O/Scheudler/SJFScheduler.o: Scheudler/SJFScheduler.cc \
	NetPacket/NetPacket_m.h \
	Scheudler/AbstractScheduler.h \
	Scheudler/SJFScheduler.h

