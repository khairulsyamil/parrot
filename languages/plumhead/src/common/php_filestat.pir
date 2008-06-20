# Copyright (C) 2008, The Perl Foundation.
# $Id$

=head1 NAME

php_filestat.pir - PHP filestat Standard Library

=head1 DESCRIPTION

=head2 Functions

=over 4

=cut

=item C<bool chgrp(string filename, mixed group)>

Change file group

=cut

.sub 'chgrp'
    not_implemented()
.end

=item C<bool chmod(string filename, int mode)>

Change file mode

=cut

.sub 'chmod'
    not_implemented()
.end

=item C<bool chown(string filename, mixed user)>

Change file owner

=cut

.sub 'chown'
    not_implemented()
.end

=item C<bool chown(string filename, mixed user)>

Change file owner

=cut

.sub 'chown'
    not_implemented()
.end

=item C<void clearstatcache(void)>

Clear file stat cache

=cut

.sub 'clearstatcache'
    not_implemented()
.end

=item C<float disk_free_space(string path)>

Get free disk space for filesystem that path is on

=cut

.sub 'disk_free_space'
    not_implemented()
.end

=item C<float disk_total_space(string path)>

Get total disk space for filesystem that path is on

=cut

.sub 'disk_total_space'
    not_implemented()
.end

=item C<bool file_exists(string filename)>

Returns true if filename exists

=cut

.sub 'file_exists'
    not_implemented()
.end

=item C<int fileatime(string filename)>

Get last access time of file

=cut

.sub 'fileatime'
    not_implemented()
.end

=item C<int filectime(string filename)>

Get inode modification time of file

=cut

.sub 'filectime'
    not_implemented()
.end

=item C<int filegroup(string filename)>

Get file group

=cut

.sub 'filegroup'
    not_implemented()
.end

=item C<int fileinode(string filename)>

Get file inode

=cut

.sub 'fileinode'
    not_implemented()
.end

=item C<int filemtime(string filename)>

Get last modification time of file

=cut

.sub 'filemtime'
    not_implemented()
.end

=item C<int fileowner(string filename)>

Get file owner

=cut

.sub 'fileowner'
    not_implemented()
.end

=item C<int fileperms(string filename)>

Get file permissions

=cut

.sub 'fileperms'
    not_implemented()
.end

=item C<int filesize(string filename)>

Get file size

=cut

.sub 'filesize'
    not_implemented()
.end

=item C<string filetype(string filename)>

Get file type

=cut

.sub 'filetype'
    not_implemented()
.end

=item C<bool is_dir(string filename)>

Returns true if file is directory

=cut

.sub 'is_dir'
    not_implemented()
.end

=item C<bool is_executable(string filename)>

Returns true if file is executable

=cut

.sub 'is_executable'
    not_implemented()
.end

=item C<bool is_file(string filename)>

Returns true if file is a regular file

=cut

.sub 'is_file'
    not_implemented()
.end

=item C<bool is_link(string filename)>

Returns true if file is symbolic link

=cut

.sub 'is_link'
    not_implemented()
.end

=item C<bool is_readable(string filename)>

Returns true if file can be read

=cut

.sub 'is_readable'
    not_implemented()
.end

=item C<bool is_writable(string filename)>

Returns true if file can be written

=cut

.sub 'is_writable'
    not_implemented()
.end

=item C<bool lchgrp(string filename, mixed group)>

Change symlink group

=cut

.sub 'lchgrp'
    not_implemented()
.end

=item C<array lstat(string filename)>

Give information about a file or symbolic link

=cut

.sub 'lstat'
    not_implemented()
.end

=item C<array stat(string filename)>

Give information about a file

=cut

.sub 'stat'
    not_implemented()
.end

=item C<bool touch(string filename [, int time [, int atime]])>

Set modification time of file

=cut

.sub 'touch'
    not_implemented()
.end

=back

=cut

# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4 ft=pir:
