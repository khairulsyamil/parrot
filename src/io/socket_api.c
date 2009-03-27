/*
Copyright (C) 2001-2008, Parrot Foundation.
$Id$

=head1 NAME

src/io/socket_api.c - Socket I/O API

=head1 DESCRIPTION

These are the primary interface functions for working with socket objects.

=head2 Networking Functions

=over 4

=cut

*/

#include "parrot/parrot.h"
#include "io_private.h"
#include "api.str"

#include <stdarg.h>

/* HEADERIZER HFILE: include/parrot/io.h */

/*

=item C<INTVAL Parrot_io_socket_is_closed>

=cut

*/

PARROT_EXPORT
PARROT_WARN_UNUSED_RESULT
PARROT_CANNOT_RETURN_NULL
INTVAL
Parrot_io_socket_is_closed(ARGMOD(PMC *socket))
{
    ASSERT_ARGS(Parrot_io_socket_is_closed)
    return 0;
}

/*

=item C<INTVAL Parrot_io_poll>

Polls C<*pmc> for the events in C<which> every C<sec> seconds + C<usec>
microseconds.

=cut

*/

PARROT_EXPORT
INTVAL
Parrot_io_poll(PARROT_INTERP, ARGMOD(PMC *pmc), INTVAL which, INTVAL sec, INTVAL usec)
{
    ASSERT_ARGS(Parrot_io_poll)
    if (PMC_IS_NULL(pmc))
        Parrot_ex_throw_from_c_args(interp, NULL, EXCEPTION_INVALID_OPERATION,
            "Can't poll a NULL socket object");

    return PIO_POLL(interp, pmc, which, sec, usec);
}

/*

=item C<PMC * Parrot_io_socket>

Creates and returns a socket using the specified address family, socket type,
and protocol number. Check the returned PMC with a boolean test to see whether
the socket was successfully created.

=cut

*/

PARROT_EXPORT
PARROT_WARN_UNUSED_RESULT
PARROT_CANNOT_RETURN_NULL
PMC *
Parrot_io_socket(PARROT_INTERP, ARGMOD_NULLOK(PMC * socket), INTVAL fam,
            INTVAL type, INTVAL proto)
{
    ASSERT_ARGS(Parrot_io_socket)
    PMC *new_socket;

    if (PMC_IS_NULL(socket))
        new_socket = Parrot_io_new_socket_pmc(interp,
                PIO_F_SOCKET|PIO_F_READ|PIO_F_WRITE);
    else
        new_socket = socket;

    return PIO_SOCKET(interp, socket, fam, type, proto);
}

/*

=item C<INTVAL Parrot_io_recv>

Receives a message from the connected socket C<*pmc> in C<*buf>.  Returns C<-1>
if it fails.

=cut

*/

PARROT_EXPORT
INTVAL
Parrot_io_recv(PARROT_INTERP, ARGMOD(PMC *pmc), ARGOUT(STRING **buf))
{
    ASSERT_ARGS(Parrot_io_recv)
    if (Parrot_io_socket_is_closed(pmc))
        return -1;

    return PIO_RECV(interp, pmc, buf);
}

/*

=item C<INTVAL Parrot_io_send>

Sends the message C<*buf> to the connected socket C<*pmc>.  Returns
C<-1> if it cannot send the message.

=cut

*/

PARROT_EXPORT
PARROT_WARN_UNUSED_RESULT
INTVAL
Parrot_io_send(PARROT_INTERP, ARGMOD(PMC *pmc), ARGMOD(STRING *buf))
{
    ASSERT_ARGS(Parrot_io_send)
    if (Parrot_io_socket_is_closed(pmc))
        return -1;

    return PIO_SEND(interp, pmc, buf);
}

/*

=item C<INTVAL Parrot_io_connect>

Connects C<*pmc> to C<*address>.  Returns C<-1> on failure.

=cut

*/

PARROT_EXPORT
INTVAL
Parrot_io_connect(PARROT_INTERP, ARGMOD(PMC *pmc), ARGMOD(PMC *address))
{
    ASSERT_ARGS(Parrot_io_connect)
    if (Parrot_io_socket_is_closed(pmc))
        return -1;

    return PIO_CONNECT(interp, pmc, address);
}

/*

=item C<INTVAL Parrot_io_bind>

Binds C<*pmc>'s socket to the local address and port specified by
C<*address>.  Returns C<-1> on failure.

=cut

*/

PARROT_EXPORT
INTVAL
Parrot_io_bind(PARROT_INTERP, ARGMOD(PMC *pmc), ARGMOD(PMC *address))
{
    ASSERT_ARGS(Parrot_io_bind)
    if (Parrot_io_socket_is_closed(pmc))
        return -1;

    return PIO_BIND(interp, pmc, address);
}

/*

=item C<INTVAL Parrot_io_listen>

Listens for new connections on socket C<*pmc>.  Returns C<-1> on failure.

=cut

*/

PARROT_EXPORT
PARROT_WARN_UNUSED_RESULT
INTVAL
Parrot_io_listen(PARROT_INTERP, ARGMOD(PMC *pmc), INTVAL backlog)
{
    ASSERT_ARGS(Parrot_io_listen)
    if (Parrot_io_socket_is_closed(pmc))
        return -1;

    return PIO_LISTEN(interp, pmc, backlog);
}

/*

=item C<PMC * Parrot_io_accept>

Accepts a new connection and returns a newly created C<ParrotIO> socket.
Returns C<NULL> on failure.

=cut

*/

PARROT_EXPORT
PARROT_WARN_UNUSED_RESULT
PARROT_CAN_RETURN_NULL
PMC *
Parrot_io_accept(PARROT_INTERP, ARGMOD(PMC *pmc))
{
    ASSERT_ARGS(Parrot_io_accept)
    if (Parrot_io_socket_is_closed(pmc))
        return PMCNULL;

    return PIO_ACCEPT(interp, pmc);
}

/*

=item C<PMC * Parrot_io_new_socket_pmc>

Creates a new I/O socket object. The value of C<flags> is set
in the returned PMC.

=cut

*/

PARROT_EXPORT
PARROT_WARN_UNUSED_RESULT
PARROT_CANNOT_RETURN_NULL
PMC *
Parrot_io_new_socket_pmc(PARROT_INTERP, INTVAL flags)
{
    ASSERT_ARGS(Parrot_io_new_socket_pmc)
    PMC * const new_io = pmc_new(interp, enum_class_Socket);

    Parrot_io_set_flags(interp, new_io, flags);

    return new_io;
}
/*

=back

=head1 SEE ALSO

F<io/api.c>

=cut

*/



/*
 * Local variables:
 *   c-file-style: "parrot"
 * End:
 * vim: expandtab shiftwidth=4:
 */
