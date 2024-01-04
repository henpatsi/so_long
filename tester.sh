#!/bin/bash

SO_LONG=./so_long

VALID_MAP_DIR=./maps/valid/
INVALID_MAP_DIR=./maps/invalid/

# can be leaks or valgrind
LEAKS_TOOL="leaks"

# Output storage
LEAKS_LOG=tmp/leaks.log
TRASH_LOG=tmp/trash.log
rm -f $LEAKS_LOG
rm -f $TRASH_LOG

# Colors
NC='\033[0m'
GREEN='\033[0;32m'
LGREEN='\033[1;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
LCYAN='\033[1;36m'
YELLOW='\033[0;33m'

HEADER_COLOR=${LCYAN}
SUBHEADER_COLOR=${CYAN}

printf ${HEADER_COLOR}"\n\n----- INVALID MAPS -----\n\n"${NC}

for file in $INVALID_MAP_DIR*; do
	echo $( basename $file )
	$SO_LONG $file
	EXIT_CODE=$( echo $? )
	if [ ${EXIT_CODE} -eq 1 ]
	then
		echo -e ${GREEN}"Invalid map: [OK]"${NC}
	else
		echo -e ${RED}"Invalid map: [KO]"${NC}
	fi
done

echo "file_that_does_not_exist.ber"
$SO_LONG file_that_does_not_exist
EXIT_CODE=$( echo $? )
if [ ${EXIT_CODE} -eq 1 ]
then
	echo -e ${GREEN}"Invalid map: [OK]"${NC}
else
	echo -e ${RED}"Invalid map: [KO]"${NC}
fi

printf ${HEADER_COLOR}"\n\n----- VALID MAPS -----\n\n"${NC}

for file in $VALID_MAP_DIR*; do
	echo $( basename $file )
	$SO_LONG $file
	EXIT_CODE=$( echo $? )
	if [ ${EXIT_CODE} -eq 0 ]
	then
		echo -e ${GREEN}"Valid map: [OK]"${NC}
	else
		echo -e ${RED}"Valid map: [KO]"${NC}
	fi
done

printf ${HEADER_COLOR}"\n\n ----- \n\n"${NC}