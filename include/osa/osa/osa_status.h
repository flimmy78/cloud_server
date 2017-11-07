#ifndef __OSA_STATUS_H__
#define __OSA_STATUS_H__

/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  
*/


/*
 * Created by Liu Papillon, on Sep 6, 2017.
 * These status codes use the codes from Linux.
 * Yes, I'm a Linux fan.
 */


#define OSA_STATUS_OK               0

/**************************** /usr/include/asm-generic/errno-base.h ***********************/

#define OSA_STATUS_EPERM            1  /* Operation not permitted */
#define OSA_STATUS_ENOENT           2  /* No such file or directory */
#define OSA_STATUS_ESRCH            3  /* No such process */
#define OSA_STATUS_EINTR            4  /* Interrupted system call */
#define OSA_STATUS_EIO              5  /* I/O error */
#define OSA_STATUS_ENXIO            6  /* No such device or address */
#define OSA_STATUS_E2BIG            7  /* Argument list too long */
#define OSA_STATUS_ENOEXEC          8  /* Exec format error */
#define OSA_STATUS_EBADF            9  /* Bad file number */
#define OSA_STATUS_ECHILD          10  /* No child processes */
#define OSA_STATUS_EAGAIN          11  /* Try again */
#define OSA_STATUS_ENOMEM          12  /* Out of memory */
#define OSA_STATUS_EACCES          13  /* Permission denied */
#define OSA_STATUS_EFAULT          14  /* Bad address */
#define OSA_STATUS_ENOTBLK         15  /* Block device required */
#define OSA_STATUS_EBUSY           16  /* Device or resource busy */
#define OSA_STATUS_EEXIST          17  /* File exists */
#define OSA_STATUS_EXDEV           18  /* Cross-device link */
#define OSA_STATUS_ENODEV          19  /* No such device */
#define OSA_STATUS_ENOTDIR         20  /* Not a directory */
#define OSA_STATUS_EISDIR          21  /* Is a directory */
#define OSA_STATUS_EINVAL          22  /* Invalid argument */
#define OSA_STATUS_ENFILE          23  /* File table overflow */
#define OSA_STATUS_EMFILE          24  /* Too many open files */
#define OSA_STATUS_ENOTTY          25  /* Not a typewriter */
#define OSA_STATUS_ETXTBSY         26  /* Text file busy */
#define OSA_STATUS_EFBIG           27  /* File too large */
#define OSA_STATUS_ENOSPC          28  /* No space left on device */
#define OSA_STATUS_ESPIPE          29  /* Illegal seek */
#define OSA_STATUS_EROFS           30  /* Read-only file system */
#define OSA_STATUS_EMLINK          31  /* Too many links */
#define OSA_STATUS_EPIPE           32  /* Broken pipe */
#define OSA_STATUS_EDOM            33  /* Math argument out of domain of func */
#define OSA_STATUS_ERANGE          34  /* Math result not representable */


/**************************** /usr/include/asm-generic/errno.h ***********************/

