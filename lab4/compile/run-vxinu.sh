#!/bin/sh
#
# script to help students running XINU kernels with VirtualBox
#
# Daniel Trinkle
# Purdue University
# 11 March 2014

PATH=${PATH}:/homes/vxinu/bin
export PATH

# Run XINU VM with user-supplied ISO image
#
# o. Put everything in ~/.vxinu
# o. Create VirtualBox VM if necessary
# o. Power down any running instance of VM
# o. Copy user-supplied ISO to configured CD/DVD drive image location
# o. Configure NIC trace file (for tcpdump) to be ./vxinu.pcap
# o. Start VM with a maximum of 30 minutes CPU time
# o. Connect serial console
# o. Power down VM when done

USAGE="Usage: run-vxinu [-p port#] [image-iso]
       run-vxinu --help
       
       -p #    provides port forwarding from the given port # (1024<#<65536)
       
       image-iso defaults to xinu.iso
"
ME=/homes/vxinu/bin/run-vxinu
ME=/homes/trinkle/src/misc/run-vxinu.sh
VM="VXINU"
CPU_T=1800	# 30 minutes
VXINU_ROOT=${HOME}/.vxinu
VBOX_USER_HOME=${VXINU_ROOT}/VirtualBox
ISO=${VBOX_USER_HOME}/${VM}.iso
COM=${VBOX_USER_HOME}/${VM}_com1
LOG=${VBOX_USER_HOME}/${VM}/Logs/VBox.log
export VBOX_USER_HOME	# used by VBox* commands
SSH="ssh -o ConnectTimeout=10 -o PasswordAuthentication=no -o PreferredAuthentications=publickey,hostbased -o StrictHostKeyChecking=yes"

# Run VirtualBox on one of a selection of servers
HERE=${PWD}
SERVER=`perl -e '
  @srvs = ("mc11","mc12","mc13","mc14","mc15","mc16");
  @keys = (361,363,419,444,478,482,490,491,519,520,525,527,532,539,542,550,586,589,639,595,599,632,633,589,642,646,664,669,713,671,688,689,700,669,719,734,736,738,747,754,759,812,829,840,841,861,844,850,852,857,841,868,884,899,324,366,486,523,625,761);
  map $hash += ord($_), split //, $ARGV[0];
  @i = grep { $keys[$_] == $hash } 0..$#keys;
  printf("%s", $srvs[$i[0] % ($#srvs+1)]) if (@i);' $USER`

if [ -z "${SERVER}" ] ; then
  echo "ERROR: You do not appear to be in the VXINU configuration.  Please contact your TA for assistance."
  exit 1
fi

if [ "${SERVER}" != "`uname -n | sed -e 's/\..*//'`" ] ; then
  if ${SSH} -n -q ${SERVER} true ; then
    :
  else
    echo "ERROR: Your ssh configuration is broken.  Please contact your TA for assistance."
    exit 1
  fi
  ${SSH} -q -t ${SERVER} "cd ${HERE} ; ${ME} $@"
  exit 0
fi

cleanupinit() {
  echo ABORTING
  rm -rf ${VXINU_ROOT}
  exit 0
}

cleanupvm() {
  echo "${1}"
  VBoxManage controlvm ${VM} poweroff 2>/dev/null || echo "[already off]"
  # check for boot failure (user will get no other feedback)
  if grep "Guest Log: BIOS: Boot from CD-ROM failed" ${LOG} >/dev/null ; then
    echo ""
    echo " * ERROR: XINU image failed to boot *"
    echo ""
  fi
  exit 0
}

verifyport() {
  # Make sure it is a number in the range [1025, 65535]
  if expr "${1}" ':' '^[0-9][0-9]*$' >/dev/null && expr ${1} '>' 1024 >/dev/null && expr ${1} '<' 65536 >/dev/null ; then
    # Make sure it is not already in use
    netstat -na | awk 'BEGIN {p = '${1}'} /^udp / {split($4, c, ":"); if (c[2] == '${1}') {p = -2}} END { print p}'
  else
    echo -1
  fi
}

case "${1}" in
-h|--help)
  echo "${USAGE}"
  exit 0
  ;;
