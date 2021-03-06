
#ifndef	_EMS_INIT_DEF_H /*_EMS_INIT_DEF_H*/
#define	_EMS_INIT_DEF_H




//#define	EXTEND_LANGUAGE_SYSTEM

//#define ONLY_USE_EXTEND_LANGUAGE	//EXTEND_LANGUAGE_SYSTEM must be defined first





#define MAX_STR_NUM_IN_LINE		24
#define MAX_CHAR_NUM_IN_LINE	256

#define SYS_RUN_SERV_TCP_PORT	44444

#define	MAX_STATION_NUM				STATION_ENTRY_NUMBER
#define	MAX_HOST_NUM				100
#define	MAX_HOST_NAME_SIZE			10
#define	MAX_HOST_LONGNAME_SIZE		48
#define	MAX_HOST_TYPE_SIZE			16
#define	MAX_HOST_IPADDR_NUM			6
#define	MAX_IPADDR_SIZE				18
#define	MAX_BASE_PROCESS_NUM		16
#define	MAX_PROCESS_NUM				32
#define	MAX_PROCESS_NAME_SIZE		32
#define	MAX_DOMAIN_NAME_SIZE		32
#define	MAX_DOMAIN_NUM				16
#define	MAX_RCP_HOST_NUM			16
#define	MAX_HOST_PAIR_NUM			16
#define	MAX_PORT_NAME_SIZE			24
#define	MAX_GPS_TYPE_NAME_SIZE		16
#define	MAX_TIME_SERVER_NUM			6
#define	MAX_PLCSCAN_HOST_NUM		12
#define	MAX_ALL_LCU_NUM				GROUP_ENTRY_NUMBER
#define	MAX_ROLE_NAME_SIZE			24
#define	MAX_HOST_NUM_IN_ROLE		16
#define	MAX_HOST_ROLE_NUM			16
#define	MAX_PLC_IPADDR_NUM			4
#define	MAX_VARIABLE_NAME_SIZE		24
#define	MAX_VARIABLE_NUM			128
#define	MAX_STRING_NAME_SIZE		24
#define	MAX_STRING_VALUE_SIZE		64
#define	MAX_STRING_NUM				128				
#define	MAX_CMD_HOST_NUM			32
#define	MAX_COMMAND_INFO_SIZE		10240

#define	HOST_STATE_NAME_DEFINE		"_STAT"
#define	SYSNET_STATE_NAME_DEFINE	"_SNET"
#define	CTRLNET_STATE_NAME_DEFINE	"_CNET"
#define	ALM_CBA_SUFFIX_DEFINE		".ALM.CBA"
#define	FALM_CBA_SUFFIX_DEFINE		".FALM.CBA"
#define	AUDALM_CBA_SUFFIX_DEFINE	".AALM.CBA"
#define	QALM_CBA_SUFFIX_DEFINE	    ".QALM.CBA"
#define	OALM_CBA_SUFFIX_DEFINE	    ".OALM.CBA"

#define	ALM_DCBA_SUFFIX_DEFINE		".ALM.DCBA"
#define	FALM_DCBA_SUFFIX_DEFINE		".FALM.DCBA"
#define	AUDALM_DCBA_SUFFIX_DEFINE	".AALM.DCBA"
#define	QALM_DCBA_SUFFIX_DEFINE	    ".QALM.DCBA"
#define	OALM_DCBA_SUFFIX_DEFINE	    ".OALM.DCBA"

#define	ALM_GCBA_SUFFIX_DEFINE		".ALM.GCBA"
#define	FALM_GCBA_SUFFIX_DEFINE		".FALM.GCBA"
#define	AUDALM_GCBA_SUFFIX_DEFINE	".AALM.GCBA"
#define	QALM_GCBA_SUFFIX_DEFINE	    ".QALM.GCBA"
#define	OALM_GCBA_SUFFIX_DEFINE	    ".OALM.GCBA" 

