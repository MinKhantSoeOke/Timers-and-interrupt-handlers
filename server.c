#include <stdio.h>
#include <time.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MY_PULSE_CODE1   _PULSE_CODE_MINAVAIL
#define MY_PULSE_CODE2   _PULSE_CODE_MINAVAIL+1

typedef union {
    struct _pulse   pulse;
    /* your other message structures would go
       here too */
} my_message_t;

int first_timer_count = 0;

void setup_timer(timer_t *timer_id, int chid, int initial_sec, long initial_nsec, int interval_sec, long interval_nsec, int MY_PULSE_CODE) {
    struct sigevent event;
    struct itimerspec itime;

    event.sigev_notify = SIGEV_PULSE;
    event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0, chid, _NTO_SIDE_CHANNEL, 0);
    event.sigev_priority = getprio(0);
    event.sigev_code = MY_PULSE_CODE;

    if (timer_create(CLOCK_REALTIME, &event, timer_id) == -1) {
        perror("timer_create_error");
        exit(EXIT_FAILURE);
    }

    printf("Timer Created\n");
    itime.it_value.tv_sec = initial_sec;
    itime.it_value.tv_nsec = initial_nsec;
    itime.it_interval.tv_sec = interval_sec;
    itime.it_interval.tv_nsec = interval_nsec;

    if (timer_settime(*timer_id, 0, &itime, NULL) == -1) {
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }
    printf("timer_create function exists.\n");
}

int main() {
    timer_t timer_id1, timer_id2;
    int chid, rcvid;
    my_message_t msg;

    chid = ChannelCreate(0);
    if (chid == -1) {
        perror("ChannelCreate_error");
        exit(EXIT_FAILURE);
    }
    printf("Channel Created\n");

    while(1){
        // Setup the first timer to expire every 10 milliseconds
        setup_timer(&timer_id1, chid, 0, 10000000, 0, 10000000, MY_PULSE_CODE1);

        // Setup the second timer to expire every 10 seconds
        setup_timer(&timer_id2, chid, 10, 0, 10, 0, MY_PULSE_CODE2);

        for (;;) {
            rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
            if (rcvid == 0) {
                if (msg.pulse.code == MY_PULSE_CODE1) {
                    first_timer_count++;
//                    printf("First timer expired %d times\n", first_timer_count);
                } else if (msg.pulse.code == MY_PULSE_CODE2) {
                    printf("Second timer. First Timer Count = %d\n", first_timer_count);
                }

            } else {
                perror("Message Receive Failed");
                exit(EXIT_FAILURE);
            }
        }

        timer_delete(timer_id1);
        timer_delete(timer_id2);
    }
    ChannelDestroy(chid);

    return 0;
}
