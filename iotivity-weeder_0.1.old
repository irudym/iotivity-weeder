SUMMARY = "Iotivity Weeder"
DESCRIPTION = "Simple Iotivity server which collect data from moist and temperature sensors."
HOMEPAGE ="http://fennec.tech"
OSTRO_USER_NAME = "weed"
OSTRO_APP_NAME = "weeder"
LICENSE = "Apache-2.0"
SECTION = "apps"
DEPENDS = "iotivity mraa"

LIC_FILES_CHKSUM = "file://COPYING;beginline=1;endline=18;md5=12c4d45738df4e074960f6f9bfd8ee79"

SRC_URI = "file://iotivity-weeder.tar.gz \
	   file://manifest"

S = "${WORKDIR}/iotivity-weeder"

# inherit ostro-app

FILES_${PN} = "/opt/iotivity/apps"
FILES_${PN} =+ "/opt/iotivity/apps/manifest"

PACKAGES = "${PN}"

IOTIVITY_BIN_DIR = "/opt/iotivity"
IOTIVITY_BIN_DIR_D = "${D}${IOTIVITY_BIN_DIR}"

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"


do_install() {
    install -d ${IOTIVITY_BIN_DIR_D}/apps/iotivity-weeder
    install -c -m 555 ${S}/weeder ${IOTIVITY_BIN_DIR_D}/apps/iotivity-weeder
}

FILES_${PN} = "${IOTIVITY_BIN_DIR}/apps/iotivity-weeder/weeder"
FILES_${PN}-dbg = "${IOTIVITY_BIN_DIR}/apps/iotivity-weeder/.debug"
RDEPENDS_${PN} += "iotivity-resource"
BBCLASSEXTEND = "native nativesdk"