#define   DATABASE_DEFINE_PATH_UNIX	"/home/ems/h9000/gen/"
#define   DATABASE_OUT_PATH_UNIX	"/home/ems/h9000/dat/"
#define   ERROR_LOG_PATH_UNIX		"/home/ems/h9000/his/trap/"
#define   SYS_DEFINE_PATH_UNIX		"/home/ems/h9000/def/"
#define   EVENT_LOG_PATH_UNIX		"/home/ems/h9000/his/event/"
#define   EVENT_TEXT_LOG_PATH_UNIX	"/home/ems/h9000/his/eventtxt/"
#define   SYS_TMP_PATH_UNIX			"/home/ems/h9000/tmp/"
#define	  SYS_RUN_PATH_UNIX			"/home/ems/h9000/bin/"
#define	  OIX_DSP_PATH_UNIX			"/home/ems/h9000/dsp/"
#define	  OIX_PIC_PATH_UNIX			"/home/ems/h9000/dsp/pic/"
#define	  RPT_DATA_PATH_UNIX		"/home/ems/h9000/his/rpt/"
#define	  AGC_LOG_PATH_UNIX			"/home/ems/h9000/his/agc/"
#define	  AUD_FILE_PATH_UNIX		"/home/ems/h9000/wav/"
#define	  SGZY_LOG_PATH_UNIX		"/home/ems/h9000/his/sgzy/"
#define	  CURVE_LOG_PATH_UNIX		"/home/ems/h9000/his/curve/"
#define	  SFTCP_LOG_PATH_UNIX		"/home/ems/h9000/his/sftcp/"
#define	  AUTOCHECK_LOG_PATH_UNIX		"/home/ems/h9000/his/oix/"

#define   DATABASE_DEFINE_PATH_WIN	"\\home\\ems\\h9000\\gen\\"
#define   DATABASE_OUT_PATH_WIN		"\\home\\ems\\h9000\\dat\\"
#define   ERROR_LOG_PATH_WIN		"\\home\\ems\\h9000\\his\\trap\\"
#define   SYS_DEFINE_PATH_WIN		"\\home\\ems\\h9000\\def\\"
#define   EVENT_LOG_PATH_WIN		"\\home\\ems\\h9000\\his\\event\\"
#define   EVENT_TEXT_LOG_PATH_WIN	"\\home\\ems\\h9000\\his\\eventtxt\\"
#define   SYS_TMP_PATH_WIN			"\\home\\ems\\h9000\\tmp\\"
#define	  SYS_RUN_PATH_WIN			"\\home\\ems\\h9000\\bin\\"
#define	  OIX_DSP_PATH_WIN			"\\home\\ems\\h9000\\dsp\\"
#define	  OIX_PIC_PATH_WIN			"\\home\\ems\\h9000\\dsp\\pic\\"
#define	  RPT_DATA_PATH_WIN			"\\home\\ems\\h9000\\his\\rpt\\"
#define	  AGC_LOG_PATH_WIN			"\\home\\ems\\h9000\\his\\agc\\"
#define	  AUD_FILE_PATH_WIN			"\\home\\ems\\h9000\\wav\\"
#define	  SGZY_LOG_PATH_WIN			"\\home\\ems\\h9000\\his\\sgzy\\"
#define	  CURVE_LOG_PATH_WIN		"\\home\\ems\\h9000\\his\\curve\\"
#define	  SFTCP_LOG_PATH_WIN		"\\home\\ems\\h9000\\his\\sftcp\\"
#define	  AUTOCHECK_LOG_PATH_WIN		"\\home\\ems\\h9000\\his\\oix\\"


#ifdef		WINDOWS_OS
#define   DATABASE_DEFINE_PATH		DATABASE_DEFINE_PATH_WIN	
#define   DATABASE_OUT_PATH			DATABASE_OUT_PATH_WIN		
#define   ERROR_LOG_PATH			ERROR_LOG_PATH_WIN		
#define   SYS_DEFINE_PATH			SYS_DEFINE_PATH_WIN		
#define   EVENT_LOG_PATH			EVENT_LOG_PATH_WIN		
#define   EVENT_TEXT_LOG_PATH		EVENT_TEXT_LOG_PATH_WIN		
#define   SYS_TMP_PATH				SYS_TMP_PATH_WIN			
#define	  SYS_RUN_PATH				SYS_RUN_PATH_WIN			
#define	  OIX_DSP_PATH				OIX_DSP_PATH_WIN			
#define	  OIX_PIC_PATH				OIX_PIC_PATH_WIN			
#define	  AGC_LOG_PATH				AGC_LOG_PATH_WIN			
#define	  AUD_FILE_PATH				AUD_FILE_PATH_WIN			
#define	  SGZY_LOG_PATH				SGZY_LOG_PATH_WIN			
#define	  CURVE_LOG_PATH			CURVE_LOG_PATH_WIN			
#define	  SFTCP_LOG_PATH			SFTCP_LOG_PATH_WIN			
#define	  RPT_DATA_PATH				RPT_DATA_PATH_WIN
#define   AUTOCHECK_LOG_PATH	AUTOCHECK_LOG_PATH_WIN			
#else /*UNIX*/
#define   DATABASE_DEFINE_PATH		DATABASE_DEFINE_PATH_UNIX	
#define   DATABASE_OUT_PATH			DATABASE_OUT_PATH_UNIX	
#define   ERROR_LOG_PATH			ERROR_LOG_PATH_UNIX		
#define   SYS_DEFINE_PATH			SYS_DEFINE_PATH_UNIX		
#define   EVENT_LOG_PATH			EVENT_LOG_PATH_UNIX		
#define   EVENT_TEXT_LOG_PATH		EVENT_TEXT_LOG_PATH_UNIX		
#define   SYS_TMP_PATH				SYS_TMP_PATH_UNIX			
#define	  SYS_RUN_PATH				SYS_RUN_PATH_UNIX			
#define	  OIX_DSP_PATH				OIX_DSP_PATH_UNIX			
#define	  OIX_PIC_PATH				OIX_PIC_PATH_UNIX			
#define	  AGC_LOG_PATH				AGC_LOG_PATH_UNIX			
#define	  AUD_FILE_PATH				AUD_FILE_PATH_UNIX			
#define	  SGZY_LOG_PATH				SGZY_LOG_PATH_UNIX			
#define	  CURVE_LOG_PATH			CURVE_LOG_PATH_UNIX			
#define	  SFTCP_LOG_PATH			SFTCP_LOG_PATH_UNIX			
#define	  RPT_DATA_PATH				RPT_DATA_PATH_UNIX	
#define   AUTOCHECK_LOG_PATH	AUTOCHECK_LOG_PATH_UNIX			
		
