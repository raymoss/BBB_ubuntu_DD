#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/ioctl.h>

#include"query_ioctl.h"

void get_vars(int fd){
query_arg_t q;
if (ioctl(fd,QUERY_GET_VARIABLES,&q)==-1){
    perror("query_apps ioctl get");
}
else{
    printf("Status : %d\n",q.status);
    printf("Diginity: %d\n",q.dignity);
    printf("Ego : %d\n",q.ego);
}
}
void clr_vars(int fd){
    if(ioctl(fd,QUERY_CLR_VARIABLES)==-1)
    perror("query_apps ioclt clr");
}
void set_vars(int fd){
    int v;
    query_arg_t q;
    printf("Enter status: ");
    scanf("%d",&v);
    q.status=v;
    printf("Enter diginity: ");
    scanf("%d",&v);
    q.dignity=v;
    printf("Enter ego: ");
    scanf("%d",&v);
    q.ego=v;
    if(ioctl(fd,QUERY_SET_VARIABLES,&q)==-1){
        perror("query_apps ioctl set");
    }
}
int main(int argc,char **argv/* arguments */) {
    char *file_name="/dev/query";
    int fd;
    enum{set,clr,get}option;
    if(argc<2){
        printf("Please check usage of the app");
        return -1;
    }
    else{
    if(argc==2){
        if(strcmp(argv[1],"-s")==0)
        option = set;
        else if(strcmp(argv[1],"-c")==0)
        option= clr;
        else if(strcmp(argv[1],"-g")==0)
        option = get;
        else{
        printf(stderr, "Usage: %s [-g | -c | -s]\n", argv[0]);
        return -1;
    }
    }
    else {
        printf("ERROR: invalid number of arguments");
        return -1;
    }
}

    fd=open(file_name,O_RDWR);
    if(fd==-1){
        perror("query_apps open");
    }
    switch(option){
        case set:
            set_vars(fd);
            break;
        case get:
            get_vars(fd);
            break;
        case clr:
            clr_vars(fd);
            break;
    }
    close(fd);
    return 0;
}
