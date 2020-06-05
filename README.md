# JCAT

jcat is a self-contained command line tool for viewing jupyter notebook file in terminal. It parse notebook's underlying json content, hence it runs *without the dependency of jupyter/ipython core*.

## Prerequisites

Most system with `g++` and `make` installed should be fine.


## Build

```
git clone ... --recursive
cd jcat
make
```
and optionally:
```
sudo make install (by default install to /usr/local/bin)
```

## Usage

```
Usage: jcat FILE [OPTION]

FILE:	A json parsable notebook file (*.ipynb).

OPTION:
  -a:	Align prompt (In/Out) for copy.
```
```
./jcat 
```
Example notebook (credit (https://github.com/09rohanchopra/cifar10/blob/master/cifar10-basic.ipynb))

Output:

Aligned Output:

## License

Distributed uder the [Boost Software License](http://www.boost.org/users/license.html). 

## Acknoledgement

jcat parse notebook with [jsoncons](https://github.com/danielaparker/jsoncons), a header only json library.