#endif

#define	  SYS_DATA_PATH				DATABASE_OUT_PATH

#define   DATABASE_NAME				"DATABASE.OUT"
#define   DATABASE_NEW				"DATABASE.NEW"
#define   DMS_ERROR_FILE			"dmserror.rec"
#define   STATION_DEF_FILE			"DBSTATION.DEF"
#define   GROUP_DEF_FILE			"DATABASE.DEF"
#define   IOGROUP_DEF_FILE			"DBIOGROUP.DEF"
#define	  RECORD_DEF_FILE			"DATABASE.GEN"
#define	  MSG_DEF_FILE				"MSG_DEF.DEF"
#define	  CMD_MSG_FILE				"CMD_MSG.DEF"
#define	  SYS_DEFINE_FILE			"ems_config.def"
#define	  LMS_DEFINE_FILE			"lms_define.def"
#define	  EMS_RUN_TIME_FILE			"ems_run_time"
#define	  CALCU_FILE_DEF			"CalcuFile.def"
#define	  CALCU_DATA_FILE			"CalcuGen.dat"
#define	  CALCU1_FILE_DEF			"CalcuFile1.def"
#define	  CALCU1_DATA_FILE			"Calcu1Gen.dat"
#define	  INTERLOCK_FILE_DEF		"InterLockFile.def"
#define	  INTERLOCK_DATA_FILE		"InterLockGen.dat"
#define	  RELATEPOINT_FILE_DEF		"RelatePointFile.def"
#define	  RELATEPOINT_DATA_FILE		"RelatePointGen.dat"
#define	  WATER_REVERT_DEFINE_FILE	"water_revert.def"
#define	  PDC_PERIOD_DEFINE_FILE	"pdcperiod.def"
#define	  TEMP_ENG_DEFINE_FILE		"temp_eigenvalue.def"
#define	  DOWNLOAD_ANA_DEFINE_FILE	"download_ana.def"
#define	  DOWNLOAD_ANA_SCALE_DEFINE_FILE	"download_ana_scale.def"
#define	  DOWNLOAD_IND_DEFINE_FILE	"download_ind.def"
#define	  CURVE_DATA_FILE			"curvefile.dat"
#define	  PRIVILEGE_DATABASE_FILE	"priority_database.dat" 
#define	  AGC_LOG_FILE				"AGCcmd" 
#define	  AVC_LOG_FILE				"AVCcmd" 
#define	  PRJ_DEFINE_FILE			"prj_aud.def"
#define	  COM_DEFINE_FILE			"com_aud.def"
#define	  SGZY_DATA_FILE			"sgzyfile.dat"
#define	  WDQS_DATA_FILE			"wdqsfile.dat"
#define	  EVENT_SEARCH_TMP_FILE		"search_rec_file.rec"
#define	  STR_TEXT_DEFINE_FILE		"str_text_list.def"
#define	  STR_TEXT_DATA_FILE		"strTextFile.dat"
#define	  OBJ_CALC_DEFINE_FILE		"obj_calc.def"
#define   AUDALM_STATION_DEFINE_FILE  "audalm_station_define_file.def"//cxs











#endif   /*_EMS_INIT_DEF_H*/


