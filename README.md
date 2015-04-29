# ImageIndexing

A M1 mini-project to create an image indexing algorithm.

This project is esentially based on DGtal, a generic open source library for Digital Geometry programming.

# Install DGtal on your machine

You will need development packages for boost and boost-programs_option. Then, get the code and compile the library:

	git clone https://github.com/DGtal-team/DGtal.git
	cd DGtal && mkdir build && cd build
	cmake .. -DDGTAL_BUILD_TESTING=OFF
	make

# Compile the project

Get the code of the project and compile it using cmake :

	git clone https://github.com/WilliamAufort/ImageIndexing.git
	cd ImageIndexing && mkdir build & cd build
	cmake .. -DDGtal_DIR=folder
	make

where "folder" is your DGtal build folder.

# Execute

In the build folder, you will find the different executables. Run them with the classical way, for example

	./granulometry arguments

To know how the executables work, just run them without arguments.

More details about each of them.

	./deleteNoise

uses a linear filter to delete noise on the image. Particularly efficient against specular noise.

	./genHistograms

generated all the histograms needed to do the shape retrieval.
Be careful ! This executable is too much long (more than a day with parallelization). That's why you can use directly the histograms in the directory: histograms/database

	./indexing

returns a vector of scalar quantities which describes the shape. Here, we just compute the distribution of the granulometric values on the shape.

	./retrieval

just says "Distance computations" for the moment.
