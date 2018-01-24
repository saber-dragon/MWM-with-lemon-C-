# Bipartite Matching with lemon C++

This repo uses a simple bipartite graph to demonstrate the usage of lemon C++ to compute the maximum weighted matching in a bipartite graph.

Note that, as the algorithms specially designed and optimized for bipartite graphs are still under development, this repo uses the API designed for general graphs (_i.e.,_ `lemon::MaxWeightedMatching`).


## Installation of lemon C++ 

On MacOS or Linux, you can simply download the [source codes](http://lemon.cs.elte.hu/pub/sources/lemon-1.3.1.tar.gz), then compile and install it as follows.

```bash
cd /path/to/lemon-1.3.1.tar.gz
tar zxf lemon-1.3.1.tar.gz
cd lemon-1.3.1
mkdir build && cd build
cmake ..
make && sudo make install
```

More details on installation can be found at [Lemon C++ Documentation](http://lemon.cs.elte.hu/trac/lemon/wiki/Documentation).


## Usage of This Example

On MacOS or Linux, you can simply compile and run this example as follows. 

```bash
cd /path/to/<this example>
mkdir build && cd build
cmake ..
make
./MWM_with_lemon_C_
```

You should see the following output.

```bash
The maximum weighted matching is:
	L0 -- R1
	L1 -- R2
	L2 -- R0
Its weight is: 13
```