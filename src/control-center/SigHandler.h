#ifndef SIGHANDLER_H
#define SIGHANDLER_H

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include <signal.h>
#include <unistd.h>

namespace {

volatile sig_atomic_t do_shutdown = 0;
std::atomic<bool> shutdown_requested = false;
static_assert(std::atomic<bool>::is_always_lock_free);
}

void Signal_Handler(int /*signum*/)
{
    do_shutdown = 1;
    shutdown_requested = true;
    std::cout << "[I] [ Control-Center -> SigHandler ] Received Interrupt Signal, Exiting Cleanly \n" << std::endl;
}

#endif /* SIGHANDLER_H */