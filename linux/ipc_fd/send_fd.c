#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int recv_fd(int sd)
{
    struct msghdr msg;
    struct cmsghdr *cmsg;
    struct iovec iov[1];
    char buf[32];
    int cmsg_size;

    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf);

    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    cmsg_size = sizeof(struct cmsghdr)+sizeof(int);

    if ( (cmsg = (struct cmsghdr*)malloc(cmsg_size)) == NULL )
        return -1;

    msg.msg_control = (caddr_t)cmsg;
    msg.msg_controllen = cmsg_size;
    if ( recvmsg(sd, &msg, 0) <= 0 )
        return -1;
    return *(int *)CMSG_DATA(cmsg);
}

int send_fd(int sd, int fd)
{
    struct msghdr msg;
    struct cmsghdr *cmsg;
    struct iovec iov[1];
    char buf[1];
    int cmsg_size;

    iov[0].iov_base = buf;
    iov[0].iov_len = 1;

    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    cmsg_size = sizeof(struct cmsghdr)+sizeof(int);

    if ( (cmsg = (struct cmsghdr*)malloc(cmsg_size)) == NULL )

        return -1;

    cmsg->cmsg_len = cmsg_size;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *(int *)CMSG_DATA(cmsg) = fd;

    msg.msg_control = (caddr_t)cmsg;
    msg.msg_controllen = cmsg_size;
    if ( sendmsg(sd, &msg, 0) != 1 )

        return -1;
    return 0;
}
