#ifndef     _DMS_READWRITE_H
#define     _DMS_READWRITE_H


//#include	"./os_type_def.h" //del by hcl 20100817
//#include	"./dms_com.h"	//del by hcl 20100817


#ifdef __cplusplus
extern "C"{
#endif 


/*dms util functions*/
int	FindLastPrimeNumber(int num);
void GetNameStrHash(char *namestr, GULONG *hash);
int	PointNametoStr(POINT_NAME *point_name, char *str);
int	StrtoPointName(char *str, POINT_NAME *point_name);
int	GetPtIdFromStr(char *str, POINTER *point);
int	GetStringsFromStr ( char *bufptr, int strbuf_num, char strbuf[][MAX_CHAR_NUM_IN_LINE]);

/*link or unlink database*/
int	MountDB(char *db_filename);
int	UnMountDB(void);
int	MountDBFile(char *filename, BOOL loadConfigFile);
void*	MountFile(char *filename, GULONG mount_size);
int	UnMountFile(void* mount_ptr, GULONG mount_size);

int	InterLockFileLoad(void);
BOOL InterLock_Judge(char *pt);
void InterLockFree(void);


/*Get database info*/
int GetDBName( char *dbName );
int GetDBLongname( char *dbLongname );
int GetDBVersion( char *dbVersion );
int GetStationNum( GULONG *stn_num );



/*Get database station info*/
int GetStnNameById( UCHAR stnId, char *stnName );
int GetStnLongnameById( UCHAR stnId, char *stnLongname );
int GetStnCommentById( UCHAR stnId, char *stnComment );
int GetStnIdByName( char *stnName, UCHAR *stnId );
int GetStnTypeById( UCHAR stnId, UCHAR *stnType );
int GetGroupNumById( UCHAR stnId, GULONG *grp_num );
int GetStnSysLcuIdById( UCHAR stnId, UCHAR *sysLcuId );
int GetStnIdByIndex( UCHAR stnIndex, UCHAR *stnId ); //index from 1
int GetStnIndexById( UCHAR stnId, UCHAR *stnIndex ); //index from 1



/*Get database group info*/
int	GetGroupNameById( UCHAR stnId, UCHAR groupId, char *groupName );
int	GetGroupLongnameById( UCHAR stnId, UCHAR groupId, char *groupLongname );
int GetGroupCommentById( UCHAR stnId, UCHAR groupId, char *groupComment );
int GetGroupIdByName( UCHAR stnId, char *groupName, UCHAR *grpId );
int	GetGroupTypeNameById( UCHAR stnId, UCHAR groupId, char *groupTypeName );
int GetRecordNumById( UCHAR stnId, UCHAR groupId, GULONG *rec_num );
int GetGroupSysLcuFlagById( UCHAR stnId, UCHAR groupId, UCHAR *sysLcuFlag );
int GetLcuIoGroupNumById( UCHAR stnId, UCHAR devId, int *ioGroup_num );
int GetLcuIoGroupInfoByIndex( UCHAR stnId, UCHAR devId, int index, IOGROUP_INFO *ioGroupInfo );
int GetLcuIoGroupInfoById( UCHAR stnId, UCHAR devId, UCHAR ioGroup, IOGROUP_INFO *ioGroupInfo );



/*Get database record info*/
int GetRecNameByType( UCHAR recType, char *recName );
int GetRecLongnameByType( UCHAR recType, char *recLongname );
int GetRecTypeByName( char *recName, UCHAR *recType );
int GetEntryNumById( UCHAR stnId, UCHAR groupId, UCHAR recType, GULONG *entry_num );
int GetRecTypeByOffset( UCHAR stnId, UCHAR groupId, UCHAR offset, UCHAR *recType );
int GetEntryNumByRecOffset( UCHAR stnId, UCHAR groupId, UCHAR offset, GULONG *entry_num );



/*Get database entry info*/
int	GetPtIdByNameStr( char *ptNameStr, POINTER *point );
int	ReadEntryById( POINTER *point , DMS_COMMON *common_all);
int	ReadEntryByNameStr( char *ptNameStr, DMS_COMMON *common_all);



/*Get database point info*/
BOOL IsPointExist( POINTER *point );
int GetEntryNameById( POINTER *point, char *entryName );
int GetEntryLongnameById( POINTER *point, char *entryLongname );
int GetPtNameById( POINTER *point, char *ptNameStr, POINT_NAME *pt_name );
int GetPtLongnameById( POINTER *point, char *pointLongname );
int	GetPtCmdMsgSelById( POINTER *point, UCHAR *cmd_sel );
int	GetPtAlmMsgSelById( POINTER *point, UCHAR *alm_sel );
int	GetPtHardAddrById( POINTER *point, HARD_ADDR *hard_addr );
int	GetPtCtrlAddrById( POINTER *point, USHORT *ctrl_addr );
int	GetPtUpdateSrcById( POINTER *point, CHAR *update_src );
int	GetPtIoGroupById( POINTER *point, USHORT *io_group );
int	GetPtDspFileNameById( POINTER *point, char *dsp_filename );
int	GetPtUpdateTimeById( POINTER *point, DATE_TIME *update_time );
int	IsPtValueManSetById( POINTER *point, BOOL *manSet );
int	IsPtValueChanFailById( POINTER *point, BOOL *chanFail);

int GetEntryIdByName( char *entryName, POINTER *point );
int GetEntryLongnameByNameStr( char *ptNameStr, char *entryLongname );
int GetPtLongnameByNameStr( char *ptNameStr, char *pointLongname );
int	GetPtCmdMsgSelByNameStr( char *ptNameStr, UCHAR *cmd_sel );
int	GetPtAlmMsgSelByNameStr( char *ptNameStr, UCHAR *alm_sel );
int	GetPtHardAddrByNameStr( char *ptNameStr, HARD_ADDR *hard_addr );
int	GetPtCtrlAddrByNameStr( char *ptNameStr, USHORT *ctrl_addr );
int	GetPtUpdateSrcByNameStr( char *ptNameStr, CHAR *update_src );
int	GetPtIoGroupByNameStr( char *ptNameStr, USHORT *io_group );
int	GetPtDspFileNameByNameStr( char *ptNameStr, char *dsp_filename );
int	GetPtUpdateTimeByNameStr( char *ptNameStr, DATE_TIME *update_time );
int	IsPtValueManSetByNameStr( char *ptNameStr, BOOL *manSet );
int	IsPtValueChanFailByNameStr( char *ptNameStr, BOOL *chanFail);

int GetPtCmdMsgStrById( POINTER *point, UCHAR cmdType, USHORT cmd_opt, CHAR *str );
int GetPtCmdMsgStrByNameStr( char *ptNameStr, UCHAR cmdType, USHORT cmd_opt, CHAR *str );

int GetPairPtById( POINTER *point, POINTER *pair_pt );
int GetPairPtByNameStr( char *ptNameStr, POINTER *pair_pt );


/*Get point iost functions*/
int	GetPtViewPointById( POINTER *point, USHORT *viewPoint );
int	IsPtScanEnableById( POINTER *point, USHORT *scanEnable );
int	IsPtAlmEnableById( POINTER *point, USHORT *almEnable );
int	IsPtAlmNotAckedById( POINTER *point, USHORT *almNoAck );
int	IsPtCtrlLockedById( POINTER *point, USHORT *ctrlLock );
int	IsPtNoUpdateById( POINTER *point, USHORT *noUpdate );
int	IsPtAlmRepeatById( POINTER *point, USHORT *almRepeat );
int	GetPtTagStateById( POINTER *point, USHORT *tagState );

int	GetPtViewPointByNameStr( char *ptNameStr, USHORT *viewPoint );
int	IsPtScanEnableByNameStr( char *ptNameStr, USHORT *scanEnable );
int	IsPtAlmEnableByNameStr( char *ptNameStr, USHORT *almEnable );
int	IsPtAlmNotAckedByNameStr( char *ptNameStr, USHORT *almNoAck );
int	IsPtCtrlLockedByNameStr( char *ptNameStr, USHORT *ctrlLock );
int	IsPtNoUpdateByNameStr( char *ptNameStr, USHORT *noUpdate );
int	IsPtAlmRepeatByNameStr( char *ptNameStr, USHORT *almRepeat );
int	GetPtTagStateByNameStr( char *ptNameStr, USHORT *tagState );



/*Get point ioattr functions*/
int	GetPtProcTypeById( POINTER *point, USHORT *procType );
int	IsPtAlmCbaById( POINTER *point, BOOL *almCba );
int	IsPtStatisticById( POINTER *point, BOOL *statistic );
int	IsPtFaultById( POINTER *point, BOOL *fault );
int	IsPtFailById( POINTER *point, BOOL *fail );
int	IsPtCtrlById( POINTER *point, BOOL *ctrl );
int	IsPtSoeById( POINTER *point, BOOL *soe );
int	IsPtTrendAlmById( POINTER *point, BOOL *trendAlm );
int	IsPtKeySignalById( POINTER *point, BOOL *keySignal );
int	IsPtFaultRecById( POINTER *point, BOOL *faultRec );
int	IsPtAudAlmById( POINTER *point, BOOL *audAlm );
int	IsPtNormalCloseById( POINTER *point, BOOL *normalClose );
int	IsPtDoublePointById( POINTER *point, BOOL *doublePt );
int	IsPtSysVirtualById( POINTER *point, BOOL *sysVirtual );
int	IsPtLcuVirtualById( POINTER *point, BOOL *lcuVirtual );
int	IsPtCascadeById( POINTER *point, BOOL *cascade );
int	IsPtHdbRecordById( POINTER *point, BOOL *hdbRec );
int	IsPtHdbCurveById( POINTER *point, BOOL *hdbCurve );
int	GetPtIoGroupById( POINTER *point, USHORT *ioGroup );
int	GetPtIoGroupCommentById( POINTER *point, char *ioGroupComment );
int	GetPtIoGroupStatusById( POINTER *point, UINT *ioGroupStatus );
int	IsPtOnAlmById( POINTER *point, BOOL *onAlm );
int	IsPtOffAlmById( POINTER *point, BOOL *onAlm );
int	GetPtNormalStateById( POINTER *point, GULONG *normalState );
int	GetPtHdbPeriodById( POINTER *point, GULONG *hdbPeriod );



int	GetPtProcTypeByNameStr( char *ptNameStr, USHORT *procType );
int	IsPtAlmCbaByNameStr( char *ptNameStr, BOOL *almCba );
int	IsPtStatisticByNameStr( char *ptNameStr, BOOL *statistic );
int	IsPtFaultByNameStr( char *ptNameStr, BOOL *fault );
int	IsPtFailByNameStrd( char *ptNameStr, BOOL *fail );
int	IsPtCtrlByNameStr( char *ptNameStr, BOOL *ctrl );
int	IsPtSoeByNameStr( char *ptNameStr, BOOL *soe );
int	IsPtTrendAlmByNameStr( char *ptNameStr, BOOL *trendAlm );
int	IsPtKeySignalByNameStr( char *ptNameStr, BOOL *keySignal );
int	IsPtFaultRecByNameStr( char *ptNameStr, BOOL *faultRec );
int	IsPtAudAlmByNameStr( char *ptNameStr, BOOL *audAlm );
int	IsPtNormalCloseByNameStr( char *ptNameStr, BOOL *normalClose );
int	IsPtDoublePointByNameStr( char *ptNameStr, BOOL *doublePt );
int	IsPtSysVirtualByNameStr( char *ptNameStr, BOOL *sysVirtual );
int	IsPtLcuVirtualByNameStr( char *ptNameStr, BOOL *lcuVirtual );
int	IsPtCascadeByNameStr( char *ptNameStr, BOOL *cascade );
int	IsPtHdbRecordByNameStr( char *ptNameStr, BOOL *hdbRec );
int	IsPtHdbCurveByNameStr( char *ptNameStr, BOOL *hdbCurve );
int	GetPtIoGroupByNameStr( char *ptNameStr, USHORT *ioGroup );
int	GetPtIoGroupCommentByNameStr( char *ptNameStr, char *ioGroupComment );
int	GetPtIoGroupStatusByNameStr( char *ptNameStr, UINT *ioGroupStatus );
int	IsPtOnAlmByNameStr( char *ptNameStr, BOOL *onAlm );
int	IsPtOffAlmByNameStr( char *ptNameStr, BOOL *onAlm );
int	GetPtNormalStateByNameStr( char *ptNameStr, GULONG *normalState );
int	GetPtHdbPeriodByNameStr( char *ptNameStr, GULONG *hdbPeriod );



int GetPtDataByStr( char *nameStr, FLOAT *fValue, UINT *chan_fail, POINTER *point );


/*Get analog or calculate point functions*/
int	GetAnaPtValueById( POINTER *point, ANLG_DATA *value );
int	GetAnaPtfValueById( POINTER *point, FLOAT *fValue );
int	GetAnaPtLmtStateById( POINTER *point, USHORT *lmtState );
int	GetAnaPtTrendStateById( POINTER *point, USHORT *trendState );
int	GetAnaPtUnitNameById( POINTER *point, char *unitName );
int	GetAnaPtEngLmtParaById( POINTER *point, ANA_ENG_PARA *eng_para, LMT_PARA *lmt_para );
int	GetAnaPtCtrlblockStateById( POINTER *point, USHORT *ctrlBlock );

int	GetAnaPtValueByNameStr( char *ptNameStr, ANLG_DATA *value );
int	GetAnaPtfValueByNameStr( char *ptNameStr, FLOAT *fValue );
int	GetAnaPtLmtStateByNameStr( char *ptNameStr, USHORT *lmtState );
int	GetAnaPtTrendStateByNameStr( char *ptNameStr, USHORT *trendState );
int	GetAnaPtUnitNameByNameStr( char *ptNameStr, char *unitName );
int	GetAnaPtEngLmtParaByNameStr( char *ptNameStr, ANA_ENG_PARA *eng_para, LMT_PARA *lmt_para );
int	GetAnaPtCtrlBlockStateByNameStr( char *ptNameStr, USHORT *ctrlBlock );




/*Get impulse point functions*/
int	GetImpPtRtValueById( POINTER *point, GULONG *rt_value );
int	GetImpPtBaseValueById( POINTER *point, GLONG *base_value );
int	GetImpPtDaccumById( POINTER *point, FLOAT *d_accum );
int	GetImpPtEngParaById( POINTER *point, IMP_ENG_PARA *eng_para );
int	GetImpPtDataById( POINTER *point, enum RD_IMP_DATA_OPT opt, IMP_DATA *imp_data );
int	GetImpPtFloatDataById( POINTER *point, enum RD_IMP_DATA_OPT opt, IMP_FLOAT_DATA *imp_fdata );
int	GetImpPtStatisticUnitNameById( POINTER *point, enum IMP_STATISTIC_TYPE type, char *unitName );

int	GetImpPtRtValueByNameStr( char *ptNameStr, GULONG *rt_value );
int	GetImpPtBaseValueByNameStr( char *ptNameStr, GLONG *base_value );
int	GetImpPtDaccumByNameStr( char *ptNameStr, FLOAT *d_accum );
int	GetImpPtEngParaByNameStr( char *ptNameStr, IMP_ENG_PARA *eng_para );
int	GetImpPtDataByNameStr( char *ptNameStr, enum RD_IMP_DATA_OPT opt, IMP_DATA *imp_data );
int	GetImpPtFloatDataByNameStr( char *ptNameStr, enum RD_IMP_DATA_OPT opt, IMP_FLOAT_DATA *imp_fdata );
int	GetImpPtStatisticUnitNameByNameStr( char *ptNameStr, enum IMP_STATISTIC_TYPE type, char *unitName );




/*Get indication point functions*/
int GetIndPtStateById( POINTER *point, USHORT *state );
int GetIndPtRtStateById( POINTER *point, USHORT *rt_state );
int GetIndPtChangeTimeById( POINTER *point, DATE_TIME *change_time );
int IsIndPtFaultTagById( POINTER *point, BOOL *fault_tag );
int GetIndPtSTCById( POINTER *point, STC_DATA *stc_data );
int GetIndPtStateStrById( POINTER *point, CHAR *str );
int GetIndPtRtStateStrById( POINTER *point, CHAR *str );
int GetIndPtAlmMsgStrById( POINTER *point, USHORT state, CHAR *str );

int GetIndPtStateByNameStr( char *ptNameStr, USHORT *state );
int GetIndPtRtStateByNameStr( char *ptNameStr, USHORT *rt_state );
int GetIndPtChangeTimeByNameStr( char *ptNameStr, DATE_TIME *change_time );
int IsIndPtFaultTagByNameStr( char *ptNameStr, BOOL *fault_tag );
int GetIndPtSTCByNameStr( char *ptNameStr, STC_DATA *stc_data );
int GetIndPtStateStrByNameStr( char *ptNameStr, CHAR *str );
int GetIndPtRtStateStrByNameStr( char *ptNameStr, CHAR *str );
int GetIndPtAlmMsgStrByNameStr( char *ptNameStr, USHORT state, CHAR *str );




/*Get temp character point functions*/
int GetCharaPtDataById( POINTER *point, CHARA_DATA *chara_data );
int GetCharaStartPtNameById( POINTER *point, char *pt_name );
int GetCharaPtNumById( POINTER *point, UCHAR *pt_num );

int GetCharaPtDataByNameStr( char *ptNameStr, CHARA_DATA *chara_data );
int GetCharaStartPtNameByNameStr( char *ptNameStr, char *pt_name );
int GetCharaPtNumByNameStr( char *ptNameStr, UCHAR *pt_num );


/*Get curve point functions*/
int	GetCurvePtDataById( POINTER *point, CURVE_DATA *curve );
int	GetCurvePtEngParaById( POINTER *point, ANA_ENG_PARA *eng_para );
int	GetCurvePtSegNumById( POINTER *point, USHORT *segNum );
int	GetCurvePtDataByNameStr( char *ptNameStr, CURVE_DATA *curve );
int	GetCurvePtEngParaByNameStr( char *ptNameStr, ANA_ENG_PARA *eng_para );
int	GetCurvePtSegNumByNameStr( char *ptNameStr, USHORT *segNum );


/*Get devobj point functions*/
int	GetObjPtStateById( POINTER *point, USHORT *state );
int	GetObjPtStateByNameStr( char *ptNameStr, USHORT *state );
int	GetObjPtCmdTimeById( POINTER *point, DATE_TIME *cmd_time );
int	GetObjPtCmdTimeByNameStr( char *ptNameStr, DATE_TIME *cmd_time );
int	GetObjPtUsrNameById( POINTER *point, char *usr_name );
int	GetObjPtUsrNameByNameStr( char *ptNameStr, char *usr_name );
int	GetObjPtHostIdById( POINTER *point, UCHAR *host_id );
int	GetObjPtHostIdByNameStr( char *ptNameStr, UCHAR *host_id );
int	GetObjPtCmdStatusById( POINTER *point, COMMAND_STATUS *cmd_status );
int	GetObjPtCmdStatusByNameStr( char *ptNameStr, COMMAND_STATUS *cmd_status );
int	GetObjPtCmdDataById( POINTER *point, COMMAND_STATUS *cmd_data );
int	GetObjPtCmdDataByNameStr( char *ptNameStr, COMMAND_STATUS *cmd_data );
int	GetObjPtFbStatus1ById( POINTER *point, FB_STATUS1 *fb_status1 );
int	GetObjPtFbStatus1ByNameStr( char *ptNameStr, FB_STATUS1 *fb_status1 );
int	GetObjPtFbStatus2ById( POINTER *point, FB_STATUS2 *fb_status2 );
int	GetObjPtFbStatus2ByNameStr( char *ptNameStr, FB_STATUS2 *fb_status2 );
int	GetObjPtCmdParamById( POINTER *point, USHORT *cmd_param );
int	GetObjPtCmdParamByNameStr( char *ptNameStr, USHORT *cmd_param );


/*Get time point functions*/
int	GetTimePtSecValueById( POINTER *point, GULONG *second );
int	GetTimePtSecValueByNameStr( char *ptNameStr, GULONG *second );
int	GetTimePtMsValueById( POINTER *point, USHORT *ms );
int	GetTimePtMsValueByNameStr( char *ptNameStr, USHORT *ms );
int	GetTimePtStatusById( POINTER *point, COMMAND_STATUS *status );
int	GetTimePtStatusByNameStr( char *ptNameStr, COMMAND_STATUS *status );
int	GetTimePtUsrNameById( POINTER *point, char *usr_name );
int	GetTimePtUsrNameByNameStr( char *ptNameStr, char *usr_name );
int	GetTimePtHostIdById( POINTER *point, UCHAR *host_id );
int	GetTimePtHostIdByNameStr( char *ptNameStr, UCHAR *host_id );
int	GetTimePtUpdateTimeById( POINTER *point, DATE_TIME *update_time );
int	GetTimePtUpdateTimeByNameStr( char *ptNameStr, DATE_TIME *update_time );
int	GetTimePtCoordinateById( POINTER *point, TIME_PT_COORDS *coordinate );
int	GetTimePtCoordinateByNameStr( char *ptNameStr, TIME_PT_COORDS *coordinate );



/*Set point functions*/
int	SetPtValueIostById( POINTER *point, WR_VAR_UNION new_value, 
				IOST iost, DATE_TIME update_time, enum RW_FLAG rw_flag );
int	SetPtIoattrById( POINTER *point, IOATTR ioattr, enum RW_IOATTR_FLAG rw_flag );
int	SetImpPtVarById( POINTER *point , ENTRY_IMP_VAL imp_var);
int	SetCharaPtDataById( POINTER *point, CHARA_DATA chara_data, DATE_TIME update_time);
int	SetAnaPtfValueById( POINTER *point, FLOAT value, DATE_TIME time );
int	SetAnaPtEngLmtParaById( POINTER *point, FLOAT data, enum RW_ENG_LMT_OPT opt );
int	SetIndPtStcById( POINTER *point, USHORT data, enum RW_STC_OPT opt );


int	SetPtValueIostByNameStr( char *ptNameStr, WR_VAR_UNION value, 
				IOST iost, DATE_TIME update_time, enum RW_FLAG rw_flag );
int	SetPtIoattrByNameStr( char *ptNameStr, IOATTR ioattr, enum RW_IOATTR_FLAG rw_flag );
int	SetImpPtVarByNameStr( char *ptNameStr, ENTRY_IMP_VAL imp_var);
int	SetCharaPtDataByNameStr( char *ptNameStr, CHARA_DATA chara_data, DATE_TIME update_time);
int	SetAnaPtfValueByNameStr( char *ptNameStr, FLOAT value, DATE_TIME time );
int	SetAnaPtEngLmtParaByNameStr( char *ptNameStr, FLOAT data, enum RW_ENG_LMT_OPT opt );
int	SetIndPtStcByNameStr( char *ptNameStr, USHORT data, enum RW_STC_OPT opt );

int	SetIndPtAlmMsgSelById( POINTER *point, UCHAR sel );
int	SetIndPtAlmMsgSelByNameStr( char *ptNameStr, UCHAR sel );
int	SetPtCmdMsgSelById( POINTER *point, UCHAR sel );
int	SetPtCmdMsgSelByNameStr( char *ptNameStr, UCHAR sel );
int	SetPtCtrlAddrById( POINTER *point, USHORT addr );
int	SetPtCtrlAddrByNameStr( char *ptNameStr, USHORT addr );
int	SetPtIoGroupById( POINTER *point, USHORT io_group );
int	SetPtIoGroupByNameStr( char *ptNameStr, USHORT io_group );

int SetCurvePtDataById( POINTER *point, FLOAT data[], USHORT seg_offset, 
					   USHORT seg_num, DATE_TIME time );
int SetCurvePtDataByNameStr( char *ptNameStr, FLOAT data[], USHORT seg_offset, 
					   USHORT seg_num, DATE_TIME time );
int	SetCurvePtEngParaById( POINTER *point, FLOAT data, enum RW_ENG_LMT_OPT opt );
int	SetCurvePtEngParaByNameStr( char *ptNameStr, FLOAT data, enum RW_ENG_LMT_OPT opt );

int SetPairPtById( POINTER *point, POINTER pair_pt );
int SetPairPtByNameStr( char *ptNameStr, POINTER pair_pt );

int SetDevObjPtVarById( POINTER *point, ENTRY_DEVOBJ_VAL devobj_var );
int	SetDevObjPtVarByNameStr( char *ptNameStr, ENTRY_DEVOBJ_VAL devobj_var );

int SetTimePtVarById( POINTER *point, ENTRY_TIME_VAL time_var );
int	SetTimePtVarByNameStr( char *ptNameStr, ENTRY_TIME_VAL time_var );

int SetLcuIoGroupStatusById( UCHAR stnId, UCHAR devId, UCHAR ioGroup, UINT ioGroupStatus );

/*load and get ems define*/
int	LoadEmsDefine(char *filename);
int GetSysHostNum(void);
int	GetHostStnId(char *hostname, UCHAR *stn_id);
int	GetHostId(char *hostname, UCHAR	*host_id);
int	GetHostType(char *hostname, char *type);
int	GetHostDomain(char *hostname, char *domain);
int	GetHostDisk(char *hostname, char *disk);
int	GetLocalHostStnId(UCHAR *stn_id);
int	GetLocalHostId(UCHAR	*host_id);
int	GetHostNameById(int host_id, char *hostname);
int	GetBroadcastIpaddr(int netNo, char *ipaddr);
int	GetHostIpaddrNum(char *hostname, int *ipaddrNum);
int	GetHostIpaddr(char *hostname, int netNo, char *ipaddr);
int GetLocalHostPrvg(char *prvg, BOOL *own);
BOOL IsServerStation(void);
BOOL IsOperatorStation(void);
int	GetAlmPrinterNum(void);
int	GetAlmPrinter(int printerNo, char *printer);
int	GetHcopyPrinterNum(void);
int	GetHcopyPrinter(int printerNo, char *printer);
int	GetRptPrinterNum(void);
int	GetRptPrinter(int printerNo, char *printer);
int	GetRunProcessNum(void);
int	GetRunProcess(int procNo, char *process);
int	GetRcpHostNum(void);
int	GetRcpHostName(int hostNo, char *hostname);
int	GetDhswHostName(char *hostname);
int	GetTimeServerNum(void);
int	GetTimeServer(int hostNo, char *hostname, char *port, char *gps_type);
int	GetPlcScanHostNum(UCHAR stn_id, UCHAR dev_id);
int	GetPlcScanHost(UCHAR stn_id, UCHAR dev_id, int hostNo, char *hostname);
int	GetLcuIpaddrNum(UCHAR stn_id, UCHAR dev_id);
int	GetLcuIpaddr(UCHAR stn_id, UCHAR dev_id, int netNo, char *ipaddr);
int	GetPlcMode(UCHAR stn_id, UCHAR dev_id, int	*mode);
int	GetSysNetNum(void);
int	GetCtrlNetNum(void);
BOOL	IsCtrlNetIndepend(void);
BOOL	IsEventFileLog(void);
BOOL	IsPowerAdjLog(void);
BOOL	IsIoForceDisable(void);
BOOL	IsDevObjDisable(void);
BOOL	IsHisRdbDisable(void);
BOOL	IsHostNoHardDisk(void);
BOOL	IsHostIsland(void);
BOOL	IsInfoRecTable(void);

enum DisableTypeFlag
{
	GenPowerPlanCurveDisable,
	OperCharacterCurveDisable,
	DisableTypeEnd
};

BOOL	IsCurveWndDisable(int);
int	GetEmsVariable(char *variable, float *value);
int	GetEmsString(char *strName, char *strValue);
int	GetSystemPassword(BOOL isUnix, char *password);


int	GetSysLcuId(UCHAR stn_id, UCHAR *dev_id);
int	GetHostSysLcuId(char *hostname, UCHAR *dev_id);
int	GetLocalSysLcuId(UCHAR *dev_id);
int	GetHostCmdId(UCHAR host_id, UCHAR *cmd_id);

int GetHostState(char *hostname, USHORT *state);
int GetLocalHostState(USHORT *state);
int GetHostStatePtId(char *hostname, POINTER *point);
int GetHostStatePtNameStr(char *hostname, char *ptNameStr);
int GetHostSysNetState(char *hostname, USHORT net_no, USHORT *state);
int GetHostSysNetStatePtId(char *hostname, USHORT net_no, POINTER *point);
int GetHostSysNetStatePtNameStr(char *hostname, USHORT net_no, char *ptNameStr);
int GetHostCtrlNetState(char *hostname, USHORT net_no, USHORT *state);
int GetHostCtrlNetStatePtId(char *hostname, USHORT net_no, POINTER *point);
int GetHostCtrlNetStatePtNameStr(char *hostname, USHORT net_no, char *ptNameStr);

int	GetDispatchStnName(char *StnName);
BOOL IsLocalHostDispatch(void);
BOOL IsHostStateManage(char *hostname);
int	GetHostLongname(char *hostname, char *longname);
BOOL IsColorPrinter(char *hostname);


#ifdef __cplusplus
}
#endif



#endif   /*_DMS_READWRITE_H*/

