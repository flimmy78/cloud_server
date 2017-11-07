#ifndef __SYNC_H_
#define __SYNC_H_

#include "dbm.h"
#include "syslog.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stCond {
	const char	*name;
	int		offset;
	int		type;
}stCond_t;


typedef struct stTableSts {
	const char		 *name;					/* table name */
	int				size;					/* record size */
	int				type;					/* EntityType */
	int				syncoff;
	int				condcnt;
	stCond_t	conds[5];
}stTableSts_t;


#define member_offset(type, field) ((size_t)&(((type *)0)->field))


#define MYSQL_CONNECT_STR ("User ID = harper; Password = Hello; Server = localhost; Initial Catalog = SAC")

#if 0
#define log_info(fmt,...)		syslog(LOG_INFO | LOG_CONS, fmt, __VA_ARGS__)
#define log_warn(fmt,...)		syslog(LOG_WARNING | LOG_CONS, fmt,__VA_ARGS__ )
#define log_err(fmt, ...)		syslog(LOG_ERR | LOG_CONS, fmt,__VA_ARGS__ )
#define log_debug(fmt,...)	syslog(LOG_DEBUG | LOG_CONS, fmt,__VA_ARGS__)
#else
#define log_info(fmt,...)		printf("[INFO] [%s] [%d]:" fmt, __func__, __LINE__, __VA_ARGS__)

#define log_warn(fmt,...)		printf("[WARN] [%s] [%d]:" fmt, __func__, __LINE__, __VA_ARGS__)

#define log_err(fmt, ...)		printf("[ERRR] [%s] [%d]:" fmt, __func__, __LINE__, __VA_ARGS__)

#define log_debug(fmt,...)	printf("[DBUG] [%s] [%d]:" fmt, __func__, __LINE__, __VA_ARGS__)

#endif



#ifdef __cplusplus
}
#endif



#endif
