/*******************************************************************************************************************************************************************
FILENAME:	alarm.c

FUNCTION:	
	
	source code of  curvescan module,include:
	(1) connect to history database
	(2) get curve, minute, five,fifteen,hour data from history database
	(3) write data to curve shared memory

VERSION:	v4.0a

OPERATE SYSTEM:	window 2000, Unix

HISTORY:

2006.6.7	create the file for  V4.0		yyp
2008.9.16   update the code for new db structure yyp
******************************************************************************************************************************************************************/
#include "../inc/hdbhead_all.h"
char LoginStr[50];
int AlChgFlag;									
int ClearAlQueryInfo();
int GetAlQueryInfo(struct hdb_al *p_rs);
/***************************************** main function ****************************************************************/
void main(int argc, char *argv[])
{	  
 	struct hdb_al rs_al;			/* variable of data structure hdb_curve */
 	struct tm starttime;
 	struct tm endtime;
 	struct tm lasttime;
 	int	result;
 	int count,waitcount;
 	unsigned char curid=0;
 	int rscount=0;
 	char hostname[20];
	char log_str[256];
	wsa_startup();
	SetLogLevel(argc, argv);
#ifdef SUN
	signal(SIGKILL,sig_termp); 
	signal(SIGTERM,sig_termp);
	signal(SIGINT,sig_termp);
	signal(SIGPIPE,SIG_IGN);
#endif
	gethostname(hostname,20); 	
  	ReadDefFile();
	sprintf(strPwd,"%s/%s@",strUsername,strPassword);
 	strcpy(LoginID,strPwd);
 	strcat(LoginID,SIDSTR);
	strcpy(LoginStr,LoginID);
	if(MountDB(DB_NAME) == -1)
	{
		printf("==== curvescan.c: call MountDB(DATABASE_NAME) error\n");		
		exit(0);
	}
	if(lan_init_all() == FALSE)
	{
		printf("==== curvescan.c: call Lan_init_all() error\n");		
		exit(0);
	}

	if(GetPtConf()==FALSE)	
	{
		printf("\n==== curvescan.c: GetPtConf() error!\n");
		exit(0);
	}
	else
	{
		printf("\n==== GetPtConf() successfully!\n");
	}
	
	if(get_hdb_shm()==FALSE)
	{
		exit(0);
	}
	shm_hdb_addr->data_al.hdb_rec.head.buf_size = MAX_HDB_RECORD_NUM;
	starttime.tm_isdst =-1;
	endtime.tm_isdst =-1;
	lasttime.tm_isdst =-1;	

	/*************** connect hdb *****************/
	for(;;)
	{
		if( ConnectHDB(&lda_al,&cda_al,LoginStr)==FALSE )
		{	
			printf("ConnectHDB() Orcal error !   ( %s )\n",SIDSTR);  
			shm_hdb_addr->connflag_al=2; 
			/* BdSms("alarmscan 连接历史库失败"); */ 
			HdbConn = FALSE;
			MySleep(10000);
			continue; 
		}
		else
		{	
			shm_hdb_addr->connflag_al=1;
			/* BdSms("alarmscan 连接历史库成功"); */
			printf("\n==== Connect '%s' Success \n",SIDSTR); 
			HdbConn=TRUE;
			break;
		}
	}
#ifdef SUN
	signal(SIGINT,sig_termp);
#endif
	count=0;
	
	/******** clear the shm  **********/
	ClearAlQueryInfo();
	
	waitcount = 0;
	/*************** start  looping *****************/
	for(;;)
	{
			MySleep(100);
			AlChgFlag=0;
			/******* if new query, clear the shm *********/
			if(shm_hdb_addr->data_al.queryflag==1)	
			{
				waitcount=0;
				if(GetAlQueryInfo(&rs_al) == FALSE) 
				{
					printf("\n=============== Invalid query info\n");
					ClearAlQueryInfo();
					break;
				}
				StrToTime(rs_al.starttime,&starttime,0,0);
				StrToTime(rs_al.endtime,&endtime,0,0);
				/* shm_hdb_addr->data_al.queryflag=0; */
				shm_hdb_addr->data_al.alnum=0;
			}
			else
			{
				waitcount++;
				if(waitcount>=1000) waitcount = 0;
				if(waitcount==1) printf("\n==== waitting for new alarm query %d ......\n", shm_hdb_addr->connflag_al);
				continue;
			}
		
			/****** select data from hdb ******/		
			sprintf(log_str,"\nStart SelectAlRecFromHdb...!\n");
			log_write(INF,1,log_str);
			result = SelectAlRecFromHdb(cda_al,&rs_al);
			if( result == FALSE )
			{	
				printf("SelectAlRecFromHdb error !\n");
				HdbConn=FALSE;
			}
			else
			{	
				sprintf(log_str,"\nSelectAlRecFromHdb successfully !\n");
				log_write(INF,1,log_str);
				rscount=rs_al.alnum;
				sprintf(log_str,"-- rs return count =  %d --\n",rscount);
				log_write(INF,1,log_str);
			}
			if( shm_hdb_addr->data_al.queryflag==1 )
			{
				shm_hdb_addr->data_al.queryflag = 0;
			}
			if(rscount >= 1)
			{
				/***** Update data to shm *****/
				UpdateAlarmShm(&rs_al);					
			}
			else
			{
				shm_hdb_addr->data_al.hdb_rec.head.header_ptr= 0;
				shm_hdb_addr->data_al.hdb_rec.head.count= 0;				
			}
			MySleep(1000);
			count++;
			/****** reconnect hdb when loop count reach max ******/
			if( count>=MAXLOOPCOUNT || HdbConn!=TRUE )
			{	
				DisconnectHDB(&lda_al,&cda_al);
				MySleep(2000);
				if( ConnectHDB(&lda_al,&cda_al,LoginStr)==FALSE )
				{	
					printf("REConnectHDB() Orcal error !   ( %s )\n",LoginStr);  
					MySleep(60000);
				}
				else
				{	
					printf("\n==== ReConnect '%s' Success \n",LoginStr); 
					HdbConn=TRUE;
				}
				
#ifdef SUN
				signal(SIGINT,sig_termp);
#endif
				count=0;	
			}

	}/* end for(;;) */
		
	if( DisconnectHDB(&lda_al,&cda_al)==FALSE )
	{	printf("DisconnectHDB() Orcal error !\n");  exit(-1); }
	else
	{	printf("\n==== Disconnect '%s' Success \n",LoginStr); }	
	

}

