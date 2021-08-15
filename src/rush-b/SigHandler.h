#ifndef SIGHANDLER_H
#define SIGHANDLER_H

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include <signal.h>
#include <unistd.h>

#define RUNNING (!do_shutdown && !shutdown_requested.load())

static volatile int s_interrupted = 0;
static void s_signal_handler(int signal_value)
{
    s_interrupted = 1;
}

static void Catch_Signals(void)
{
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

#endif /* SIGHANDLER_H */
