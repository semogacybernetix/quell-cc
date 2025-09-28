/*

Netzwerkkarte mit ioctl in Promiskuitätsmodus schalten

man packet

I once had to listen on raw ethernet frames and ended up creating a wrapper for this.
By calling the function with the device name, ex eth0 I got a socket in return that was in promiscuous mode.
What you need to do is to create a raw socket and then put it into promiscuous mode. Here is how I did it.


Then when you have your socket you can just use select to handle packets as they arrive.

*/



int raw_init (const char *device)
{
    struct ifreq ifr;
    int raw_socket;

    memset (&ifr, 0, sizeof (struct ifreq));

    /* Open A Raw Socket */
    if ((raw_socket = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 1)
    {
        printf ("ERROR: Could not open socket, Got #?\n");
        exit (1);
    }

    /* Set the device to use */
    strcpy (ifr.ifr_name, device);

    /* Get the current flags that the device might have */
    if (ioctl (raw_socket, SIOCGIFFLAGS, &ifr) == -1)
    {
        perror ("Error: Could not retrive the flags from the device.\n");
        exit (1);
    }

    /* Set the old flags plus the IFF_PROMISC flag */
    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
    {
        perror ("Error: Could not set flag IFF_PROMISC");
        exit (1);
    }
    printf ("Entering promiscuous mode\n");

    /* Configure the device */

    if (ioctl (raw_socket, SIOCGIFINDEX, &ifr) < 0)
    {
        perror ("Error: Error getting the device index.\n");
        exit (1);
    }

    return raw_socket;
}