/*********************** get the alarm shm **********************************************/
int GetAlQueryInfo(struct hdb_al *p_rs)
{
	p_rs->queryflag=shm_hdb_addr->data_al.queryflag;
	p_rs->querytype=shm_hdb_addr->data_al.querytype;
	p_rs->lockflag=shm_hdb_addr->data_al.lockflag;
	p_rs->filter_stnid=shm_hdb_addr->data_al.filter_stnid;	
	p_rs->filter_devid=shm_hdb_addr->data_al.filter_devid;	
	p_rs->filter_typeid=shm_hdb_addr->data_al.filter_typeid;
	p_rs->cname_type = shm_hdb_addr->data_al.cname_type;
	strcpy(p_rs->cname,shm_hdb_addr->data_al.cname);	
	strcpy(p_rs->starttime,shm_hdb_addr->data_al.starttime);
	strcpy(p_rs->endtime,shm_hdb_addr->data_al.endtime);
	return TRUE;
}

/*********************** get the alarm shm **********************************************/
int ClearAlQueryInfo()
{
	shm_hdb_addr->data_al.queryflag=0;
	shm_hdb_addr->data_al.alnum=0;
	shm_hdb_addr->data_al.querytype=0;
	shm_hdb_addr->data_al.filter_stnid=0;
	shm_hdb_addr->data_al.filter_devid=0;
	shm_hdb_addr->data_al.filter_typeid=0;
	return TRUE;	
}

