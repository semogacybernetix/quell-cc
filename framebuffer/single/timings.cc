#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>

#if 0
	__u32 pixclock;			/* pixel clock in ps (pico seconds) */
	__u32 left_margin;		/* time from sync to picture	*/
	__u32 right_margin;		/* time from picture to sync	*/
	__u32 upper_margin;		/* time from sync to picture	*/
	__u32 lower_margin;
	__u32 hsync_len;		/* length of horizontal sync	*/
	__u32 vsync_len;		/* length of vertical sync	*/
	__u32 sync;			/* see FB_SYNC_*		*/
	__u32 vmode;			/* see FB_VMODE_*		*/
#endif

int main()
{
    int dbuffer= open ("/dev/fb0", O_RDWR);

    fb_var_screeninfo info;
    ioctl (dbuffer, FBIOGET_VSCREENINFO, &info);

    printf("xres %d\n", info.xres);
    printf("yres %d\n", info.yres);
    printf("zres %d\n", info.bits_per_pixel);
    printf("pixclock %d\n", info.pixclock);
    printf("left %d\n", info.left_margin);
    printf("right %d\n", info.right_margin);
    printf("upper %d\n", info.upper_margin);
    printf("lower %d\n", info.lower_margin);
    printf("hslen %d\n", info.hsync_len);
    printf("vslen %d\n", info.vsync_len);

    close(dbuffer);

    return 0;
}