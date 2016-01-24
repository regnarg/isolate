/*
 *	Process Isolator
 *
 *	(c) 2012-2016 Martin Mares <mj@ucw.cz>
 *	(c) 2012-2014 Bernard Blackham <bernard@blackham.com.au>
 */

#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>

#include "config.h"

#define NONRET __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define ARRAY_SIZE(a) (int)(sizeof(a)/sizeof(a[0]))

/* isolate.c */

void die(char *msg, ...) NONRET;
void NONRET __attribute__((format(printf,1,2))) err(char *msg, ...);
void __attribute__((format(printf,1,2))) msg(char *msg, ...);

extern int pass_environ;
extern int verbose;
extern int block_quota;
extern int inode_quota;
extern int cg_enable;
extern int cg_memory_limit;
extern int cg_timing;

extern int box_id;
extern uid_t box_uid;
extern gid_t box_gid;

/* util.c */

void *xmalloc(size_t size);
char *xstrdup(char *str);
int dir_exists(char *path);
void rmtree(char *path);
void make_dir(char *path);
void chowntree(char *path, uid_t uid, gid_t gid);

void meta_open(const char *name);
void meta_close(void);
void __attribute__((format(printf,1,2))) meta_printf(const char *fmt, ...);

/* rules.c */

int set_env_action(char *a0);
char **setup_environment(void);

void init_dir_rules(void);
int set_dir_action(char *arg);
void apply_dir_rules(void);

void set_quota(void);

/* cg.c */

void cg_init(void);
void cg_prepare(void);
void cg_enter(void);
int cg_get_run_time_ms(void);
void cg_stats(void);
void cg_remove(void);