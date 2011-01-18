Requirements
------------

To build Ocarina you will need the following:

**GNU gcc**

At the moment I don't know what the earliest version of gcc supported is, or
which architectures are supported. Ocarina was developed using gcc 4.3.4 under
Cygwin on various x86 machines; that works for me.

**GNU Make**

The build system is just a bunch of hand-rolled vanilla makefiles. I use
GNU Make 3.81 under Cygwin.

**Doxygen**

This is optional. You will only need it if you want to generate some
documentation from the comments in the source files.

Installation
------------

**App**

Just run make in this directory, like this:

    make

That will compile the sources and run a few
tests to make sure everything is sane. Then you will find ocarina.exe in the
src directory.

**Documenation**

To generate the documentation, run the following in this directory:

    make doc

If all goes according to plan you should find some auto-generated documenation
in the doc/doxygen directory.