/***************** update data got from hdb  to share memories **************************/
int UpdateAlarmShm(struct hdb_al *p_rs)
{
 	unsigned int	i,j;
 	unsigned char curid=0;
 	int rscount=0;
	int year,mon,day,hour,min,sec;
	struct tm starttime,endtime,curtime,almtime;
	POINTER		point;
	int lastptr=0;
	int loopcount=0;
	for(;;)
	{
		if(shm_hdb_addr->data_al.lockflag==0)	
			break;
		MySleep(10);
	}
	if(shm_hdb_addr->data_al.querytype==2)
	{
		StrToTime(shm_hdb_addr->data_revert.starttime,&starttime,0,0);
		StrToTime(shm_hdb_addr->data_revert.endtime,&endtime,0,0);
		curtime=starttime;
		printf("Start to Update alarm shared memeries!\n\n");
	}
	shm_hdb_addr->data_al.lockflag=1;
	shm_hdb_addr->data_al.alnum=p_rs->alnum;
	memcpy(shm_hdb_addr->data_al.rec_data, p_rs->rec_data , p_rs->alnum * sizeof(struct al_rec));
	j= 0;
	i= 0;
	while( i < (unsigned int)p_rs->alnum )
	{
		sscanf(p_rs->rec_data[i].TimeTag,"%d-%d-%d %d:%d:%d",&year,&mon,&day,
	 				&hour,&min,&sec);
		StrToTime(p_rs->rec_data[i].TimeTag,&almtime,0,0);

		if(shm_hdb_addr->data_al.querytype==2)
		{
			if(shm_hdb_addr->data_revert.queryflag == 2)
			{
				break;
			}
			curtime = DateAddSec(starttime,shm_hdb_addr->data_revert.curptr);
			if(mktime( &almtime ) > mktime( &curtime ))
			{
				//printf("\nalmtime=%s, \n curtime=%s\n",asctime(&almtime),asctime(&curtime));
				MySleep(50);
				loopcount++;
				if(loopcount>6000)
				{
					break;
				}
				continue;
			}
			else
			{
				loopcount=0;
			}
		}
		else
		{
			
		}
		if(-1==GetPtIdByNameStr(p_rs->rec_data[i].l_name, &point))
		{
			i++;
			continue;
		}
		
		switch(p_rs->rec_data[i].type_id)
		{
		case	DPS_ANA_ALM:
		case	DPS_IMP_ALM:
			p_rs->hdb_rec.rec[j].ana_rec.rec_sn= i+1;
			p_rs->hdb_rec.rec[j].ana_rec.type_id= p_rs->rec_data[i].type_id;
			p_rs->hdb_rec.rec[j].ana_rec.stn_id= point.stn_id;
			p_rs->hdb_rec.rec[j].ana_rec.dev_id= point.dev_id;
			p_rs->hdb_rec.rec[j].ana_rec.data_type= point.data_type;
			p_rs->hdb_rec.rec[j].ana_rec.pt_id= point.pt_id;
			memcpy(&p_rs->hdb_rec.rec[j].ana_rec.status, &p_rs->rec_data[i].status, 2);
			//modified by yyp 2009.3.26
			p_rs->hdb_rec.rec[j].ana_rec.data= (GULONG)(p_rs->rec_data[i].fvalue);
			p_rs->hdb_rec.rec[j].ana_rec.host_id= 0;
			p_rs->hdb_rec.rec[j].ana_rec.second= sec;
			p_rs->hdb_rec.rec[j].ana_rec.minute= min;
			p_rs->hdb_rec.rec[j].ana_rec.hour= hour;
			p_rs->hdb_rec.rec[j].ana_rec.day= day;
			p_rs->hdb_rec.rec[j].ana_rec.month= mon;
			p_rs->hdb_rec.rec[j].ana_rec.year= year;
			memset(&p_rs->hdb_rec.rec[j].ana_rec.iost, 0, 2);
			shm_hdb_addr->data_al.hdb_rec.rec[j] = p_rs->hdb_rec.rec[j];
			j++;
			break;

		case	DPS_IND_ALM:
			p_rs->hdb_rec.rec[j].ind_rec.rec_sn= i+1;
			p_rs->hdb_rec.rec[j].ind_rec.type_id= p_rs->rec_data[i].type_id;
			p_rs->hdb_rec.rec[j].ind_rec.stn_id= point.stn_id;
			p_rs->hdb_rec.rec[j].ind_rec.dev_id= point.dev_id;
			p_rs->hdb_rec.rec[j].ind_rec.data_type= point.data_type;
			p_rs->hdb_rec.rec[j].ind_rec.pt_id= point.pt_id;
			memcpy(&p_rs->hdb_rec.rec[j].ind_rec.ind_status, &p_rs->rec_data[i].status, 2);
			p_rs->hdb_rec.rec[j].ind_rec.ms= p_rs->rec_data[i].msecond;
			memset(&p_rs->hdb_rec.rec[j].ind_rec.iost, 0, 2);
			p_rs->hdb_rec.rec[j].ind_rec.host_id= 0;
			p_rs->hdb_rec.rec[j].ind_rec.second= sec;
			p_rs->hdb_rec.rec[j].ind_rec.minute= min;
			p_rs->hdb_rec.rec[j].ind_rec.hour= hour;
			p_rs->hdb_rec.rec[j].ind_rec.day= day;
			p_rs->hdb_rec.rec[j].ind_rec.month= mon;
			p_rs->hdb_rec.rec[j].ind_rec.year= year;
			shm_hdb_addr->data_al.hdb_rec.rec[j] = p_rs->hdb_rec.rec[j];
			j++;
			break;

		case	DPS_ANA_PARAM_SET:
		case	DPS_IMP_PARAM_SET:
		case	DPS_C_ONOFF_SET:
			p_rs->hdb_rec.rec[j].param_set_rec.rec_sn= i+1;
			p_rs->hdb_rec.rec[j].param_set_rec.type_id= p_rs->rec_data[i].type_id;
			p_rs->hdb_rec.rec[j].param_set_rec.stn_id= point.stn_id;
			p_rs->hdb_rec.rec[j].param_set_rec.dev_id= point.dev_id;
			p_rs->hdb_rec.rec[j].param_set_rec.data_type= point.data_type;
			p_rs->hdb_rec.rec[j].param_set_rec.pt_id= point.pt_id;
			memcpy(&p_rs->hdb_rec.rec[j].param_set_rec.cmd_status, &p_rs->rec_data[i].status, 2);
			//modified by yyp 2011.12.13
			p_rs->hdb_rec.rec[j].param_set_rec.data_new.iValue= (GULONG)(p_rs->rec_data[i].fvalue);	
			p_rs->hdb_rec.rec[j].param_set_rec.data_old.fValue= 0;
			p_rs->hdb_rec.rec[j].param_set_rec.host_id= 0;
			p_rs->hdb_rec.rec[j].param_set_rec.second= sec;
			p_rs->hdb_rec.rec[j].param_set_rec.minute= min;
			p_rs->hdb_rec.rec[j].param_set_rec.hour= hour;
			p_rs->hdb_rec.rec[j].param_set_rec.day= day;
			p_rs->hdb_rec.rec[j].param_set_rec.month= mon;
			p_rs->hdb_rec.rec[j].param_set_rec.year= year;
			shm_hdb_addr->data_al.hdb_rec.rec[j] = p_rs->hdb_rec.rec[j];
			j++;
			break;

		case	DPS_LMS:
			break;

		case	DPS_SMS:
		case	DPS_SM_ALM:
			break;

		default:/*cmd*/
			p_rs->hdb_rec.rec[j].cmd_rec.rec_sn= i+1;
			p_rs->hdb_rec.rec[j].cmd_rec.type_id= p_rs->rec_data[i].type_id;
			p_rs->hdb_rec.rec[j].cmd_rec.stn_id= point.stn_id;
			p_rs->hdb_rec.rec[j].cmd_rec.dev_id= point.dev_id;
			p_rs->hdb_rec.rec[j].cmd_rec.data_type= point.data_type;
			p_rs->hdb_rec.rec[j].cmd_rec.pt_id= point.pt_id;
			memcpy(&p_rs->hdb_rec.rec[j].cmd_rec.cmd_status, &p_rs->rec_data[i].status, 2);
			//memcpy(&p_rs->hdb_rec.rec[j].cmd_rec.data, &p_rs->rec_data[i].fvalue, 4);
			//modified by yyp 2011.08.10
			p_rs->hdb_rec.rec[j].cmd_rec.data.iValue= (GULONG)(p_rs->rec_data[i].fvalue);			
			p_rs->hdb_rec.rec[j].cmd_rec.ctrl_addr= 0;
			p_rs->hdb_rec.rec[j].cmd_rec.host_id= 0;
			p_rs->hdb_rec.rec[j].cmd_rec.second= sec;
			p_rs->hdb_rec.rec[j].cmd_rec.minute= min;
			p_rs->hdb_rec.rec[j].cmd_rec.hour= hour;
			p_rs->hdb_rec.rec[j].cmd_rec.day= day;
			p_rs->hdb_rec.rec[j].cmd_rec.month= mon;
			p_rs->hdb_rec.rec[j].cmd_rec.year= year;
			shm_hdb_addr->data_al.hdb_rec.rec[j] = p_rs->hdb_rec.rec[j];
			j++;
			break;
		}
		i++;
		p_rs->hdb_rec.head.header_ptr= j;
		shm_hdb_addr->data_al.hdb_rec.head.header_ptr= j;
		shm_hdb_addr->data_al.hdb_rec.head.count= j;		
	}//end while
	p_rs->hdb_rec.head.buf_size= MAX_HDB_RECORD_NUM;
	p_rs->hdb_rec.head.header_ptr= j;
	p_rs->hdb_rec.head.count= j;

	memcpy(&(shm_hdb_addr->data_al.hdb_rec), &(p_rs->hdb_rec) , sizeof(HDB_HISTORY_RECORD));
	shm_hdb_addr->data_al.lockflag=0;

	printf("Update alarm shared memeries successfully, alnum=%d!\n\n",shm_hdb_addr->data_al.hdb_rec.head.header_ptr);
	MySleep(10);	
	return TRUE;	
}
