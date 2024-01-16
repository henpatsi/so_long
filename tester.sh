#!/bin/bash

ALL_CHECK_ARG=a
INVALID_CHECK_ARG=i
VALID_CHECK_ARG=v
LEAKS_CHECK_ARG=l

SO_LONG=./so_long

VALID_MAP_DIR=./maps/valid/
INVALID_MAP_DIR=./maps/invalid/

# can be leaks or valgrind
LEAKS_TOOL="valgrind"

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

# INVALID
if [ $1 == "$ALL_CHECK_ARG" ] || [ $1 == "$INVALID_CHECK_ARG" ]; then
	printf ${HEADER_COLOR}"\n\n----- INVALID -----\n\n"${NC}

	for file in $INVALID_MAP_DIR*; do
		$SO_LONG $file
		EXIT_CODE=$( echo $? )
		if [ ${EXIT_CODE} -eq 1 ]; then
			echo -e ${GREEN}"$( basename $file ): [OK]"${NC}
		else
			echo -e ${RED}"$( basename $file ): [KO]"${NC}
		fi
		echo ""
	done

	$SO_LONG file_that_does_not_exist
	EXIT_CODE=$( echo $? )
	if [ ${EXIT_CODE} -eq 1 ]; then
		echo -e ${GREEN}"file_that_does_not_exist.ber: [OK]"${NC}
	else
		echo -e ${RED}"file_that_does_not_exist.ber: [KO]"${NC}
	fi
	echo ""

	$SO_LONG
	EXIT_CODE=$( echo $? )
	if [ ${EXIT_CODE} -eq 1 ]; then
		echo -e ${GREEN}"noargs: [OK]"${NC}
	else
		echo -e ${RED}"noargs.ber: [KO]"${NC}
	fi
	echo ""

	$SO_LONG $VALID_MAP_DIR/m1.ber "123"
	EXIT_CODE=$( echo $? )
	if [ ${EXIT_CODE} -eq 1 ]; then
		echo -e ${GREEN}"2 args: [OK]"${NC}
	else
		echo -e ${RED}"2 args.ber: [KO]"${NC}
	fi
	echo ""

	$SO_LONG ""
	EXIT_CODE=$( echo $? )
	if [ ${EXIT_CODE} -eq 1 ]; then
		echo -e ${GREEN}"emptyarg: [OK]"${NC}
	else
		echo -e ${RED}"emptyarg: [KO]"${NC}
	fi
	echo ""
fi

# VALID
if [ $1 == "$ALL_CHECK_ARG" ] || [ $1 == "$VALID_CHECK_ARG" ]; then
	printf ${HEADER_COLOR}"\n\n----- VALID -----\n\n"${NC}

	for file in $VALID_MAP_DIR*; do
		echo $( basename $file )
		$SO_LONG $file
		EXIT_CODE=$( echo $? )
		if [ ${EXIT_CODE} -eq 0 ]; then
			echo -e ${GREEN}"Valid map: [OK]"${NC}
		else
			echo -e ${RED}"Valid map: [KO]"${NC}
		fi
	done
fi

# LEAKS
if [ $1 == "$ALL_CHECK_ARG" ] || [ $1 == "$LEAKS_CHECK_ARG" ]; then
	printf ${HEADER_COLOR}"\n\n----- LEAKS -----\n\n"${NC}

	if [ $LEAKS_TOOL == "leaks" ]; then
		echo "testing leaks with leaks"
		EXPECTED_LINES=4
		for file in $INVALID_MAP_DIR*; do
			leaks --atExit -q -- $SO_LONG $file 1>$LEAKS_LOG 2>$TRASH_LOG
			LINES=$(sed -n '$=' $LEAKS_LOG)
			if [ $LINES -eq $EXPECTED_LINES ]; then
				echo -e ${GREEN}"$( basename $file ): [OK]"${NC}
			else
				echo -e ${RED}"$( basename $file ): [KO]"${NC}
			fi
		done
		leaks --atExit -q -- $SO_LONG $VALID_MAP_DIR/m1.ber 1>$LEAKS_LOG 2>$TRASH_LOG
		LINES=$(sed -n '$=' ${LEAKS_LOG})
		if [ $LINES -eq $EXPECTED_LINES ]; then
			echo -e ${GREEN}"valid map: [OK]"${NC}
		else
			echo -e ${RED}"valid map: [KO]"${NC}
		fi
	else
		echo "testing leaks with valgrind"
		echo "(only invalid maps, valid maps result in weird behaviour)"
		rm -f $LEAKS_LOG
		for file in $INVALID_MAP_DIR*; do
			echo $file >> $LEAKS_LOG
			valgrind $SO_LONG $file 2>>$LEAKS_LOG
		done
		grep "at exit" $LEAKS_LOG
	fi

fi

printf ${HEADER_COLOR}"\n\n ----- \n\n"${NC}