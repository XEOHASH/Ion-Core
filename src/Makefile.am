DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

ION_CONFIG_INCLUDES=-I$(builddir)/config
ION_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

ION_INCLUDES += -I$(srcdir)/secp256k1/include
ION_INCLUDES += -I$(srcdir)/univalue/include

LIBION_SERVER=libion_server.a
LIBION_WALLET=libion_wallet.a
LIBION_COMMON=libion_common.a
LIBION_CLI=libion_cli.a
LIBION_UTIL=libion_util.a
LIBION_CRYPTO=crypto/libion_crypto.a
LIBIONQT=qt/libionqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBUNIVALUE=univalue/libunivalue.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  crypto/libion_crypto.a \
  libion_util.a \
  libion_common.a \
  libion_server.a \
  libion_cli.a
if ENABLE_WALLET
ION_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libion_wallet.a
endif
if ENABLE_ZMQ
EXTRA_LIBRARIES += libion_zmq.a
endif

if BUILD_ION_LIBS
lib_LTLIBRARIES = libionconsensus.la
LIBION_CONSENSUS=libionconsensus.la
else
LIBION_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_IOND
  bin_PROGRAMS += iond
endif

if BUILD_ION_UTILS
  bin_PROGRAMS += ion-cli ion-tx
endif

.PHONY: FORCE check-symbols check-security
# ion core #
ION_CORE_H = \
  activemasternode.h \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h \
  bignum.h \
  chainparams.h \
  chainparamsseeds.h \
  checkpoints.h \
  clientversion.h \
  coincontrol.h \
  compat.h \
  core.h \
  crypter.h \
  darksend.h \
  darksend-relay.h \
  db.h \
  ecwrapper.h \
  hash.h \
  init.h \
  instantx.h \
  kernel.h \
  key.h \
  keystore.h \
  main.h \
  masternodeconfig.h \
  masternode.h \
  masternodeman.h \
  masternode-payments.h \
  masternode-pos.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  pbkdf2.h \
  protocol.h \
  pubkey.h \
  rpc/rpcclient.h \
  rpc/rpcprotocol.h \
  rpc/rpcserver.h \
  script/interpreter.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/script_error.h \
  compressor.h \
  scrypt.h \
  serialize.h \
  smessage.h \
  spork.h \
  stealth.h \
  strlcpy.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  util.h \
  utilstrencodings.h \
  version.h \
  wallet/walletdb.h \
  wallet/wallet.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libion_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between iond and ion-qt
libion_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libion_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libion_server_a_SOURCES = \
  alert.cpp \
  checkpoints.cpp \
  init.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  rpc/rpcblockchain.cpp \
  rpc/rpcmining.cpp \
  rpc/rpcmisc.cpp \
  rpc/rpcnet.cpp \
  rpc/rpcrawtransaction.cpp \
  rpc/rpcserver.cpp \
  timedata.cpp \
  txmempool.cpp \
  script/sigcache.cpp \
  $(ION_CORE_H)

if ENABLE_ZMQ
LIBION_ZMQ=libion_zmq.a

libion_zmq_a_CPPFLAGS = $(ION_INCLUDES) $(ZMQ_CFLAGS)
libion_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libion_zmq_a_SOURCES =
#  zmq/zmqabstractnotifier.cpp \
#  zmq/zmqnotificationinterface.cpp \
#  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between iond and ion-qt, but only linked
# when wallet enabled
libion_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES)
libion_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libion_wallet_a_SOURCES = \
  activemasternode.cpp \
  darksend.cpp \
  darksend-relay.cpp \
  wallet/db.cpp \
  crypter.cpp \
  instantx.cpp \
  masternodeconfig.cpp \
  masternode.cpp \
  masternodeman.cpp \
  masternode-payments.cpp \
  masternode-pos.cpp \
  rpc/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  kernel.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  $(ION_CORE_H)

# crypto primitives library
crypto_libion_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(ION_CONFIG_INCLUDES) $(PIC_FLAGS)
crypto_libion_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
crypto_libion_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# common: shared between iond, and ion-qt and non-server tools
libion_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES)
libion_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libion_common_a_SOURCES = \
  allocators.cpp \
  base58.cpp \
  chainparams.cpp \
  compressor.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  spork.cpp \
  $(ION_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libion_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES)
libion_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libion_util_a_SOURCES = \
  allocators.cpp \
  compat/strnlen.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  rpc/rpcprotocol.cpp \
  sync.cpp \
  util.cpp \
  utilstrencodings.cpp \
  $(ION_CORE_H)
#  clientversion.cpp

#if GLIBC_BACK_COMPAT
#libion_util_a_SOURCES += compat/glibc_compat.cpp
#endif

# cli: shared between ion-cli and ion-qt
libion_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES)
libion_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libion_cli_a_SOURCES = \
  rpc/rpcclient.cpp \
  $(ION_CORE_H)

nodist_libion_util_a_SOURCES = $(srcdir)/obj/build.h
#

# iond binary #
iond_SOURCES = bitcoind.cpp
iond_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES)
iond_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
iond_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
iond_SOURCES += iond-res.rc
endif

iond_LDADD = \
  $(LIBION_SERVER) \
  $(LIBION_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBION_UTIL) \
  $(LIBION_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_ZMQ
iond_LDADD += $(LIBION_ZMQ) $(ZMQ_LIBS)
endif

if ENABLE_WALLET
iond_LDADD += libion_wallet.a
endif

iond_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# ion-cli binary #
ion_cli_SOURCES = ion-cli.cpp
ion_cli_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES) $(EVENT_CFLAGS)
ion_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
ion_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
ion_cli_SOURCES += ion-cli-res.rc
endif

ion_cli_LDADD = \
  $(LIBION_CLI) \
  $(LIBUNIVALUE) \
  $(LIBION_UTIL)
ion_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# ion-tx binary #
ion_tx_SOURCES = ion-tx.cpp
ion_tx_CPPFLAGS = $(AM_CPPFLAGS) $(ION_INCLUDES)
ion_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
ion_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
ion_tx_SOURCES += ion-tx-res.rc
endif

ion_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBION_COMMON) \
  $(LIBION_UTIL) \
  $(LIBION_CRYPTO) \
  $(LIBSECP256K1)

ion_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# ionconsensus library #
if BUILD_ION_LIBS
include_HEADERS = script/ionconsensus.h
libionconsensus_la_SOURCES = \
  script/ionconsensus_dummy.cpp \
  allocators.cpp \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  ecwrapper.cpp \
  hash.cpp \
  pubkey.cpp \
  utilstrencodings.cpp \
  script/script.cpp \
  script/interpreter.cpp \
  script/ionconsensus.cpp

#if GLIBC_BACK_COMPAT
#  libionconsensus_la_SOURCES += compat/glibc_compat.cpp
#endif

libionconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libionconsensus_la_LIBADD = $(LIBSECP256K1)
libionconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_ION_INTERNAL
libionconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a
CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += script/*.gcda script/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

#if ENABLE_TESTS
#include Makefile.test.include
#endif

#if ENABLE_BENCH
#include Makefile.bench.include
#endif

if ENABLE_QT
include Makefile.qt.include
endif

#if ENABLE_QT_TESTS
#include Makefile.qttest.include
#endif
