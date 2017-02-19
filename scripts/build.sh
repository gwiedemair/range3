#!/bin/bash

moduleList="TetGen RangeBase RangeAuth RangeModel RangeSolverLib RangeLicense RangeSolver Range"
buildDir="${HOME}/Work/build-range3/build"
qmakeCmd=$(which qmake-qt5)
selfDebug=false

clean=false
debug=false

myName=$(basename $0 .sh)
myPath=$(dirname  $(readlink -f ${BASH_SOURCE[0]}))
myUser=$(id -nu)
myNode=$(hostname -s)
timeStamp=$(date +%H%M%S)

. ${myPath}/lib.sh

moduleDir=$(dirname $myPath)

MAKE="make"
if [ -f /proc/cpuinfo ]
then
    np=$(cat /proc/cpuinfo | grep processor | wc -l)
    np=$[np-1]
    if [ $np -gt $[1] ]
    then
        MAKE=$MAKE" -j$np"
    fi
fi

function print_help
{
    echo "Usage: $myName"
    echo "Usage: $myName.sh [OPTION]..."
    echo ""
    echo " mandatory"
    echo ""
    echo " optional"
    echo ""
    echo "  --clean                  Clean old build"
    echo "  --debug                  Build debug version"
    echo "  --build-dir=[DIRECTORY]  Custom build directory"
    echo "  --help, -h, -?           Print this help and exit"
}

while [ $# -gt 0 ]
do
    case $1 in
        --build-dir=*)
            buildDir=$( echo $1 | awk 'BEGIN{ FS="=" } { print $2 }' )
            ;;
        --clean)
            clean=true
            ;;
        --debug)
            debug=true
            ;;
        --help | -h | -?)
            print_help; exit 0;;
        *)
            echo_e "Unknown parameter '$1'"
            exit 1
            ;;
    esac
    shift
done

logDir="${buildDir}/log"

if [ ! -x $qmakeCmd ]
then
    echo_e "File is not executable '${qmakeCmd}'"
    exit 1
fi

touch_dir $buildDir
if [ $? -ne 0 ]
then
    echo_e "Failed to touch build directory '${buildDir}'"
    exit 1
fi

touch_dir $logDir
if [ $? -ne 0 ]
then
    echo_e "Failed to touch log directory '${logDir}'"
    exit 1
fi

_BUILD_LOG_FNAME="${logDir}/${myName}-${timeStamp}.log"
if [ $selfDebug = true ]
then
    _DEBUG_LOG_FNAME="${logDir}/op-${myName}-${timeStamp}.log"
fi

if [ $clean = true ]
then
    echo_i "Removing build directory '${buildDir}'"
    rm -rf $buildDir
    if [ $? -ne 0 ]
    then
        echo_e "Failed to remove build directory '${buildDir}'"
        exit 1
    fi
fi

qmakeArgs="-recursive"
if [ $debug = true ]
then
    qmakeArgs+=" CONFIG+=debug"
fi

for module in $moduleList
do
    moduleProjectDir="$moduleDir/$module"
    moduleProjectFile="$moduleProjectDir/$module.pro"
    moduleBuildDir="$buildDir/$module"
    if [ $debug = true ]
    then
        moduleBuildDir+="-Debug"
    else
        moduleBuildDir+="-Release"
    fi
    moduleMakefile="$moduleBuildDir/Makefile"

    echo_i "Building $module"
    set_indent
    # QMAKE
    echo_i "Running qmake"
    curDir=$(pwd)
    cd $moduleProjectDir
    $qmakeCmd $moduleProjectFile $qmakeArgs -o $moduleMakefile
    cd $curDir
    # QMAKE
    echo_i "Running make"
    curDir=$(pwd)
    cd $moduleBuildDir
    $MAKE
    if [ $? -ne 0 ]
    then
        echo_e "Failed to build module '$module'"
        exit 1
    fi
    $MAKE install
    if [ $? -ne 0 ]
    then
        echo_e "Failed to install module '$module'"
        exit 1
    fi
    cd $curDir
    set_unindent
done
