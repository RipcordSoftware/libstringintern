GTEST_VER=1.7.0

build: force_true .googletest
	cd src/libstringintern && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build
	cd src/testlibstringintern && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true .googletest
	cd src/libstringintern && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all
	cd src/testlibstringintern && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

test: force_true .googletest
	cd src/libstringintern && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) test

clean: force_true
	cd src/libstringintern && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	cd src/testlibstringintern && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean

.googletest: force_true
	if [ "${CI}" = "true" ]; then \
		curl ftp://ftp.ripcordsoftware.com/pub/gtest-${GTEST_VER}-travis-ci-externals-installed.tar.xz -O && \
		tar xfJ gtest-*; \
	elif [ ! -d externals/gtest-${GTEST_VER}/lib/.libs ]; then \
		mkdir -p externals && \
		cd externals && \
		if [ ! -f gtest-${GTEST_VER}.zip ]; then curl https://googletest.googlecode.com/files/gtest-${GTEST_VER}.zip -O; fi && \
		unzip gtest-${GTEST_VER}.zip && \
		cd gtest-${GTEST_VER} && \
		./configure && \
		$(MAKE) -j 2 && \
		if [ ! -d "../installed/include" ]; then mkdir -p ../installed/include; fi && \
		if [ ! -d "../installed/lib" ]; then mkdir -p ../installed/lib; fi && \
		cp -Rf include/* ../installed/include && \
		cp -Rf lib/.libs/* ../installed/lib; \
	fi

force_true:
	true
