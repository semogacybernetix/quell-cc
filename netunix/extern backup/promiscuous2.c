
/*
ohne ioctls in den PromiModus schalten
There is an internal counter on each device that is incremented each time a process uses PACKET_MR_PROMISC, and decremented when that process goes away. That solves the race you originally described.

*/


void set_promisc(const char *ifname, bool enable)
{
    struct packet_mreq mreq = {0};
    int sfd;
    int action;

    if ((sfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
        perror("unable to open socket");
        return;
    }

    mreq.mr_ifindex = if_nametoindex(ifname);
    mreq.mr_type = PACKET_MR_PROMISC;

    if (mreq.mr_ifindex == 0) {
        perror("unable to get interface index");
        return;
    }

    if (enable)
        action = PACKET_ADD_MEMBERSHIP;
    else
        action = PACKET_DROP_MEMBERSHIP;

    if (setsockopt(sfd, SOL_PACKET, action, &mreq, sizeof(mreq)) != 0) {
        perror("unable to enter promiscouous mode");
        return;
    }

    close(sfd);
}