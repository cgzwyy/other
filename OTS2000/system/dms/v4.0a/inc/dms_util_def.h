#ifndef     _UTIL_DEF_H
#define     _UTIL_DEF_H

#include "./os_type_def.h"
#include "./dms_structure_def.h"




enum	H9000_ERROR_ID	{
		H9000_ERROR_DB=1,
		H9000_ERROR_CONFIGFILE,
		H9000_ERROR_NO_LICENSE,
		H9000_ERROR_ILLEGAL_LICENSE
		};


#ifdef __cplusplus
extern "C"{
#endif
	
float	AnlgDatatoFloat ( ANLG_DATA *anlg_data );
void    FloattoAnlgData( float value, ANLG_DATA *anlg_data );
void	CrossCopy( void *strDest, void *strSrc, int nNum);



#ifdef	_BIG_ENDIAN_
void Swap2Byte(void *pShort);
void Swap4Byte(void *pInt);
void SwapImpDataByte( IMP_DATA *pImp);
void SwapImpEngParaByte( IMP_ENG_PARA *eng);
void SwapAnaEngParaByte( ANA_ENG_PARA *eng);
void SwapLmtParaByte( LMT_PARA *lmt);
void SwapCharaDataByte( CHARA_DATA *chara);
void SwapCurveDataByte( CURVE_DATA *data);
void SwapStcDataByte( STC_DATA *stc);
void SwapDateTimeByte( DATE_TIME *date_time);
#else
#define Swap2Byte(p)			; 
#define Swap4Byte(p)			; 
#define SwapImpDataByte(p)		;
#define SwapLmtParaByte(p)		;
#define SwapCharaDataByte(p)	;
#define SwapImpEngParaByte(p)	;
#define SwapAnaEngParaByte(p)	;
#define SwapLmtParaByte(p)		;
#define SwapStcDataByte(p)		;
#define SwapDateTimeByte(p)		;
#define SwapCurveDataByte(p)	;
#endif

BOOL	IsIndTypePoint(POINTER *pt);
BOOL	IsAnaTypePoint(POINTER *pt);

					 
void	GetSysTime( DATE_TIME *curr_time);
void	GetSysTimeEx( DATE_TIME *date_time, time_t *sec);
void 	GetSysTimeStr( char *timeStr);
void	PrintfWithCurrTime(char *str);
void	GetSysShortTimeStr( char *timeStr);
void	PrintfWithCurrShortTime(char *str);


BOOL	GetExLangState(void);
int		SetExLangState(BOOL	ex_lang_state);
int		InitStrTextDefine(void);/*-1 mean fail, 0 mean ok*/
char*	_CS_( char* name );


int	LocateKeyword( FILE *fp, char *keyword );

void AsciiToHex(char *asc, char *bin, int size);

int GetH9000ErrorId(void);



#ifdef	WINDOWS_OS
#define		pthread_t				HANDLE
#define 	bzero(addr, size)		memset(addr, 0, size)
#define		Msleep(ms)				Sleep(ms)
#define		sleep(sec)				Sleep(sec*1000)
#define		SIGQUIT					SIGBREAK
#define		kill(run_pid, SIGNAL)	TerminateProcess(run_pid, 0)
#else
#define		DWORD					pthread_t
#ifndef		closesocket
#define		closesocket(socket)		close(socket)
#endif
#define		Msleep(ms)				usleep(ms*1000)
#endif














#ifdef __cplusplus
}
#endif



#endif  /*_UTIL_DEF_H*/