#define OSA_STATUS_EDEADLK         35  /* Resource deadlock would occur */
#define OSA_STATUS_ENAMETOOLONG    36  /* File name too long */
#define OSA_STATUS_ENOLCK          37  /* No record locks available */
#define OSA_STATUS_ENOSYS          38  /* Function not implemented */
#define OSA_STATUS_ENOTEMPTY       39  /* Directory not empty */
#define OSA_STATUS_ELOOP           40  /* Too many symbolic links encountered */
#define OSA_STATUS_EWOULDBLOCK     OSA_STATUS_EAGAIN  /* Operation would block */
#define OSA_STATUS_ENOMSG          42  /* No message of desired type */
#define OSA_STATUS_EIDRM           43  /* Identifier removed */
#define OSA_STATUS_ECHRNG          44  /* Channel number out of range */
#define OSA_STATUS_EL2NSYNC        45  /* Level 2 not synchronized */
#define OSA_STATUS_EL3HLT          46  /* Level 3 halted */
#define OSA_STATUS_EL3RST          47  /* Level 3 reset */
#define OSA_STATUS_ELNRNG          48  /* Link number out of range */
#define OSA_STATUS_EUNATCH         49  /* Protocol driver not attached */
#define OSA_STATUS_ENOCSI          50  /* No CSI structure available */
#define OSA_STATUS_EL2HLT          51  /* Level 2 halted */
#define OSA_STATUS_EBADE           52  /* Invalid exchange */
#define OSA_STATUS_EBADR           53  /* Invalid request descriptor */
#define OSA_STATUS_EXFULL          54  /* Exchange full */
#define OSA_STATUS_ENOANO          55  /* No anode */
#define OSA_STATUS_EBADRQC         56  /* Invalid request code */
#define OSA_STATUS_EBADSLT         57  /* Invalid slot */
#define OSA_STATUS_EDEADLOCK       OSA_STATUS_EDEADLK
#define OSA_STATUS_EBFONT          59  /* Bad font file format */
#define OSA_STATUS_ENOSTR          60  /* Device not a stream */
#define OSA_STATUS_ENODATA         61  /* No data available */
#define OSA_STATUS_ETIME           62  /* Timer expired */
#define OSA_STATUS_ENOSR           63  /* Out of streams resources */
#define OSA_STATUS_ENONET          64  /* Machine is not on the network */
#define OSA_STATUS_ENOPKG          65  /* Package not installed */
#define OSA_STATUS_EREMOTE         66  /* Object is remote */
#define OSA_STATUS_ENOLINK         67  /* Link has been severed */
#define OSA_STATUS_EADV            68  /* Advertise error */
#define OSA_STATUS_ESRMNT          69  /* Srmount error */
#define OSA_STATUS_ECOMM           70  /* Communication error on send */
#define OSA_STATUS_EPROTO          71  /* Protocol error */
#define OSA_STATUS_EMULTIHOP       72  /* Multihop attempted */
#define OSA_STATUS_EDOTDOT         73  /* RFS specific error */
#define OSA_STATUS_EBADMSG         74  /* Not a data message */
#define OSA_STATUS_EOVERFLOW       75  /* Value too large for defined data type */
#define OSA_STATUS_ENOTUNIQ        76  /* Name not unique on network */
#define OSA_STATUS_EBADFD          77  /* File descriptor in bad state */
#define OSA_STATUS_EREMCHG         78  /* Remote address changed */
#define OSA_STATUS_ELIBACC         79  /* Can not access a needed shared library */
#define OSA_STATUS_ELIBBAD         80  /* Accessing a corrupted shared library */
#define OSA_STATUS_ELIBSCN         81  /* .lib section in a.out corrupted */
#define OSA_STATUS_ELIBMAX         82  /* Attempting to link in too many shared libraries */
#define OSA_STATUS_ELIBEXEC        83  /* Cannot exec a shared library directly */
#define OSA_STATUS_EILSEQ          84  /* Illegal byte sequence */
#define OSA_STATUS_ERESTART        85  /* Interrupted system call should be restarted */
#define OSA_STATUS_ESTRPIPE        86  /* Streams pipe error */
#define OSA_STATUS_EUSERS          87  /* Too many users */
#define OSA_STATUS_ENOTSOCK        88  /* Socket operation on non-socket */
#define OSA_STATUS_EDESTADDRREQ    89  /* Destination address required */
#define OSA_STATUS_EMSGSIZE        90  /* Message too long */
#define OSA_STATUS_EPROTOTYPE      91  /* Protocol wrong type for socket */
#define OSA_STATUS_ENOPROTOOPT     92  /* Protocol not available */
#define OSA_STATUS_EPROTONOSUPPORT 93  /* Protocol not supported */
#define OSA_STATUS_ESOCKTNOSUPPORT 94  /* Socket type not supported */
#define OSA_STATUS_EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define OSA_STATUS_EPFNOSUPPORT    96  /* Protocol family not supported */
#define OSA_STATUS_EAFNOSUPPORT    97  /* Address family not supported by protocol */
#define OSA_STATUS_EADDRINUSE      98  /* Address already in use */
#define OSA_STATUS_EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define OSA_STATUS_ENETDOWN        100 /* Network is down */
#define OSA_STATUS_ENETUNREACH     101 /* Network is unreachable */
#define OSA_STATUS_ENETRESET       102 /* Network dropped connection because of reset */
#define OSA_STATUS_ECONNABORTED    103 /* Software caused connection abort */
#define OSA_STATUS_ECONNRESET      104 /* Connection reset by peer */
#define OSA_STATUS_ENOBUFS         105 /* No buffer space available */
#define OSA_STATUS_EISCONN         106 /* Transport endpoint is already connected */
#define OSA_STATUS_ENOTCONN        107 /* Transport endpoint is not connected */
#define OSA_STATUS_ESHUTDOWN       108 /* Cannot send after transport endpoint shutdown */
#define OSA_STATUS_ETOOMANYREFS    109 /* Too many references: cannot splice */
#define OSA_STATUS_ETIMEDOUT       110 /* Connection timed out */
#define OSA_STATUS_ECONNREFUSED    111 /* Connection refused */
#define OSA_STATUS_EHOSTDOWN       112 /* Host is down */
#define OSA_STATUS_EHOSTUNREACH    113 /* No route to host */
#define OSA_STATUS_EALREADY        114 /* Operation already in progress */
#define OSA_STATUS_EINPROGRESS     115 /* Operation now in progress */
#define OSA_STATUS_ESTALE          116 /* Stale NFS file handle */
#define OSA_STATUS_EUCLEAN         117 /* Structure needs cleaning */
#define OSA_STATUS_ENOTNAM         118 /* Not a XENIX named type file */
#define OSA_STATUS_ENAVAIL         119 /* No XENIX semaphores available */
#define OSA_STATUS_EISNAM          120 /* Is a named type file */
#define OSA_STATUS_EREMOTEIO       121 /* Remote I/O error */
#define OSA_STATUS_EDQUOT          122 /* Quota exceeded */

#define OSA_STATUS_ENOMEDIUM       123 /* No medium found */
#define OSA_STATUS_EMEDIUMTYPE     124 /* Wrong medium type */
#define OSA_STATUS_ECANCELED       125 /* Operation Canceled */
#define OSA_STATUS_ENOKEY          126 /* Required key not available */
#define OSA_STATUS_EKEYEXPIRED     127 /* Key has expired */
#define OSA_STATUS_EKEYREVOKED     128 /* Key has been revoked */
#define OSA_STATUS_EKEYREJECTED    129 /* Key was rejected by service */

/* for robust mutexes */
#define OSA_STATUS_EOWNERDEAD      130 /* Owner died */
#define OSA_STATUS_ENOTRECOVERABLE 131 /* State not recoverable */

#define OSA_STATUS_EGENERAL        255

/*******************************************************************/

#define OSA_isSucceeded(status)    (OSA_STATUS_OK == (status))
#define OSA_isFailed(status)       (OSA_STATUS_OK != (status))


#endif  /* __OSA_STATUS_H__ */

