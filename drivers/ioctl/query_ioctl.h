#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H
#include <linux/ioctl.h>

typedef struct{
    int status;
    int dignity;
    int ego;

}query_arg_t;

#define QUERY_CLR_VARIABLES _IO('q',1)
#define QUERY_SET_VARIABLES _IOW('q',2, query_arg_t)
#define QUERY_GET_VARIABLES _IOR('q',3,query_arg_t)

#endif