-p)
  PORT=`verifyport "${2}"`
  case "${PORT}" in
  -1)
    echo "ERROR: invalid port number: ${2}"
    exit 1
    ;;
  -2)
    echo "ERROR: port is in use: ${2}"
    exit 1
    ;;
  esac
  shift; shift
  ;;
esac

ulimit -t ${CPU_T}

# check for VM configuration
if VBoxManage showvminfo ${VM} >/dev/null 2>&1 ; then
  :
else
  echo "Creating initial VirtualBox setup in ${VXINU_ROOT}"
  echo ""

  trap 'cleanupinit' 1 2 3 4 13 14 15
  # create empty ISO (xinu image)
  mkdir -p ${VBOX_USER_HOME}
  if mkdir ${VBOX_USER_HOME}/empty ; then
    :
  else
    echo "ERROR: failed to create empty directory for initial ISO image, aborting"
    exit 1
  fi
  if mkisofs -quiet -J -l -r -o ${ISO} ${VBOX_USER_HOME}/empty ; then
    :
  else
    echo "ERROR: failed to create initial ISO image, aborting"
    exit 1
  fi
  rmdir ${VBOX_USER_HOME}/empty
  # create VM
  VBoxManage createvm \
 	--name ${VM} \
	--ostype Other \
	--register \
	--basefolder ${VBOX_USER_HOME}
  VBoxManage modifyvm ${VM} \
	--chipset piix3 \
	--firmware bios \
	--memory 32 \
	--audio none \
	--usb off \
	--boot1 dvd \
	--boot2 none \
	--boot3 none \
	--boot4 none \
	--pae off
  VBoxManage storagectl ${VM} \
	--name "IDE Controller" \
	--add ide \
	--controller PIIX4 \
	--hostiocache on \
	--bootable on
  VBoxManage storageattach ${VM} \
	--storagectl "IDE Controller" \
	--port 0 \
	--device 0 \
	--type dvddrive \
	--medium ${ISO} \
	--mtype readonly
  VBoxManage modifyvm ${VM} \
	--nic1 nat \
	--nictype1 82545EM \
	--cableconnected1 on \
	--nictrace1 on \
	--nictracefile1 ${VBOX_USER_HOME}/${VM}.pcap \
	--macaddress1 auto
  VBoxManage modifyvm ${VM} \
	--uart1 0x3F8 4 \
	--uartmode1 server ${COM}
  trap 1 2 3 4 13 14 15
  echo ""
fi

# Make sure it is not still running
if VBoxManage list runningvms | grep '^"'"${VM}"'"' ; then
  echo Stopping running VM first...
  VBoxManage controlvm ${VM} poweroff
fi

# Remove any existing port forwarding
if VBoxManage showvminfo ${VM} | grep " name = portforwarding, protocol = udp," >/dev/null 2>&1 ; then
  VBoxManage modifyvm ${VM} --natpf1 delete portforwarding
fi
# Add port forwarding if port is specified
if [ -n "${PORT}" ] ; then
  VBoxManage modifyvm ${VM} --natpf1 "portforwarding,udp,,${PORT},,80"
fi

IMG=${1-xinu.iso}
# copy ISO to CD/DVD image path and modify NIC trace file location
if [ ! -f ${IMG} ] ; then
  echo "ERROR: ${IMG} does not exist, aborting"
  exit 1
fi
if file ${IMG} | grep "DOS" >/dev/null ; then
  :
else
  echo "ERROR: ${IMG} does not appear to be a valid image, aborting"
  exit 1
fi
cp ${IMG} ${ISO}

VBoxManage modifyvm ${VM} \
	--nictracefile1 ${HERE}/vxinu.pcap

echo "Starting XINU VM with ${IMG}"
echo "  (network trace file in ${HERE}/vxinu.pcap)"
echo ""

trap 'cleanupvm "ABORTING"' 1 3 4 13 14 15
trap 'cleanupvm "Powering off XINU VM"' 2

VBoxHeadless --startvm ${VM} --vrde off &
sleep 1
echo "Connecting to console"
socket-connect ${COM}

cleanupvm "Powering off XINU VM"
