.intel_syntax noprefix

# fds
.equ stdin,  0
.equ stdout, 1
.equ stderr, 2

# system v
.equ sysc, rax
.equ arg0, rdi
.equ arg1, rsi
.equ arg2, rdx
.equ arg3, rcx
.equ arg4, r8
.equ arg5, r9
.equ arf0, xmm0
.equ arf1, xmm1
.equ arf2, xmm2
.equ arf3, xmm3
.equ arf4, xmm4
.equ arf5, xmm5
.equ arf6, xmm6
.equ arf7, xmm7
.equ schn, r10
.equ ret0, rax
.equ ret1, rdx
.equ ref0, xmm0
.equ ref1, xmm1

# syscalls: /arch/x86/entry/syscalls/syscall_64.tbl in the Linux kernel source tree

.equ read,                      0 # sys_read                          # common
.equ write,                     1 # sys_write                         # common
.equ open,                      2 # sys_open                          # common
.equ close,                     3 # sys_close                         # common
.equ stat,                      4 # sys_newstat                       # common
.equ fstat,                     5 # sys_newfstat                      # common
.equ lstat,                     6 # sys_newlstat                      # common
.equ poll,                      7 # sys_poll                          # common
.equ lseek,                     8 # sys_lseek                         # common
.equ mmap,                      9 # sys_mmap                          # common
.equ mprotect,                 10 # sys_mprotect                      # common
.equ munmap,                   11 # sys_munmap                        # common
.equ brk,                      12 # sys_brk                           # common
.equ rt_sigaction,             13 # sys_rt_sigaction                  # 64
.equ rt_sigprocmask,           14 # sys_rt_sigprocmask                # common
.equ rt_sigreturn,             15 # sys_rt_sigreturn                  # 64
.equ ioctl,                    16 # sys_ioctl                         # 64
.equ pread64,                  17 # sys_pread64                       # common
.equ pwrite64,                 18 # sys_pwrite64                      # common
.equ readv,                    19 # sys_readv                         # 64
.equ writev,                   20 # sys_writev                        # 64
.equ access,                   21 # sys_access                        # common
.equ pipe,                     22 # sys_pipe                          # common
.equ select,                   23 # sys_select                        # common
.equ sched_yield,              24 # sys_sched_yield                   # common
.equ mremap,                   25 # sys_mremap                        # common
.equ msync,                    26 # sys_msync                         # common
.equ mincore,                  27 # sys_mincore                       # common
.equ madvise,                  28 # sys_madvise                       # common
.equ shmget,                   29 # sys_shmget                        # common
.equ shmat,                    30 # sys_shmat                         # common
.equ shmctl,                   31 # sys_shmctl                        # common
.equ dup,                      32 # sys_dup                           # common
.equ dup2,                     33 # sys_dup2                          # common
.equ pause,                    34 # sys_pause                         # common
.equ nanosleep,                35 # sys_nanosleep                     # common
.equ getitimer,                36 # sys_getitimer                     # common
.equ alarm,                    37 # sys_alarm                         # common
.equ setitimer,                38 # sys_setitimer                     # common
.equ getpid,                   39 # sys_getpid                        # common
.equ sendfile,                 40 # sys_sendfile64                    # common
.equ socket,                   41 # sys_socket                        # common
.equ connect,                  42 # sys_connect                       # common
.equ accept,                   43 # sys_accept                        # common
.equ sendto,                   44 # sys_sendto                        # common
.equ recvfrom,                 45 # sys_recvfrom                      # 64
.equ sendmsg,                  46 # sys_sendmsg                       # 64
.equ recvmsg,                  47 # sys_recvmsg                       # 64
.equ shutdown,                 48 # sys_shutdown                      # common
.equ bind,                     49 # sys_bind                          # common
.equ listen,                   50 # sys_listen                        # common
.equ getsockname,              51 # sys_getsockname                   # common
.equ getpeername,              52 # sys_getpeername                   # common
.equ socketpair,               53 # sys_socketpair                    # common
.equ setsockopt,               54 # sys_setsockopt                    # 64
.equ getsockopt,               55 # sys_getsockopt                    # 64
.equ clone,                    56 # sys_clone                         # common
.equ fork,                     57 # sys_fork                          # common
.equ vfork,                    58 # sys_vfork                         # common
.equ execve,                   59 # sys_execve                        # 64
.equ exit,                     60 # sys_exit - noreturn               # common
.equ wait4,                    61 # sys_wait4                         # common
.equ kill,                     62 # sys_kill                          # common
.equ uname,                    63 # sys_newuname                      # common
.equ semget,                   64 # sys_semget                        # common
.equ semop,                    65 # sys_semop                         # common
.equ semctl,                   66 # sys_semctl                        # common
.equ shmdt,                    67 # sys_shmdt                         # common
.equ msgget,                   68 # sys_msgget                        # common
.equ msgsnd,                   69 # sys_msgsnd                        # common
.equ msgrcv,                   70 # sys_msgrcv                        # common
.equ msgctl,                   71 # sys_msgctl                        # common
.equ fcntl,                    72 # sys_fcntl                         # common
.equ flock,                    73 # sys_flock                         # common
.equ fsync,                    74 # sys_fsync                         # common
.equ fdatasync,                75 # sys_fdatasync                     # common
.equ truncate,                 76 # sys_truncate                      # common
.equ ftruncate,                77 # sys_ftruncate                     # common
.equ getdents,                 78 # sys_getdents                      # common
.equ getcwd,                   79 # sys_getcwd                        # common
.equ chdir,                    80 # sys_chdir                         # common
.equ fchdir,                   81 # sys_fchdir                        # common
.equ rename,                   82 # sys_rename                        # common
.equ mkdir,                    83 # sys_mkdir                         # common
.equ rmdir,                    84 # sys_rmdir                         # common
.equ creat,                    85 # sys_creat                         # common
.equ link,                     86 # sys_link                          # common
.equ unlink,                   87 # sys_unlink                        # common
.equ symlink,                  88 # sys_symlink                       # common
.equ readlink,                 89 # sys_readlink                      # common
.equ chmod,                    90 # sys_chmod                         # common
.equ fchmod,                   91 # sys_fchmod                        # common
.equ chown,                    92 # sys_chown                         # common
.equ fchown,                   93 # sys_fchown                        # common
.equ lchown,                   94 # sys_lchown                        # common
.equ umask,                    95 # sys_umask                         # common
.equ gettimeofday,             96 # sys_gettimeofday                  # common
.equ getrlimit,                97 # sys_getrlimit                     # common
.equ getrusage,                98 # sys_getrusage                     # common
.equ sysinfo,                  99 # sys_sysinfo                       # common
.equ times,                   100 # sys_times                         # common
.equ ptrace,                  101 # sys_ptrace                        # 64
.equ getuid,                  102 # sys_getuid                        # common
.equ syslog,                  103 # sys_syslog                        # common
.equ getgid,                  104 # sys_getgid                        # common
.equ setuid,                  105 # sys_setuid                        # common
.equ setgid,                  106 # sys_setgid                        # common
.equ geteuid,                 107 # sys_geteuid                       # common
.equ getegid,                 108 # sys_getegid                       # common
.equ setpgid,                 109 # sys_setpgid                       # common
.equ getppid,                 110 # sys_getppid                       # common
.equ getpgrp,                 111 # sys_getpgrp                       # common
.equ setsid,                  112 # sys_setsid                        # common
.equ setreuid,                113 # sys_setreuid                      # common
.equ setregid,                114 # sys_setregid                      # common
.equ getgroups,               115 # sys_getgroups                     # common
.equ setgroups,               116 # sys_setgroups                     # common
.equ setresuid,               117 # sys_setresuid                     # common
.equ getresuid,               118 # sys_getresuid                     # common
.equ setresgid,               119 # sys_setresgid                     # common
.equ getresgid,               120 # sys_getresgid                     # common
.equ getpgid,                 121 # sys_getpgid                       # common
.equ setfsuid,                122 # sys_setfsuid                      # common
.equ setfsgid,                123 # sys_setfsgid                      # common
.equ getsid,                  124 # sys_getsid                        # common
.equ capget,                  125 # sys_capget                        # common
.equ capset,                  126 # sys_capset                        # common
.equ rt_sigpending,           127 # sys_rt_sigpending                 # 64
.equ rt_sigtimedwait,         128 # sys_rt_sigtimedwait               # 64
.equ rt_sigqueueinfo,         129 # sys_rt_sigqueueinfo               # 64
.equ rt_sigsuspend,           130 # sys_rt_sigsuspend                 # common
.equ sigaltstack,             131 # sys_sigaltstack                   # 64
.equ utime,                   132 # sys_utime                         # common
.equ mknod,                   133 # sys_mknod                         # common
.equ uselib,                  134 #                                   # 64
.equ personality,             135 # sys_personality                   # common
.equ ustat,                   136 # sys_ustat                         # common
.equ statfs,                  137 # sys_statfs                        # common
.equ fstatfs,                 138 # sys_fstatfs                       # common
.equ sysfs,                   139 # sys_sysfs                         # common
.equ getpriority,             140 # sys_getpriority                   # common
.equ setpriority,             141 # sys_setpriority                   # common
.equ sched_setparam,          142 # sys_sched_setparam                # common
.equ sched_getparam,          143 # sys_sched_getparam                # common
.equ sched_setscheduler,      144 # sys_sched_setscheduler            # common
.equ sched_getscheduler,      145 # sys_sched_getscheduler            # common
.equ sched_get_priority_max,  146 # sys_sched_get_priority_max        # common
.equ sched_get_priority_min,  147 # sys_sched_get_priority_min        # common
.equ sched_rr_get_interval,   148 # sys_sched_rr_get_interval         # common
.equ mlock,                   149 # sys_mlock                         # common
.equ munlock,                 150 # sys_munlock                       # common
.equ mlockall,                151 # sys_mlockall                      # common
.equ munlockall,              152 # sys_munlockall                    # common
.equ vhangup,                 153 # sys_vhangup                       # common
.equ modify_ldt,              154 # sys_modify_ldt                    # common
.equ pivot_root,              155 # sys_pivot_root                    # common
.equ _sysctl,                 156 # sys_ni_syscall                    # 64
.equ prctl,                   157 # sys_prctl                         # common
.equ arch_prctl,              158 # sys_arch_prctl                    # common
.equ adjtimex,                159 # sys_adjtimex                      # common
.equ setrlimit,               160 # sys_setrlimit                     # common
.equ chroot,                  161 # sys_chroot                        # common
.equ sync,                    162 # sys_sync                          # common
.equ acct,                    163 # sys_acct                          # common
.equ settimeofday,            164 # sys_settimeofday                  # common
.equ mount,                   165 # sys_mount                         # common
.equ umount2,                 166 # sys_umount                        # common
.equ swapon,                  167 # sys_swapon                        # common
.equ swapoff,                 168 # sys_swapoff                       # common
.equ reboot,                  169 # sys_reboot                        # common
.equ sethostname,             170 # sys_sethostname                   # common
.equ setdomainname,           171 # sys_setdomainname                 # common
.equ iopl,                    172 # sys_iopl                          # common
.equ ioperm,                  173 # sys_ioperm                        # common
.equ create_module,           174 #                                   # 64
.equ init_module,             175 # sys_init_module                   # common
.equ delete_module,           176 # sys_delete_module                 # common
.equ get_kernel_syms,         177 #                                   # 64
.equ query_module,            178 #                                   # 64
.equ quotactl,                179 # sys_quotactl                      # common
.equ nfsservctl,              180 #                                   # 64
.equ getpmsg,                 181 #                                   # common
.equ putpmsg,                 182 #                                   # common
.equ afs_syscall,             183 #                                   # common
.equ tuxcall,                 184 #                                   # common
.equ security,                185 #                                   # common
.equ gettid,                  186 # sys_gettid                        # common
.equ readahead,               187 # sys_readahead                     # common
.equ setxattr,                188 # sys_setxattr                      # common
.equ lsetxattr,               189 # sys_lsetxattr                     # common
.equ fsetxattr,               190 # sys_fsetxattr                     # common
.equ getxattr,                191 # sys_getxattr                      # common
.equ lgetxattr,               192 # sys_lgetxattr                     # common
.equ fgetxattr,               193 # sys_fgetxattr                     # common
.equ listxattr,               194 # sys_listxattr                     # common
.equ llistxattr,              195 # sys_llistxattr                    # common
.equ flistxattr,              196 # sys_flistxattr                    # common
.equ removexattr,             197 # sys_removexattr                   # common
.equ lremovexattr,            198 # sys_lremovexattr                  # common
.equ fremovexattr,            199 # sys_fremovexattr                  # common
.equ tkill,                   200 # sys_tkill                         # common
.equ time,                    201 # sys_time                          # common
.equ futex,                   202 # sys_futex                         # common
.equ sched_setaffinity,       203 # sys_sched_setaffinity             # common
.equ sched_getaffinity,       204 # sys_sched_getaffinity             # common
.equ set_thread_area,         205 #                                   # 64
.equ io_setup,                206 # sys_io_setup                      # 64
.equ io_destroy,              207 # sys_io_destroy                    # common
.equ io_getevents,            208 # sys_io_getevents                  # common
.equ io_submit,               209 # sys_io_submit                     # 64
.equ io_cancel,               210 # sys_io_cancel                     # common
.equ get_thread_area,         211 #                                   # 64
.equ lookup_dcookie,          212 #                                   # common
.equ epoll_create,            213 # sys_epoll_create                  # common
.equ epoll_ctl_old,           214 #                                   # 64
.equ epoll_wait_old,          215 #                                   # 64
.equ remap_file_pages,        216 # sys_remap_file_pages              # common
.equ getdents64,              217 # sys_getdents64                    # common
.equ set_tid_address,         218 # sys_set_tid_address               # common
.equ restart_syscall,         219 # sys_restart_syscall               # common
.equ semtimedop,              220 # sys_semtimedop                    # common
.equ fadvise64,               221 # sys_fadvise64                     # common
.equ timer_create,            222 # sys_timer_create                  # 64
.equ timer_settime,           223 # sys_timer_settime                 # common
.equ timer_gettime,           224 # sys_timer_gettime                 # common
.equ timer_getoverrun,        225 # sys_timer_getoverrun              # common
.equ timer_delete,            226 # sys_timer_delete                  # common
.equ clock_settime,           227 # sys_clock_settime                 # common
.equ clock_gettime,           228 # sys_clock_gettime                 # common
.equ clock_getres,            229 # sys_clock_getres                  # common
.equ clock_nanosleep,         230 # sys_clock_nanosleep               # common
.equ exit_group,              231 # sys_exit_group - noreturn         # common
.equ epoll_wait,              232 # sys_epoll_wait                    # common
.equ epoll_ctl,               233 # sys_epoll_ctl                     # common
.equ tgkill,                  234 # sys_tgkill                        # common
.equ utimes,                  235 # sys_utimes                        # common
.equ vserver,                 236 #                                   # 64
.equ mbind,                   237 # sys_mbind                         # common
.equ set_mempolicy,           238 # sys_set_mempolicy                 # common
.equ get_mempolicy,           239 # sys_get_mempolicy                 # common
.equ mq_open,                 240 # sys_mq_open                       # common
.equ mq_unlink,               241 # sys_mq_unlink                     # common
.equ mq_timedsend,            242 # sys_mq_timedsend                  # common
.equ mq_timedreceive,         243 # sys_mq_timedreceive               # common
.equ mq_notify,               244 # sys_mq_notify                     # 64
.equ mq_getsetattr,           245 # sys_mq_getsetattr                 # common
.equ kexec_load,              246 # sys_kexec_load                    # 64
.equ waitid,                  247 # sys_waitid                        # 64
.equ add_key,                 248 # sys_add_key                       # common
.equ request_key,             249 # sys_request_key                   # common
.equ keyctl,                  250 # sys_keyctl                        # common
.equ ioprio_set,              251 # sys_ioprio_set                    # common
.equ ioprio_get,              252 # sys_ioprio_get                    # common
.equ inotify_init,            253 # sys_inotify_init                  # common
.equ inotify_add_watch,       254 # sys_inotify_add_watch             # common
.equ inotify_rm_watch,        255 # sys_inotify_rm_watch              # common
.equ migrate_pages,           256 # sys_migrate_pages                 # common
.equ openat,                  257 # sys_openat                        # common
.equ mkdirat,                 258 # sys_mkdirat                       # common
.equ mknodat,                 259 # sys_mknodat                       # common
.equ fchownat,                260 # sys_fchownat                      # common
.equ futimesat,               261 # sys_futimesat                     # common
.equ newfstatat,              262 # sys_newfstatat                    # common
.equ unlinkat,                263 # sys_unlinkat                      # common
.equ renameat,                264 # sys_renameat                      # common
.equ linkat,                  265 # sys_linkat                        # common
.equ symlinkat,               266 # sys_symlinkat                     # common
.equ readlinkat,              267 # sys_readlinkat                    # common
.equ fchmodat,                268 # sys_fchmodat                      # common
.equ faccessat,               269 # sys_faccessat                     # common
.equ pselect6,                270 # sys_pselect6                      # common
.equ ppoll,                   271 # sys_ppoll                         # common
.equ unshare,                 272 # sys_unshare                       # common
.equ set_robust_list,         273 # sys_set_robust_list               # 64
.equ get_robust_list,         274 # sys_get_robust_list               # 64
.equ splice,                  275 # sys_splice                        # common
.equ tee,                     276 # sys_tee                           # common
.equ sync_file_range,         277 # sys_sync_file_range               # common
.equ vmsplice,                278 # sys_vmsplice                      # 64
.equ move_pages,              279 # sys_move_pages                    # 64
.equ utimensat,               280 # sys_utimensat                     # common
.equ epoll_pwait,             281 # sys_epoll_pwait                   # common
.equ signalfd,                282 # sys_signalfd                      # common
.equ timerfd_create,          283 # sys_timerfd_create                # common
.equ eventfd,                 284 # sys_eventfd                       # common
.equ fallocate,               285 # sys_fallocate                     # common
.equ timerfd_settime,         286 # sys_timerfd_settime               # common
.equ timerfd_gettime,         287 # sys_timerfd_gettime               # common
.equ accept4,                 288 # sys_accept4                       # common
.equ signalfd4,               289 # sys_signalfd4                     # common
.equ eventfd2,                290 # sys_eventfd2                      # common
.equ epoll_create1,           291 # sys_epoll_create1                 # common
.equ dup3,                    292 # sys_dup3                          # common
.equ pipe2,                   293 # sys_pipe2                         # common
.equ inotify_init1,           294 # sys_inotify_init1                 # common
.equ preadv,                  295 # sys_preadv                        # 64
.equ pwritev,                 296 # sys_pwritev                       # 64
.equ rt_tgsigqueueinfo,       297 # sys_rt_tgsigqueueinfo             # 64
.equ perf_event_open,         298 # sys_perf_event_open               # common
.equ recvmmsg,                299 # sys_recvmmsg                      # 64
.equ fanotify_init,           300 # sys_fanotify_init                 # common
.equ fanotify_mark,           301 # sys_fanotify_mark                 # common
.equ prlimit64,               302 # sys_prlimit64                     # common
.equ name_to_handle_at,       303 # sys_name_to_handle_at             # common
.equ open_by_handle_at,       304 # sys_open_by_handle_at             # common
.equ clock_adjtime,           305 # sys_clock_adjtime                 # common
.equ syncfs,                  306 # sys_syncfs                        # common
.equ sendmmsg,                307 # sys_sendmmsg                      # 64
.equ setns,                   308 # sys_setns                         # common
.equ getcpu,                  309 # sys_getcpu                        # common
.equ process_vm_readv,        310 # sys_process_vm_readv              # 64
.equ process_vm_writev,       311 # sys_process_vm_writev             # 64
.equ kcmp,                    312 # sys_kcmp                          # common
.equ finit_module,            313 # sys_finit_module                  # common
.equ sched_setattr,           314 # sys_sched_setattr                 # common
.equ sched_getattr,           315 # sys_sched_getattr                 # common
.equ renameat2,               316 # sys_renameat2                     # common
.equ seccomp,                 317 # sys_seccomp                       # common
.equ getrandom,               318 # sys_getrandom                     # common
.equ memfd_create,            319 # sys_memfd_create                  # common
.equ kexec_file_load,         320 # sys_kexec_file_load               # common
.equ bpf,                     321 # sys_bpf                           # common
.equ execveat,                322 # sys_execveat                      # 64
.equ userfaultfd,             323 # sys_userfaultfd                   # common
.equ membarrier,              324 # sys_membarrier                    # common
.equ mlock2,                  325 # sys_mlock2                        # common
.equ copy_file_range,         326 # sys_copy_file_range               # common
.equ preadv2,                 327 # sys_preadv2                       # 64
.equ pwritev2,                328 # sys_pwritev2                      # 64
.equ pkey_mprotect,           329 # sys_pkey_mprotect                 # common
.equ pkey_alloc,              330 # sys_pkey_alloc                    # common
.equ pkey_free,               331 # sys_pkey_free                     # common
.equ statx,                   332 # sys_statx                         # common
.equ io_pgetevents,           333 # sys_io_pgetevents                 # common
.equ rseq,                    334 # sys_rseq                          # common
.equ uretprobe,               335 # sys_uretprobe                     # common
.equ uprobe,                  336 # sys_uprobe                        # common
.equ pidfd_send_signal,       424 # sys_pidfd_send_signal             # common
.equ io_uring_setup,          425 # sys_io_uring_setup                # common
.equ io_uring_enter,          426 # sys_io_uring_enter                # common
.equ io_uring_register,       427 # sys_io_uring_register             # common
.equ open_tree,               428 # sys_open_tree                     # common
.equ move_mount,              429 # sys_move_mount                    # common
.equ fsopen,                  430 # sys_fsopen                        # common
.equ fsconfig,                431 # sys_fsconfig                      # common
.equ fsmount,                 432 # sys_fsmount                       # common
.equ fspick,                  433 # sys_fspick                        # common
.equ pidfd_open,              434 # sys_pidfd_open                    # common
.equ clone3,                  435 # sys_clone3                        # common
.equ close_range,             436 # sys_close_range                   # common
.equ openat2,                 437 # sys_openat2                       # common
.equ pidfd_getfd,             438 # sys_pidfd_getfd                   # common
.equ faccessat2,              439 # sys_faccessat2                    # common
.equ process_madvise,         440 # sys_process_madvise               # common
.equ epoll_pwait2,            441 # sys_epoll_pwait2                  # common
.equ mount_setattr,           442 # sys_mount_setattr                 # common
.equ quotactl_fd,             443 # sys_quotactl_fd                   # common
.equ landlock_create_ruleset, 444 # sys_landlock_create_ruleset       # common
.equ landlock_add_rule,       445 # sys_landlock_add_rule             # common
.equ landlock_restrict_self,  446 # sys_landlock_restrict_self        # common
.equ memfd_secret,            447 # sys_memfd_secret                  # common
.equ process_mrelease,        448 # sys_process_mrelease              # common
.equ futex_waitv,             449 # sys_futex_waitv                   # common
.equ set_mempolicy_home_node, 450 # sys_set_mempolicy_home_node       # common
.equ cachestat,               451 # sys_cachestat                     # common
.equ fchmodat2,               452 # sys_fchmodat2                     # common
.equ map_shadow_stack,        453 # sys_map_shadow_stack              # common
.equ futex_wake,              454 # sys_futex_wake                    # common
.equ futex_wait,              455 # sys_futex_wait                    # common
.equ futex_requeue,           456 # sys_futex_requeue                 # common
.equ statmount,               457 # sys_statmount                     # common
.equ listmount,               458 # sys_listmount                     # common
.equ lsm_get_self_attr,       459 # sys_lsm_get_self_attr             # common
.equ lsm_set_self_attr,       460 # sys_lsm_set_self_attr             # common
.equ lsm_list_modules,        461 # sys_lsm_list_modules              # common
.equ mseal,                   462 # sys_mseal                         # common
.equ setxattrat,              463 # sys_setxattrat                    # common
.equ getxattrat,              464 # sys_getxattrat                    # common
.equ listxattrat,             465 # sys_listxattrat                   # common
.equ removexattrat,           466 # sys_removexattrat                 # common
.equ open_tree_attr,          467 # sys_open_tree_attr                # common
.equ file_getattr,            468 # sys_file_getattr                  # common
.equ file_setattr,            469 # sys_file_setattr                  # common
.equ listns,                  470 # sys_listns                        # common
.equ rseq_slice_yield,        471 # sys_rseq_slice_yield              # common
# .equ rt_sigaction,            512 # compat_sys_rt_sigaction           # x32
# .equ rt_sigreturn,            513 # compat_sys_x32_rt_sigreturn       # x32
# .equ ioctl,                   514 # compat_sys_ioctl                  # x32
# .equ readv,                   515 # sys_readv                         # x32
# .equ writev,                  516 # sys_writev                        # x32
# .equ recvfrom,                517 # compat_sys_recvfrom               # x32
# .equ sendmsg,                 518 # compat_sys_sendmsg                # x32
# .equ recvmsg,                 519 # compat_sys_recvmsg                # x32
# .equ execve,                  520 # compat_sys_execve                 # x32
# .equ ptrace,                  521 # compat_sys_ptrace                 # x32
# .equ rt_sigpending,           522 # compat_sys_rt_sigpending          # x32
# .equ rt_sigtimedwait,         523 # compat_sys_rt_sigtimedwait_time64 # x32
# .equ rt_sigqueueinfo,         524 # compat_sys_rt_sigqueueinfo        # x32
# .equ sigaltstack,             525 # compat_sys_sigaltstack            # x32
# .equ timer_create,            526 # compat_sys_timer_create           # x32
# .equ mq_notify,               527 # compat_sys_mq_notify              # x32
# .equ kexec_load,              528 # compat_sys_kexec_load             # x32
# .equ waitid,                  529 # compat_sys_waitid                 # x32
# .equ set_robust_list,         530 # compat_sys_set_robust_list        # x32
# .equ get_robust_list,         531 # compat_sys_get_robust_list        # x32
# .equ vmsplice,                532 # sys_vmsplice                      # x32
# .equ move_pages,              533 # sys_move_pages                    # x32
# .equ preadv,                  534 # compat_sys_preadv64               # x32
# .equ pwritev,                 535 # compat_sys_pwritev64              # x32
# .equ rt_tgsigqueueinfo,       536 # compat_sys_rt_tgsigqueueinfo      # x32
# .equ recvmmsg,                537 # compat_sys_recvmmsg_time64        # x32
# .equ sendmmsg,                538 # compat_sys_sendmmsg               # x32
# .equ process_vm_readv,        539 # sys_process_vm_readv              # x32
# .equ process_vm_writev,       540 # sys_process_vm_writev             # x32
# .equ setsockopt,              541 # sys_setsockopt                    # x32
# .equ getsockopt,              542 # sys_getsockopt                    # x32
# .equ io_setup,                543 # compat_sys_io_setup               # x32
# .equ io_submit,               544 # compat_sys_io_submit              # x32
# .equ execveat,                545 # compat_sys_execveat               # x32
# .equ preadv2,                 546 # compat_sys_preadv64v2             # x32
# .equ pwritev2,                547 # compat_sys_pwritev64v2            # x32
