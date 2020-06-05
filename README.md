# JCAT

jcat is a self-contained command line tool for viewing jupyter notebook file in terminal. It parses notebook's underlying json content, hence it runs *without the dependency of jupyter/ipython core*.

## Prerequisites

Most system with `g++` and `make` installed should be fine.

## Build and Install

Clone this repo, then
```
cd jcat
make
sudo make install
```
Optionally, one could use `./jcat` without runing `sudo make install`, by default jcat is installed into `/usr/local/bin`.

## Usage

```
Usage: jcat FILE [OPTION]

FILE:	A json parsable notebook file (*.ipynb).

OPTION:
  -a:	Align prompt (In/Out) for copy.
```

Example notebook (credit (https://github.com/09rohanchopra/cifar10/blob/master/cifar10-basic.ipynb)):

<details>
    <summary>Output</summary>

```
                =========================================================================
   `markdown`   # CIFAR - 10 
                ## Decode data
                =========================================================================
   `markdown`   Activate virtual environment
                =========================================================================
        In [1]: %%bash
                source ~/kerai/bin/activate
                =========================================================================
   `markdown`   ### Imports
                =========================================================================
        In [2]: %matplotlib inline
                from helper import get_class_names, get_train_data, get_test_data, plot_images
                -------------------------------------------------------------------------
    `stderr`    Using TensorFlow backend.

                =========================================================================
   `markdown`   Get class names
                =========================================================================
        In [3]: class_names = get_class_names()
                class_names
                -------------------------------------------------------------------------
    `stdout`    Decoding file: data/batches.meta

        Out[3]: ['airplane',
                 'automobile',
                 'bird',
                 'cat',
                 'deer',
                 'dog',
                 'frog',
                 'horse',
                 'ship',
                 'truck']
=========================================================================
```

<details>
    <summary>Aligned output:</summary>

```
=========================================================================
# `markdown`
# CIFAR - 10 
## Decode data
=========================================================================
# `markdown`
Activate virtual environment
=========================================================================
# In [1]: 
%%bash
source ~/kerai/bin/activate
=========================================================================
# `markdown`
### Imports
=========================================================================
# In [2]: 
%matplotlib inline
from helper import get_class_names, get_train_data, get_test_data, plot_images
-------------------------------------------------------------------------
# `stderr`
Using TensorFlow backend.

=========================================================================
# `markdown`
Get class names
=========================================================================
# In [3]: 
class_names = get_class_names()
class_names
-------------------------------------------------------------------------
# `stdout`
Decoding file: data/batches.meta

# Out[3]: 
['airplane',
 'automobile',
 'bird',
 'cat',
 'deer',
 'dog',
 'frog',
 'horse',
 'ship',
 'truck']
=========================================================================
```

## Uninstall

`rm /usr/local/bin/jcat`

## License

Distributed uder the [Boost Software License](http://www.boost.org/users/license.html). 

## Acknoledgement

jcat parse notebook with [jsoncons](https://github.com/danielaparker/jsoncons), a header only json library.
